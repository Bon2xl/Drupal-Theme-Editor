<?php
/**
 * Template file for theming registration form
 */
?>

<?php
  $space_id = '';
  $capacity = '';
  $space_title = '';
  $space_body = '';
  $space_date = '';

  if (!empty($form['space_id'])) {
    $space_id = $form['space_id']['#value'];
  }
  if (!empty($form['space_id_display'])) {
    $space_title = $form['space_id_display']['#markup'];
  }
  if (!empty($form['space_body'])) {
    $space_body = $form['space_body']['#markup'];
  }
  if (!empty($form['field_reservation_datetime'])) {
    $space_date = strtotime($form['field_reservation_datetime']['und'][0]['#value']['value']);
  }

  if ($space_id != "") {
    //dpm((int)$space_id);
    $studyroom_space = entity_load_single('studyroom_space', (int)$space_id);
    $capacity = $studyroom_space->capacity;
  }

  // overwrite description field label
  $form['field_reservation_contact_desc']['und'][0]['value']['#title'] = 'Room Booking Description';

  // overwrite occupancy field label
  $form['field_reservation_occupancy']['und'][0]['value']['#title'] = 'Occupants';
?>
<div class="panel row">
  <br>
  <h3 class="text-center">
    <b><?php echo $space_title; ?></b>
  </h3>
  <?php
  if (!empty($space_date)) {
    echo "<p class=\"text-center\">".date('l, F jS Y',$space_date)." | ".date('g:ia',$space_date)."</p>";
  }

  echo $space_body;

  //dpm(get_defined_vars());
  //dpm($space_id);
  //dpm($form['field_reservation_datetime']['und'][0]['#value']);
  print render($form['user_name']);

  print "<!--".render($form['space_id_display'])."-->";

  print "<div class='small-12 medium-12 large-6 columns'>";
  print drupal_render($form['field_reservation_contact_name']);
  print "</div><div class='small-12 medium-12 large-6 columns'>";
  print drupal_render($form['field_reservation_contact_phone']);
  print "</div><div class='small-12 medium-12 large-6 columns'>";
  print drupal_render($form['field_reservation_contact_email']);
  print "</div><div class='small-12 medium-12 large-6 columns'>";
  print render($form['duration']);
  print "</div><div class='small-12 medium-12 large-12 columns'>";
  print drupal_render($form['field_reservation_contact_desc']);
  print "</div>";

  print "<div class='small-12 medium-12 large-6 columns'>";
  print render($form['field_reservation_occupancy']);

  if ($capacity != "") {
    print "<p>Maximum number of occupants is: ".$capacity."</p>";
  }
  print "</div>";


  print "<div class='small-12 medium-12 large-6 columns'>";
  print drupal_render($form['field_reservation_datetime']);
  print "</div>";

  print render($form['submit']);

  print render($form['form_build_id']);
  print render($form['form_token']);
  print render($form['form_id']);
  print drupal_render_children($form);
  ?>
</div>