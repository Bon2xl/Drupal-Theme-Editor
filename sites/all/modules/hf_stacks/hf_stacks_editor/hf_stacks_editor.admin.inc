<?php
/**
 * Form for providing options to configure stacks.
 * @param $form
 * @param $form_state
 * @return mixed
 */
function hf_stacks_editor_form($form, &$form_state) {
  $form['site_information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Site details'),
  );
  $form['site_information']['site_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Site name'),
    '#default_value' => variable_get('site_name', 'Drupal'),
    '#required' => TRUE
  );
  $form['site_information']['site_slogan'] = array(
    '#type' => 'textfield',
    '#title' => t('Slogan'),
    '#default_value' => variable_get('site_slogan', ''),
    '#description' => t("How this is used depends on your site's theme."),
  );
  $form['site_information']['site_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#default_value' => variable_get('site_mail', ini_get('sendmail_from')),
    '#description' => t("The <em>From</em> address in automated e-mails sent during registration and new password requests, and other notifications. (Use an address ending in your site's domain to help prevent this e-mail being flagged as spam.)"),
    '#required' => TRUE,
  );

  $form['set_var'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enable Landing Page'),
  );
  $form['set_var']['stacks_landing_checkbox'] = array(
    '#type' => 'checkbox',
    '#title' => "Enable Landing Page",
    '#default_value' => variable_get('stacks_landing'),
  );

  $form['set_topmenu'] = array(
    '#type' => 'fieldset',
    '#title' => t('Top Menu Icons'),
  );
  $form['set_topmenu']['stacks_topmenu_databases'] = array(
    '#type' => 'checkbox',
    '#title' => "Enable Databases Icon",
    '#default_value' => variable_get('stacks_topmenu_databases'),
  );
  $form['set_topmenu']['stacks_topmenu_calendar'] = array(
    '#type' => 'checkbox',
    '#title' => "Enable Events Icon",
    '#default_value' => variable_get('stacks_topmenu_calendar'),
  );
  $form['set_topmenu']['stacks_topmenu_rooms'] = array(
    '#type' => 'checkbox',
    '#title' => "Enable Room Booking Icon",
    '#default_value' => variable_get('stacks_topmenu_rooms'),
  );

  $form['set_fontresizer'] = array(
    '#type' => 'fieldset',
    '#title' => t('Font Resizer'),
  );
  $form['set_fontresizer']['stacks_font_resizer'] = array(
    '#type' => 'checkbox',
    '#title' => "Yes",
    '#default_value' => variable_get('stacks_font_resizer'),
    '#description' => t('Allow users to enlarge fonts in order to facilitate accessibility.')
  );

  $form['#validate'][] = 'hf_stacks_config_form_validate';

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }
  $form['#submit'][] = 'hf_stacks_config_form_submit';
//
  return $form;
}

/**
 * Validates the submitted site-information form.
 */
function hf_stacks_editor_form_validate($form, &$form_state) {
  // Validate the e-mail address.
  if ($error = user_validate_mail($form_state['values']['site_mail'])) {
    form_set_error('site_mail', $error);
  }
}

/**
 * Form submission handler for system_settings_form().
 *
 * If you want node type configure style handling of your checkboxes,
 * add an array_filter value to your form.
 */
function hf_stacks_editor_form_submit($form, &$form_state) {
  variable_set('stacks_landing', $form_state['values']['stacks_landing_checkbox']);
  if ($form_state['values']['stacks_landing_checkbox'] == '') {
    variable_del('stacks_landing');
  }
  variable_set('stacks_topmenu_databases', $form_state['values']['stacks_topmenu_databases']);
  if ($form_state['values']['stacks_topmenu_databases'] == '') {
    variable_del('stacks_topmenu_databases');
  }
  variable_set('stacks_topmenu_calendar', $form_state['values']['stacks_topmenu_calendar']);
  if ($form_state['values']['stacks_topmenu_calendar'] == '') {
    variable_del('stacks_topmenu_calendar');
  }
  variable_set('stacks_topmenu_rooms', $form_state['values']['stacks_topmenu_rooms']);
  if ($form_state['values']['stacks_topmenu_rooms'] == '') {
    variable_del('stacks_topmenu_rooms');
  }
  variable_set('stacks_font_resizer', $form_state['values']['stacks_font_resizer']);
  if ($form_state['values']['stacks_font_resizer'] == '') {
    variable_del('stacks_font_resizer');
  }

  drupal_set_message(t('The configuration options have been saved.'));
}
