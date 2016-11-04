<?php

function hf_stacks_pages_add($form, $form_state) {
  $form['page_name'] = array(
    '#type' => 'textfield',
    '#title' => 'Landing Page Name',
    '#description' => 'Enter a name for the page.',
    '#required' => TRUE
  );

  $form['page_path'] = array(
    '#type' => 'textfield',
    '#title' => 'Landing Page Path',
    '#description' => 'Enter a page path or URL.',
    '#required' => TRUE
  );

  $form['page_task'] = array(
    '#type' => 'hidden',
    '#default_value' => 'page',
    '#required' => TRUE
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Add Landing Page'
  );

  return $form;
}

function hf_stacks_pages_add_validate($form, &$form_state) {
  $page = (object)$form_state['values'];

  if (!trim($page->page_name)) {
    form_set_error('title', 'Name cannot be empty.');
  }
  if (!trim($page->page_path)) {
    form_set_error('title', 'Path cannot be empty.');
  }
  if (!trim($page->page_task)) {
    form_set_error('title', 'Task cannot be empty.');
  }
}

function hf_stacks_pages_add_submit($form, &$form_state) {
  require_once drupal_get_path('module', 'ctools') . '/page_manager/plugins/tasks/page.inc';
  module_load_include('inc','pathauto','pathauto');

  $uuid = ctools_uuid_generate();

  $name = '';
  $machine_name = '';
  $path = '';
  $task = '';

  $values = $form_state['values'];

  if (isset($values['page_name'])) {
    $name = $values['page_name'];
    $machine_name = strtolower($name);
    $machine_name = preg_replace('@[^a-z0-9_]+@','_',$machine_name);
  }
  if (isset($values['page_path'])) {
    $path = $values['page_path'];
    $path = pathauto_cleanstring($path);
  }
  if (isset($values['page_task'])) {
    $task = $values['page_task'];
  }

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = $machine_name;
  $page->task = 'page';
  $page->admin_title = $name;
  $page->admin_description = '';
  $page->path = $path;
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_'.$machine_name.'__panel';
  $handler->task = 'page';
  $handler->subtask = $machine_name;
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'twocol_stacked';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = $uuid;
  $display->content = array();
  $display->panels = array();
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;

  // Create an empty cache.
  $cache = new stdClass();

  // Add the page to the cache.
  page_manager_page_new_page_cache($page, $cache);

  // Save the cache (which saves the page).
  page_manager_save_page_cache($cache);

  drupal_set_message('Landing page added');
  drupal_goto('admin/landing-pages');
}

function hf_stacks_pages_edit($form, $form_state) {
  $path = explode("/", current_path());
  $pid = $path[3];

  $title = '';
  $name = '';
  $path = '';
  $task = '';

  if (!empty ($pid)) {
    $pages = db_select('page_manager_pages', 'p')
      ->fields('p', array('pid'))
      ->fields('p', array('name'))
      ->fields('p', array('task'))
      ->fields('p', array('path'))
      ->fields('p', array('admin_title'))
      ->condition('p.pid', $pid, '=')
      ->execute()
      ->fetchAll(); // returns an indexed array

    foreach ($pages as $row) {
      $title = $row->admin_title;
      $name = $row->name;
      $path = $row->path;
      $task = $row->task;
    }
  }

  $form['page_name'] = array(
    '#type' => 'textfield',
    '#title' => 'Landing Page Name',
    '#description' => 'Enter a name for the page.',
    '#required' => TRUE,
    '#default_value' => $title
  );

  $form['page_path'] = array(
    '#type' => 'textfield',
    '#title' => 'Landing Page Path',
    '#description' => 'Enter a page path or URL.',
    '#required' => TRUE,
    '#default_value' => $path
  );

  $form['pid'] = array(
    '#type' => 'hidden',
    '#required' => TRUE,
    '#default_value' => $pid
  );

  $form['machine_name'] = array(
    '#type' => 'hidden',
    '#required' => TRUE,
    '#default_value' => $name
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Update Landing Page'
  );

  return $form;
}

function hf_stacks_pages_edit_validate($form, &$form_state) {
  $page = (object)$form_state['values'];

  if (!trim($page->page_name)) {
    form_set_error('title', 'Name cannot be empty.');
  }
  if (!trim($page->page_path)) {
    form_set_error('title', 'Path cannot be empty.');
  }
}

function hf_stacks_pages_edit_submit($form, &$form_state) {
  require_once drupal_get_path('module', 'ctools') . '/page_manager/plugins/tasks/page.inc';
  module_load_include('inc','pathauto','pathauto');

  $pid = '';
  $machine_name = '';
  $name = '';
  $path = '';

  $values = $form_state['values'];

  if (isset($values['pid'])) {
    $pid = $values['pid'];
  }
  if (isset($values['machine_name'])) {
    $machine_name = $values['machine_name'];
  }
  if (isset($values['page_name'])) {
    $name = $values['page_name'];
  }
  if (isset($values['page_path'])) {
    $path = $values['page_path'];
    $path = pathauto_cleanstring($path);
  }

  // update page manager page
  db_update('page_manager_pages')
    ->fields(array(
      "admin_title" => $name,
      "path" => pathauto_cleanstring($path)
    ))
    ->condition('pid', $pid, '=')
    ->execute();

  $page = page_manager_page_load($machine_name);

  // Create an empty cache.
  $cache = new stdClass();

  // Add the page to the cache.
  page_manager_page_new_page_cache($page, $cache);

  // Save the cache (which saves the page).
  page_manager_save_page_cache($cache);

  drupal_set_message('Landing page updated');
  drupal_goto('admin/landing-pages');
}

function hf_stacks_pages_delete($form, &$form_state) {
  $path = explode("/", current_path());
  $pid = $path[3];

  $name = '';

  if (!empty ($pid)) {
    $pages = db_select('page_manager_pages', 'p')
      ->fields('p', array('name'))
      ->condition('p.pid', $pid, '=')
      ->execute()
      ->fetchAll(); // returns an indexed array

    foreach ($pages as $row) {
      $name = $row->name;
    }
  }

  if (($name == 'homepage') || ($name == 'multi_search') || ($name == 'multisearch') || ($name == 'bento')) {
    $form['header_message'] = array(
      '#markup' => '<p>This page cannot be deleted.</p>'
    );
  } else {
    $form['header_message'] = array(
      '#markup' => '<p>Are you sure you want to delete this landing page?</p>'
    );

    $form['pid'] = array(
      '#type' => 'hidden',
      '#default_value' => $pid
    );

    $form['page_name'] = array(
      '#type' => 'hidden',
      '#default_value' => $name
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
      '#submit' => array('hf_stacks_pages_delete_cancel'),
    );
  }

  return $form;
}

function hf_stacks_pages_delete_submit($form, &$form_state) {
  require_once drupal_get_path('module', 'ctools') . '/page_manager/plugins/tasks/page.inc';

  $values = $form_state['values'];

  if (isset($values['page_name'])) {
    $name = $values['page_name'];
    $page = page_manager_page_load($name);
    page_manager_page_delete($page);
  }

  drupal_set_message('Landing page deleted');
  drupal_goto('admin/landing-pages');
}

function hf_stacks_pages_delete_cancel(){
  drupal_goto('admin/landing-pages');
}