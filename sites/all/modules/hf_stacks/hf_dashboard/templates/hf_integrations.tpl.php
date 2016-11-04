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


        <!-- ILS -->
        <div id="div_1" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
          <div class="flip">
            <fieldset class="card">
              <a href="/admin/config/stacks/auth">
                <legend>
                  <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-clipboard-notes.svg" class="svg-color">
                  <span class="fieldset-legend">ILS</span>
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

        <!-- Search -->
        <div id="div_2" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
          <div class="flip">
            <fieldset class="card">
              <a href="/admin/config/stacks/eds">
                <legend>
                  <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-address-book.svg" class="svg-color">
                  <span class="fieldset-legend">Search</span>
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

        <!-- Book Jackets -->
        <div id="div_3" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
          <div class="flip">
            <fieldset class="card">
              <a href="/admin/config/stacks/resource-list">
                <legend>
                  <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-photo.svg" class="svg-color">
                  <span class="fieldset-legend">Book Jackets</span>
                </legend>
                <div class="face front form-wrapper book-jackets"></div>
              </a>

              <i class="fi-arrows-out"></i>

              <div class="face back">
                <h3>Book Jackets</h3>
                <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Nisi, libero omnis ut quos doloremque commodi perspiciatis.</p>
                <a href="#" class="close-btn">&#215;</a>
              </div>
            </fieldset>
          </div>
        </div>

        <!-- Reviews -->
        <div id="div_4" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
          <div class="flip">
            <fieldset class="card">
              <a href="/admin/config/stacks/reviews">
                <legend>
                  <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-book.svg" class="svg-color">
                  <span class="fieldset-legend">Reviews</span>
                </legend>
                <div class="face front form-wrapper reviews"></div>
              </a>

              <i class="fi-arrows-out"></i>

              <div class="face back">
                <h3>Reviews</h3>
                <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Nisi, libero omnis ut quos doloremque commodi perspiciatis.</p>
                <a href="#" class="close-btn">&#215;</a>
              </div>
            </fieldset>
          </div>
        </div>

        <!-- IP-Whitelist -->
        <div id="div_5" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
          <div class="flip">
            <fieldset class="card">
              <a href="/admin/config/stacks/e-resources">
                <legend>
                  <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-check.svg" class="svg-color">
                  <span class="fieldset-legend">IP Whitelist</span>
                </legend>
                <div class="face front form-wrapper whitelist"></div>
              </a>

              <i class="fi-arrows-out"></i>

              <div class="face back">
                <h3>IP Whitelist</h3>
                <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Nisi, libero omnis ut quos doloremque commodi perspiciatis.</p>
                <a href="#" class="close-btn">&#215;</a>
              </div>
            </fieldset>
          </div>
        </div>

        <!-- Google Places -->
        <div id="div_6" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
          <div class="flip">
            <fieldset class="card">
              <a href="/admin/config/stacks/places">
                <legend>
                  <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-map.svg" class="svg-color">
                  <span class="fieldset-legend">Google Places</span>
                </legend>
                <div class="face front form-wrapper google-places"></div>
              </a>

              <i class="fi-arrows-out"></i>

              <div class="face back">
                <h3>Google Places</h3>
                <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Nisi, libero omnis ut quos doloremque commodi perspiciatis.</p>
                <a href="#" class="close-btn">&#215;</a>
              </div>
            </fieldset>
          </div>
        </div>

        <!-- NoveList Select -->
        <div id="div_7" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
          <div class="flip">
            <fieldset class="card">
              <a href="/admin/config/stacks/similartitles">
                <legend>
                  <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-list-bullet.svg" class="svg-color">
                  <span class="fieldset-legend">Similar Titles</span>
                </legend>
                <div class="face front form-wrapper novelist"></div>
              </a>

              <i class="fi-arrows-out"></i>

              <div class="face back">
                <h3>NoveList Select</h3>
                <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Nisi, libero omnis ut quos doloremque commodi perspiciatis.</p>
                <a href="#" class="close-btn">&#215;</a>
              </div>
            </fieldset>
          </div>
        </div>

        <?php
        //If the Flipster module EXISTS and ENALBED, show the tile
        if(module_exists('hf_flipster')) : ?>
        <!-- Flipster -->
        <div id="div_8" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
          <div class="flip">
            <fieldset class="card">
              <a href="/admin/config/stacks/flipster">
                <legend>
                  <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-graph-trend.svg" class="svg-color">
                  <span class="fieldset-legend">Flipster</span>
                </legend>
                <div class="face front form-wrapper hf-flipster"></div>
              </a>

              <i class="fi-arrows-out"></i>

              <div class="face back">
                <h3>Flipster</h3>
                <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Nisi, libero omnis ut quos doloremque commodi perspiciatis.</p>
                <a href="#" class="close-btn">&#215;</a>
              </div>
            </fieldset>
          </div>
        </div>
        <?php endif; ?>

        <?php
        //If the Calendar Import module EXISTS and ENALBED, show the tile
        if(module_exists('hf_calendar_import')) : ?>
          <!-- Google Calendar Import -->
          <div id="div_8" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
            <div class="flip">
              <fieldset class="card">
                <a href="/admin/config/stacks/calendarimport">
                  <legend>
                    <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-graph-trend.svg" class="svg-color">
                    <span class="fieldset-legend">Google Calendar Import</span>
                  </legend>
                  <div class="face front form-wrapper calendar-import"></div>
                </a>

                <i class="fi-arrows-out"></i>

                <div class="face back">
                  <h3>Google Calendar Import</h3>
                  <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Nisi, libero omnis ut quos doloremque commodi perspiciatis.</p>
                  <a href="#" class="close-btn">&#215;</a>
                </div>
              </fieldset>
            </div>
          </div>
        <?php endif; ?>

        <?php
        //If the Stacks Config exists and ENALBED, show the tile
        if(module_exists('hf_stacks_config')) : ?>
          <!-- Google Calendar Import -->
          <div id="div_8" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
            <div class="flip">
              <fieldset class="card">
                <a href="/admin/config/stacks/configuration">
                  <legend>
                    <img src="/sites/all/modules/hf_stacks/hf_dashboard/img/fi-graph-trend.svg" class="svg-color">
                    <span class="fieldset-legend">Stacks Configuration</span>
                  </legend>
                  <div class="face front form-wrapper stacks-config"></div>
                </a>

                <i class="fi-arrows-out"></i>

                <div class="face back">
                  <h3>Stacks Configuration</h3>
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