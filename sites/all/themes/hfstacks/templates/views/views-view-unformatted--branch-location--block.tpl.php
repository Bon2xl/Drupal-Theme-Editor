<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
  <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
    <?php print $row; ?>
  </div>
<?php endforeach; ?>

<?php $maps_key = variable_get('hf_stacks_maps_api_key', ''); ?>
<?php if (!empty($maps_key)):?>
  <!-- google maps gererated in here -->
  <div class="map-wrapper">
    <div id="gmap_canvas" class="uni-map-inline">
      <i class="fa fa-spinner fa-spin"></i> Loading maps...
    </div>
  </div>
<?php endif; ?>