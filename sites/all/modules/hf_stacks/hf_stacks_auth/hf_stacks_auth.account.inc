<?php

function isSerialized($str) {
  return ($str == serialize(false) || @unserialize($str) !== false);
}

function hf_stacks_account_page($page) {
  global $user;

  $vars = array();
  $vars['stacks_auth'] = variable_get('stacks_auth','');

  //watchdog('stacks_auth','stacks_auth',$vars);

  switch ($vars['stacks_auth']) {
    // Authentication for Polaris
    case "polaris":
      $auth = new PolarisAuthentication();

      if (!empty($_SESSION['barcode'])) {
        $user_bar = $_SESSION['barcode'];
      } else {
        $user_bar = '';
      }
      if (!empty($_SESSION['pass'])) {
        $user_pin = $_SESSION['pass'];
      } else {
        $user_pin = '';
      }

      // Determine which template to use for displaying patron data
      if ($page == 'items') {
        $response = $auth->patronItems($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        return theme('stacks-account-polaris-items', array('vars' => $vars));
      } elseif ($page == 'items_renew') {
        $response = $auth->patronItemsRenew($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        return theme('stacks-account-polaris-items-renew', array('vars' => $vars));
      } elseif ($page == 'items_info') {
        $response = $auth->bibGet($user_bar, $user_pin);
        drupal_json_output($response);
        return null;
      } elseif ($page == 'bib_info') {
        $response = $auth->bibInfo($user_bar, $user_pin);
        drupal_json_output($response);
        return null;
      } elseif ($page == 'holds') {
        $response = $auth->patronHolds($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        return theme('stacks-account-polaris-holds', array('vars' => $vars));
      } elseif ($page == 'holds_cancel') {
        $response = $auth->patronHoldsCancel($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        return theme('stacks-account-polaris-holds-cancel', array('vars' => $vars));
      } elseif ($page == 'holds_create') {
        $user = $auth->patronBasicData($user_bar, $user_pin);
        $patron_id = $user['patron_id'];
        $url = "http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
        $bib_id = substr($url, strrpos($url, '/') + 1);
        $response = $auth->patronHoldsCreate($user_bar, $user_pin, $patron_id, $bib_id);
        drupal_set_message(t("Hold Placed!"), 'status');
        return null;
      } elseif ($page == 'bib_search') {
        $response = $auth->bibSearch($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        drupal_json_output($vars['bibid']);
        return null;
      } elseif ($page == 'read') {
        $response = $auth->patronRead($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        return theme('stacks-account-polaris-read', array('vars' => $vars));
      } else {
        $response = $auth->patronBasicData($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        return theme('stacks-account-polaris', array('vars' => $vars));
      }
      break;

    // Authentication for Sirsi
    case "sirsi":
      $auth = new SirsiAuthentication();

      if (!empty($_SESSION['barcode'])) {
        $user_bar = $_SESSION['barcode'];
      } else {
        $user_bar = '';
      }
      if (!empty($_SESSION['pass'])) {
        $user_pin = $_SESSION['pass'];
      } else {
        $user_pin = '';
      }

      // Determine which template to use for displaying patron data
      if ($page == 'items') {
        $response = $auth->patronItems($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        return theme('stacks-account-sirsi-items', array('vars' => $vars));
      } elseif ($page == 'items_renew') {
        $response = $auth->patronItemsRenew($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        return theme('stacks-account-sirsi-items-renew', array('vars' => $vars));
      } elseif ($page == 'items_info') {
        $response = $auth->bibGet($user_bar, $user_pin);
        drupal_json_output($response);
        return null;
      } elseif ($page == 'bib_info') {
        $response = $auth->bibInfo($user_bar, $user_pin);
        drupal_json_output($response);
        return null;
      } elseif ($page == 'holds') {
        $response = $auth->patronHolds($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        return theme('stacks-account-sirsi-holds', array('vars' => $vars));
      } elseif ($page == 'holds_cancel') {
        $response = $auth->patronHoldsCancel($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        return theme('stacks-account-sirsi-holds-cancel', array('vars' => $vars));
      } elseif ($page == 'holds_create') {
        $user = $auth->patronBasicData($user_bar, $user_pin);
        $patron_id = $user['patron_id'];
        $url = "http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
        $bib_id = substr($url, strrpos($url, '/') + 1);
        $response = $auth->patronHoldsCreate($user_bar, $user_pin, $patron_id, $bib_id);
        drupal_set_message(t("Hold Placed!"), 'status');
        return null;
      } elseif ($page == 'bib_search') {
        $response = $auth->bibSearch($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        drupal_json_output($vars['bibid']);
        return null;
      } elseif ($page == 'read') {
        $response = $auth->patronRead($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        return theme('stacks-account-sirsi-read', array('vars' => $vars));
      } else {
        $response = $auth->patronBasicData($user_bar, $user_pin);
        // Mapping some data to make it available in the template
        $vars = $response;
        return theme('stacks-account-sirsi', array('vars' => $vars));
      }
      break;

    // Authentication for SIP 2
    case "sip2":
      // Create Sip2 object.
      $mysip = new SIP2Authentication();

      // Populate the object with form settings.
      $mysip->hostname = variable_get('stacks_auth_sip2_host');
      $mysip->port = variable_get('stacks_auth_sip2_port');
      $mysip->sip_login = variable_get('stacks_auth_sip2_username');
      $mysip->sip_password = variable_get('stacks_auth_sip2_password');

      // Connect to SIP server.
      $result = $mysip->sip2Connect();

      // SC Login.
      $login = $mysip->sip2MsgLogin($mysip->sip_login, $mysip->sip_password);
      $result = $mysip->sip2ParseLoginResponse($mysip->sip2GetMessage($login));

      // Send selfcheck status message.
      $in = $mysip->sip2MsgScStatus();
      $result = $mysip->sip2ParseAcsStatusResponse($mysip->sip2GetMessage($in));

      // Use result to populate SIP2 setings.
      if (isset($result['variable']['AO'][0])) {
        $mysip->AO = $result['variable']['AO'][0]; /* set AO to value returned */
      }
      else {
        $mysip->AO = "NOTINACSSTATUS";
      }
      if (isset($result['variable']['AN'][0])) {
        $mysip->AN = $result['variable']['AN'][0]; /* set AN to value returned */
      }

      // Patron login.
      $mysip->patron = $_SESSION['barcode'];
      $mysip->patronpwd = $_SESSION['pass'];

      // Load patron status into array.
      $in = $mysip->sip2MsgPatronInformation('none');
      $result = $mysip->sip2ParsePatronInfoResponse($mysip->sip2GetMessage($in));

      return theme('stacks-account-sip2', array('vars' => $result));
      break;

    // Authentication for III
    case 'iii':
      $auth = new IIIAuthentication();
      $response = $auth->getAccountFromUser($user);
      // Mapping some data to make it available in the template
      $vars = $response;

      drupal_set_title('Hello ' . $vars['PATRN NAME[pn]']);

      return theme('stacks-account-iii', array('vars' => $vars));
      break;
  }

  return "Sorry for the inconvenience, but the library has yet to connect their ILS system to Stacks. Once they have, all of your fees, holds, requests and other account information will be available here. Thanks for visiting and we hope you continue to explore the site!";
}
