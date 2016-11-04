<?php

/**
 * Form for Adding a Tile to the Dashboard Screen
 * @param $form
 * @param $form_state
 * @return mixed
 */
function hf_tiles_add_tile($form, &$form_state) {
  global $user;
  drupal_add_css('https://cdnjs.cloudflare.com/ajax/libs/foundicons/3.0.0/foundation-icons.min.css', array('type' => 'external'));
  drupal_add_css(base_path().drupal_get_path('theme', 'hfstacks').'/assets/bower_components/components-font-awesome/css/font-awesome.min.css', array('type' => 'external'));
  $icons = _hf_tiles_query_icons();
  $roles = _hf_tiles_get_roles();


  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Tile Name',
    '#required' => TRUE,
  );

  $form['path_url'] = array(
    '#type' => 'textfield',
    '#description' => 'Enter a URL path that the tile will direct a user to, e.g. "/admin/content/callouts"',
    '#title' => 'URL',
    '#required' => TRUE,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => 'Help Text',
    '#required' => TRUE,
    '#maxlength' => '250',
    '#maxlength_js' => TRUE,
    '#attributes' =>array(
      'maxlength_js_label' => '@remaining characters left.',
    ),
    '#description' => 'Enter a description of the tile, and it\'s purpose, the maximum number of characters allowed is 250.',
  );

  if($user->uid == 1) {
    $form['help_url'] = array(
      '#type' => 'textfield',
      '#title' => 'Help Manual URL',
      '#description' => '<i>Super Admins Only:</i> Enter a URL path that will direct a user to specific portion of the stacks manual, e.g. "http://help.stacksdiscovery.com/#Database_Listings"',
      '#required' => FALSE,
    );
  }

  $form['icon'] = array(
    '#type' => 'radios',
    '#title' => 'Icon',
    '#description' => 'Select an icon for this Tile.',
    '#options' => $icons,
    '#required' => TRUE,
  );

  $form['user_role'] = array(
    '#type' => 'checkboxes',
    '#title' => 'Select which users can view this Tile',
    '#options' => $roles,
    '#default_value' => ''
  );

  if($user->uid == 1) {
    $form['locked'] = array(
      '#type' => 'checkbox',
      '#title' => 'Lock Tile',
      '#description' => '<i>Super Admins Only:</i> Lock this tile so only super admins are able to edit/delete tile.',
      '#default_value' => 0,
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Add Tile'
  );

  return $form;
}

/**
 * Form for Editing a Tile.
 * @param $form
 * @param $form_state
 * @return mixed
 */
function hf_tiles_edit_tile($form, &$form_state, $tile_id) {
  global $user;
  drupal_add_css('https://cdnjs.cloudflare.com/ajax/libs/foundicons/3.0.0/foundation-icons.min.css', array('type' => 'external'));
  drupal_add_css(base_path().drupal_get_path('theme', 'hfstacks').'/assets/bower_components/components-font-awesome/css/font-awesome.min.css', array('type' => 'external'));
  $icons = _hf_tiles_query_icons();
  $roles = _hf_tiles_get_roles();
  $tile = _hf_tiles_get_existing_tile($tile_id);

  $user_role = unserialize($tile['user_role']);
  $user_role = array_filter($user_role);
  $user_role = array_keys($user_role);

  $form['tile_id'] = array(
    '#type' => 'value',
    '#value' => $tile_id,
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Tile Name',
    '#required' => TRUE,
    '#default_value' => $tile['name'],
  );

  $form['path_url'] = array(
    '#type' => 'textfield',
    '#description' => 'Enter a URL path that the tile will direct a user to, e.g. "/admin/content/callouts"',
    '#title' => 'Path URL',
    '#required' => TRUE,
    '#default_value' => $tile['path_url'],
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => 'Help Text',
    '#required' => TRUE,
    '#default_value' => $tile['description'],
    '#maxlength' => '250',
    '#maxlength_js' => TRUE,
    '#attributes' =>array(
      'maxlength_js_label' => '@remaining characters left.',
    ),
    '#description' => 'Enter a description of the tile, and it\'s purpose, the maximum number of characters allowed is 250.',
  );

  if($user->uid == 1) {
    $form['help_url'] = array(
      '#type' => 'textfield',
      '#title' => 'Help Manual URL',
      '#description' => '<i>Super Admins Only:</i> Enter a URL path that will direct a user to specific portion of the stacks manual, e.g. "http://help.stacksdiscovery.com/#Database_Listings"',
      '#required' => FALSE,
      '#default_value' => $tile['help_url'],
    );
  }

  $form['icon'] = array(
    '#type' => 'radios',
    '#title' => 'Icon',
    '#description' => 'Select an icon for this Tile.',
    '#options' => $icons,
    '#required' => TRUE,
    '#default_value' => $tile['tid'],
  );

  $form['user_role'] = array(
    '#type' => 'checkboxes',
    '#title' => 'Select which users can view this Tile',
    '#options' => $roles,
    '#default_value' => $user_role,
  );

  if($user->uid == 1) {
    $form['locked'] = array(
      '#type' => 'checkbox',
      '#title' => 'Lock Tile',
      '#description' => '<i>Super Admins Only:</i> Lock this tile so only super admins are able to edit/delete tile.',
      '#default_value' => $tile['locked'],
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save Tile'
  );

  return $form;
}

/**
 * Delete Confirmation Form
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function hf_tiles_delete_tile($form, &$form_state, $tile_id) {
  $form['header_message'] = array(
    '#markup' => '<p>Are you sure you want to delete this dashboard tile?</p>'
  );

  $form['tile_id'] = array(
    '#type' => 'value',
    '#value' => $tile_id,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Delete Tile'
  );

  $form['cancel'] = array(
    '#type' => 'button',
    '#value' => t('Cancel'),
    '#weight' => 20,
    '#executes_submit_callback' => TRUE,
    '#submit' => array('hf_tiles_delete_cancel'),
  );

  return $form;
}

/**
 * Validation for Add Form
 * @param $form
 * @param $form_state
 */
function hf_tiles_add_tile_validate($form, &$form_state) {
  if(empty($form_state['values']['name'])) {
    form_set_error('title', t('Please enter a name for this tile.'));
  }
  if(empty($form_state['values']['description'])) {
    form_set_error('title', t('Please enter a description for this tile.'));
  }
  if(strlen($form_state['values']['path_url']) > 2048 || strlen($form_state['values']['help_url'] > 2048)) {
    form_set_error('title', t('URL must be less than 2048 characters.'));
  }

}

/**
 * Validation for Edit Form
 * @param $form
 * @param $form_state
 */
function hf_tiles_edit_tile_validate($form, &$form_state) {
  if(empty($form_state['values']['name'])) {
    form_set_error('title', t('Please enter a name for this tile.'));
  }
  if(empty($form_state['values']['description'])) {
    form_set_error('title', t('Please enter a description for this tile.'));
  }
  if(strlen($form_state['values']['path_url']) > 2048 || strlen($form_state['values']['help_url'] > 2048)) {
    form_set_error('title', t('URL must be less than 2048 characters.'));
  }

}

/**
 * Implements hook_submit() for adding a tile.
 * @param array $form
 * @param array $form_state
 * @throws Exception
 */
function hf_tiles_add_tile_submit(array $form, array &$form_state) {
  global $user;

  $name = $form_state['values']['name'];
  $description = $form_state['values']['description'];
  $path_url = $form_state['values']['path_url'];
  $help_url = $form_state['values']['help_url'];
  $icon = $form_state['values']['icon'];
  $locked = (isset($form_state['values']['locked'])) ?  $form_state['values']['locked'] : 0;
  $user_id = $user->uid;

  //Adding Super Admin as checked
  $user_role = $form_state['values']['user_role'];
  $user_role[86] = strval(86);
  //Serialize the array for DB storage
  $user_role = serialize($user_role);

  try {
    db_insert('stacks_tiles')
      ->fields(array(
        'name' => $name,
        'description' => $description,
        'path_url' => $path_url,
        'help_url' => $help_url,
        'tid' => $icon,
        'user_role' => $user_role,
        'uid' => $user_id,
        'locked' => $locked,
      ))->execute();
  } catch(Exception $e) {
    //Display error message if something goes wrong.
    drupal_set_message(t('Unable to add this tile at the moment, please try again later.'), 'error');
    watchdog('module', 'Error occurred while adding a new tile. Message: !message', array('!message' => $e->getMessage()), WATCHDOG_ERROR);
  }
  //Display Success Message
  drupal_set_message('This tile has been added!');
  drupal_goto('admin/config/stacks/tiles');
}

/**
 * Implements hook_submit() for editing a tile.
 * @param array $form
 * @param array $form_state
 * @throws Exception
 */
function hf_tiles_edit_tile_submit(array $form, array &$form_state) {
  global $user;

  $name = $form_state['values']['name'];
  $description = $form_state['values']['description'];
  $path_url = $form_state['values']['path_url'];
  $help_url = $form_state['values']['help_url'];
  $icon = $form_state['values']['icon'];
  $locked = $form_state['values']['locked'];
  $user_id = $user->uid;

  //Adding Super Admin as checked
  $user_role = $form_state['values']['user_role'];
  $user_role[86] = strval(86);
  //Serialize the array for DB storage
  $user_role = serialize($user_role);

  try {
    db_update('stacks_tiles')
      ->fields(array(
        'name' => $name,
        'description' => $description,
        'path_url' => $path_url,
        'help_url' => $help_url,
        'tid' => $icon,
        'user_role' => $user_role,
        'uid' => $user_id,
        'locked' => $locked,
      ))
      ->condition('tile_id', $form_state['values']['tile_id'])
      ->execute();
  } catch(Exception $e) {
    //Display error message if something goes wrong.
    drupal_set_message(t('Unable to update this tile at the moment, please try again later.'), 'error');
    watchdog('module', 'Error occurred while update a tile. Message: !message', array('!message' => $e->getMessage()), WATCHDOG_ERROR);
  }

  //Display Success Message
  drupal_set_message('This tile has been updated!');
  drupal_goto('admin/config/stacks/tiles');
}

/**
 * Implements hook_submit() for deleting a tile.
 * @param array $form
 * @param array $form_state
 * @throws Exception
 */
function hf_tiles_delete_tile_submit($form, &$form_state) {
  try {
    db_delete('stacks_tiles')->condition('tile_id', $form_state['values']['tile_id'])->execute();
  } catch(Exception $e) {
    //Display error message if something goes wrong.
    drupal_set_message(t('Unable to delete this tile at the moment, please try again later.'), 'error');
    watchdog('module', 'Error occurred while deleting a tile. Message: !message', array('!message' => $e->getMessage()), WATCHDOG_ERROR);
  }
  //Display Success Message
  drupal_set_message('This tile has been deleted!');
  drupal_goto('admin/config/stacks/tiles');
}

/**
 * Redirects back to dashboard config page when cancel button is pressed.
 */
function hf_tiles_delete_cancel() {
  drupal_goto('admin/config/stacks/tiles');
}

/**
 * Helper function to retreive a specific tiles information for editing.
 * @param $tile_id
 * @return mixed
 */
function _hf_tiles_get_existing_tile($tile_id) {
  $query = db_select('stacks_tiles', 'tile');
  $query->fields('tile', array('name', 'description', 'path_url', 'help_url', 'tid', 'locked', 'user_role'));
  $query->condition('tile_id', $tile_id, '=');
  return $query->execute()->fetchAssoc();
}

/**
 * Returns all stored icons in the database. Used for the radio list.
 * @return array
 */
function _hf_tiles_query_icons() {
  $icons = array();

  $query = db_select('field_data_field_icon_class', 'icon');
  $query->innerJoin('taxonomy_term_data', 'taxonomy', 'taxonomy.tid = icon.entity_id');
  $query->fields('icon', array('field_icon_class_value'));
  $query->fields('taxonomy', array('tid'));

  $results = $query->execute()->fetchAll();

  foreach($results as $result) {
    $icons[$result->tid] = "<i class='$result->field_icon_class_value'></i>";
  }

  return $icons;

}

/**
 * Returns all user roles with their associated rid.
 * @return array
 */
function _hf_tiles_get_roles() {
  $roles = array();

  $query = db_select('role', 'r');
  $query->fields('r', array('rid', 'name'));
  $query->condition('name', array('administrator', 'moderator', 'editor', 'contributor'), 'IN');

  $results = $query->execute()->fetchAll();

  foreach($results as $result) {
    $roles[$result->rid] = ucfirst($result->name);
  }

  return $roles;
}