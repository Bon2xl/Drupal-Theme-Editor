<?php

function hf_footer_form($form, &$form_state) {

  if (module_exists('domain_conf')) {
    $domain = domain_get_domain();

    $form['contact-fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => 'Contact Info',
    );

    $form['contact-fieldset']['footer_contact_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Contact Block Title'),
      '#size' => 60,
      '#required' => TRUE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_contact_title'),
      // '#description' => t('Contact Block Title'),
    );

    $form['contact-fieldset']['footer_email'] = array(
      '#type' => 'textfield',
      '#title' => t('Email Address'),
      '#size' => 60,
      '#required' => TRUE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_email'),
      // '#description' => t('Email Address'),
    );

    $form['contact-fieldset']['footer_staff'] = array(
      '#type' => 'textfield',
      '#title' => t('Staff Directory URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_staff'),
      // '#description' => t('Staff Directory URL'),
    );

    $form['contact-fieldset']['footer_directions'] = array(
      '#type' => 'textfield',
      '#title' => t('Directions URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_directions'),
      // '#description' => t('Directions URL (for external links use an http:// prefix)'),
    );

    $form['contact-fieldset']['footer_locations'] = array(
      '#type' => 'textfield',
      '#title' => t('Dropbox Locations URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_locations'),
      // '#description' => t('Dropbox Locations URL (for external links use an http:// prefix)'),
    );

    $form['contact-fieldset']['footer_phone'] = array(
      '#type' => 'textfield',
      '#title' => t('Phone #'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_phone'),
      // '#description' => t('Phone Number'),
    );

    $form['contact-fieldset']['footer_phone2'] = array(
      '#type' => 'textfield',
      '#title' => t('Phone # (Alternate)'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_phone2'),
      // '#description' => t('Alternate Phone Number'),
    );

    $form['contact-fieldset']['footer_fax'] = array(
      '#type' => 'textfield',
      '#title' => t('Fax #'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_fax'),
      // '#description' => t('Fax Number'),
    );

    $form['contact-fieldset']['footer_newsletter'] = array(
      '#type' => 'textfield',
      '#title' => t('Newsletter URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_newsletter'),
      // '#description' => t('Newsletter URL (for external links use an http:// prefix)'),
    );

    $form['connect-fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => 'Connect Info',
    );

    $form['connect-fieldset']['footer_connect_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Connect Block Title'),
      '#size' => 60,
      '#required' => TRUE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_connect_title'),
      // '#description' => t('Connect Block Title'),
    );

    $form['connect-fieldset']['footer_txt'] = array(
      '#type' => 'textfield',
      '#title' => t('Mobile TXT URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_txt'),
      // '#description' => t('Mobile TXT URL'),
    );

    $form['connect-fieldset']['footer_twitter'] = array(
      '#type' => 'textfield',
      '#title' => t('Twitter URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_twitter'),
      // '#description' => t('Twitter URL'),
    );

    $form['connect-fieldset']['footer_facebook'] = array(
      '#type' => 'textfield',
      '#title' => t('Facebook URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_facebook'),
      // '#description' => t('Facebook URL'),
    );

    $form['connect-fieldset']['footer_youtube'] = array(
      '#type' => 'textfield',
      '#title' => t('YouTube URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_youtube'),
      // '#description' => t('YouTube URL'),
    );

    $form['connect-fieldset']['footer_flickr'] = array(
      '#type' => 'textfield',
      '#title' => t('Flickr URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_flickr'),
      // '#description' => t('Flickr URL'),
    );

    $form['connect-fieldset']['footer_gplus'] = array(
      '#type' => 'textfield',
      '#title' => t('Google+ URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_gplus'),
      // '#description' => t('Google+ URL'),
    );

    $form['connect-fieldset']['footer_instagram'] = array(
      '#type' => 'textfield',
      '#title' => t('Instagram URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_instagram'),
      // '#description' => t('Instagram URL'),
    );

    $form['connect-fieldset']['footer_linkedin'] = array(
      '#type' => 'textfield',
      '#title' => t('LinkedIn URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_linkedin'),
      // '#description' => t('LinkedIn URL'),
    );

    $form['connect-fieldset']['footer_pinterest'] = array(
      '#type' => 'textfield',
      '#title' => t('Pinterest URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_pinterest'),
      // '#description' => t('Pinterest URL'),
    );

    $form['connect-fieldset']['footer_tumblr'] = array(
      '#type' => 'textfield',
      '#title' => t('Tumblr URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => domain_conf_variable_get($domain['domain_id'], 'hf_footer_tumblr'),
      // '#description' => t('Tumblr URL'),
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Save Configuration'
    );
  } else {
    $form['contact-fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => 'Contact Info',
    );

    $form['contact-fieldset']['footer_contact_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Contact Block Title'),
      '#size' => 60,
      '#required' => TRUE,
      '#default_value' => variable_get('hf_footer_contact_title'),
      // '#description' => t('Contact Block Title'),
    );

    $form['contact-fieldset']['footer_email'] = array(
      '#type' => 'textfield',
      '#title' => t('Email Address'),
      '#size' => 60,
      '#required' => TRUE,
      '#default_value' => variable_get('hf_footer_email'),
      // '#description' => t('Email Address'),
    );

    $form['contact-fieldset']['footer_staff'] = array(
      '#type' => 'textfield',
      '#title' => t('Staff Directory URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_staff'),
      // '#description' => t('Staff Directory URL'),
    );

    $form['contact-fieldset']['footer_directions'] = array(
      '#type' => 'textfield',
      '#title' => t('Directions URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_directions'),
      // '#description' => t('Directions URL (for external links use an http:// prefix)'),
    );

    $form['contact-fieldset']['footer_locations'] = array(
      '#type' => 'textfield',
      '#title' => t('Dropbox Locations URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_locations'),
      // '#description' => t('Dropbox Locations URL (for external links use an http:// prefix)'),
    );

    $form['contact-fieldset']['footer_phone'] = array(
      '#type' => 'textfield',
      '#title' => t('Phone #'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_phone'),
      // '#description' => t('Phone Number'),
    );

    $form['contact-fieldset']['footer_phone2'] = array(
      '#type' => 'textfield',
      '#title' => t('Phone # (Alternate)'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_phone2'),
      // '#description' => t('Alternate Phone Number'),
    );

    $form['contact-fieldset']['footer_fax'] = array(
      '#type' => 'textfield',
      '#title' => t('Fax #'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_fax'),
      // '#description' => t('Fax Number'),
    );

    $form['contact-fieldset']['footer_newsletter'] = array(
      '#type' => 'textfield',
      '#title' => t('Newsletter URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_newsletter'),
      // '#description' => t('Newsletter URL (for external links use an http:// prefix)'),
    );

    $form['connect-fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => 'Connect Info',
    );

    $form['connect-fieldset']['footer_connect_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Connect Block Title'),
      '#size' => 60,
      '#required' => TRUE,
      '#default_value' => variable_get('hf_footer_connect_title'),
      // '#description' => t('Connect Block Title'),
    );

    $form['connect-fieldset']['footer_txt'] = array(
      '#type' => 'textfield',
      '#title' => t('Mobile TXT URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_txt'),
      // '#description' => t('Mobile TXT URL'),
    );

    $form['connect-fieldset']['footer_twitter'] = array(
      '#type' => 'textfield',
      '#title' => t('Twitter URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_twitter'),
      // '#description' => t('Twitter URL'),
    );

    $form['connect-fieldset']['footer_facebook'] = array(
      '#type' => 'textfield',
      '#title' => t('Facebook URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_facebook'),
      // '#description' => t('Facebook URL'),
    );

    $form['connect-fieldset']['footer_youtube'] = array(
      '#type' => 'textfield',
      '#title' => t('YouTube URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_youtube'),
      // '#description' => t('YouTube URL'),
    );

    $form['connect-fieldset']['footer_flickr'] = array(
      '#type' => 'textfield',
      '#title' => t('Flickr URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_flickr'),
      // '#description' => t('Flickr URL'),
    );

    $form['connect-fieldset']['footer_gplus'] = array(
      '#type' => 'textfield',
      '#title' => t('Google+ URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_gplus'),
      // '#description' => t('Google+ URL'),
    );

    $form['connect-fieldset']['footer_instagram'] = array(
      '#type' => 'textfield',
      '#title' => t('Instagram URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_instagram'),
      // '#description' => t('Instagram URL'),
    );

    $form['connect-fieldset']['footer_linkedin'] = array(
      '#type' => 'textfield',
      '#title' => t('LinkedIn URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_linkedin'),
      // '#description' => t('LinkedIn URL'),
    );

    $form['connect-fieldset']['footer_pinterest'] = array(
      '#type' => 'textfield',
      '#title' => t('Pinterest URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_pinterest'),
      // '#description' => t('Pinterest URL'),
    );

    $form['connect-fieldset']['footer_tumblr'] = array(
      '#type' => 'textfield',
      '#title' => t('Tumblr URL'),
      '#size' => 60,
      '#required' => FALSE,
      '#default_value' => variable_get('hf_footer_tumblr'),
      // '#description' => t('Tumblr URL'),
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Save Configuration'
    );
  }

  return ($form);
}

/**
 * Implementation of Hook_Form_Validate()
 */
function hf_footer_form_validate($form, &$form_state) {
  //$form_state['values']['footer_twitter'] = preg_replace('/[^a-z0-9]+/', '', $form_state['values']['footer_twitter']);

  if (!empty($form_state['values']['footer_twitter'])) {
    if (valid_url($form_state['values']['footer_twitter'], TRUE) == false) {
      form_set_error('title', 'Twitter field must be a valid URL');
    }
  }
  if (!empty($form_state['values']['hf_footer_facebook'])) {
    if (valid_url($form_state['values']['hf_footer_facebook'], TRUE) == false) {
      form_set_error('title', 'Facebook field must be a valid URL');
    }
  }
  if (!empty($form_state['values']['hf_footer_youtube'])) {
    if (valid_url($form_state['values']['hf_footer_youtube'], TRUE) == false) {
      form_set_error('title', 'YouTube field must be a valid URL');
    }
  }
  if (!empty($form_state['values']['hf_footer_flickr'])) {
    if (valid_url($form_state['values']['hf_footer_flickr'], TRUE) == false) {
      form_set_error('title', 'Flickr field must be a valid URL');
    }
  }
  if (!empty($form_state['values']['hf_footer_gplus'])) {
    if (valid_url($form_state['values']['hf_footer_gplus'], TRUE) == false) {
      form_set_error('title', 'Google Plus field must be a valid URL');
    }
  }
  if (!empty($form_state['values']['hf_footer_instagram'])) {
    if (valid_url($form_state['values']['hf_footer_instagram'], TRUE) == false) {
      form_set_error('title', 'Instagram field must be a valid URL');
    }
  }
  if (!empty($form_state['values']['hf_footer_linkedin'])) {
    if (valid_url($form_state['values']['hf_footer_linkedin'], TRUE) == false) {
      form_set_error('title', 'LinkedIn field must be a valid URL');
    }
  }
  if (!empty($form_state['values']['hf_footer_pinterest'])) {
    if (valid_url($form_state['values']['hf_footer_pinterest'], TRUE) == false) {
      form_set_error('title', 'Pinterest field must be a valid URL');
    }
  }
  if (!empty($form_state['values']['hf_footer_tumblr'])) {
    if (valid_url($form_state['values']['hf_footer_tumblr'], TRUE) == false) {
      form_set_error('title', 'Tumble field must be a valid URL');
    }
  }
}

// saving the variable for multidomains
function hf_footer_form_submit($form, &$form_state) {

  if (module_exists('domain_conf')) {
    $domain = domain_get_domain();

    domain_conf_variable_set($domain['domain_id'], 'hf_footer_contact_title', $form_state['values']['footer_contact_title']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_connect_title', $form_state['values']['footer_connect_title']);

    domain_conf_variable_set($domain['domain_id'], 'hf_footer_email', $form_state['values']['footer_email']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_staff', $form_state['values']['footer_staff']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_directions', $form_state['values']['footer_directions']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_locations', $form_state['values']['footer_locations']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_phone', $form_state['values']['footer_phone']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_phone2', $form_state['values']['footer_phone2']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_fax', $form_state['values']['footer_fax']);

    domain_conf_variable_set($domain['domain_id'], 'hf_footer_txt', $form_state['values']['footer_txt']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_twitter', $form_state['values']['footer_twitter']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_facebook', $form_state['values']['footer_facebook']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_youtube', $form_state['values']['footer_youtube']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_flickr', $form_state['values']['footer_flickr']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_gplus', $form_state['values']['footer_gplus']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_instagram', $form_state['values']['footer_instagram']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_linkedin', $form_state['values']['footer_linkedin']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_pinterest', $form_state['values']['footer_pinterest']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_tumblr', $form_state['values']['footer_tumblr']);
    domain_conf_variable_set($domain['domain_id'], 'hf_footer_newsletter', $form_state['values']['footer_newsletter']);

    drupal_set_message('Settings saved on the current domain');
  } else {
    variable_set('hf_footer_contact_title', $form_state['values']['footer_contact_title']);
    variable_set('hf_footer_connect_title', $form_state['values']['footer_connect_title']);

    variable_set('hf_footer_email', $form_state['values']['footer_email']);
    variable_set('hf_footer_staff', $form_state['values']['footer_staff']);
    variable_set('hf_footer_directions', $form_state['values']['footer_directions']);
    variable_set('hf_footer_locations', $form_state['values']['footer_locations']);
    variable_set('hf_footer_phone', $form_state['values']['footer_phone']);
    variable_set('hf_footer_phone2', $form_state['values']['footer_phone2']);
    variable_set('hf_footer_fax', $form_state['values']['footer_fax']);

    variable_set('hf_footer_txt', $form_state['values']['footer_txt']);
    variable_set('hf_footer_twitter', $form_state['values']['footer_twitter']);
    variable_set('hf_footer_facebook', $form_state['values']['footer_facebook']);
    variable_set('hf_footer_youtube', $form_state['values']['footer_youtube']);
    variable_set('hf_footer_flickr', $form_state['values']['footer_flickr']);
    variable_set('hf_footer_gplus', $form_state['values']['footer_gplus']);
    variable_set('hf_footer_instagram', $form_state['values']['footer_instagram']);
    variable_set('hf_footer_linkedin', $form_state['values']['footer_linkedin']);
    variable_set('hf_footer_pinterest', $form_state['values']['footer_pinterest']);
    variable_set('hf_footer_tumblr', $form_state['values']['footer_tumblr']);
    variable_set('hf_footer_newsletter', $form_state['values']['footer_newsletter']);
  }
}