<?php

function _hf_stacks_auth_form($form, &$form_state) {

	$form = array();

	$form['authentication'] = array(
		'#type' => 'fieldset',
		'#title' => 'Authentication System',

		// options

		'system' => array(
			'#type' => 'select',
			'#options' => array(
				'' => '- None -',
				'iii' => 'III',
				'polaris' => 'Polaris',
				'sirsi' => 'Sirsi',
				'sip2' => 'SIP 2'
			),
			'#default_value' => variable_get('stacks_auth', '')
		)

	);

	$form['config-tabs'] = array(
		'#title' => 'Configuration',
		'#type' => 'vertical_tabs',
		'#default_tab' => 'edit-'.variable_get('stacks_auth', '')
	);

	$form['iii'] = array(
		'#type' => 'fieldset',
		'#title' => 'III',
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
		'#description' => 'Patron authentication for III based systems',
		'#group' => 'config-tabs',

		// options
		'iii_url' => array(
			'#title' => "URL for Authentication",
			'#type' => 'textfield',
			'#default_value' => variable_get('stacks_auth_iii', '')
		)
	);

	$form['polaris'] = array(
		'#type' => 'fieldset',
		'#title' => 'Polaris',
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
		'#description' => 'Patron authentication for Polaris based systems',
		'#group' => 'config-tabs',

		// options
		'polaris_url' => array(
			'#title' => "URL for Authentication",
			'#type' => 'textfield',
			'#default_value' => variable_get('stacks_auth_polaris_url', '')
		),
		'polaris_signature' => array(
			'#title' => "Signature",
			'#type' => 'textfield',
			'#default_value' => variable_get('stacks_auth_polaris_signature', '')
		),
		'polaris_private_key' => array(
			'#title' => "Private Key",
			'#type' => 'textfield',
			'#default_value' => variable_get('stacks_auth_polaris_private_key', '')
		),
		'polaris_access_id' => array(
			'#title' => "Access ID",
			'#type' => 'textfield',
			'#default_value' => variable_get('stacks_auth_polaris_access_id', '')
		)
	);

	$form['sirsi'] = array(
		'#type' => 'fieldset',
		'#title' => 'Sirsi',
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
		'#description' => 'Patron authentication for Sirsi based systems',
		'#group' => 'config-tabs',

		// options
		'sirsi_url' => array(
			'#title' => "URL for Authentication",
			'#type' => 'textfield',
			'#default_value' => variable_get('stacks_auth_sirsi_url', '')
		),
		'sirsi_client' => array(
			'#title' => "Cliend ID",
			'#type' => 'textfield',
			'#default_value' => variable_get('stacks_auth_sirsi_client', '')
		)
	);

	$form['sip2'] = array(
		'#type' => 'fieldset',
		'#title' => 'SIP 2',
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
		'#description' => 'Patron authentication for SIP 2 based systems',
		'#group' => 'config-tabs',

		// options
		'sip2_host' => array(
			'#title' => "SIP Host",
			'#type' => 'textfield',
			'#default_value' => variable_get('stacks_auth_sip2_host', '')
		),
		'sip2_port' => array(
			'#title' => "SIP Server's Listening Port",
			'#type' => 'textfield',
			'#default_value' => variable_get('stacks_auth_sip2_port', '')
		),
		'sip2_username' => array(
			'#title' => "SIP Username",
			'#type' => 'textfield',
			'#default_value' => variable_get('stacks_auth_sip2_username', '')
		),
		'sip2_password' => array(
			'#title' => "SIP Password",
			'#type' => 'textfield',
			'#default_value' => variable_get('stacks_auth_sip2_password', '')
		)
	);

	$form['test'] = array(
		'#type' => 'fieldset',
		'#title' => 'Test Authentication',
		'#description' => 'Test the authentication on the current configured system',

		// options
		'barcode_test' => array(
			'#title' => "barcode",
			'#type' => 'textfield',
			'#default_value' => ''
		),
		'pin_test' => array(
			'#title' => "Pin",
			'#type' => 'textfield',
		)
	);

	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save Configuration'
	);

	return $form;
}

function _hf_stacks_auth_form_submit($form, &$form_state) {
	$vals = $form_state['values'];

	// authentication system
	variable_set('stacks_auth', $vals['system']);
	if ($form_state['values']['system'] == '') {
		variable_del('stacks_auth');
	}

	variable_set('stacks_auth_iii', $vals['iii_url']);
	if ($vals['iii_url'] == '') {
		variable_del('stacks_auth_iii');
	}

	// Polaris settings
	variable_set('stacks_auth_polaris_url', $vals['polaris_url']);
	variable_set('stacks_auth_polaris_signature', $vals['polaris_signature']);
	variable_set('stacks_auth_polaris_private_key', $vals['polaris_private_key']);
	variable_set('stacks_auth_polaris_access_id', $vals['polaris_access_id']);

	// Sirsi settings
	variable_set('stacks_auth_sirsi_url', $vals['sirsi_url']);
	variable_set('stacks_auth_sirsi_client', $vals['sirsi_client']);

	// SIP2 settings
	variable_set('stacks_auth_sip2_host', $vals['sip2_host']);
	variable_set('stacks_auth_sip2_port', $vals['sip2_port']);
	variable_set('stacks_auth_sip2_username', $vals['sip2_username']);
	variable_set('stacks_auth_sip2_password', $vals['sip2_password']);

	// Barcode testing
	if (!empty($vals['barcode_test'])) {
		_hf_stacks_auth_barcode_test($vals['barcode_test'], $vals['pin_test']);
	}

	drupal_set_message('Settings saved.');

}

/**
 * Tries to authenticate a barcode based on the configuration options.
 */
function _hf_stacks_auth_barcode_test($barcode, $pin) {

	if (variable_get('stacks_auth','') === 'iii') {
		$auth = new IIIAuthentication();
	} else if (variable_get('stacks_auth','') === 'polaris') {
		//error_log('testing polaris');
		$auth = new PolarisAuthentication();
    } else if (variable_get('stacks_auth','') === 'sip2') {
        //error_log('testing sip2');
        $auth = new SIP2Authentication();
	} else {
		drupal_set_message('No authentication method');
		return;
	}
	drupal_set_message(print_r($auth->patronBasicData($barcode, $pin),true));
}