<?php

/**
 * @file
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $caption: The caption for this table. May be empty.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 * @ingroup views_templates
 */
?>
<div class="build-progress">
  <div class="row">
    <div class="large-12 columns">

        <!-- ILS -->
        <div class="large-3 medium-6 small-12 columns">
          <a href="/admin/config/stacks/auth">
            <div class="panel">
              <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-clipboard-notes.svg">
              <h4>ILS</h4>
            </div> <!-- ./panel -->
          </a>
        </div> <!-- /ILS -->

        <!-- EDS -->
        <div class="large-3 medium-6 small-12 columns">
          <a href="/admin/config/stacks/eds">
            <div class="panel">
              <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-address-book.svg">
              <h4>EDS</h4>
            </div> <!-- ./panel -->
          </a>
        </div> <!-- /EDS -->

        <!-- Footer Block -->
        <div class="large-3 medium-6 small-12 columns">
          <a href="/admin/config/stacks/footer">
            <div class="panel">
              <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-layout.svg">
              <h4>Footer Blocks</h4>
            </div> <!-- ./panel -->
          </a>
        </div> <!-- /Footer Block -->

        <!-- Book jackets -->
        <div class="large-3 medium-6 small-12 columns">
          <a href="/admin/config/stacks/resource-list">
            <div class="panel">
              <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-photo.svg">
              <h4>Book Jackets</h4>
            </div> <!-- ./panel -->
          </a>
        </div> <!-- /Book jackets -->

        <!-- Search -->
        <div class="large-3 medium-6 small-12 columns">
          <a href="/admin/config/stacks/search">
            <div class="panel">
              <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-magnifying-glass.svg">
              <h4>Search</h4>
            </div> <!-- ./panel -->
          </a>
        </div> <!-- /search -->

        <!-- Reviews -->
        <div class="large-3 medium-6 small-12 columns">
          <a href="/admin/config/stacks/reviews">
            <div class="panel">
              <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-book.svg">
              <h4>Reviews</h4>
            </div> <!-- ./panel -->
          </a>
        </div> <!-- /Reviews -->

        <!-- IP Whitelist -->
        <div class="large-3 medium-6 small-12 columns">
          <a href="/admin/config/stacks/e-resources">
            <div class="panel">
              <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-check.svg">
              <h4>IP Whitelist</h4>
            </div> <!-- ./panel -->
          </a>
        </div> <!-- /IP Whitelist -->

        <!-- Google Places -->
        <div class="large-3 medium-6 small-12 columns">
          <a href="/admin/config/stacks/places">
            <div class="panel">
              <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-map.svg">
              <h4>Google Places</h4>
            </div> <!-- ./panel -->
          </a>
        </div> <!-- /Google Places -->

        <!-- NoveList -->
        <div class="large-3 medium-6 small-12 columns end">
          <a href="/admin/config/stacks/similartitles">
            <div class="panel">
              <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-list-bullet.svg">
              <h4>NoveList</h4>
            </div> <!-- ./panel -->
          </a>
        </div> <!-- /NoveList -->

    </div> <!-- /.columns -->
  </div> <!-- /.row -->
</div> <!-- /.build-progress -->