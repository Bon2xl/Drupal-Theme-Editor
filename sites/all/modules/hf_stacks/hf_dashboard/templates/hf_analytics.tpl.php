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
<a href='http://help.stacksdiscovery.com/#Integrations' class='button modal-btn'>More Help</a>

<div class="dashboard">
  <div class="row">
    <div class="large-12 columns">
      <div id="sortable">


        <!-- Google-->
        <div id="div_1" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
          <div class="flip">
            <fieldset class="card">
              <a href="config/system/googleanalytics">
                <legend>
                  <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-clipboard-notes.svg" class="svg-color">
                  <span class="fieldset-legend">Google Analytics</span>
                </legend>
                <div class="face front form-wrapper ils"></div>
              </a>

              <i class="fi-arrows-out"></i>

              <div class="face back">
                <h3>ILS</h3>
                <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Nisi, libero omnis ut quos doloremque commodi perspiciatis.</p>
                <a href="#" class="close-btn">&#215;</a>
              </div>
            </fieldset>
          </div>
        </div>


        <?php
        //If the Piwik module EXISTS and ENALBED, show the tile
        if(module_exists('piwik')) : ?>
        <!-- Piwik -->
        <div id="div_2" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
          <div class="flip">
            <fieldset class="card">
              <a href="config/system/piwik">
                <legend>
                  <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-address-book.svg" class="svg-color">
                  <span class="fieldset-legend">Piwik Web Analytics</span>
                </legend>
                <div class="face front form-wrapper eds"></div>
              </a>

              <i class="fi-arrows-out"></i>

              <div class="face back">
                <h3>EDS</h3>
                <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Nisi, libero omnis ut quos doloremque commodi perspiciatis.</p>
                <a href="#" class="close-btn">&#215;</a>
              </div>
            </fieldset>
          </div>
        </div>
      <?php endif; ?>

      </div>
    </div>
  </div>
</div>


<script>
  jQuery(document).foundation();
  // jQuery(".help-btn").click(function(){
  //   jQuery("#modal-build").foundation('reveal', 'open');
  // });
</script>