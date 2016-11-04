<?php

class SIP2Authentication extends StacksAuthentication {

    public function __construct() {
        $this->url = variable_get('stacks_auth_sip2', '');
        $this->hostname = variable_get('stacks_auth_sip2_host', '');
        $this->port = variable_get('stacks_auth_sip2_port', '');
    }

    /* Public variables for configuration */
    public $hostname = '12.160.114.140';
    public $port     = '5000';
    public $library    = '';
    public $language   = '001'; /* 001= english */

    /* Patron ID */
    //public $patron     = variable_get('stacks_auth_sip2_username'); /* AA */
    //public $patronpwd  = variable_get('stacks_auth_sip2_password'); /* AD */

    /* terminal password */
    public $AC       = ''; /* AC */

    /* Maximum number of resends allowed before sip2GetMessage gives up */
    public $maxretry   = 3;

    /* Terminator s */
    public $fldTerminator = '|';
    public $msgTerminator = "\r\n";

    /* Login Variables */
    public $uidAlgorithm = 0;   /* 0  = unencrypted, default */
    public $pwdAlgorithm = 0;   /* undefined in documentation */
    public $scLocation   = '';  /* Location Code */

    /* Debug */
    public $debug    = FALSE;

    /* Private variables for building messages */
    public $ao = 'WohlersSIP';
    public $an = 'SIPCHK';

    /* Private variable to hold socket connection */
    protected $socket;

    /* Sequence number counter */
    protected $seq   = -1;

    /* resend counter */
    protected $retry = 0;

    /* Workarea for building a message */
    protected $msgBuild = '';
    protected $noFixed = FALSE;

    /**
     * Authenticates against SIP2 IP.
     *
     *
     * @param string $barcode
     * @param string $pin
     * @return false on failure or array on success.
     */
    public function authenticate($barcode = '', $pin = '') {
        /* Login (93) - untested */
        $this->sip2NewMessage('23');
        $this->sip2AddVarOption('AA', $barcode);
        $this->sip2AddVarOption('AD', $pin);
        return $this->sip2ReturnMessage();
    }


    /**
     * Implements "Patron Status Request" Command Message.
     */
    public function sip2MsgPatronStatusRequest() {
        /* Server Response: Patron Status Response message. */
        $this->sip2NewMessage('23');
        $this->sip2AddFixedOption($this->language, 3);
        $this->sip2AddFixedOption($this->sip2Datestamp(), 18);
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AA', $this->patron);
        $this->sip2AddVarOption('AC', $this->AC);
        $this->sip2AddVarOption('AD', $this->patronpwd);
        return $this->sip2ReturnMessage();
    }

    /**
     * Implements "Checkout" Command Message.
     */
    public function sip2MsgCheckout($item, $nb_date_due = '', $sc_renewal = 'N', $itm_prop = '', $fee = 'N', $no_block = 'N', $cancel = 'N') {
        /* Checkout an item  (11) - untested */
        $this->sip2NewMessage('11');
        $this->sip2AddFixedOption($sc_renewal, 1);
        $this->sip2AddFixedOption($no_block, 1);
        $this->sip2AddFixedOption($this->sip2Datestamp(), 18);
        if ($nb_date_due != '') {
            /* override defualt date due */
            $this->sip2AddFixedOption($this->sip2Datestamp($nb_date_due), 18);
        }
        else {
            /* send a blank date due to allow ACS to use default date due computed for item */
            $this->sip2AddFixedOption('', 18);
        }
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AA', $this->patron);
        $this->sip2AddVarOption('AB', $item);
        $this->sip2AddVarOption('AC', $this->AC);
        $this->sip2AddVarOption('CH', $itm_prop, TRUE);
        $this->sip2AddVarOption('AD', $this->patronpwd, TRUE);
        $this->sip2AddVarOption('BO', $fee, TRUE); /* Y or N */
        $this->sip2AddVarOption('BI', $cancel, TRUE); /* Y or N */

        return $this->sip2ReturnMessage();
    }

    /**
     * Implements "Checkin" Command Message.
     */
    public function sip2MsgCheckin($item, $itm_return_date, $itm_location = '', $itm_prop = '', $no_block = 'N', $cancel = '') {
        /* Checkin an item (09) - untested */
        if ($itm_location == '') {
            /* If no location is specified, assume the defualt location of the SC, behavior suggested by spec*/
            $itm_location = $this->scLocation;
        }

        $this->sip2NewMessage('09');
        $this->sip2AddFixedOption($no_block, 1);
        $this->sip2AddFixedOption($this->sip2Datestamp(), 18);
        $this->sip2AddFixedOption($this->sip2Datestamp($itm_return_date), 18);
        $this->sip2AddVarOption('AP', $itm_location);
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AB', $item);
        $this->sip2AddVarOption('AC', $this->AC);
        $this->sip2AddVarOption('CH', $itm_prop, TRUE);
        $this->sip2AddVarOption('BI', $cancel, TRUE); /* Y or N */

        return $this->sip2ReturnMessage();
    }

    /**
     * Implements "Block Patron" Command Message.
     */
    public function sip2MsgBlockPatron($message, $retained = 'N') {
        /* Blocks a patron, and responds with a patron status response  (01) - untested */
        $this->sip2NewMessage('01');
        $this->sip2AddFixedOption($retained, 1); /* Y if card has been retained */
        $this->sip2AddFixedOption($this->sip2Datestamp(), 18);
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AL', $message);
        $this->sip2AddVarOption('AA', $this->AA);
        $this->sip2AddVarOption('AC', $this->AC);

        return $this->sip2ReturnMessage();
    }

    /**
     * Implements "SC Status" Command Message.
     */
    public function sip2MsgScStatus($status = 0, $width = 80, $version = 2) {
        /* selfcheck status message, this should be sent immediatly after login  - untested */
        /* status codes, from the spec:
          * 0 SC unit is OK
          * 1 SC printer is out of paper
          * 2 SC is about to shut down
          */

        if ($version > 3) {
            $version = 2;
        }
        if ($status < 0 || $status > 2) {
            $this->sip2DebugMsg("SIP2: Invalid status passed to sip2MsgScStatus");
            return FALSE;
        }
        $this->sip2NewMessage('99');
        $this->sip2AddFixedOption($status, 1);
        $this->sip2AddFixedOption($width, 3);
        $this->sip2AddFixedOption(sprintf("%03.2f", $version), 4);
        return $this->sip2ReturnMessage();
    }

    /**
     * Implements "Request ACS Resend" Command Message.
     */
    public function sip2MsgRequestAcsResend() {
        /* Used to request a resend due to CRC mismatch - No sequence number is used */
        $this->sip2NewMessage('97');
        return $this->sip2ReturnMessage(FALSE);
    }

    /**
     * Implements "Login" Command Message.
     */
    public function sip2MsgLogin($sip_login, $sip_password) {
        /* Login (93) - untested */
        $this->sip2NewMessage('93');
        $this->sip2AddFixedOption($this->uidAlgorithm, 1);
        $this->sip2AddFixedOption($this->pwdAlgorithm, 1);
        $this->sip2AddVarOption('CN', $sip_login);
        $this->sip2AddVarOption('CO', $sip_password);
        $this->sip2AddVarOption('CP', $this->scLocation, TRUE);
        return $this->sip2ReturnMessage();
    }

    /**
     * Implements "Patron Information" Command Message.
     */
    public function sip2MsgPatronInformation($type, $start = '1', $end = '5') {
        /*
        * According to the specification:
        * Only one category of items should be  requested at a time, i.e. it would
        * take 6 of these messages, each with a different position set to Y, to get
        * all the detailed information about a patron's items.
        */
        $summary['none']   = '    ';
        $summary['hold']   = 'Y   ';
        $summary['overdue']  = ' Y  ';
        $summary['charged']  = '  Y   ';
        $summary['fine']   = '   Y  ';
        $summary['recall']   = '  Y ';
        $summary['unavail']  = '   Y';

        /* Request patron information */
        $this->sip2NewMessage('63');
        $this->sip2AddFixedOption($this->language, 3);
        $this->sip2AddFixedOption($this->sip2Datestamp(), 18);
        $this->sip2AddFixedOption(sprintf("%-10s", $summary[$type]), 10);
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AA', $this->patron);
        $this->sip2AddVarOption('AC', $this->AC, TRUE);
        $this->sip2AddVarOption('AD', $this->patronpwd, TRUE);
        $this->sip2AddVarOption('BP', $start, TRUE); /* old public function version used padded 5 digits, not sure why */
        $this->sip2AddVarOption('BQ', $end, TRUE); /* old public function version used padded 5 digits, not sure why */

        return $this->sip2ReturnMessage();
    }

    /**
     * Implements "End Patron Session" Command Message.
     */
    public function sip2MsgEndPatronSession() {
        /*  End Patron Session, should be sent before switching to a new patron. (35) - untested */

        $this->sip2NewMessage('35');
        $this->sip2AddFixedOption($this->sip2Datestamp(), 18);
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AA', $this->patron);
        $this->sip2AddVarOption('AC', $this->AC, TRUE);
        $this->sip2AddVarOption('AD', $this->patronpwd, TRUE);
        return $this->sip2ReturnMessage();
    }

    /**
     * Implements "Fee Paid" Command Message.
     */
    public function sip2MsgFeePaid($fee_type, $pmt_type, $pmt_amount, $cur_type = 'USD', $fee_id = '', $trans_id = '') {
        /* Fee payment public function (37) - untested */
        /* Fee Types: */
        /* 01 other/unknown */
        /* 02 administrative */
        /* 03 damage */
        /* 04 overdue */
        /* 05 processing */
        /* 06 rental*/
        /* 07 replacement */
        /* 08 computer access charge */
        /* 09 hold fee */

        /* Value Payment Type */
        /* 00   cash */
        /* 01   VISA */
        /* 02   credit card */

        if (!is_numeric($fee_type) || $fee_type > 99 || $fee_type < 1) {
            /* not a valid fee type - exit */
            $this->sip2DebugMsg("SIP2: (sip2MsgFeePaid) Invalid fee type: {$fee_type}");
            return FALSE;
        }

        if (!is_numeric($pmt_type) || $pmt_type > 99 || $pmt_type < 0) {
            /* not a valid payment type - exit */
            $this->sip2DebugMsg("SIP2: (sip2MsgFeePaid) Invalid payment type: {$pmt_type}");
            return FALSE;
        }

        $this->sip2NewMessage('37');
        $this->sip2AddFixedOption($this->sip2Datestamp(), 18);
        $this->sip2AddFixedOption(sprintf('%02d', $fee_type), 2);
        $this->sip2AddFixedOption(sprintf('%02d', $pmt_type), 2);
        $this->sip2AddFixedOption($cur_type, 3);
        $this->sip2AddVarOption('BV', $pmt_amount); /* due to currancy format localization, it is up to the programmer to properly format their payment amount */
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AA', $this->patron);
        $this->sip2AddVarOption('AC', $this->AC, TRUE);
        $this->sip2AddVarOption('AD', $this->patronpwd, TRUE);
        $this->sip2AddVarOption('CG', $fee_id, TRUE);
        $this->sip2AddVarOption('BK', $trans_id, TRUE);

        return $this->sip2ReturnMessage();
    }

    /**
     * Implements "Item Information" Command Message.
     */
    public function sip2MsgItemInformation($item) {
        $this->sip2NewMessage('17');
        $this->sip2AddFixedOption($this->sip2Datestamp(), 18);
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AB', $item);
        $this->sip2AddVarOption('AC', $this->AC, TRUE);
        return $this->sip2ReturnMessage();

    }

    /**
     * Implements "Item Status Update" Command Message.
     */
    public function sip2msgItemStatus($item, $itm_prop = '') {
        /* Item status update public function (19) - untested  */

        $this->sip2NewMessage('19');
        $this->sip2AddFixedOption($this->sip2Datestamp(), 18);
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AB', $item);
        $this->sip2AddVarOption('AC', $this->AC, TRUE);
        $this->sip2AddVarOption('CH', $itm_prop);
        return $this->sip2ReturnMessage();
    }

    /**
     * Implements "Patron Enable" Command Message.
     */
    public function sip2MsgPatronEnable() {
        /* Patron Enable public function (25) - untested */
        /*  This message can be used by the SC to re-enable canceled patrons. It should only be used for system testing and validation. */
        $this->sip2NewMessage('25');
        $this->sip2AddFixedOption($this->sip2Datestamp(), 18);
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AA', $this->patron);
        $this->sip2AddVarOption('AC', $this->AC, TRUE);
        $this->sip2AddVarOption('AD', $this->patronpwd, TRUE);
        return $this->sip2ReturnMessage();

    }

    /**
     * Implements "Hold" Command Message.
     */
    public function sip2MsgHold($mode, $exp_date = '', $holdtype = '', $item = '', $title = '', $fee = 'N', $pkup_location = '') {
        /* mode validity check */
        /*
        * - remove hold
        * + place hold
        * * modify hold
        */
        if (strpos('-+*', $mode) === FALSE) {
            /* not a valid mode - exit */
            $this->sip2DebugMsg("SIP2: Invalid hold mode: {$mode}");
            return FALSE;
        }

        if ($holdtype != '' && ($holdtype < 1 || $holdtype > 9)) {
            /*
             * Valid hold types range from 1 - 9
             * 1   other
             * 2   any copy of title
             * 3   specific copy
             * 4   any copy at a single branch or location
             */
            $this->sip2DebugMsg("SIP2: Invalid hold type code: {$holdtype}");
            return FALSE;
        }

        $this->sip2NewMessage('15');
        $this->sip2AddFixedOption($mode, 1);
        $this->sip2AddFixedOption($this->sip2Datestamp(), 18);
        if ($exp_date != '') {
            /* hold expiration date,  due to the use of the datestamp function, we have to check here for empty value. when datestamp is passed an empty value it will generate a current datestamp */
            $this->sip2AddVarOption('BW', $this->sip2Datestamp($exp_date), TRUE); /* spec says this is fixed field, but it behaves like a var field and is optional... */
        }
        $this->sip2AddVarOption('BS', $pkup_location, TRUE);
        $this->sip2AddVarOption('BY', $holdtype, TRUE);
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AA', $this->patron);
        $this->sip2AddVarOption('AD', $this->patronpwd, TRUE);
        $this->sip2AddVarOption('AB', $item, TRUE);
        $this->sip2AddVarOption('AJ', $title, TRUE);
        $this->sip2AddVarOption('AC', $this->AC, TRUE);
        $this->sip2AddVarOption('BO', $fee, TRUE); /* Y when user has agreed to a fee notice */

        return $this->sip2ReturnMessage();

    }

    /**
     * Implements "Renew" Command Message.
     */
    public function sip2MsgRenew($item = '', $title = '', $nb_date_due = '', $itm_prop = '', $fee = 'N', $no_block = 'N', $third_party = 'N') {
        /* renew a single item (29) - untested */
        $this->sip2NewMessage('29');
        $this->sip2AddFixedOption($third_party, 1);
        $this->sip2AddFixedOption($no_block, 1);
        $this->sip2AddFixedOption($this->sip2Datestamp(), 18);
        if ($nb_date_due != '') {
            /* override default date due */
            $this->sip2AddFixedOption($this->sip2Datestamp($nb_date_due), 18);
        }
        else {
            /* send a blank date due to allow ACS to use default date due computed for item */
            $this->sip2AddFixedOption('', 18);
        }
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AA', $this->patron);
        $this->sip2AddVarOption('AD', $this->patronpwd, TRUE);
        $this->sip2AddVarOption('AB', $item, TRUE);
        $this->sip2AddVarOption('AJ', $title, TRUE);
        $this->sip2AddVarOption('AC', $this->AC, TRUE);
        $this->sip2AddVarOption('CH', $itm_prop, TRUE);
        $this->sip2AddVarOption('BO', $fee, TRUE); /* Y or N */

        return $this->sip2ReturnMessage();
    }

    /**
     * Implements "Renew All" Command Message.
     */
    public function sip2MsgRenewAll($fee = 'N') {
        /* renew all items for a patron (65) - untested */
        $this->sip2NewMessage('65');
        $this->sip2AddVarOption('AO', $this->AO);
        $this->sip2AddVarOption('AA', $this->patron);
        $this->sip2AddVarOption('AD', $this->patronpwd, TRUE);
        $this->sip2AddVarOption('AC', $this->AC, TRUE);
        $this->sip2AddVarOption('BO', $fee, TRUE); /* Y or N */

        return $this->sip2ReturnMessage();
    }

    /**
     * Parses "Patron Status Response" Message from the ACS.
     */
    public function sip2ParsePatronStatusResponse($response) {
        $result['fixed'] = array(
            'PatronStatus'    => drupal_substr($response, 2, 14),
            'Language'      => drupal_substr($response, 16, 3),
            'TransactionDate'   => drupal_substr($response, 19, 18),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 37);
        return $result;
    }

    /**
     * Parses "Checkout Response" Message from the ACS.
     */
    public function sip2ParseCheckoutResponse($response) {
        $result['fixed'] = array(
            'Ok'        => drupal_substr($response, 2, 1),
            'RenewalOk'     => drupal_substr($response, 3, 1),
            'Magnetic'      => drupal_substr($response, 4, 1),
            'Desensitize'     => drupal_substr($response, 5, 1),
            'TransactionDate'   => drupal_substr($response, 6, 18),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 24);
        return $result;

    }

    /**
     * Parses "Checkin Response" Message from the ACS.
     */
    public function sip2ParseCheckinResponse($response) {
        $result['fixed'] = array(
            'Ok'        => drupal_substr($response, 2, 1),
            'Resensitize'     => drupal_substr($response, 3, 1),
            'Magnetic'      => drupal_substr($response, 4, 1),
            'Alert'       => drupal_substr($response, 5, 1),
            'TransactionDate'   => drupal_substr($response, 6, 18),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 24);
        return $result;

    }

    /**
     * Parses "ACS Status" Message from the ACS.
     */
    public function sip2ParseAcsStatusResponse($response) {
        $result['fixed'] = array(
            'Online'      => drupal_substr($response, 2, 1),
            // Is Checkin by the SC allowed?
            'Checkin'       => drupal_substr($response, 3, 1),
            // Is Checkout by the SC allowed?
            'Checkout'      => drupal_substr($response, 4, 1),
            // Is renewal allowed?
            'Renewal'       => drupal_substr($response, 5, 1),
            // Is patron status updating by the SC allowed?
            'PatronUpdate'    => drupal_substr($response, 6, 1),
            'Offline'       => drupal_substr($response, 7, 1),
            'Timeout'       => drupal_substr($response, 8, 3),
            'Retries'       => drupal_substr($response, 11, 3),
            'TransactionDate'   => drupal_substr($response, 14, 18),
            'Protocol'      => drupal_substr($response, 32, 4),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 36);
        return $result;
    }

    /**
     * Parses "Login Response" Message from the ACS.
     */
    public function sip2ParseLoginResponse($response) {
        $result['fixed'] = array(
            'Ok'        => drupal_substr($response, 2, 1),
        );
        $result['variable'] = array();
        return $result;
    }

    /**
     * Parses "Patron Information Response" Message from the ACS.
     */
    public function sip2ParsePatronInfoResponse($response) {
        $result['fixed'] = array(
            'PatronStatus'    => drupal_substr($response, 2, 14),
            'Language'      => drupal_substr($response, 16, 3),
            'TransactionDate'   => drupal_substr($response, 19, 18),
            'HoldCount'     => intval(drupal_substr($response, 37, 4)),
            'OverdueCount'    => intval(drupal_substr($response, 41, 4)),
            'ChargedCount'    => intval(drupal_substr($response, 45, 4)),
            'FineCount'     => intval(drupal_substr($response, 49, 4)),
            'RecallCount'     => intval(drupal_substr($response, 53, 4)),
            'UnavailableCount'  => intval(drupal_substr($response, 57, 4)),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 61);
        return $result;
    }

    /**
     * Parses "End Session Response" Message from the ACS.
     */
    public function sip2ParseEndSessionResponse($response) {
        /*   Response example:  36Y20080228 145537AOWOHLERS|AAX00000000|AY9AZF474   */

        $result['fixed'] = array(
            'EndSession'    => drupal_substr($response, 2, 1),
            'TransactionDate'   => drupal_substr($response, 3, 18),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 21);

        return $result;
    }

    /**
     * Parses "Fee Paid Response" Message from the ACS.
     */
    public function sip2ParseFeePaidResponse($response) {
        $result['fixed'] = array(
            'PaymentAccepted'   => drupal_substr($response, 2, 1),
            'TransactionDate'   => drupal_substr($response, 3, 18),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 21);
        return $result;

    }

    /**
     * Parses "Item Information Response" Message from the ACS.
     */
    public function sip2ParseItemInfoResponse($response) {
        $result['fixed'] = array(
            'CirculationStatus' => intval(drupal_substr($response, 2, 2)),
            'SecurityMarker'  => intval(drupal_substr($response, 4, 2)),
            'FeeType'       => intval(drupal_substr($response, 6, 2)),
            'TransactionDate'   => drupal_substr($response, 8, 18),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 26);

        return $result;
    }

    /**
     * Parses "Item Status Update Response" Message from the ACS.
     */
    public function sip2ParseItemStatusResponse($response) {
        $result['fixed'] = array(
            'PropertiesOk'    => drupal_substr($response, 2, 1),
            'TransactionDate'   => drupal_substr($response, 3, 18),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 21);
        return $result;

    }

    /**
     * Parses "Patron Enable Response" Message from the ACS.
     */
    public function sip2ParsePatronEnableResponse($response) {
        $result['fixed'] = array(
            'PatronStatus'    => drupal_substr($response, 2, 14),
            'Language'      => drupal_substr($response, 16, 3),
            'TransactionDate'   => drupal_substr($response, 19, 18),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 37);
        return $result;

    }

    /**
     * Parses "Hold Response" Message from the ACS.
     */
    public function sip2ParseHoldResponse($response) {

        $result['fixed'] = array(
            'Ok'        => drupal_substr($response, 2, 1),
            'available'     => drupal_substr($response, 3, 1),
            'TransactionDate'   => drupal_substr($response, 4, 18),
            'ExpirationDate'  => drupal_substr($response, 22, 18),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 40);

        return $result;
    }

    /**
     * Parses "Renew Response" Message from the ACS.
     */
    public function sip2ParseRenewResponse($response) {
        /* Response Example:  300NUU20080228  222232AOWOHLERS|AAX00000241|ABM02400028262|AJFolksongs of Britain and Ireland|AH5/23/2008,23:59|CH|AFOverride required to exceed renewal limit.|AY1AZCDA5 */
        $result['fixed'] = array(
            'Ok'        => drupal_substr($response, 2, 1),
            'RenewalOk'     => drupal_substr($response, 3, 1),
            'Magnetic'      => drupal_substr($response, 4, 1),
            'Desensitize'     => drupal_substr($response, 5, 1),
            'TransactionDate'   => drupal_substr($response, 6, 18),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 24);

        return $result;
    }

    /**
     * Parses "Renew All Response" Message from the ACS.
     */
    public function sip2ParseRenewAllResponse($response) {
        $result['fixed'] = array(
            'Ok'        => drupal_substr($response, 2, 1),
            'Renewed'       => drupal_substr($response, 3, 4),
            'Unrenewed'     => drupal_substr($response, 7, 4),
            'TransactionDate'   => drupal_substr($response, 11, 18),
        );

        $result['variable'] = $this->sip2ParseVariableData($response, 29);

        return $result;
    }

    /**
     * Sends the current message, and gets the response.
     */
    public function sip2GetMessage($message) {
        $result   = '';
        $terminator = '';
        $nr     = '';

        $this->sip2DebugMsg('SIP2: Sending SIP2 request...');
        socket_write($this->socket, $message, drupal_strlen($message));

        $this->sip2DebugMsg('SIP2: Request Sent, Reading response');

        while ($terminator != "\x0D" && $nr !== FALSE) {
            $nr = socket_recv($this->socket, $terminator, 1, 0);
            $result = $result . $terminator;
        }

        $this->sip2DebugMsg("SIP2: {$result}");

        /* test message for CRC validity */
        if ($this->sip2CheckCrc($result)) {
            /* reset the retry counter on successful send */
            $this->retry = 0;
            $this->sip2DebugMsg("SIP2: Message from ACS passed CRC check");
        }
        else {
            /* CRC check failed, request a resend */
            $this->retry++;
            if ($this->retry < $this->maxretry) {
                /* try again */
                $this->sip2DebugMsg("SIP2: Message failed CRC check, retrying ({$this->retry})");

                $this->sip2GetMessage($message);
            }
            else {
                /* give up */
                $this->sip2DebugMsg("SIP2: Failed to get valid CRC after {$this->maxretry} retries.");
                return FALSE;
            }
        }
        return $result;
    }

    /**
     * Socket Communications.
     */
    public function sip2Connect() {
        $this->sip2DebugMsg("SIP2: --- BEGIN SIP communication ---");

        /* Get the IP address for the target host. */
        $address = gethostbyname($this->hostname);

        /* Create a TCP/IP socket. */
        $this->socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);

        /* check for actual truly false result using ===*/
        if ($this->socket === FALSE) {
            $this->sip2DebugMsg("SIP2: socket_create() failed: reason: " . socket_strerror($this->socket));
            return FALSE;
        }
        else {
            $this->sip2DebugMsg("SIP2: Socket Created");
        }
        $this->sip2DebugMsg("SIP2: Attempting to connect to '$address' on port '{$this->port}'...");

        /* open a connection to the host */
        $result = socket_connect($this->socket, $address, $this->port);
        if (!$result) {
            $this->sip2DebugMsg("SIP2: socket_connect() failed.\nReason: ($result) " . socket_strerror($result));
        }
        else {
            $this->sip2DebugMsg("SIP2: --- SOCKET READY ---");
        }
        /* return the result from the socket connect */
        return $result;
    }

    /**
     * Close the socket.
     */
    public function sip2Disconnect() {
        socket_close($this->socket);
    }

    /* Core local utility functions. */

    /**
     * Generate a SIP2 compatable datestamp.
     *
     * From the spec: YYYYMMDDZZZZHHMMSS.
     * All dates and times are expressed according to the ANSI standard X3.30
     * for date and X3.43 for time.
     * The ZZZZ field should contain blanks (code $20) to represent local time.
     * To represent universal time, a Z character (code $5A)
     * should be put in the last (right hand) position of the ZZZZ field.
     * To represent other time zones the appropriate character should be used;
     * a Q character (code $51) should be put in the last (right hand) position
     * of the ZZZZ field to represent Atlantic Standard Time.
     * When possible local time is the preferred format.
     */
    protected function sip2Datestamp($timestamp = '') {
        if ($timestamp != '') {
            /* Generate a proper date time from the date provided */
            return date('Ymd  His', $timestamp);
        }
        else {
            /* Current Date/Time */
            return date('Ymd  His');
        }
    }

    /**
     * SD occasionally returns odd values; strip these from the parsed array.
     *
     * Unable to locate the purpose in spec.
     * Orig values will remain in ['raw'] element.
     */
    public function sip2ParseVariableData($response, $start) {
        $result = array();
        $result['Raw'] = explode("|", drupal_substr($response, $start, -7));
        foreach ($result['Raw'] as $item) {
            $field = drupal_substr($item, 0, 2);
            $value = drupal_substr($item, 2);
            $clean = trim($value, "\x00..\x1F");
            if (trim($clean) <> '') {
                $result[$field][] = $clean;
            }
        }
        $result['AZ'][] = drupal_substr($response, -5);

        return ($result);
    }

    /**
     * Calculate CRC.
     */
    protected function sip2Crc($buf) {
        $sum = 0;

        $len = drupal_strlen($buf);
        for ($n = 0; $n < $len; $n++) {
            $sum = $sum + ord(drupal_substr($buf, $n, 1));
        }
        $crc = ($sum & 0xFFFF) * -1;

        /* 2008.03.15 - Fixed a bug that allowed the checksum to be larger then 4 digits. */
        return drupal_substr(sprintf("%4X", $crc), -4, 4);
    }

    /**
     * Get a sequence number for the AY field.
     */
    protected function sip2GetSeqNum() {
        // Valid numbers range 0-9.
        $this->seq++;
        if ($this->seq > 9) {
            $this->seq = 0;
        }
        return ($this->seq);
    }

    /**
     * Custom debug function,  why repeat the check for the debug flag in code?.
     */
    protected function sip2DebugMsg($message) {
        if ($this->debug) {
            trigger_error(check_plain($message), E_USER_NOTICE);
        }
    }

    /**
     * Test recieved message's CRC by generating our own CRC from the message.
     */
    protected function sip2CheckCrc($message) {
        $test = preg_split('/(.{4})$/', trim($message), 2, PREG_SPLIT_DELIM_CAPTURE);

        if ($this->sip2Crc($test[0]) == $test[1]) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }

    /**
     * Resets msgBuild to the value of $code and clears the fixed messages flag.
     */
    protected function sip2NewMessage($code) {
        $this->noFixed  = FALSE;
        $this->msgBuild = $code;
    }

    /**
     * Adds a fixed length option to msgBuild if no variable options were added.
     */
    protected function sip2AddFixedOption($value, $len) {
        if ($this->noFixed) {
            return FALSE;
        }
        else {
            $this->msgBuild .= sprintf("%{$len}s", drupal_substr($value, 0, $len));
            return TRUE;
        }
    }

    /**
     * Adds a varaiable length option to the message.
     *
     * Also prevents adding addtional fixed fields.
     */
    protected function sip2AddVarOption($field, $value, $optional = FALSE) {
        if ($optional == TRUE && $value == '') {
            /* skipped */
            $this->sip2DebugMsg("SIP2: Skipping optional field {$field}");
        }
        else {
            $this->noFixed  = TRUE; /* no more fixed for this message */
            $this->msgBuild .= $field . drupal_substr($value, 0, 255) . $this->fldTerminator;
        }
        return TRUE;
    }

    /**
     * Finalizes the message and returns it.
     *
     * Message will remain in msgBuild until newMessage is called.
     */
    protected function sip2ReturnMessage($with_seq = TRUE, $with_crc = TRUE) {
        if ($with_seq) {
            $this->msgBuild .= 'AY' . $this->sip2GetSeqNum();
        }
        if ($with_crc) {
            $this->msgBuild .= 'AZ';
            $this->msgBuild .= $this->sip2Crc($this->msgBuild);
        }
        $this->msgBuild .= $this->msgTerminator;

        return $this->msgBuild;
    }
}