<?php

function hf_stacks_places_config($form, $form_state) {
	$form['api_key_places'] = array(
    '#type' => 'textfield',
    '#title' => 'Google Places API key',
    '#default_value' => variable_get('hf_stacks_places_api_key', ''),
    '#description' => 'Please create and add a "Google Places API Web Service" Key. You can obtain one at the Google API console.'
	);

  /*
  if (!empty(variable_get('hf_stacks_places_api_key', ''))) {
    $form['api_key_places']['#attributes'] = array('placeholder' => '····················');
  }
  */

	$form['api_key_maps'] = array(
		'#type' => 'textfield',
		'#title' => 'Google Maps API key',
		'#default_value' => variable_get('hf_stacks_maps_api_key', ''),
		'#description' => 'Please create and add a "Google Maps JavaScript API" Key. You can obtain one at the Google API console.'
	);

  /*
  if (!empty(variable_get('hf_stacks_maps_api_key', ''))) {
    $form['api_key_maps']['#attributes'] = array('placeholder' => '····················');
  }
  */

	$form['search_test'] = array(
			'#type' => 'textfield',
			'#title' => 'Test search',
			'#description' => 'Enter a test search query to ensure your API key is working.'
	);
	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Save Configuration'
	);
//	$form['test'] = array(
//			'#type' => 'markup',
//			'#markup' => '<pre>'. print_r(hf_stacks_places_place_details('Lakeland Library Branch saskatchewan'), true) . '</pre>'
//	);
	return $form;
}


function hf_stacks_places_config_submit($form, $form_state){
  if (!empty($form_state['values']['api_key_places'])) {
    variable_set('hf_stacks_places_api_key', $form_state['values']['api_key_places']);
  }
  if (!empty($form_state['values']['api_key_maps'])) {
    variable_set('hf_stacks_maps_api_key', $form_state['values']['api_key_maps']);
  }

	variable_set('hf_stacks_places_content_type', 'library_branch');
	variable_set('hf_stacks_maps_content_type', 'library_branch');

	drupal_set_message('Settings saved');
	if (!empty($form_state['values']['search_test'])) {
		drupal_set_message('<pre>' . print_r(hf_stacks_places_search($form_state['values']['search_test'], variable_get('hf_stacks_places_api_key', '')), true).'</pre>');
	}
}

function _hf_stacks_places_contenttypes() {
	$cts = node_type_get_types();
	$options = array('' => '-None-');
	foreach ($cts as $id => $ct) {
		$options[$id] = $ct->name;
	}
	return $options;
}



/* TEST FUNCTIONS */
function testplaces() {
	$ch = curl_init();
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
	curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
	curl_setopt($ch, CURLOPT_VERBOSE, TRUE);
	curl_setopt($ch, CURLOPT_URL, "https://maps.googleapis.com/maps/api/place/details/json?placeid=ChIJN1t_tDeuEmsRUsoyG83frY4&key=AIzaSyBGlT4i0YieX7akomA_koH75eSecJRkk_M&sensor=false&userIp=127.0.0.1");
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	$output = curl_exec($ch);
	curl_close($ch);
	return $output;
}

function findplace() {
	$ch = curl_init();
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
	curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
	curl_setopt($ch, CURLOPT_VERBOSE, TRUE);
	curl_setopt($ch, CURLOPT_URL, "https://maps.googleapis.com/maps/api/place/textsearch/json?key=AIzaSyBGlT4i0YieX7akomA_koH75eSecJRkk_M&query=Lakeland+Library+Branch+saskatchewan&userIp=127.0.0.1");
	$output = curl_exec($ch);
	curl_close($ch);
	return $output;
}