<?php

class PolarisAuthentication extends StacksAuthentication {

	public function __construct() {
		$this->url = variable_get('stacks_auth_polaris_url', '');
	}

	/**
	 * Authenticates a user in Polaris
	 *
	 * @param string $barcode
	 * @param string $pin
	 * @return false on authentication failure or array on success.
	 */
	public function authenticate($barcode = '', $pin = '') {
		if (empty($this->url)) {
			return false;
		}

		$requestMethod = 'GET';
		$urlAction = '1/patron/' . $barcode;
		$urlAction = trim(trim($urlAction), '/');
		$requestUrl = $this->url . $urlAction;
		$pin = trim($pin);
		$timestamp = $this->createHttpDate();
		$polaris_sig_url = variable_get('stacks_auth_polaris_signature', '');
		$signatureUrl = $polaris_sig_url . $urlAction;
		$authentication = $this->createAuthenticationString($signatureUrl, $timestamp, $pin, $requestMethod);
		$ch = curl_init($requestUrl);


		//error_log($requestUrl);
		curl_setopt_array($ch,
			array(
				CURLOPT_RETURNTRANSFER => true,
				CURLOPT_TIMEOUT=> 10,
				CURLOPT_SSL_VERIFYHOST => FALSE,
				CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
				CURLOPT_HTTPHEADER => array(
					'Content-Type: text/xml',
					'Polarisdate:' . $timestamp,
					'Authorization:' . $authentication,
					'Content-Length: ' . strlen(''),
					'Accept-Encoding: gzip,deflate'
				)
			)
		);

		if($requestMethod === 'PUT') {
			curl_setopt($ch, CURLOPT_CUSTOMREQUEST, $requestMethod);
			curl_setopt($ch, CURLOPT_POSTFIELDS, '');
		}

		if($requestMethod === 'POST') {
			curl_setopt($ch, CURLOPT_POST, 1);
			curl_setopt($ch, CURLOPT_POSTFIELDS, '');
		}

		$output = curl_exec($ch);
		//error_log($output);
		//error_log('Error code:' . curl_error($ch));
		curl_close($ch);

		if($output){
			$xmlDom = new SimpleXMLElement($output);
			$result["validpatron"] = (string)$xmlDom->ValidPatron === 'true';
			$result["patronid"] = (string)$xmlDom->PatronID;
			$result["assignedbranchid"] = (string)$xmlDom->AssignedBranchID;
			$result["assignedbranchname"] = (string)$xmlDom->AssignedBranchName;
			$result["errormessage"] = (string)$xmlDom->ErrorMessage;
		}
		return $result;
	}

	/**
	 * Pulls basic patron data
	 *
	 * @param $barcode
	 * @param $pin
	 * @return array|string
	 */
	function patronBasicData($barcode, $pin) {
		if (!$barcode || !is_numeric($barcode) || !$pin) {
			//error_log('Valid barcode and pin are required for this call');
			return false;
		}
		$urlAction = '1/patron/' . $barcode . '/basicdata';
		$requestUrl = $this->url . $urlAction;
		$pin = trim($pin);
		$timestamp = $this->createHttpDate();
		$polaris_sig_url = variable_get('stacks_auth_polaris_signature', '');
		$signatureUrl = $polaris_sig_url . $urlAction;
		$authentication = $this->createAuthenticationString($signatureUrl, $timestamp, $pin, 'GET');
		$ch = curl_init($requestUrl);
//		$xml = $this->beginAuthenticatedRequest($urlAction, $pin);
		curl_setopt_array($ch,
			array(
				CURLOPT_RETURNTRANSFER => true,
				CURLOPT_TIMEOUT=> 10,
				CURLOPT_SSL_VERIFYHOST => FALSE,
				CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
				CURLOPT_HTTPHEADER => array(
					'Content-Type: text/xml',
					'Polarisdate:' . $timestamp,
					'Authorization:' . $authentication,
					'Content-Length: ' . strlen(''),
					'Accept-Encoding: gzip,deflate'
				)
			)
		);

		$xml = curl_exec($ch);
		if($xml){
			$xmlDom = new SimpleXMLElement($xml);
			$xmlDom = $xmlDom->PatronBasicData;

			$output =  array(
				'current_fees' => (string)$xmlDom->ChargeBalance,
				'name_first' => (string)$xmlDom->NameFirst,
				'name_last' => (string)$xmlDom->NameLast,
				'address' => (string)$xmlDom->PatronAddresses,
				'phone' => (string)$xmlDom->PhoneNumber,
				'email_address' => (string)$xmlDom->EmailAddress,
				'items_out' => (string)$xmlDom->ItemsOutCount,
				'items_overdue' => (string)$xmlDom->ItemsOverdueCount,
				'items_lost' => (string)$xmlDom->ItemsOutLostCount,
				'holds_total' => (string)$xmlDom->HoldRequestsTotalCount,
				'holds_current' => (string)$xmlDom->HoldRequestsCurrentCount,
				'holds_shipped' => (string)$xmlDom->HoldRequestsShippedCount,
				'holds_held' => (string)$xmlDom->HoldRequestsHeldCount,
				'holds_unclaimed' => (string)$xmlDom->HoldRequestsUnclaimedCount,
        'patron_id' => (string)$xmlDom->PatronID,
			);
			return $output;
		}

		return false;
	}

	/**
	 * Pulls patron holds
	 *
	 * @param $barcode
	 * @param $pin
	 * @return array|string
	 */
	function patronHolds($barcode, $pin) {
		if (!$barcode || !is_numeric($barcode) || !$pin) {
			//error_log('Valid barcode and pin are required for this call');
		}
		$urlAction = '1/patron/' . $barcode . '/holdrequests/all';
		$requestUrl = $this->url . $urlAction;
		$pin = trim($pin);
		$timestamp = $this->createHttpDate();
		$polaris_sig_url = variable_get('stacks_auth_polaris_signature', '');
		$signatureUrl = $polaris_sig_url . $urlAction;
		$authentication = $this->createAuthenticationString($signatureUrl, $timestamp, $pin, 'GET');
		$ch = curl_init($requestUrl);
//		$xml = $this->beginAuthenticatedRequest($urlAction, $pin);
		curl_setopt_array($ch,
			array(
				CURLOPT_RETURNTRANSFER => true,
				CURLOPT_TIMEOUT=> 10,
				CURLOPT_SSL_VERIFYHOST => FALSE,
				CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
				CURLOPT_HTTPHEADER => array(
					'Content-Type: text/xml',
					'Polarisdate:' . $timestamp,
					'Authorization:' . $authentication,
					'Content-Length: ' . strlen(''),
					'Accept-Encoding: gzip,deflate'
				)
			)
		);

		$xml = curl_exec($ch);
		if($xml){
			$xmlDom = new SimpleXMLElement($xml);

			$items = $xmlDom->PatronHoldRequestsGetRows->PatronHoldRequestsGetRow;

			$output = array();

			foreach ($items as $item) {
				$itemArray =  array (
					'request_id' => (string)$item->HoldRequestID,
					'bib_id' => (string)$item->BibID,
					'status_id' => (string)$item->StatusID,
					'stadus_desc' => (string)$item->StatusDescription,
					'title' => (string)$item->Title,
					'author' => (string)$item->Author,
				);

				$output[] = $itemArray;
			}
			return $output;
		}

		return false;
	}

	/**
	 * Cancels a hold
	 *
	 * @param $barcode
	 * @param $pin
	 * @return array|string
	 */
	function patronHoldsCancel($barcode, $pin) {
		$request = arg(3);
		if (!$barcode || !is_numeric($barcode) || !$pin) {
			//error_log('Valid barcode and pin are required for this call');
		}
		$urlAction = '1/patron/' . $barcode . '/holdrequests/' . $request . '/cancelled?wsid=1&userid=1';
		$requestUrl = $this->url . $urlAction;
		$pin = trim($pin);
		$timestamp = $this->createHttpDate();
		$polaris_sig_url = variable_get('stacks_auth_polaris_signature', '');
		$signatureUrl = $polaris_sig_url . $urlAction;
		$authentication = $this->createAuthenticationString($signatureUrl, $timestamp, $pin, 'PUT');
		$ch = curl_init($requestUrl);

		curl_setopt_array($ch,
			array(
				CURLOPT_CUSTOMREQUEST => 'PUT',
				CURLOPT_POSTFIELDS => '',
				CURLOPT_RETURNTRANSFER => true,
				CURLOPT_TIMEOUT=> 10,
				CURLOPT_SSL_VERIFYHOST => FALSE,
				CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
				CURLOPT_HTTPHEADER => array(
					'Content-Type: text/xml',
					'Polarisdate:' . $timestamp,
					'Authorization:' . $authentication,
					'Content-Length: ' . strlen(''),
					'Accept-Encoding: gzip,deflate'
				)
			)
		);

		$xml = curl_exec($ch);
		if($xml){
			$output = array();
			$xmlDom = new SimpleXMLElement($xml);

			$output['success'] = $xmlDom->PAPIErrorCode == '0';
			$output['notice'] = (string)$xmlDom->ErrorMessage;

			return $output;
		}

		return false;
	}


	/**
	 * Holds an item
	 *
	 * @param $barcode
	 * @param $pin
	 * @param $patron_id
	 * @param $bib_id
	 * @return array|string
	 */
	function patronHoldsCreate($barcode, $pin, $patron_id, $bib_id) {
		//$item = arg(3);
		$patronID = $patron_id;
		$bibID = $bib_id;
		$pickUpOrgID = '0';

		date_default_timezone_set ('GMT');
		$time = strtotime('-1 day');
		$dateActive = date('Y-m-d\TH:i:s', $time) . "\n";

		if (!$barcode || !is_numeric($barcode) || !$pin) {
			//error_log('Valid barcode and pin are required for this call');
		}
		$urlAction = '1/holdrequest';

		$requestUrl = $this->url . $urlAction;
		$pin = trim($pin);
		$timestamp = $this->createHttpDate();
		$polaris_sig_url = variable_get('stacks_auth_polaris_signature', '');
		$signatureUrl = $polaris_sig_url . $urlAction;
		$authentication = $this->createAuthenticationString($signatureUrl, $timestamp, $pin, 'PUT');
		$ch = curl_init($requestUrl);

		$requestBody = "<HoldRequestCreateData><PatronID>$patronID</PatronID><BibID>$bibID</BibID><ItemBarcode/><VolumeNumber/><Designation/><PickupOrgID>$pickUpOrgID</PickupOrgID><PatronNotes/><ActivationDate>$dateActive</ActivationDate><Answer/><RequestID/><WorkstationID>1</WorkstationID><UserID>1</UserID><RequestingOrgID>1</RequestingOrgID><TargetGUID/></HoldRequestCreateData>";

		curl_setopt_array($ch,
			array(
				CURLOPT_CUSTOMREQUEST => 'POST',
				CURLOPT_POSTFIELDS => $requestBody,
				CURLOPT_RETURNTRANSFER => true,
				CURLOPT_TIMEOUT=> 10,
				CURLOPT_SSL_VERIFYHOST => FALSE,
				CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
				CURLOPT_HTTPHEADER => array(
					'Content-Type: text/xml',
					'Polarisdate:' . $timestamp,
					'Authorization:' . $authentication,
					'Content-Length: ' . strlen($requestBody),
					'Accept-Encoding: gzip,deflate'
				)
			)
		);

		$xml = curl_exec($ch);
		print $xml;
		if($xml){
			//$xmlDom = new SimpleXMLElement($xml);
			//print_r($xmlDom);

			$output = array();
			$xmlDom = new SimpleXMLElement($xml);
			// get success flag  0=success, -2=multiple notices
			$output['success'] = $xmlDom->PAPIErrorCode == '0';

			// get notice msg
			$errmsg_rows = $xmlDom->HoldRequestResult;
			$errors = array();
			foreach ($errmsg_rows as $row) {
				if ($row->PAPIErrorType != 0) { //1=patron block, 2=item renewal block
					$errors[(string)$row->ItemRecordID] = (string)$row->ErrorMessage;
				}
			}
			if (empty($errors)) {
				$output['notice'] = ($output['success'])
					? 'Hold successful.'
					: 'Hold not permitted due to an active block on patron account, please contact your library for details.';
			}
			else {
				$output['notice'] = implode("\n", $errors);
			}

			if ($bibID == 0) {  // patron_login_book_renew_all() requires item record id to generate notices with error matching the book title
				$output['errors'] = $errors;
			}

			// get due date
			$output['message'] = (string)$xmlDom->HoldRequestResult->Message;

			return $xmlDom;
		}

		return false;
	}


	/**
	 * Pulls patron items
	 *
	 * @param $barcode
	 * @param $pin
	 * @return array|string
	 */
	function patronItems($barcode, $pin) {
		if (!$barcode || !is_numeric($barcode) || !$pin) {
			//error_log('Valid barcode and pin are required for this call');
		}
		$urlAction = '1/patron/' . $barcode . '/itemsout/all';
		$requestUrl = $this->url . $urlAction;
		$pin = trim($pin);
		$timestamp = $this->createHttpDate();
		$polaris_sig_url = variable_get('stacks_auth_polaris_signature', '');
		$signatureUrl = $polaris_sig_url . $urlAction;
		$authentication = $this->createAuthenticationString($signatureUrl, $timestamp, $pin, 'GET');
		$ch = curl_init($requestUrl);

		curl_setopt_array($ch,
			array(
				CURLOPT_RETURNTRANSFER => true,
				CURLOPT_TIMEOUT=> 10,
				CURLOPT_SSL_VERIFYHOST => FALSE,
				CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
				CURLOPT_HTTPHEADER => array(
					'Content-Type: text/xml',
					'Polarisdate:' . $timestamp,
					'Authorization:' . $authentication,
					'Content-Length: ' . strlen(''),
					'Accept-Encoding: gzip,deflate'
				)
			)
		);

		$xml = curl_exec($ch);
		if($xml){
			$xmlDom = new SimpleXMLElement($xml);

			$items = $xmlDom->PatronItemsOutGetRows->PatronItemsOutGetRow;

			$output = array();

			foreach ($items as $item) {
				$itemArray =  array (
					'item_id' => (string)$item->ItemID,
					'barcode' => (string)$item->Barcode,
					'bib_id' => (string)$item->BibID,
					'format_id' => (string)$item->FormatID,
					'format_description' => (string)$item->FormatDescription,
					'title' => (string)$item->Title,
					'author' => (string)$item->Author,
					'call_number' => (string)$item->CallNumber,
					'checkout_date' => (string)$item->CheckOutDate,
					'isbn' => (string)$item->ISBN,
					'issn' => (string)$item->ISSN,
					'due_date' => (string)$item->DueDate,
					'renewal_count' => (string)$item->RenewalCount,
					'renewal_limit' => (string)$item->RenewalLimit,
					'upc' => (string)$item->UPCNumber,
				);

				$output[] = $itemArray;
			}
			return $output;
		}

		return false;
	}

	/**
	 * Renews an item
	 *
	 * @param $barcode
	 * @param $pin
	 * @return array|string
	 */
	function patronItemsRenew($barcode, $pin) {
		$item = arg(3);
		if (!$barcode || !is_numeric($barcode) || !$pin) {
			//error_log('Valid barcode and pin are required for this call');
		}
		$urlAction = '1/patron/' . $barcode . '/itemsout/' . $item;

		$requestUrl = $this->url . $urlAction;
		$pin = trim($pin);
		$timestamp = $this->createHttpDate();
		$polaris_sig_url = variable_get('stacks_auth_polaris_signature', '');
		$signatureUrl = $polaris_sig_url . $urlAction;
		$authentication = $this->createAuthenticationString($signatureUrl, $timestamp, $pin, 'PUT');
		$ch = curl_init($requestUrl);

		$requestBody = "<ItemsOutActionData><Action>renew</Action><LogonBranchID>1</LogonBranchID><LogonUserID>1</LogonUserID><LogonWorkstationID>1</LogonWorkstationID><RenewData><IgnoreOverrideErrors>true</IgnoreOverrideErrors></RenewData></ItemsOutActionData>";

		curl_setopt_array($ch,
			array(
				CURLOPT_CUSTOMREQUEST => 'PUT',
				CURLOPT_POSTFIELDS => $requestBody,
				CURLOPT_RETURNTRANSFER => true,
				CURLOPT_TIMEOUT=> 10,
				CURLOPT_SSL_VERIFYHOST => FALSE,
				CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
				CURLOPT_HTTPHEADER => array(
					'Content-Type: text/xml',
					'Polarisdate:' . $timestamp,
					'Authorization:' . $authentication,
					'Content-Length: ' . strlen($requestBody),
					'Accept-Encoding: gzip,deflate'
				)
			)
		);

		$xml = curl_exec($ch);
		//print $xml;
		if($xml){
			//$xmlDom = new SimpleXMLElement($xml);
			//print_r($xmlDom);

			$output = array();
			$xmlDom = new SimpleXMLElement($xml);
			// get success flag  0=success, -2=multiple notices
			$output['success'] = $xmlDom->PAPIErrorCode == '0';

			// get notice msg
			$errmsg_rows = $xmlDom->ItemRenewResult->BlockRows->ItemRenewBlockRow;
			$errors = array();
			foreach ($errmsg_rows as $row) {
				if ($row->PAPIErrorType == 2) { //1=patron block, 2=item renewal block
					$errors[(string)$row->ItemRecordID] = (string)$row->ErrorDesc;
				}
			}
			if (empty($errors)) {
				$output['notice'] = ($output['success'])
					? 'Renewal successful.'
					: 'Renewal not permitted due to an active block on patron account, please contact your library for details.';
			}
			else {
				$output['notice'] = implode("\n", $errors);
			}

			if ($item == 0) {  // patron_login_book_renew_all() requires item record id to generate notices with error matching the book title
				$output['errors'] = $errors;
			}

			// get due date
			$output['duedate'] = (string)$xmlDom->ItemRenewResult->DueDateRows->ItemRenewDueDateRow->DueDate;

			return $output;
		}

		return false;
	}

	/**
	 * Pulls patron holds
	 *
	 * @param $barcode
	 * @param $pin
	 * @return array|string
	 */
	function patronRead($barcode, $pin) {
		if (!$barcode || !is_numeric($barcode) || !$pin) {
			//error_log('Valid barcode and pin are required for this call');
		}
		$urlAction = '1/patron/' . $barcode . '/readinghistory' . '?rowsperpage=10&page=0';
		$requestUrl = $this->url . $urlAction;
		$pin = trim($pin);
		$timestamp = $this->createHttpDate();
		$polaris_sig_url = variable_get('stacks_auth_polaris_signature', '');
		$signatureUrl = $polaris_sig_url . $urlAction;
		$authentication = $this->createAuthenticationString($signatureUrl, $timestamp, $pin, 'GET');
		$ch = curl_init($requestUrl);
		curl_setopt_array($ch,
			array(
				CURLOPT_RETURNTRANSFER => true,
				CURLOPT_TIMEOUT=> 10,
				CURLOPT_SSL_VERIFYHOST => FALSE,
				CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
				CURLOPT_HTTPHEADER => array(
					'Content-Type: text/xml',
					'Polarisdate:' . $timestamp,
					'Authorization:' . $authentication,
					'Content-Length: ' . strlen(''),
					'Accept-Encoding: gzip,deflate'
				)
			)
		);

		$xml = curl_exec($ch);
		if($xml){
			$xmlDom = new SimpleXMLElement($xml);

			$items = $xmlDom->PatronReadingHistoryGetRows->PatronReadingHistoryGetRow;

			$output = array();

			foreach ($items as $item) {
				$itemArray =  array (
					'item_id' => (string)$item->ItemID,
					'bib_id' => (string)$item->BibID,
					'status_id' => (string)$item->StatusID,
					'checkout' => (string)$item->CheckOutDate,
					'title' => (string)$item->Title,
					'author' => (string)$item->Author,
					'type' => (string)$item->FormatDescription,
				);

				$output[] = $itemArray;
			}

			return array_reverse($output);
		}

		return false;
	}

  /**
   * BibID Search
   *
   * @param $barcode
   * @param $pin
   * @return array|string
   */
	function bibSearch($barcode, $pin) {
    $isbn = arg(2);

    $urlAction = '1/search/bibs/keyword/isbn?q=' . $isbn . '';
    $requestUrl = $this->url . $urlAction;
    $pin = trim($pin);
    $timestamp = $this->createHttpDate();
    $polaris_sig_url = variable_get('stacks_auth_polaris_signature', '');
    $signatureUrl = $polaris_sig_url . $urlAction;
    $authentication = $this->createAuthenticationString($signatureUrl, $timestamp, $pin, 'GET');
    $ch = curl_init($requestUrl);

    curl_setopt_array($ch,
      array(
        CURLOPT_CUSTOMREQUEST => 'GET',
        CURLOPT_POSTFIELDS => '',
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_TIMEOUT=> 10,
        CURLOPT_SSL_VERIFYHOST => FALSE,
        CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
        CURLOPT_HTTPHEADER => array(
          'Content-Type: text/xml',
          'Polarisdate:' . $timestamp,
          'Authorization:' . $authentication,
          'Content-Length: ' . strlen(''),
					'Accept-Encoding: gzip,deflate'
        )
      )
    );

    $xml = curl_exec($ch);
    if($xml){
      $output = array();
      $xmlDom = new SimpleXMLElement($xml);

      $output['bibid'] = $xmlDom->BibSearchRows->BibSearchRow->ControlNumber;

      return $output;
    }

    return false;
  }

	/**
	 * Bib Info
	 *
	 * @param $barcode
	 * @param $pin
	 * @return array|string
	 */
	function bibGet($barcode, $pin) {
		$bibid = arg(3);

    $urlAction = '1/bib/' . $bibid . '/holdings';
    $requestUrl = $this->url . $urlAction;
    $pin = trim($pin);
    $timestamp = $this->createHttpDate();
    $polaris_sig_url = variable_get('stacks_auth_polaris_signature', '');
    $signatureUrl = $polaris_sig_url . $urlAction;
    $authentication = $this->createAuthenticationString($signatureUrl, $timestamp, $pin, 'GET');
    $ch = curl_init($requestUrl);

    curl_setopt_array($ch,
      array(
        CURLOPT_CUSTOMREQUEST => 'GET',
        CURLOPT_POSTFIELDS => '',
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_TIMEOUT=> 10,
        CURLOPT_SSL_VERIFYHOST => FALSE,
        CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
        CURLOPT_HTTPHEADER => array(
          'Content-Type: text/xml',
          'Polarisdate:' . $timestamp,
          'Authorization:' . $authentication,
          'Content-Length: ' . strlen(''),
          'Accept-Encoding: gzip,deflate'
        )
      )
    );

    $xml = curl_exec($ch);
    if($xml){
      $output = array();
      $xmlDom = new SimpleXMLElement($xml);

      $output = $xmlDom->BibHoldingsGetRows;

      return $output;
    }

		return false;
	}

	/**
	 * Search Keyword
	 *
	 * @param $keyword    string    Search term to query.
	 * @param $pin        int       PIN of the client
	 * @param $tom 	      string		Type of Material.
   * @param $limit      int       The number of search result returned.
	 * @return array|string
	 */
	function searchKeyWord($keyword, $pin, $tom, $limit = 5) {
	  //$tom = "bks+OR+TOM=ebk";
		$urlAction = '1/search/bibs/keyword/kw?q=' . $keyword;
		$urlAction .= '&limit=TOM=' . $tom;
		$urlAction .= '&bibsperpage=' . $limit;
		$requestUrl = $this->url . $urlAction;
		$pin = trim($pin);
		$timestamp = $this->createHttpDate();
		$polaris_sig_url = variable_get('stacks_auth_polaris_signature', '');
		$signatureUrl = $polaris_sig_url . $urlAction;
		$authentication = $this->createAuthenticationString($signatureUrl, $timestamp, $pin, 'GET');
		$ch = curl_init($requestUrl);

		curl_setopt_array($ch,
			array(
				CURLOPT_CUSTOMREQUEST => 'GET',
				CURLOPT_POSTFIELDS => '',
				CURLOPT_RETURNTRANSFER => true,
				CURLOPT_TIMEOUT=> 10,
				CURLOPT_SSL_VERIFYHOST => FALSE,
				CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
				CURLOPT_HTTPHEADER => array(
					'Content-Type: application/json',
					'Polarisdate:' . $timestamp,
					'Authorization:' . $authentication,
					'Content-Length: ' . strlen(''),
					'Accept-Encoding: gzip,deflate'
				)
			)
		);

		$json = curl_exec($ch);
		if($json){
			$output = array();
			$json = json_decode($json);

			$output['records'] = $json->BibSearchRows;
			$output['count'] = $json->TotalRecordsFound;
			return $output;
		}

		return false;
	}

  /**
   * Bib Info
   *
   * @param $barcode
   * @param $pin
   * @return array|string
   */
  function bibInfo($barcode, $pin) {
    $bibid = arg(2);

    if (!$barcode || !is_numeric($barcode) || !$pin) {
      //error_log('Valid barcode and pin are required for this call');
    }

    $urlAction = '1/bib/' . $bibid;
    $requestUrl = $this->url . $urlAction;
    $pin = trim($pin);
    $timestamp = $this->createHttpDate();
    $polaris_sig_url = variable_get('stacks_auth_polaris_signature', '');
    $signatureUrl = $polaris_sig_url . $urlAction;
    $authentication = $this->createAuthenticationString($signatureUrl, $timestamp, $pin, 'GET');
    $ch = curl_init($requestUrl);

    curl_setopt_array($ch,
      array(
        CURLOPT_CUSTOMREQUEST => 'GET',
        CURLOPT_POSTFIELDS => '',
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_TIMEOUT=> 10,
        CURLOPT_SSL_VERIFYHOST => FALSE,
        CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
        CURLOPT_HTTPHEADER => array(
          'Content-Type: text/xml',
          'Polarisdate:' . $timestamp,
          'Authorization:' . $authentication,
          'Content-Length: ' . strlen(''),
					'Accept-Encoding: gzip,deflate'
        )
      )
    );

    $xml = curl_exec($ch);

    if($xml){
      $output = array();
      $xmlDom = new SimpleXMLElement($xml);

      $output = $xmlDom->BibGetRows;

      return $output;
    }

    return false;
  }

	private function beginAuthenticatedRequest($urlAction, $pin) {

	}

	private function createHttpDate() {
		//create HTTP Date RC1123 format
		date_default_timezone_set ('GMT');
		return date("D, d M Y H:i:s") . ' GMT';
	}

	private function createServerDate() {
		date_default_timezone_set ('GMT');
		$time = strtotime('-1 day');
		return date('Y-m-d\TH:i:s', $time) . "\n";
	}


	/**
	 * Builds the authentication string to be passed in the request.
	 *
	 * @param $urlAction
	 * @param $timestamp
	 * @param $pin
	 * @param $requestMethod
	 * @return string
	 */
	private function createAuthenticationString($urlAction, $timestamp , $pin, $requestMethod) {
		$signature = sprintf("%s%s%s%s", $requestMethod, $urlAction, $timestamp, $pin);
		$papim_private_key = variable_get('stacks_auth_polaris_private_key', '');
		if (function_exists('hash_hmac')) {
			$sigHash = hash_hmac('sha1',$signature, $papim_private_key, true);
		}
		else {
			$sigHash = $this->custom_hash_hmac('sha1',$signature, $papim_private_key, true);
		}

		$papim_access_id = variable_get('stacks_auth_polaris_access_id', '');
		return 'PWS ' . $papim_access_id . ':' . base64_encode($sigHash);
	}


	/**
	 * Creates a custom hash
	 *
	 * @param $algo
	 * @param $data
	 * @param $key
	 * @param bool $raw_output
	 * @return string
	 */
	private function custom_hash_hmac($algo, $data, $key, $raw_output = false) {
		$algo = strtolower($algo);
		$pack = 'H'.strlen($algo('test'));
		$size = 64;
		$opad = str_repeat(chr(0x5C), $size);
		$ipad = str_repeat(chr(0x36), $size);

		if (strlen($key) > $size) {
			$key = str_pad(pack($pack, $algo($key)), $size, chr(0x00));
		} else {
			$key = str_pad($key, $size, chr(0x00));
		}

		for ($i = 0; $i < strlen($key) - 1; $i++) {
			$opad[$i] = $opad[$i] ^ $key[$i];
			$ipad[$i] = $ipad[$i] ^ $key[$i];
		}

		$output = $algo($opad.pack($pack, $algo($ipad.$data)));

		return ($raw_output) ? pack($pack, $output) : $output;
	}
}