<?php

function stacks_rss_add($form, $form_state) {
  $form['rss_name'] = array(
    '#type' => 'textfield',
    '#title' => 'RSS Feed Name',
    '#description' => 'Enter a name for the RSS Feed.',
    '#required' => TRUE
  );

  $form['rss_url'] = array(
    '#type' => 'textfield',
    '#title' => 'RSS Feed URL',
    '#description' => 'Enter a URL for the feed.',
    '#required' => TRUE
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Add RSS Feed'
  );

  return $form;
}

function stacks_rss_add_validate($form, &$form_state) {
  $rss = (object)$form_state['values'];

  if (!trim($rss->rss_name)) {
    form_set_error('title', 'Name cannot be empty.');
  }
  if (!trim($rss->rss_url)) {
    form_set_error('title', 'URL cannot be empty.');
  }
}

function stacks_rss_add_submit($form, &$form_state) {
  require_once drupal_get_path('module', 'ctools') . '/page_manager/plugins/tasks/page.inc';
  module_load_include('inc','pathauto','pathauto');

  $id = '';
  $name = '';
  $url = '';

  $values = $form_state['values'];

  if (isset($values['rss_name'])) {
    $name = $values['rss_name'];

    $id = $values['rss_name'];
    $id = strtolower($id);
    $id = pathauto_cleanstring($id);
  }
  if (isset($values['rss_url'])) {
    $url = $values['rss_url'];
    $url = strtolower($url);
  }

  $mapping = array(
    'name' => $name,
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => TRUE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
        'auto_scheme' => 'http',
        'accept_invalid_cert' => FALSE,
      )
    ),
    'parser' => array(
      'plugin_key' => 'FeedsSyndicationParser',
      'config' => array()
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
        'mappings' => Array(
          0 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'url',
            'target' => 'field_rss_link:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          2 => array(
            'source' => 'author_name',
            'target' => 'field_rss_source',
            'unique' => FALSE,
            'language' => 'und',
          ),
          3 => array(
            'source' => 'timestamp',
            'target' => 'field_rss_timestamp:start',
            'unique' => FALSE,
            'language' => 'und',
          ),
        ),
        'insert_new' => '1',
        'update_existing' => '0',
        'update_non_existent' => 'skip',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'rss_item',
        'language' => 'und',
      )
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => 1800,
    'expire_period' => 3600,
    'import_on_create' => TRUE,
    'process_in_background' => 1,
  );

  $map = serialize($mapping);

  // create the RSS feed with all of the config options
  db_insert('feeds_importer') // Table name no longer needs {}
  ->fields(array(
    'id' => $id,
    'config' => $map
  ))
    ->execute();

  // set the RSS feed URL
  $feedSource = feeds_source($id);
  $configer = $feedSource->getConfig();
  $configer['FeedsHTTPFetcher']['source'] = $url;
  $feedSource->setConfig($configer);
  $feedSource->save();

  drupal_set_message('RSS feed added');
  drupal_goto('admin/rss-feeds');
}

function stacks_rss_edit($form, $form_state) {
  $path = explode("/", current_path());
  $fid = $path[3];

  $id = '';
  $config = '';

  if (!empty ($fid)) {
    $rss = db_select('feeds_importer', 'f')
      ->fields('f', array('id'))
      ->fields('f', array('config'))
      ->condition('f.id', $fid, '=')
      ->execute()
      ->fetchAll(); // returns an indexed array

    foreach ($rss as $row) {
      $id = $row->id;
      $config = $row->config;
    }
  }

  $feedSource = feeds_source($id);
  $configer = $feedSource->getConfig();

  $url = $configer['FeedsHTTPFetcher']['source'];

  $form['rss_name'] = array(
    '#type' => 'textfield',
    '#title' => 'RSS Feed Name',
    '#description' => 'Enter a name for the feed.',
    '#required' => TRUE,
    '#default_value' => unserialize($config)['name']
  );

  $form['rss_url'] = array(
    '#type' => 'textfield',
    '#title' => 'RSS Feed Config',
    '#description' => 'Enter a URL for the feed.',
    '#required' => TRUE,
    '#default_value' => $url
  );

  $form['rss_id'] = array(
    '#type' => 'hidden',
    '#required' => TRUE,
    '#default_value' => $id
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Update RSS Feed'
  );

  return $form;
}

function stacks_rss_edit_validate($form, &$form_state) {
  $rss = (object)$form_state['values'];

  if (!trim($rss->rss_name)) {
    form_set_error('title', 'Name cannot be empty.');
  }
  if (!trim($rss->rss_url)) {
    form_set_error('title', 'URL cannot be empty.');
  }
}

function stacks_rss_edit_submit($form, &$form_state) {
  require_once drupal_get_path('module', 'ctools') . '/page_manager/plugins/tasks/page.inc';
  module_load_include('inc','pathauto','pathauto');

  $id = '';
  $name = '';
  $url = '';

  $values = $form_state['values'];

  if (isset($values['rss_name'])) {
    $name = $values['rss_name'];

    $id = $values['rss_name'];
    $id = strtolower($id);
    $id = pathauto_cleanstring($id);
  }
  if (isset($values['rss_url'])) {
    $url = $values['rss_url'];
    $url = strtolower($url);
  }

  $mapping = array(
    'name' => $name,
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
        'auto_scheme' => 'http',
        'accept_invalid_cert' => FALSE,
      )
    ),
    'parser' => array(
      'plugin_key' => 'FeedsSyndicationParser',
      'config' => array()
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
        'mappings' => Array(
          0 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => 1,
            'language' => 'und'
          ),
          1 => array(
            'source' => 'url',
            'target' => 'field_rss_link:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          2 => array(
            'source' => 'author_name',
            'target' => 'field_rss_source',
            'unique' => FALSE,
            'language' => 'und',
          ),
          3 => array(
            'source' => 'timestamp',
            'target' => 'field_rss_timestamp:start',
            'unique' => FALSE,
            'language' => 'und',
          ),
        ),
        'insert_new' => '1',
        'update_existing' => '0',
        'update_non_existent' => 'skip',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'rss_item',
        'language' => 'und',
      )
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => 1800,
    'expire_period' => 3600,
    'import_on_create' => TRUE,
    'process_in_background' => 1,
  );

  $map = serialize($mapping);

  // create the RSS feed with all of the config options
  db_update('feeds_importer') // Table name no longer needs {}
  ->fields(array(
    'id' => $id,
    'config' => $map
  ))
    ->condition('id', $id, '=')
    ->execute();

  // set the RSS feed URL
  $feedSource = feeds_source($id);
  $configer = $feedSource->getConfig();
  $configer['FeedsHTTPFetcher']['source'] = $url;
  $feedSource->setConfig($configer);
  $feedSource->save();

  drupal_set_message('RSS feed updated');
  drupal_goto('admin/rss-feeds');
}

function stacks_rss_delete($form, &$form_state) {
  $path = explode("/", current_path());
  $pid = $path[3];

  $form['header_message'] = array(
    '#markup' => '<p>Are you sure you want to delete this RSS feed?</p>'
  );

  $form['id'] = array(
    '#type' => 'hidden',
    '#default_value' => $pid
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Delete Feed'
  );

  $form['cancel'] = array(
    '#type' => 'button',
    '#value' => t('Cancel'),
    '#weight' => 20,
    '#executes_submit_callback' => TRUE,
    '#submit' => array('stacks_rss_delete_cancel'),
  );

  return $form;
}

function stacks_rss_delete_submit($form, &$form_state) {
  require_once drupal_get_path('module', 'ctools') . '/page_manager/plugins/tasks/page.inc';

  $values = $form_state['values'];

  if (isset($values['id'])) {
    $id = $values['id'];

    // delete the RSS feed
    db_delete('feeds_importer')
      ->condition('id', $id)
      ->execute();
  }

  drupal_set_message('RSS feed deleted');
  drupal_goto('admin/rss-feeds');
}

function stacks_rss_delete_cancel(){
  drupal_goto('admin/rss-feeds');
}