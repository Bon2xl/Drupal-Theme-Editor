<?php

function hf_mobile_admin_form($form, &$form_state) {
	$form = array();

	$form['config-tabs'] = array(
		'#type' => 'vertical_tabs'
	);

  // get all of the resource flows
  $query = db_select('node', 'n');
  $query->fields('n', array('title', 'nid'));
  $query->condition('type', 'resource_list', '=');
  $query->orderBy('title', 'ASC');
  $options = array();
  $results = $query->execute();
  while($record = $results->fetchAssoc()) {
    //$record["title"];
    $options[$record["nid"]] = $record["title"];
  }

	$form['access-key-fieldset'] = array(
		'#type' => 'fieldset',
		'#title' => 'Access Key',
		'#description' => 'The access key for the mobile application to access the website',
		'#group' => 'config-tabs',

		'access-key' => array(
			'#type' => 'textfield',
			'#title' => 'Access Key',
			'#maxlength' => 512,
			'#default_value' => variable_get('stacks_mobile_key', ''),
		)
	);

	$form['resourceflow-fieldset'] = array(
		'#type' => 'fieldset',
		'#title' => 'Resource Flow',
		'#description' => 'Enter in the resource flow that you want to display in the mobile application',
		'#group' => 'config-tabs',

		// options
		'resourceflows' => array(
			'#title' => "Default Resource Flow",
			'#type' => 'select',
			'#options' => $options,
			'#default_value' => variable_get('stacks_mobile_resource', '')
		),
	);

	$form['events-fieldset'] = array(
		'#type' => 'fieldset',
		'#title' => 'Events',
		'#description' => 'Enter the URL for the primary events page listing',
		'#group' => 'config-tabs',

		'events-url' => array(
			'#type' => 'textfield',
			'#title' => 'Events Page URL',
      '#maxlength' => 512,
			'#default_value' => variable_get('stacks_mobile_events', ''),
			'#description' => 'Example: http://events.stacksdiscovery.com',
		)
	);

  $form['databases-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => 'Databases',
    '#description' => 'Enter the URL for the databases listing page.',
    '#group' => 'config-tabs',

    'database-url' => array(
      '#type' => 'textfield',
      '#title' => 'Databases URL',
      '#maxlength' => 512,
      '#default_value' => variable_get('stacks_mobile_database', ''),
      '#description' => 'Example: http://databases.stacksdiscovery.com ',
    )
  );

	$form['push-fieldset'] = array(
		'#type' => 'fieldset',
		'#title' => 'Push Registration URL',
		'#description' => 'Enter the URL for push registrations.',
		'#group' => 'config-tabs',

		'push-url' => array(
			'#type' => 'textfield',
			'#title' => 'Push Registration URL',
			'#maxlength' => 512,
			'#default_value' => variable_get('stacks_mobile_push', ''),
			'#description' => 'Example: http://push.stacksdiscovery.com ',
		)
	);

	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save Configuration'
	);
	return $form;
}


function hf_mobile_admin_form_submit($form, &$form_state) {
	variable_set('stacks_mobile_key', $form_state['values']['access-key']);
	variable_set('stacks_mobile_resource', $form_state['values']['resourceflows']);
  variable_set('stacks_mobile_events', $form_state['values']['events-url']);
  variable_set('stacks_mobile_database', $form_state['values']['database-url']);
  variable_set('stacks_mobile_push', $form_state['values']['push-url']);
	//dpm($form_state);
}