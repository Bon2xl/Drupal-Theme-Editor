<?php
/**
  * $var_type = content type name
  * $page_title = page title
  * $btn_label = button label
  * $url_path =  url path
  */
global $base_url;
function hf_dashboard_menu_page_callback() {
  // We are going to output the results in a table with a nice header.
  $header = array(
    // The header gives the table the information it needs in order to make
    // the query calls for ordering. TableSort uses the field information
    // to know what database column to sort by.
    array('data' => t('Title'), 'field' => 'title', 'width'=>'75%'),
    array('data' => t('Operations')),
    array('data' => t('')),
    array('data' => t('')),
  );

  // Using the TableSort Extender is what tells the the query object that we are sorting.
  $query = db_select('menu_custom', 'm')->extend('PagerDefault')->extend('TableSort');
  $query->fields('m', array('menu_name', 'title', 'description')); 

  // Don't forget to tell the query object how to find the header information.
  $result = $query
      ->limit(20)
      ->orderByHeader($header)
      ->execute();

  $rows = array();
  foreach ($result as $row) {
    $rows[] = array(
      "<span>" .$row->title. "</span><br />
      <span class='description'>".t($row->description)."</span>",
      "<a href=\"" .base_path(). "admin/structure/menu/manage/" .$row->menu_name. "\" class=\"btn-edit\">List links</a>",
      "<a href=\"" .base_path(). "admin/structure/menu/manage/" .$row->menu_name. "/edit\" class=\"btn-delete\">Edit menu</a>",
      "<a href=\"" .base_path(). "admin/structure/menu/manage/" .$row->menu_name. "/add\" class=\"btn-add\">Add link</a>"
    );
  }
  
  drupal_add_css(drupal_get_path('theme', 'hfstacks').'/assets/bower_components/components-font-awesome/css/font-awesome.css', array( 'type' => 'internal', 'scope' => 'footer', 'weight' => 0));
  $output = '<div class="dashboard-table-views">';
  // Buttons
  $output .= add_new_button();
  // Build the table for the nice output.
  $output .= theme('table', array('header' => $header,'rows' => $rows));
  $output .= theme('pager');
  $output .= '</div>';
  return $output;
}


function add_new_button() {
  $output = '';
  $output .= '<ul class="action-links">';
    $output .= '<li>';
      $output .= '<a class="waves-effect waves-button waves-float waves-classic" href="/admin/structure/menu/add">Add New</a>';
    $output .= '</li>';
  $output .= '</ul>';  

  return $output;
}