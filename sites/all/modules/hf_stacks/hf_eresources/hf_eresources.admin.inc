<?php
function hf_eresources_config($form, &$form_state, $no_js_use = FALSE) {
  $form['description'] = array(
    '#markup' => '<div>' . t('Enter in either a IP Range, or for a single IP address put the same address in both fields.') . '</div>',
  );
	
	if (variable_get('hf_eresources_size')) {
		$form_size = variable_get('hf_eresources_size');
		$form_array = variable_get('hf_eresources_whitelist');
		//$form_state['num_ips'] = $form_size;
		//$form_state['rebuild'] = TRUE;
	} else {
		$form_size = 1;
	}
	
  if (!isset($form_state['num_changed'])) {
    $form_state['num_ips'] = $form_size;
  }
	
	//dpm($form_state);
	
  // Because we have many fields with the same values, we have to set
  // #tree to be able to access them.
  $form['#tree'] = TRUE;
  $form['ips_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('IP Address Whitelist'),
    // Set up the wrapper so that AJAX will be able to replace the fieldset.
    '#prefix' => '<div id="ips-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  // Build the fieldset with the proper number of ips. We'll use
  // $form_state['num_ips'] to determine the number of textfields to build.
  if (empty($form_state['num_ips'])) {
    $form_state['num_ips'] = 1;
  }
  for ($i = 0; $i < $form_state['num_ips']; $i++) {
    $form['ips_fieldset'][$i]['ip1'] = array(
      '#type' => 'textfield',
      '#title' => t('IP Start'),
      '#default_value' => $form_array[$i]['s'],
      '#prefix' => '<div class="two-col"><div class="col1">',
      '#suffix' => '</div>'
    );
    
    $form['ips_fieldset'][$i]['ip2'] = array(
      '#type' => 'textfield',
      '#title' => t('IP End'),
      '#default_value' => $form_array[$i]['e'],
      '#prefix' => '<div class="col2">',
      '#suffix' => '</div>'  
    );
    /*
    $form['ips_fieldset'][$i]['remove_item'] = array(
    	'#item_id' => $i,
      '#type' => 'submit',
      '#value' => 'Remove',
      '#name' => 'Remove'.$i,
      '#submit' => array('hf_eresources_config_remove_item'),
      '#ajax' => array(
        'callback' => 'hf_eresources_config_callback',
        'wrapper' => 'ips-fieldset-wrapper',
      ),
      '#prefix' => '<div class="col3">',
      '#suffix' => '</div></div>'
    );
    */
  }
  
  $form['ips_fieldset']['add_ip'] = array(
    '#type' => 'submit',
    '#value' => t('Add one more'),
    '#submit' => array('hf_eresources_config_add_one'),
    '#ajax' => array(
      'callback' => 'hf_eresources_config_callback',
      'wrapper' => 'ips-fieldset-wrapper',
    ),
    '#prefix' => '<div class="field_add">',
    '#suffix' => '</div>'
  );
  
  if ($form_state['num_ips'] > 1) {
    $form['ips_fieldset']['remove_ip'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one'),
      '#submit' => array('hf_eresources_config_remove_one'),
      '#ajax' => array(
        'callback' => 'hf_eresources_config_callback',
        'wrapper' => 'ips-fieldset-wrapper',
      ),
	    '#prefix' => '<div class="field_remove">',
	    '#suffix' => '</div>'
    );
  }
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  // This simply allows us to demonstrate no-javascript use without
  // actually turning off javascript in the browser. Removing the #ajax
  // element turns off AJAX behaviors on that element and as a result
  // ajax.js doesn't get loaded.
  // For demonstration only! You don't need this.
  if ($no_js_use) {
    // Remove the #ajax from the above, so ajax.js won't be loaded.
    if (!empty($form['ips_fieldset']['remove_ip']['#ajax'])) {
      unset($form['ips_fieldset']['remove_ip']['#ajax']);
    }
    unset($form['ips_fieldset']['add_ip']['#ajax']);
  }

  return $form;
}

/**
 * Callback for both ajax-enabled buttons.
 *
 * Selects and returns the fieldset with the ips in it.
 */
function hf_eresources_config_callback($form, $form_state) {
  return $form['ips_fieldset'];
}

/**
 * Submit handler for the "add-one-more" button.
 *
 * Increments the max counter and causes a rebuild.
 */
function hf_eresources_config_add_one($form, &$form_state) {
  $form_state['num_ips']++;
  $form_state['num_changed'] = TRUE;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the "remove one" button.
 *
 * Decrements the max counter and causes a form rebuild.
 */
function hf_eresources_config_remove_one($form, &$form_state) {
  if ($form_state['num_ips'] > 1) {
    $form_state['num_ips']--;
    $form_state['num_changed'] = TRUE;
  }
  $form_state['rebuild'] = TRUE;
}

function hf_eresources_config_remove_item($form, &$form_state) {

}

/**
 * Final submit handler.
 *
 * Reports what values were finally set.
 */
function hf_eresources_config_submit($form, &$form_state) {
	//dpm($form_state);
	//dpm($form_state['num_ips']);
	//dpm($form_state['values']['ips_fieldset']);
	
	$ip_array = array();
	
  for ($i = 0; $i < $form_state['num_ips']; $i++) {
  	$ip_array[$i]['s'] = $form_state['values']['ips_fieldset'][$i]['ip1'];
  	$ip_array[$i]['e'] = $form_state['values']['ips_fieldset'][$i]['ip2'];
  }
	
	variable_set('hf_eresources_size', $form_state['num_ips']);
	variable_set('hf_eresources_whitelist', $ip_array);
	
	drupal_set_message('Whitelist Saved');
}