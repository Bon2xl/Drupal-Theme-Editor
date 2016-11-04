<?php

/**
 * @file
 * Default theme implementation to display a day.
 *
 * Available variables:
 * - $loc: The location of the space.
 * - $spaces: An array of all spaces.
 * - $header: An array of all spaces for displaying in header.
 * - $items: The array of each time slot.
 *
 * @see template_preprocess_studyroom_availability_day()
 *
 * @ingroup themeable
 */
?>
<div class="studyroom-space-calendar">
<div class="text-center header">
  <?php print $loc; ?>
  <?php print render($page['navigation']); ?>
</div>
    <?php
    $max_days_advance = 0;
    $max_days_valid = true;
    foreach ($spaces as $space) {
      $max_days_advance = $space->max_days_advance;
    }
    if ($max_days_advance > 0) {
      $current_day = date('Y-m-d');
      preg_match("/[^\/]+$/", request_path(), $day_match);
      $selected_day = $day_match[0];
      $datediff = strtotime($selected_day) - strtotime($current_day);
      $days = floor($datediff / (60 * 60 * 24));
      if ($days > $max_days_advance) {
        $max_days_valid = false;
      }
    }

    $slot_counter = 0;
    if ($max_days_valid == true) {
      foreach ($items as $time) {
        $curpos = 0;
        foreach ($spaces as $id => $space) {
          if (strpos($time['values'][$id]['entry'], 'available') !== FALSE) {
            echo "<a class=\"button expand\" href=\"";
            if (!empty($time['values'][$id]['entry'])) {
              $timeURL = $time['values'][$id]['entry'];
              preg_match('/href=(["\'])([^\1]*)\1/i', $timeURL, $m);
              echo $m[2] . "\n";
            }
            echo "\">";

            echo $time['hour'];
            echo $time['ampm'];

            echo "</a>";
            $slot_counter++;
          }
        }
      }
    }

    if ($slot_counter == 0) {
      echo "There are no time slots available for today.";
    }
    ?>
</div>
