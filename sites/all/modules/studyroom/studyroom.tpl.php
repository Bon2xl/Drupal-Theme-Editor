<div class="large-3 columns">
  <div class="views-exposed-widget side-filter">
    <?php
    $block = module_invoke('studyroom_availability', 'block_view', 'studyroom_availability');
    print render($block['content']);
    ?>
  </div>
</div>

<div class="large-9 columns">
<?php
$type = "";
$space_id = "";
$hours = FALSE;
//dpm($vars);
foreach($vars as $spaces) {
  if (($space_id != $spaces->space_id) && ($space_id != "")) {
    echo "</div>";
    echo "</div>";
    echo "</div>";

    echo "</a>";

    $hours = FALSE;
  }

  if ( ($type != $spaces->type) && ($hours == FALSE) && ($space_id != $spaces->space_id) ) {
    echo "<h2 class=\"first\">".t($spaces->description)."</h2>";
  }

  if ($space_id != $spaces->space_id) {
    echo "<a href=\"availability/".$spaces->space_id."/".date('Y-m-d')."\">";
    echo "<div class=\"view view-research-guide view-id-research_guide\">";
    echo "<div class=\"view-content\">";
    echo "<div class=\"views-row\">";
  }

    if ($space_id != $spaces->space_id) {
      echo "<div class=\"views-field views-field-title views-title\">";
      echo "<strong class=\"field-content\">" . t($spaces->label) . "</strong>";
      echo "</div>";

      if (isset($spaces->field_space_body_value)) {
        echo "<div class=\"views-field views-lbl-inline views-small-details views-mar-1\">";
        echo "<span class=\"views-label\">Description: </span>";
        echo "<div class=\"field-content\">" . t($spaces->field_space_body_value) . "</div>";
        echo "</div>";
      }

      echo "<div class=\"views-field views-lbl-inline views-small-details views-mar-1\">";
      echo "<span class=\"views-label\">Capacity: </span>";
      echo "<div class=\"field-content\">" . t($spaces->capacity) . "</div>";
      echo "</div>";
    }

    if (isset($spaces->field_space_hours_start_time)) {
      echo "<div class=\"views-field views-lbl-inline views-small-details views-mar-1\">";

      if ($hours == FALSE) {
        echo "<span class=\"views-label\">Today's Hours:</span>";
        $hours = TRUE;
      }

      $weekday = '';
      switch ($spaces->delta) {
        case 0:
          $weekday = "SUN ";
        break;
        case 1:
          $weekday = "MON ";
        break;
        case 2:
          $weekday = "TUE ";
        break;
        case 3:
          $weekday = "WED ";
          break;
        case 4:
          $weekday = "THU ";
          break;
        case 5:
          $weekday = "FRI ";
          break;
        case 6:
          $weekday = "SAT ";
          break;
      }

      /*
      echo "<span class=\"views-label\">";
        echo $weekday.' '.strtoupper(date('D'));
      echo "</span>";
      */

      if ( trim(strtoupper($weekday)) == trim(strtoupper(date('D'))) ) {
        echo "<div class=\"field-content\">".date('g:i A',strtotime($spaces->field_space_hours_start_time))." - ".date('g:i A',strtotime($spaces->field_space_hours_end_time))."</div>";
      }
      echo "</div>";
    }

  $type = $spaces->type;
  $space_id = $spaces->space_id;
}
?>
</div>
</div>
</div>

</div>
