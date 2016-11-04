<?php
/**
  * $var_type = content type name
  * $page_title = page title
  * $btn_label = button label
  * $url_path =  url path
  */
global $base_url;
function hf_dashboard_views_page_callback($var_type, $add_content_path, $page_title, $btn_label, $url_path, $workflow, $xcolumns) {
  if (!empty($_GET["search"])) {
    $search = $_GET["search"];
  } else {
    $search = $_GET["search"];
  }

  // parse the extra columns into an array (comma delimited)
  $column_array = explode(";", $xcolumns);

  // create the header for the table
  $header = array();
  $header[] = array('data' => t('Title'), 'field' => 'title');
  if (is_array($column_array)) {
    foreach ($column_array as $column) {
      switch ($column) {
        case 'roombooking_room':
          $header[] = array('data' => t('Room'), 'field' => 'nrr.title');
          break;
        case 'roombooking_date':
          $header[] = array('data' => t('Date/Time'), 'field' => 'rd.reservation_date_value');
          break;
        case 'roombooking_capacity':
          $header[] = array('data' => t('Capacity'), 'field' => 'rcp.reservations_room_capacity_value');
          break;
        case 'roombooking_category':
          $header[] = array('data' => t('Category'), 'field' => 'nrct.title');
          break;
      }
    }
  }
  $header[] = array('data' => t('Updated by'), 'field' => 'u.name');
  $header[] = array('data' => t('Updated date'), 'field' => 'changed');
  $header[] = array('data' => t('Published'), 'field' => 'v.status');
  if ($workflow == TRUE) {
    $header[] = array('data' => t('Workflow'), 'field' => 's.name');
  }
  $header[] = array('data' => t('Operations'));

  // using the TableSort Extender tells the query object that we are sorting.
  $query = db_select('node', 't')->extend('PagerDefault')->extend('TableSort');

  // query joins
  $query->join('node_revision', 'v', 't.vid = v.vid');
  $query->join('users', 'u', 'v.uid = u.uid');
  if ($workflow == TRUE) {
    $query->join('field_data_field_workflow', 'w', 'v.nid = w.entity_id');
    $query->join('workflow_states', 's', 'w.field_workflow_value = s.sid');
  }
  if (is_array($column_array)) {
    foreach ($column_array as $column) {
      switch ($column) {
        case 'roombooking_room':
          $query->join('field_data_reservation_room', 'rr', 't.nid = rr.entity_id');
          $query->join('node', 'nrr', 'rr.reservation_room_target_id = nrr.nid');
          break;
        case 'roombooking_date':
          $query->join('field_data_reservation_date', 'rd', 't.nid = rd.entity_id');
          break;
        case 'roombooking_capacity':
          $query->join('field_data_reservations_room_capacity', 'rcp', 't.nid = rcp.entity_id');
          break;
        case 'roombooking_category':
          $query->join('field_data_reservations_room_category', 'rct', 't.nid = rct.entity_id');
          $query->join('node', 'nrct', 'rct.reservations_room_category_target_id = nrct.nid');
          break;
      }
    }
  }

  // query fields
  $query->fields('t', array('nid', 'title', 'status', 'changed', 'type'));
  $query->fields('u', array('name'));
  $query->fields('v', array('uid', 'title', 'status','timestamp'));
  if ($workflow == TRUE) {
    $query->fields('s', array('state'));
  }
  if (is_array($column_array)) {
    foreach ($column_array as $column) {
      switch ($column) {
        case 'roombooking_room':
          $query->fields('nrr', array('title'));
          break;
        case 'roombooking_date':
          $query->fields('rd', array('reservation_date_value'));
          break;
        case 'roombooking_capacity':
          $query->fields('rcp', array('reservations_room_capacity_value'));
          break;
        case 'roombooking_category':
          $query->fields('nrct', array('title'));
          break;
      }
    }
  }

  // query conditions
  if (!empty($search)) {
    $query->condition('t.title', '%'.$search.'%', 'LIKE');
  }
  if ($var_type == 'slider') {
    $query->condition('t.type', array('' .$var_type. '', 'slider_mini'));
  } else {
    $query->condition('t.type', $var_type);
  }

  // tell the query object how to find the header information
  $result = $query
      ->limit(20)
      ->orderByHeader($header)
      ->execute();

  $rows = array();
  $rows2 = array();
  foreach ($result as $row) {
    $sub_rows = array();
    //dpm($row);
    $status = ($row->v_status) ? "Yes" : "No" ;
    if ($var_type == 'event') {
      $operations = "<a href=\"".base_path(). "node/" .$row->nid. "/edit?destination=" .$url_path. "?order=Updated+date\" class=\"btn-edit\">Edit</a>";
      $operations .= "<a href=\"".base_path(). "node/" .$row->nid. "/signups?destination=" .$url_path. "?order=Updated+date\" class=\"btn-edit\">Signups</a>";
      $operations .= "<a href=\"".base_path(). "node/" .$row->nid. "/delete?destination=" .$url_path. "?order=Updated+date\" class=\"btn-delete\">Delete</a>";
    } else {
      $operations = "<a href=\"".base_path(). "node/" .$row->nid. "/edit?destination=" .$url_path. "?order=Updated+date\" class=\"btn-edit\">Edit</a>";
      $operations .= "<a href=\"".base_path(). "node/" .$row->nid. "/delete?destination=" .$url_path. "?order=Updated+date\" class=\"btn-delete\">Delete</a>";
    }

    /*
    if ($workflow == TRUE) {
      $rows[] = array(
        "<a href=\"" .base_path().drupal_get_path_alias('node/' .$row->nid). "\" class=\"ttl\">" .$row->title. "</a>",
        "<span>".$row->name."</span>",
        "<span>".format_date($row->changed, 'short')."</span>",
        "<span>".$status."</span>",
        "<span>".$row->state."</span>",
        $operations,
      );
    } else {
      $rows[] = array(
        "<a href=\"" .base_path().drupal_get_path_alias('node/' .$row->nid). "\" class=\"ttl\">" .$row->title. "</a>",
        "<span>".$row->name."</span>",
        "<span>".format_date($row->changed, 'short')."</span>",
        "<span>".$status."</span>",
        $operations,
      );
    }
    */

    $sub_rows[] = "<a href=\"" .base_path().drupal_get_path_alias('node/' .$row->nid). "\" class=\"ttl\">" .$row->title. "</a>";
    if (is_array($column_array)) {
      foreach ($column_array as $column) {
        switch ($column) {
          case 'roombooking_room':
            $sub_rows[] = "<span>".$row->nrr_title."</span>";
            break;
          case 'roombooking_date':
            $sub_rows[] = "<span>".$row->reservation_date_value."</span>";
            break;
          case 'roombooking_capacity':
            $sub_rows[] = "<span>".$row->reservations_room_capacity_value."</span>";
            break;
          case 'roombooking_category':
            $sub_rows[] = "<span>".$row->nrct_title."</span>";
            break;
        }
      }
    }
    $sub_rows[] = "<span>".$row->name."</span>";
    $sub_rows[] = "<span>".format_date($row->changed, 'short')."</span>";
    $sub_rows[] = "<span>".$status."</span>";
    if ($workflow == TRUE) {
      $sub_rows[] = "<span>".$row->state."</span>";
    }
    $sub_rows[] = $operations;

    $rows[] = $sub_rows;
  }

  //dpm($rows);
  //dpm($rows2);
  
  drupal_add_css(drupal_get_path('theme', 'hfstacks').'/assets/bower_components/components-font-awesome/css/font-awesome.css', array( 'type' => 'internal', 'scope' => 'footer', 'weight' => 0));
  $output = '<div class="dashboard-table-views">';
    // search
    $output .= "<form action='#' method='get' class='search-items'>";
      $output .= "<input id=\"searchBox\" class=\"form-text\" type=\"text\" name=\"search\" title=\"Search\" size=\"60\" value=\"".$search."\">";
      $output .= "<ul class='action-links'>";
        $output .= '<li><input id="edit-submit" class="waves-effect waves-button waves-float waves-classic" type="submit" value="Search"></li>';
        $output .= '<li><a class="waves-effect waves-button waves-float waves-classic" href="/'.current_path().'">Clear</a></li>';
      $output .= "</ul>";
    $output .= "</form>";

    // buttons
    $output .= add_new_button($var_type, $btn_label, $add_content_path);

    // build the table for the nice output
    $output .= theme('table', array('header' => $header,'rows' => $rows));
    $output .= theme('pager');
  $output .= '</div>';
  return $output;
}


function add_new_button($var_type, $btn_label, $add_content_path) {
  $output = '';
  $output .= '<ul class="action-links">';
    $output .= '<li>';
      $output .= '<a class="waves-effect waves-button waves-float waves-classic" href="/node/add/' .$add_content_path. '">' .$btn_label. '</a>';
      if ($var_type == 'slider') {
        $output .= ' <a class="waves-effect waves-button waves-float waves-classic" href="/node/add/slider-mini">Add New Mini Slider</a>';
      }
    $output .= '</li>';
  $output .= '</ul>';  

  return $output;
}