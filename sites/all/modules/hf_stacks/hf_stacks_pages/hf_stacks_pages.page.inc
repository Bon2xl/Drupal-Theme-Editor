<?php

function hf_stacks_pages_list() {
  $pages = _hf_stacks_pages_load();

  $output = '';
  $output .= '<ul class="action-links">';
    $output .= '<li>';
      $output .= '<a class="waves-effect waves-button waves-float waves-classic" href="/admin/landing-pages/add">Add landing page</a>';
    $output .= '</li>';
  $output .= '</ul>';

  $header = array('Name', 'Task', 'Path', 'Operations');

  // build the table fields
  $rows = array();
  foreach ($pages as $row) {
    if (($row->path == 'homepage') || ($row->path == 'multi_search') || ($row->path == 'multisearch') || ($row->path == 'bento')) {
      $rows[] = array(
        "<a href=\"/" . $row->path . "\">".$row->admin_title."</a>",
        $row->task,
        $row->path,
        " "
      );
    } else {
      $rows[] = array(
        "<a href=\"/" . $row->path . "\">".$row->admin_title."</a>",
        $row->task,
        $row->path,
        "<a href=\"/admin/landing-pages/edit/" . $row->pid . "\">Edit</a> | <a href=\"/admin/landing-pages/delete/" . $row->pid . "\">Delete</a>",
      );
    }
  }
  $output .= theme('table', array('header' => $header, 'rows' => $rows ));

  // add the pager
  $output .= theme('pager');

  return $output;
}


function _hf_stacks_pages_load() {

  $pages = db_select('page_manager_pages', 'p')
    ->fields('p', array('pid'))
    ->fields('p', array('name'))
    ->fields('p', array('task'))
    ->fields('p', array('path'))
    ->fields('p', array('admin_title'))
    ->execute()
    ->fetchAll(); // returns an indexed array

  return $pages;
}