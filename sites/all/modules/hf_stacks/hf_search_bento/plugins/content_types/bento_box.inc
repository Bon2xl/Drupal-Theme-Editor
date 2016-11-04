<?php

/**
 * Plugins are described by creating a $plugin array which will be
 * used by the system includes this file.
 */
$plugin = array(
  'title' => t('Add a Bento Box'),
  'description' => t('Bento Box Description'),
  'category' => t('Bento Search'),
  'single' => TRUE,
  'edit form' => 'hf_search_bento_pane_edit_form',
  'render callback' => 'hf_search_bento_pane_render',
);

function hf_search_bento_pane_edit_form($form, &$form_state) {
  $form['platform'] = array(
    '#type' => 'select',
    '#title' => t('Select a Bento Box'),
    '#options' => _hf_process_array(),
    '#description' => t('Select a Bento Box'),
  );
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('Optional - Custom Title'),
  );
  $form['limit'] = array(
    '#type' => 'select',
    '#title' => t('Select how many results to display for this box'),
    '#options' => array(
      1 => '1',
      2 => '2',
      3 => '3',
      4 => '4',
      5 => '5',
      6 => '6',
      7 => '7',
      8 => '8',
      9 => '9',
      10 => '10',
    ),
    '#description' => t('Select how many results to display for this box'),
  );

  return $form;
}

function hf_search_bento_pane_edit_form_submit(&$form, &$form_state) {
  if(isset($form_state['values']['platform'])) {
    $form_state['conf']['platform'] = $form_state['values']['platform'];
    $form_state['conf']['limit'] = $form_state['values']['limit'];
    $form_state['conf']['title'] = $form_state['values']['title'];
  }
}

/**
 * Output function for the bento_box content type
 */
function hf_search_bento_pane_render($subtype, $conf, $args, $contexts) {
  $pieces = explode("_", $conf['platform']);
  $delta = $pieces[0] . "-" . $pieces[1];
  $block = new stdClass();

  $block->content = _hf_search_bento_block_main($delta, $pieces[2], $pieces[0], $conf['limit'], $conf['title']);

  return $block;
}