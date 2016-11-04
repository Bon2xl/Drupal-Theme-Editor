<?php

class IIIAuthentication extends StacksAuthentication {

	public function __construct() {
		$this->url = variable_get('stacks_auth_iii', '');
	}


	/**
	 * Authenticates against III IP.
	 *
	 *
	 * @param string $barcode
	 * @param string $pin
	 * @return false on failure or array on success.
	 */
	public function authenticate($barcode = '', $pin = '') {
		if (empty($this->url)) {
			return false;
		}

		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $this->url . '/PATRONAPI/' . $barcode . '/' . $pin . '/pintest');
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		$output = curl_exec($ch);
		curl_close($ch);
		return $this->responseToArray($output);
	}


	/**
	 * Pulls basic data from the user
	 *
	 * @param $barcode
	 * @return bool
	 */
	public function patronBasicData($barcode) {
		if (empty($this->url)) {
			return false;
		}

		$output =  array(
			'currentfees' => '',
			'namefirst' => '',
			'namelast' => '',
			'emailaddress' => '',
		);

		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $this->url . '/PATRONAPI/' . $barcode . '/dump');
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		$output = curl_exec($ch);
		curl_close($ch);
		return $this->responseToArray($output);

	}

	/**
	 * Retrieves the account information from the Drupal shadow
	 * user.
	 *
	 * @param $user
	 * @return bool
	 */
	public function getAccountFromUser($user) {
		if (empty($user)) {
			return false;
		}

		$barcode = '';
		$prefix = 'patron_';
		if (substr($user->name, 0, strlen($prefix)) == $prefix) {
			$barcode = substr($user->name, strlen($prefix));
		}

		if (!empty($barcode)) {
			return $this->patronBasicData($barcode);
		} else {
			return false;
		}

	}

	private function responseToArray($body = '') {
		// parsing the BRs out
		$parsed_body = strip_tags(preg_replace('#<BR\s*/?>#i', "\n", $body));
//		echo $nl;

		$response = array();
		foreach(preg_split("/((\r?\n)|(\r\n?))/", $parsed_body) as $line){
			// do stuff with $line
			@list($k, $v) = explode('=', $line); // adding the infamous @ for now.
			if (!empty($k)) {
				$response[$k] = $v;
			}
		}
		return $response;
	}



}