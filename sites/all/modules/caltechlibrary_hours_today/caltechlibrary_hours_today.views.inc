<?php

/**
 * @file
 * caltechlibrary_hours_today.views.inc
 */

/**
 * Implements hook_views_pre_build().
 */
function caltechlibrary_hours_today_views_pre_build(&$view) {
  if ($view->name == 'hours_today') {
    // The view itself contains all the day-of-the-week hours fields but we only
    // want to display the hours for the current day of the week in the view.
    // First we add all of the hours field objects to an array.
    $hours_fields = array();
    $hours_fields['Sunday'] = $view->field['field_branch_sunday'];
    $hours_fields['Monday'] = $view->field['field_branch_monday'];
    $hours_fields['Tuesday'] = $view->field['field_branch_tuesday'];
    $hours_fields['Wednesday'] = $view->field['field_branch_wednesday'];
    $hours_fields['Thursday'] = $view->field['field_branch_thursday'];
    $hours_fields['Friday'] = $view->field['field_branch_friday'];
    $hours_fields['Saturday'] = $view->field['field_branch_saturday'];
    // Next we remove all the hours fields from the view.
    foreach ($hours_fields as $field_object) {
      $fieldname = $field_object->field;
      unset($view->field[$fieldname]);
      unset($view->display_handler->handlers['field'][$fieldname]);
    }
    // Finally we re-add only the hours field for today.
    $weekday_today = date('l');
    $fieldname_today = $hours_fields[$weekday_today]->field;
    $view->field[$fieldname_today] = $hours_fields[$weekday_today];
  }
}
