<?php
global $user;

//JS files needed for tile sort and flipping
drupal_add_js(drupal_get_path('module', 'hf_tiles').'/js/jquery-ui.js');
drupal_add_js(drupal_get_path('module', 'hf_tiles').'/js/foundation.min.js');
drupal_add_js(drupal_get_path('module', 'hf_tiles').'/js/dashboard-sort.js');
drupal_add_js(drupal_get_path('module', 'hf_tiles').'/js/app.js');

//CSS files needed for styling of dashboard
drupal_add_css( drupal_get_path('module', 'hf_tiles').'/css/hf_dashboard.css' );
//Needed for Icons
drupal_add_css('https://cdnjs.cloudflare.com/ajax/libs/foundicons/3.0.0/foundation-icons.min.css', array('type' => 'external')); ?>

<div class="stacks-dashboard">
  <div class="dashboard">
    <div class="row">
      <div class="large-12 columns">
        <div id="sortable" class="ui-sortable">
          <!--   !!CHANGE THE DASHBOARD 2 TO DASHBOARD !!      -->
          <?php if(current_path() == 'admin/dashboard'): ?>
          <?php foreach($tiles as $tile): ?>
            <?php if($tile->plid == 0): ?>
              <?php $childCount = checkTileChildren($tiles, $tile->tile_id); ?>
              <?php $user_roles = array_map('intval', unserialize($tile->user_role)); ?>
                <?php foreach($user_roles as $user_role) :?>
                  <!-- Check to see if user role is one of the enabled users who can see this tile -->
                  <?php foreach($user->roles as $key => $value) : ?>
                    <?php if($key == $user_role): ?>
                      <div id="div_<?php print $tile->tile_id;?>" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
                        <a href="" class="flip-btn">
                          <img src="<?php print base_path() . drupal_get_path('module', 'hf_tiles').'/img/question-icon.svg'; ?>" class="svg-info">
                        </a>
                        <div class="flip">
                          <fieldset class="card">
                            <?php if($childCount == 0): ?>
                              <a href="<?php print $tile->path_url;?>">
                            <?php else: ?>
                              <a href="../admin/dashboard/<?php print lcfirst($tile->name);?>">
                            <?php endif; ?>
                              <legend>
                                <i class="<?php print $tile->field_icon_class_value; ?>"></i>
                                <span class="fieldset-legend"><?php print $tile->name;?></span>
                              </legend>
                              <div class="face front form-wrapper"><i class="<?php print $tile->field_icon_class_value; ?>"></i></div>
                            </a>
                            <i class="fi-arrows-out">&#160;</i>
                            <div class="face back">
                              <h3><?php print $tile->name; ?></h3>
                              <p><?php print $tile->description;?></p>
                              <?php if(!empty($tile->help_url)):?>
                                <ul class="button-group">
                                  <li><a href="<?php print $tile->help_url;?>" class="waves-effect waves-button waves-float waves-classic button help-btn">Continue</a></li>
                                </ul>
                              <?php endif; ?>
                              <a href="#" class="close-btn">&#215;</a>
                            </div>
                          </fieldset>
                        </div>
                      </div>
                    <?php endif; ?>
                  <?php endforeach; ?>
              <?php endforeach; ?>
              <?php endif; ?>
            <?php endforeach; ?>
          <?php else: ?>
            <?php
            //Find all children of the parent using the path name.
            $tiles = hf_tiles_get_children(explode("/", request_path())[2]); ?>
            <?php foreach($tiles as $tile): ?>
              <?php $user_roles = array_map('intval', unserialize($tile->user_role)); ?>
              <?php foreach($user_roles as $user_role) :?>
                <!-- Check to see if user role is one of the enabled users who can see this tile -->
                <?php foreach($user->roles as $key => $value) : ?>
                  <?php if($key == $user_role): ?>
                    <div id="div_<?php print $tile->tile_id;?>" draggable="true" class="large-3 medium-6 small-12 columns sortees end ui-sortable-handle">
                      <a href="" class="flip-btn">
                        <img src="<?php print base_path() . drupal_get_path('module', 'hf_tiles').'/img/question-icon.svg'; ?>"ß class="svg-info">
                      </a>
                      <div class="flip">
                        <fieldset class="card">
                          <a href="<?php print $tile->path_url;?>">
                            <legend>
                              <i class="<?php print $tile->field_icon_class_value; ?>"></i>
                              <span class="fieldset-legend"><?php print $tile->name;?></span>
                            </legend>
                            <div class="face front form-wrapper"><i class="<?php print $tile->field_icon_class_value; ?>"></i></div>
                          </a>
                          <i class="fi-arrows-out">&#160;</i>
                          <div class="face back">
                            <h3><?php print $tile->name; ?></h3>
                            <p><?php print $tile->description;?></p>
                            <?php if(!empty($tile->help_url)):?>
                              <ul class="button-group">
                                <li><a href="<?php print $tile->help_url;?>" class="waves-effect waves-button waves-float waves-classic button help-btn">Continue</a></li>
                              </ul>
                            <?php endif; ?>
                            <a href="#" class="close-btn">&#215;</a>
                          </div>
                        </fieldset>
                      </div>
                    </div>
                  <?php endif; ?>
                <?php endforeach; ?>
              <?php endforeach; ?>
            <?php endforeach; ?>
          <?php endif; ?>
        </div>
      </div>
    </div>
  </div>
</div>


<!-- Page load modal -->
<!-- parent div is only for easy code folding in text editor -->
<div>
  <div id="firstModal" class="reveal-modal reveal-no-dismiss" data-reveal data-options="close_on_background_click:false; close_on_esc:false;" aria-labelledby="firstModalTitle" aria-hidden="true" role="dialog">
    <div class="row">
      <div class="columns small-12 medium-12">
        <h1 style="text-align:center;display:block;font-weight:500;">Welcome to your Stack!</h1><hr><br>
        <h2>The Dashboard</h2>
        <p>All of Stacks main features and functions are conveniently located here. To access a feature, simply click on the corresponding tile. To see a description of the feature or to get more help, click on the <span class="modal-icons"><img src="../sites/all/modules/hf_stacks/hf_dashboard/img/question-icon.svg" class="stacks-icon"></span> button in the top-right corner of the tile.  If you’d like to customize the order of the tiles on the dashboard, click on the <span class="modal-icons"><i class="stacks-icon stacks-drag"></i></span> icon and drag the tile into its new location.</p>
        <h2>Build</h2>
        <p>Input your API credentials under <i>Integrations</i> to enable search capabilities and engage your patrons with <i>My Account</i>. Customize the look and feel of your site using <i>My Theme</i>.
          Build the backbone of your website with responsive static content Pages with easy multi-media support and full WYSIWYGs.</p>
        <h2>Create</h2>
        <p>Engage your audience with a robust home page. Create and manage beautiful visual features including: Sliders of images with links; <i>Callouts</i> to important events or sections of the website; and <i>ResourceFlows</i>, scrolling book lists that patrons can request items from.</p>
        <h2>Keep Going!</h2>
        <p>Explore the Dashboard to add additional content including Research Guides, EasyForms, and Events. Use tools such as Directory Listings, Menus and Taxonomies to manage the content throughout your new website.</p>

        <p>Time to get started! To begin building your website, click on the <i>Pages</i> tile on the Dashboard.</p>
      </div>
      <a class="close-reveal-modal" aria-label="Close">&#215;</a>
    </div>
  </div>
</div>

<?php
function checkTileChildren($tiles, $tileid) {
  $tileCount = 0;
  foreach($tiles as $tile) {
    if($tileid == $tile->plid) {
      $tileCount++;
    }
  }
  return $tileCount;
}
?>