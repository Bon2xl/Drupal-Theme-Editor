<?php


class SirsiAuthentication extends StacksAuthentication {

  private $clientID;
  private $catalogueURL;

	public function __construct() {
		$this->url = variable_get('stacks_auth_sirsi_url', '');
    $this->clientID = variable_get('stacks_auth_sirsi_client');
    $this->catalogueURL = variable_get('stacks_search_sirsi_catalogue_url');
	}

	/**
	 * Authenticates a user in sirsi
	 *
	 * @param string $barcode
	 * @param string $pin
	 * @return false on authentication failure or array on success.
	 */
	public function authenticate($barcode = '', $pin = '') {
		if (empty($this->url)) {
			return false;
		}

		$result = array();

		$sirsi_client = variable_get('stacks_auth_sirsi_client', '');
    $pin = trim($pin);
    $barcode = trim($barcode);

		$requestMethod = 'GET';
		$urlAction = '/security/loginUser?';
		//$urlAction = trim(trim($urlAction), '/');

    $urlParams = 'clientID='.$sirsi_client.'&login='.$barcode.'&password='.$pin;

		$requestUrl = $this->url . $urlAction . $urlParams;

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
					'X-Sirs-Clientid:' . $sirsi_client,
					'Content-Length: ' . strlen(''),
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
		error_log($output);
		error_log('Error code:' . curl_error($ch));
		curl_close($ch);

		if($output){
			$xmlDom = new SimpleXMLElement($output);

      //watchdog('error',(string)$xmlDom->userID);
      //watchdog('error',(string)$xmlDom->sessionToken);

      //$result["patronid"] = (string)$xmlDom->LoginUserResponse->userID;
      //$result["token"] = (string)$xmlDom->LoginUserResponse->sessionToken;

			$result["patronid"] = (string)$xmlDom->userID;
			$result["token"] = (string)$xmlDom->sessionToken;
		}

		return $result;
	}

  function searchKeyword($query, $formatType = null) {
    $urlAction = '?clientID=' . $this->clientID;
    $urlAction .= '&term1=' . $query;
    $urlAction .= '&hitsToDisplay=' . 5;
    if(isset($formatType)) {
      $urlAction .= '&formatFilter=' . $formatType;
    }
    $requestUrl = $this->catalogueURL . $urlAction;

    $ch = curl_init($requestUrl);

    curl_setopt_array($ch,
      array(
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_TIMEOUT=> 10,
        CURLOPT_SSL_VERIFYHOST => FALSE,
        CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
        CURLOPT_HTTPHEADER => array(
          'Content-Type: application/json',
//          'X-Sirs-Clientid:' . $sirsi_client,
//          'x-sirs-sessionToken:' . $token
        )
      )
    );

    $xml_string = curl_exec($ch);

    $xml = simplexml_load_string($xml_string);
    $json = json_encode($xml);
    return json_decode($json, true);
  }

	/**
	 * Pulls basic patron data
	 *
	 *
	 * @param $barcode
	 * @param $pin
	 * @return array|string
	 */
	function patronBasicData($barcode, $pin) {
    if (empty($this->url)) {
      return false;
    }

    if (!$barcode || !is_numeric($barcode) || !$pin) {
      //error_log('Valid barcode and pin are required for this call');
      return false;
    }

    $sirsi_client = variable_get('stacks_auth_sirsi_client', '');
    $pin = trim($pin);
    $barcode = trim($barcode);
    $token = $_SESSION['sirsi_token'];
    $user = $_SESSION['sirsi_user'];

    $requestMethod = 'GET';
    $urlAction = '/patron/lookupMyAccountInfo?';
    //$urlAction = trim(trim($urlAction), '/');

    $urlParams = 'userID='.$user.'&includePatronInfo=true&includePatronCirculationInfo=true&includePatronAddressInfo=true&includePatronStatusInfo=true';

    $requestUrl = $this->url . $urlAction . $urlParams;

    $ch = curl_init($requestUrl);

		curl_setopt_array($ch,
			array(
				CURLOPT_RETURNTRANSFER => true,
				CURLOPT_TIMEOUT=> 10,
				CURLOPT_SSL_VERIFYHOST => FALSE,
				CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
				CURLOPT_HTTPHEADER => array(
					'Content-Type: application/json',
          'X-Sirs-Clientid:' . $sirsi_client,
					'x-sirs-sessionToken:' . $token
				)
			)
		);

		$xml = curl_exec($ch);

		if ($xml) {
      $xmlObject = simplexml_load_string($xml,null,null,'http://schemas.sirsidynix.com/symws/patron',null);

      $sirsiArray = array();

      foreach($xmlObject->patronInfo as $item)
      {
        foreach($item as $key => $value)
        {
          $sirsiArray[(string)$key] = (string)$value;
        }
      }
      foreach($xmlObject->patronCirculationInfo as $item)
      {
        foreach($item as $key => $value)
        {
          $sirsiArray[(string)$key] = (string)$value;
        }
      }
      foreach($xmlObject->patronAddressInfo as $item)
      {
        foreach($item as $key => $value)
        {
          $sirsiArray[(string)$key] = (string)$value;
        }
      }
      foreach($xmlObject->patronStatusInfo as $item)
      {
        foreach($item as $key => $value)
        {
          $sirsiArray[(string)$key] = (string)$value;
        }
      }

			$output =  array(
				'fees' => $sirsiArray['numberOfFees'],
				'name' => $sirsiArray['displayName'],
        'items_out' => $sirsiArray['numberOfFees'],
        'items_overdue' => $sirsiArray['numberOfFees'],
        'items_lost' => $sirsiArray['numberOfFees'],
        'holds_current' => $sirsiArray['numberOfFees'],
        'holds_shipped' => $sirsiArray['numberOfFees'],
        'holds_held' => $sirsiArray['numberOfFees'],
        'holds_unclaimed' => $sirsiArray['numberOfFees'],
        'holds_total' => $sirsiArray['numberOfFees'],
        'address' => $sirsiArray['numberOfFees'],
        'email_address' => $sirsiArray['numberOfFees'],
        'phone' => $sirsiArray['numberOfFees'],
        'patron_id' => $sirsiArray['numberOfFees']
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
    if (empty($this->url)) {
      return false;
    }

    if (!$barcode || !is_numeric($barcode) || !$pin) {
      //error_log('Valid barcode and pin are required for this call');
    }

    $sirsi_client = variable_get('stacks_auth_sirsi_client', '');
    $pin = trim($pin);
    $barcode = trim($barcode);
    $token = $_SESSION['sirsi_token'];
    $user = $_SESSION['sirsi_user'];

    $requestMethod = 'GET';
    $urlAction = '/patron/lookupMyAccountInfo?';
    //$urlAction = trim(trim($urlAction), '/');

    $urlParams = 'userID='.$user.'&includePatronHoldInfo';

    $requestUrl = $this->url . $urlAction . $urlParams;

    $ch = curl_init($requestUrl);

    curl_setopt_array($ch,
      array(
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_TIMEOUT=> 10,
        CURLOPT_SSL_VERIFYHOST => FALSE,
        CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
        CURLOPT_HTTPHEADER => array(
          'Content-Type: application/json',
          'X-Sirs-Clientid:' . $sirsi_client,
          'x-sirs-sessionToken:' . $token
        )
      )
    );

    $xml = curl_exec($ch);

    if ($xml) {
      $xmlObject = simplexml_load_string($xml,null,null,'http://schemas.sirsidynix.com/symws/patron',null);

      $sirsiArray = array();

      foreach($xmlObject->PatronHoldInfo as $item)
      {
        foreach($item as $key => $value)
        {
          $sirsiArray[(string)$key] = (string)$value;
        }
      }

      $output =  array(
        'request_id' => $sirsiArray['itemID'],
        'bib_id' => $sirsiArray['itemID'],
        'status_id' => $sirsiArray['itemID'],
        'stadus_desc' => $sirsiArray['holdStatus'],
        'title' => $sirsiArray['title'],
        'author' => $sirsiArray['author']
      );
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
    /*
    $request = arg(3);
    if (!$barcode || !is_numeric($barcode) || !$pin) {
      error_log('Valid barcode and pin are required for this call');
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
    */
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
    /*
    //$item = arg(3);
    $patronID = $patron_id;
    $bibID = $bib_id;
    $pickUpOrgID = '0';

    date_default_timezone_set ('GMT');
    $time = strtotime('-1 day');
    $dateActive = date('Y-m-d\TH:i:s', $time) . "\n";

    if (!$barcode || !is_numeric($barcode) || !$pin) {
      error_log('Valid barcode and pin are required for this call');
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
    */
  }


  /**
   * Pulls patron items
   *
   * @param $barcode
   * @param $pin
   * @return array|string
   */
  function patronItems($barcode, $pin) {
    if (empty($this->url)) {
      return false;
    }

    if (!$barcode || !is_numeric($barcode) || !$pin) {
      //error_log('Valid barcode and pin are required for this call');
    }

    $sirsi_client = variable_get('stacks_auth_sirsi_client', '');
    $pin = trim($pin);
    $barcode = trim($barcode);
    $token = $_SESSION['sirsi_token'];
    $user = $_SESSION['sirsi_user'];

    $requestMethod = 'GET';
    $urlAction = '/patron/lookupMyAccountInfo?';
    //$urlAction = trim(trim($urlAction), '/');

    $urlParams = 'userID='.$user.'&includePatronCheckoutInfo';

    $requestUrl = $this->url . $urlAction . $urlParams;

    //dpm($requestUrl);

    $ch = curl_init($requestUrl);

    curl_setopt_array($ch,
      array(
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_TIMEOUT=> 10,
        CURLOPT_SSL_VERIFYHOST => FALSE,
        CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
        CURLOPT_HTTPHEADER => array(
          'Content-Type: application/json',
          'X-Sirs-Clientid:' . $sirsi_client,
          'x-sirs-sessionToken:' . $token
        )
      )
    );

    $xml = curl_exec($ch);

    //dpm($xml);

    if ($xml) {
      $xmlObject = simplexml_load_string($xml,null,null,'http://schemas.sirsidynix.com/symws/patron',null);

      $sirsiArray = array();

      foreach($xmlObject->PatronHoldInfo as $item)
      {
        foreach($item as $key => $value)
        {
          $sirsiArray[(string)$key] = (string)$value;
        }
      }

      //dpm($sirsiArray);

      $output =  array(
        'request_id' => $sirsiArray['itemID'],
        'bib_id' => $sirsiArray['itemID'],
        'status_id' => $sirsiArray['itemID'],
        'stadus_desc' => $sirsiArray['holdStatus'],
        'title' => $sirsiArray['title'],
        'author' => $sirsiArray['author']
      );

      /*
      $output =  array(
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
      */

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
    /*
    $item = arg(3);
    if (!$barcode || !is_numeric($barcode) || !$pin) {
      error_log('Valid barcode and pin are required for this call');
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
    */
  }

  /**
   * Pulls patron holds
   *
   * @param $barcode
   * @param $pin
   * @return array|string
   */
  function patronRead($barcode, $pin) {
    if (empty($this->url)) {
      return false;
    }

    if (!$barcode || !is_numeric($barcode) || !$pin) {
      //error_log('Valid barcode and pin are required for this call');
    }

    $sirsi_client = variable_get('stacks_auth_sirsi_client', '');
    $pin = trim($pin);
    $barcode = trim($barcode);
    $token = $_SESSION['sirsi_token'];
    $user = $_SESSION['sirsi_user'];

    $requestMethod = 'GET';
    $urlAction = '/patron/lookupMyAccountInfo?';
    //$urlAction = trim(trim($urlAction), '/');

    $urlParams = 'userID='.$user.'&includePatronCheckoutHistoryInfo';

    $requestUrl = $this->url . $urlAction . $urlParams;

    //dpm($requestUrl);

    $ch = curl_init($requestUrl);

    curl_setopt_array($ch,
      array(
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_TIMEOUT=> 10,
        CURLOPT_SSL_VERIFYHOST => FALSE,
        CURLOPT_USERAGENT => 'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.0.19) Gecko/2010031422 Firefox/3.0.19 ( .NET CLR 3.5.30729; .NET4.0E)',
        CURLOPT_HTTPHEADER => array(
          'Content-Type: application/json',
          'X-Sirs-Clientid:' . $sirsi_client,
          'x-sirs-sessionToken:' . $token
        )
      )
    );

    $xml = curl_exec($ch);

    //dpm($xml);

    if ($xml) {
      $xmlObject = simplexml_load_string($xml,null,null,'http://schemas.sirsidynix.com/symws/patron',null);

      $sirsiArray = array();

      foreach($xmlObject->PatronHoldInfo as $item)
      {
        foreach($item as $key => $value)
        {
          $sirsiArray[(string)$key] = (string)$value;
        }
      }

      //dpm($sirsiArray);

      $output =  array(
        'request_id' => $sirsiArray['itemID'],
        'bib_id' => $sirsiArray['itemID'],
        'status_id' => $sirsiArray['itemID'],
        'stadus_desc' => $sirsiArray['holdStatus'],
        'title' => $sirsiArray['title'],
        'author' => $sirsiArray['author']
      );

      /*
      $output =  array(
        'item_id' => (string)$item->ItemID,
        'bib_id' => (string)$item->BibID,
        'status_id' => (string)$item->StatusID,
        'checkout' => (string)$item->CheckOutDate,
        'title' => (string)$item->Title,
        'author' => (string)$item->Author,
        'type' => (string)$item->FormatDescription,
      );
      */

      return $output;
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
    /*
    $isbn = arg(2);

    if (!$barcode || !is_numeric($barcode) || !$pin) {
      error_log('Valid barcode and pin are required for this call');
    }

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
    */
  }

  /**
   * Bib Info
   *
   * @param $barcode
   * @param $pin
   * @return array|string
   */
  function bibGet($barcode, $pin) {
    /*
    $bibid = arg(3);

    if (!$barcode || !is_numeric($barcode) || !$pin) {
      error_log('Valid barcode and pin are required for this call');
    }

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
    */
  }

  /**
   * Bib Info
   *
   * @param $barcode
   * @param $pin
   * @return array|string
   */
  function bibInfo($barcode, $pin) {
    /*
    $bibid = arg(2);

    if (!$barcode || !is_numeric($barcode) || !$pin) {
      error_log('Valid barcode and pin are required for this call');
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
    */
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
		$papim_private_key = variable_get('stacks_auth_sirsi_private_key', '');
		if (function_exists('hash_hmac')) {
			$sigHash = hash_hmac('sha1',$signature, $papim_private_key, true);
		}
		else {
			$sigHash = $this->custom_hash_hmac('sha1',$signature, $papim_private_key, true);
		}

		$papim_access_id = variable_get('stacks_auth_sirsi_access_id', '');
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