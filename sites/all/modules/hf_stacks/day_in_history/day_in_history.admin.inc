<?php
/**
 * @file
 * Administration page callbacks for the Day In History module.
 */

/**********************************************************
   Copyright (c) : Hybrid Forge 2010-12 . All Rights Reserved.
   Author: James Lam
   Modified by: Jeremy Smereka
   Date: 2012-08-23
 **********************************************************/

/**
 * List Form
 */
function day_in_history_list() {
  $form = null;

  // get all events
  $events = _day_in_history_get_events();

  foreach ($events as $event) {
    $form['date'][$event->event_id] = array(
      '#type' => 'markup',
      '#markup' => sprintf("%04d-%02d-%02d", $event->year, $event->month, $event->day)
    );
    $form['event_title'][$event->event_id] = array(
      '#type' => 'markup',
      '#markup' => $event->event_title
    );
    //$form['description'][$event->event_id] = array('#value' => $event->description);
    $form['title'][$event->event_id] = array(
      '#type' => 'markup',
      '#markup' => $event->title
    );
    $form['author'][$event->event_id] = array(
      '#type' => 'markup',
      '#markup' => $event->author
    );
    $form['isbn'][$event->event_id] = array(
      '#type' => 'markup',
      '#markup' => $event->isbn
    );
    $form['edit'][$event->event_id] = array(
      '#type' => 'markup',
      '#markup' => l(t('edit'), "admin/content/day_in_history/edit/{$event->event_id}", array('query' => array('destination' => 'admin/content/day_in_history/list')))
    ); // a link that goes to edit, and then returns to list after saving edit
    $form['delete'][$event->event_id] = array(
      '#type' => 'markup',
      '#markup' => l(t('delete'), "admin/content/day_in_history/delete/{$event->event_id}", array('query' => array('destination' => 'admin/content/day_in_history/list')))
    );
  }

  return $form;
}

/**
 * Theme List Form
 */
function theme_day_in_history_list($variables) {
  global $base_url;

  $form = $variables[""];
  $has_lists = isset($form['title']) && is_array($form['title']);
  $select_header = $has_lists ? theme('table_select_header_cell') : '';
  $header = array(/* $select_header , */ t('Date'), t('Event Title'), /*t('Description'),*/ t('Title'), t('Author'), t('ISBN'), array('data' => t('Operations'), 'colspan' => 2));

  // adding foundation & dashboard css for modal
  drupal_add_js(drupal_get_path('module', 'hf_dashboard').'/js/jquery-ui.js');
  drupal_add_js(drupal_get_path('module', 'hf_dashboard').'/js/foundation.min.js');
  drupal_add_css( drupal_get_path('module', 'hf_dashboard').'/css/hf_dashboard.css' );

  $rows = array();
  $output = '';

  include ("sites/all/modules/hf_stacks/hf_dashboard/includes/hf_modal_this_day.inc");

  if ($has_lists) {
    $output .= '<a href="#" data-reveal-id="modal-history" class="button modal-btn">More Help</a><div class="view-header"><a href="/node/add/day_in_history" class="btn-add-new">+ Add New</a></div><p>All events are listed below.</p><script>jQuery(document).foundation();</script>';


    foreach (element_children($form['title']) as $key) {
      $row = array();
      //$row[] = drupal_render($form['lists'][$key]);
      $row[] = drupal_render($form['date'][$key]);
      $row[] = drupal_render($form['event_title'][$key]);
      //$row[] = drupal_render($form['description'][$key]);
      $row[] = drupal_render($form['title'][$key]);
      $row[] = drupal_render($form['author'][$key]);
      $row[] = drupal_render($form['isbn'][$key]);
      /* $row[] = drupal_render($form['block_id'][$key]); */
      $row[] = drupal_render($form['edit'][$key]);
      $row[] = drupal_render($form['delete'][$key]);
      $rows[] = $row;
    }
  }
  else {
    $rows[] = array(array('data' => t('No lists available.') . ' ' . l(t('Create Event'), 'node/add/day_in_history'), 'colspan' => '5'));
  }

  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'id' => 'table_day_in_history_list'));
	$output .= '<script type="text/javascript">jQuery("#table_day_in_history_list tr td:first").addClass("nowrap"); </script>';
  //$output .= drupal_render_children($form);

  return $output;
}

/**
 * Implementation of Hook_Form()
 */
function day_in_history_form($form, &$form_state, $op, $event) {
  if ($op == 'add') {
    $event['year'] = date('Y');
    $event['month'] = date('m');
    $event['day'] = date('d');
  }
  else {
    // do something
  }

  drupal_set_title($event['title']);

  $form['event_id'] = array('#type' => 'value', '#value' => $event['event_id']);

  $form['year'] = array(
    '#type' => 'textfield',
    '#title' => t('Year'),
    '#default_value' => $event['year'],
    '#size' => 10,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => 'Date of the historical event.',
  );
  $form['month'] = array(
    '#type' => 'textfield',
    '#title' => t('Month'),
    '#default_value' => $event['month'],
    '#size' => 10,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => 'Date of the historical event.',
  );
  $form['day'] = array(
    '#type' => 'textfield',
    '#title' => t('Day'),
    '#default_value' => $event['day'],
    '#size' => 10,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => 'Date of the historical event.',
  );

  $form['event_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Event Title'),
    '#default_value' => $event['event_title'],
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => 'Event Title for the historical event.',
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $event['description'],
    '#size' => 60,
    '#required' => TRUE,
    '#description' => 'Description for the historical event.',
  );

  $form['isbn'] = array(
    '#type' => 'textfield',
    '#title' => t('ISBN'),
    '#default_value' => $event['isbn'],
    '#size' => 20,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => 'ISBN of associated book for historical event.',
  );

  if (module_exists('patron_login')){
    $form['bc_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Bib Record ID'),
      '#default_value' => $event['bc_id'],
      '#size' => 20,
      '#maxlength' => 255,
      '#required' => FALSE,
      '#description' => 'Bib Record ID (Control Number) of associated book for historical event.',
    );
  }

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $event['title'],
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => 'Title of associated book for historical event.',
  );

  $form['author'] = array(
    '#type' => 'textfield',
    '#title' => t('Author'),
    '#default_value' => $event['author'],
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => FALSE,
    '#description' => 'Author of associated book for historical event.',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => ($op == 'add') ? t('Save New') : t('Update Item'),
  );

  return $form;
}

/**
 * Implementation of Hook_Form_Validate()
 */
function day_in_history_form_validate($form, &$form_state) {
  $form_state['values']['isbn'] = preg_replace('/[^\dx]/i', '', $form_state['values']['isbn']); // only allow digits or X in ISBN
  $event = (object)$form_state['values'];

  if (!trim($event->title)) {
    form_set_error('title', 'Title cannot be empty.');
  }
  if (strlen($event->isbn) > 13) {
    form_set_error('isbn', 'ISBN cannot be longer than 13 digits.');
  }
}

/**
 * Implementation of Hook_Form_Submit()
 */
function day_in_history_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  $event = new day_in_history_event();
  $new = true;
  if ($values['event_id']) {
    $event->load($values['event_id']);
    $new = false;
  }

  $event->exchangeArray($values);
  $event->save();

  $success = TRUE;
  if ($success) {
    if ($new) {
      drupal_set_message("Successfully created event {$event['title']} [{$event['isbn']}].");
			drupal_goto('admin/content/day_in_history');
    } else {
      drupal_set_message("Successfully updated event {$event['title']} [{$event['isbn']}].");
    }
  }
  else {
    drupal_set_message("Unable to save event {$event['title']} [{$event['isbn']}].");
  }
}

/**
 * Delete Confirmation Form
 */
function day_in_history_delete($form, &$form_state, $event) {
  $form['event_id'] = array('#type' => 'value', '#value' => $event['event_id']);
  $form['title'] = array('#type' => 'value', '#value' => $event['title']);

  $form[]['#markup'] = "<p>Would you like to continue with deleting DATE {$event['title']} ({$event['isbn']})?</p>";

  $form['submit'] = array( '#type' => 'submit', '#value' => t('Delete'));

  $form[]['#markup'] = l(t('Cancel'), "admin/content/day_in_history");

  return $form;
}

/**
 * Delete Confirmation Form Submit
 */
function day_in_history_delete_submit($form, &$form_state) {
  $event_id = $form_state['values']['event_id'];
  $title = $form_state['values']['title'];
  db_delete('day_in_history_events')
  ->condition('event_id', $event_id)
  ->execute();
  drupal_set_message('Deleted event with book ' . $title . '.');
}

//
// -- Private Functions
//

/**
 * Private: Get Events from DB
 */
function _day_in_history_get_events() {
  $events = array();

  $result_set = db_query('SELECT * FROM {day_in_history_events} ORDER BY month, day, year');

  if (!$result_set) _day_in_history_die(__LINE__, __FUNCTION__, __FILE__);

  foreach ($result_set as $result) {
    $events[] = $result;
  }

  return $events;
}

// vim: ts=2 sw=2 et syntax=php foldmethod=marker
