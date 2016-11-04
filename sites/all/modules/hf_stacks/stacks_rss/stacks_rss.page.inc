<?php

function stacks_rss_list() {
  $pages = _stacks_rss_load();

  $output = '';
  $output .= '<ul class="action-links">';
    $output .= '<li>';
      $output .= '<a class="waves-effect waves-button waves-float waves-classic" href="/admin/rss-feeds/add">Add RSS Feed</a>';
    $output .= '</li>';
  $output .= '</ul>';

  $header = array('ID', 'Operations');

  // build the table fields
  $rows = array();
  foreach ($pages as $row) {
    $rows[] = array(
      $row->id,
      "<a href=\"/admin/rss-feeds/edit/" . $row->id . "\">Edit</a> | <a href=\"/admin/rss-feeds/delete/" . $row->id . "\">Delete</a>",
    );
  }
  $output .= theme('table', array('header' => $header, 'rows' => $rows ));

  // add the pager
  $output .= theme('pager');

  return $output;
}


function _stacks_rss_load() {

  $pages = db_select('feeds_importer', 'f')
    ->fields('f', array('id'))
    ->fields('f', array('config'))
    ->execute()
    ->fetchAll(); // returns an indexed array

  return $pages;
}