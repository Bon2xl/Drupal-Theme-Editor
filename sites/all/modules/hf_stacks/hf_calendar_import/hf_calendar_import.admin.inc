<?php
/**
 * Form for importing events into stacks from an ical url.
 * @param $form
 * @param $form_state
 * @return mixed
 */
function hf_calendar_import_form($form, &$form_state) {

  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => 'Calendar (iCal) URL',
    '#description' => 'Please insert an iCal URL to import events. Please make sure it is <b>shared publicly</b>.',
    '#required' => TRUE,
    '#maxlength' => 1024,
  );

  //Event Type
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Event Type'),
    '#options' => get_dropdown_selections('type'),
    '#default_value' => (isset($query_params['filter'])) ? $query_params['filter'] : '',
  );

  //Event Category
  $form['category'] = array(
    '#type' => 'select',
    '#title' => t('Event Category'),
    '#options' => get_dropdown_selections('category'),
    '#default_value' => (isset($query_params['filter'])) ? $query_params['filter'] : '',
  );

  //Event Topic
  $form['topic'] = array(
    '#type' => 'select',
    '#title' => t('Event Topic'),
    '#options' => get_dropdown_selections('topic'),
    '#default_value' => (isset($query_params['filter'])) ? $query_params['filter'] : '',
  );
  //Event Topic
  $form['location'] = array(
    '#type' => 'select',
    '#title' => t('Location'),
    '#options' => get_dropdown_selections('branch'),
    '#default_value' => (isset($query_params['filter'])) ? $query_params['filter'] : '',
  );

  $form['delete'] = array(
    '#type' => 'checkboxes',
    '#options' => array(1 => "Remove all current events before importing"),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit URL'
  );
  return $form;
}

/**
 * Implements hook_form_submit()
 * @param $form
 * @param $form_state
 */
function hf_calendar_import_form_submit($form, $form_state) {
  //dpm("hello");
  if($form_state['values']['type'] === '') {
    $type = null;
  } else {
    $type = $form_state['values']['type'];
  }

  if($category = $form_state['values']['category'] === '') {
    $category = null;
  } else {
    $category = $form_state['values']['category'];
  }

  if($topic = $form_state['values']['topic'] === '') {
    $topic = null;
  } else {
    $topic = $form_state['values']['topic'];
  }

  if($form_state['values']['location'] === '') {
    $location = null;
  } else {
    $location = $form_state['values']['location'];
  }

  if($form_state['values']['delete'][1] == 0) {
    //dpm('hello2');
    hf_calendar_import_load($form_state['values']['url'], $type, $category, $topic, $location);
  } else {
    //dpm("delete");
    drupal_goto('admin/config/stacks/calendarimport/delete', array('query' => array(
      'url' => $form_state['values']['url'],
      'location' => $location,
      'type' => $type,
      'category' => $category,
      'topic' => $topic
    )));
  }
}


/**
 * Delete form that will remove all current existing events in stacks before importing events from ical.
 * @param $form
 * @param $form_state
 * @return mixed
 */
function hf_calendar_import_delete($form, &$form_state) {
  $params = drupal_get_query_parameters();
  //dpm($params);

  $form['header_message'] = array(
    '#markup' => '<p>Are you sure you want to delete this landing page?</p>'
  );

  $form['type'] = array(
    '#type' => 'hidden',
    '#default_value' => $params['type']
  );

  $form['location'] = array(
    '#type' => 'hidden',
    '#default_value' => $params['location']
  );

  $form['category'] = array(
    '#type' => 'hidden',
    '#default_value' => $params['category']
  );

  $form['topic'] = array(
    '#type' => 'hidden',
    '#default_value' => $params['topic']
  );

  $form['url'] = array(
    '#type' => 'hidden',
    '#default_value' => $params['url']
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Delete Page'
  );

  $form['cancel'] = array(
    '#type' => 'button',
    '#value' => t('Cancel'),
    '#weight' => 20,
    '#executes_submit_callback' => TRUE,
    '#submit' => array('hf_calendar_import_delete_cancel'),
  );

  return $form;
}

/**
 * Implements hook_form_submit()
 * @param $form
 * @param $form_state
 */
function hf_calendar_import_delete_submit($form, &$form_state) {
  //dpm("submit");
  $values = $form_state['values'];

  $existing_events = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('type', 'event', '=')
    ->execute();

  foreach($existing_events as $event) {
    node_delete($event->nid);
  }

  drupal_set_message('Removed all existing events.');
  hf_calendar_import_load($values['url'], $values['type'], $values['category'], $values['topic'], $values['location']);
  drupal_goto('admin/config/stacks/calendarimport');
}

/**
 * Implements hook_form_delete()
 *
 */
function hf_calendar_import_delete_cancel() {
  drupal_goto('admin/config/stacks/calendarimport');
}

/**
 * Queries the database to grab existing selections for dropdown lists.
 *
 * @param $type conditional passed in to deteremine which drop down to populate
 * @return array the list of selections for dropdown list
 */
function get_dropdown_selections($type) {
  if($type != 'branch') {
    $query = db_select('taxonomy_vocabulary', 'vocab');
    $query->join('taxonomy_term_data', 'name', 'name.vid = vocab.vid');
    $query->fields('name', array('name', 'tid'));
    switch($type) {
      case 'type':
        $query->condition('machine_name', 'event_type', '=');
        break;
      case 'category':
        $query->condition('machine_name', 'event_category', '=');
        break;
      case 'topic':
        $query->condition('machine_name', 'course', '=');
        break;
    }
    $results = $query->execute()->fetchAll();

    //dpm($categories);
    $options = array('' => t('None'));
    foreach($results as $value) {
      $options[$value->tid] = $value->name;
    }
  } else {
    $query = db_select('node', 'n');
    $query->fields('n', array('title', 'nid'));
    $query->condition('type', 'library_branch', '=');

    $results = $query->execute()->fetchAll();

    //dpm($categories);
    $options = array('' => t('None'));
    foreach($results as $value) {
      $options[$value->nid] = $value->title;
    }
  }

  return $options;
}
