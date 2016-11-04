<?php


abstract class StacksAuthentication {

	protected $url = '';

	protected function authenticate($barcode = '', $pin = '') {
		if (!empty($barcode)) {
			return false;
		}
		return true;
	}


}