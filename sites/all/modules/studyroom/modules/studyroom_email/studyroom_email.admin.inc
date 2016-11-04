<?php

function studyroom_email_form($form, &$form_state) {
  $form['email_booking_create_set'] = array(
    '#type' => 'fieldset',
    '#title' => 'New Bookings',

    'instructions' => array(
      '#type' => 'markup',
      '#markup' => '<p>This template will be used when bookings are created</p>' .
        '<p>Parameters: %datetime% | %duration% | %group% | %room% | %occupancy% | %description% | %name% | %email% | %phone%</p>'
    ),
  );
  $form['email_booking_create_set']['email_booking_create_address'] = array(
    '#type' => 'textfield',
    '#title' => "Reply Email Address",
    '#required' => TRUE,
    '#default_value' => variable_get('studyroom_email_booking_create_address', '')
  );
  $form['email_booking_create_set']['email_booking_create_subject'] = array(
    '#type' => 'textfield',
    '#title' => "Email Subject",
    '#required' => TRUE,
    '#default_value' => variable_get('studyroom_email_booking_create_subject', '')
  );
  $form['email_booking_create_set']['email_booking_create'] = array(
    '#type' => 'textarea',
    '#title' => 'Email Body Template',
    '#required' => TRUE,
    '#rows' => 12,
    '#maxlength' => '500',
    '#maxlength_js' => TRUE,
    '#attributes' =>array(
      'maxlength_js_label' => '@remaining characters left.',
    ),
    '#default_value' => variable_get('studyroom_email_booking_create', ''),
    '#description' => 'Enter the email copy, the maximum number of characters allowed is 500.',
  );


  $form['email_booking_cancel_set'] = array(
    '#type' => 'fieldset',
    '#title' => 'Cancelled Bookings',

    'instructions' => array(
      '#type' => 'markup',
      '#markup' => '<p>This template will be used when bookings are cancelled</p>' .
        '<p>Parameters: %datetime% | %duration% | %group% | %room% | %occupancy% | %description% | %name% | %email% | %phone%</p>'
    ),
  );
  $form['email_booking_cancel_set']['email_booking_cancel_address'] = array(
    '#type' => 'textfield',
    '#title' => "Reply Email Address",
    '#required' => TRUE,
    '#default_value' => variable_get('studyroom_email_booking_cancel_address', '')
  );
  $form['email_booking_cancel_set']['email_booking_cancel_subject'] = array(
    '#type' => 'textfield',
    '#title' => "Email Subject",
    '#required' => TRUE,
    '#default_value' => variable_get('studyroom_email_booking_cancel_subject', '')
  );
  $form['email_booking_cancel_set']['email_booking_cancel'] = array(
    '#type' => 'textarea',
    '#title' => 'Email Body Template',
    '#required' => TRUE,
    '#rows' => 12,
    '#maxlength' => '500',
    '#maxlength_js' => TRUE,
    '#attributes' =>array(
      'maxlength_js_label' => '@remaining characters left.',
    ),
    '#default_value' => variable_get('studyroom_email_booking_cancel', ''),
    '#description' => 'Enter the email copy, the maximum number of characters allowed is 500.',
  );

  $form['email_booking_reminder_set'] = array(
    '#type' => 'fieldset',
    '#title' => 'Booking Reminder',

    'instructions' => array(
      '#type' => 'markup',
      '#markup' => '<p>This template will be used for booking reminders</p>' .
        '<p>Parameters: %datetime% | %duration% | %group% | %room% | %occupancy% | %description% | %name% | %email% | %phone%</p>'
    ),
  );
  $form['email_booking_reminder_set']['email_booking_reminder_cron_days'] = array(
    '#type' => 'select',
    '#options' => array(
      '1' => '1',
      '2' => '2',
      '3' => '3',
      '4' => '4',
      '5' => '5',
      '6' => '6',
      '7' => '7',
      '8' => '8',
      '9' => '9',
      '10' => '10',
      '11' => '11',
      '12' => '12',
      '13' => '13',
      '14' => '14',
      '15' => '15',
      '16' => '16',
      '17' => '17',
      '18' => '18',
      '19' => '19',
      '20' => '20',
    ),
    '#title' => "Day(s) before event to send reply notification",
    '#required' => TRUE,
    '#default_value' => variable_get('studyroom_email_booking_reminder_cron_days', '')
  );
  $form['email_booking_reminder_set']['email_booking_reminder_cron_time'] = array(
    '#type' => 'select',
    '#options' => array(
      '12 AM' => '12 AM',
      '1 AM' => '1 AM',
      '2 AM' => '2 AM',
      '3 AM' => '3 AM',
      '4 AM' => '4 AM',
      '5 AM' => '5 AM',
      '6 AM' => '6 AM',
      '7 AM' => '7 AM',
      '8 AM' => '8 AM',
      '9 AM' => '9 AM',
      '10 AM' => '10 AM',
      '11 AM' => '11 AM',
      '12 PM' => '12 PM',
      '1 PM' => '1 PM',
      '2 PM' => '2 PM',
      '3 PM' => '3 PM',
      '4 PM' => '4 PM',
      '5 PM' => '5 PM',
      '6 PM' => '6 PM',
      '7 PM' => '7 PM',
      '8 PM' => '8 PM',
      '9 PM' => '9 PM',
      '10 PM' => '10 PM',
      '11 PM' => '11 PM',
    ),
    '#title' => "Time of day to send reply notification",
    '#required' => TRUE,
    '#default_value' => variable_get('studyroom_email_booking_reminder_cron_time', '')
  );
  $form['email_booking_reminder_set']['email_booking_reminder_address'] = array(
    '#type' => 'textfield',
    '#title' => "Bookings Reminder Reply Email Address",
    '#required' => TRUE,
    '#default_value' => variable_get('studyroom_email_booking_reminder_address', '')
  );
  $form['email_booking_reminder_set']['email_booking_reminder_subject'] = array(
    '#type' => 'textfield',
    '#title' => "Email Subject",
    '#required' => TRUE,
    '#default_value' => variable_get('studyroom_email_booking_reminder_subject', '')
  );
  $form['email_booking_reminder_set']['email_booking_reminder'] = array(
    '#type' => 'textarea',
    '#title' => 'Email Body Template',
    '#required' => TRUE,
    '#rows' => 12,
    '#maxlength' => '500',
    '#maxlength_js' => TRUE,
    '#attributes' =>array(
      'maxlength_js_label' => '@remaining characters left.',
    ),
    '#default_value' => variable_get('studyroom_email_booking_reminder', ''),
    '#description' => 'Enter the email copy, the maximum number of characters allowed is 500.',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save Email Templates'
  );

  return $form;
}

function studyroom_email_form_validate(&$form, &$form_state) {
  /*
  if ($form_state['values']['email_booking_create'] == '') {
    form_set_error('title', t('Please enter the text for booking creation.'));
  }
    if ($form_state['values']['email_booking_cancel'] == '') {
    form_set_error('title', t('Please enter the text for booking cancellation.'));
  }
    if ($form_state['values']['email_booking_reminder'] == '') {
    form_set_error('title', t('Please enter the text for booking reminders.'));
  }
  */
}

function studyroom_email_form_submit($form, $form_state) {
  variable_set('studyroom_email_booking_create_address', $form_state['values']['email_booking_create_address']);
  variable_set('studyroom_email_booking_cancel_address', $form_state['values']['email_booking_cancel_address']);
  variable_set('studyroom_email_booking_reminder_address', $form_state['values']['email_booking_reminder_address']);

  variable_set('studyroom_email_booking_create_subject', $form_state['values']['email_booking_create_subject']);
  variable_set('studyroom_email_booking_cancel_subject', $form_state['values']['email_booking_cancel_subject']);
  variable_set('studyroom_email_booking_reminder_subject', $form_state['values']['email_booking_reminder_subject']);

  variable_set('studyroom_email_booking_create', $form_state['values']['email_booking_create']);
  variable_set('studyroom_email_booking_cancel', $form_state['values']['email_booking_cancel']);
  variable_set('studyroom_email_booking_reminder', $form_state['values']['email_booking_reminder']);

  variable_set('studyroom_email_booking_reminder_cron_days', $form_state['values']['email_booking_reminder_cron_days']);
  variable_set('studyroom_email_booking_reminder_cron_time', $form_state['values']['email_booking_reminder_cron_time']);

  drupal_set_message('Email Settings Saved');
}