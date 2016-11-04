<?php

/**
 * @file node-nodeblock-default.tpl.php
 *
 * Theme implementation to display a nodeblock enabled block. This template is
 * provided as a default implementation that will be called if no other node
 * template is provided. Any node-[type] templates defined by the theme will
 * take priority over this template. Also, a theme can override this template
 * file to provide its own default nodeblock theme.
 *
 * Additional variables:
 * - $nodeblock: Flag for the nodeblock context.
 */
 global $theme_path;
?>
<?php if($node->type == 'callout'): ?>
  <div class="cta-callout">
    <div class="inner-content">
      <?php
      $field_cta1_title = field_get_items('node', $node, 'field_cta1_title');
      $field_cta1_image = field_get_items('node', $node, 'field_cta1_image');
      $field_cta1_image_url = $field_cta1_image[0]['uri'] ? file_create_url($field_cta1_image[0]['uri']) : ''.base_path().drupal_get_path('theme', 'hfstacks').'/assets/img/no-img.png';
      $field_cta1_link = field_get_items('node', $node, 'field_cta1_link');
      $field_intro_text_cta1 = field_get_items('node', $node, 'field_intro_text_cta1');
      $field_additional_link_cta1 = field_get_items('node', $node, 'field_additional_link_cta1');
      // Check if URL is avaible
      $is_imgURL1 = !empty($field_cta1_image[0]['uri']) ? "imgURL" : "no-imgURL";

      if ((!empty($field_cta1_title)) || (!empty($field_cta1_image)))  {
        echo "<div class=\"views-field views-field-nothing large-3 columns\">";
          echo "<span class=\"field-content\">";
            echo "<span class=\"imgHolder ".$is_imgURL1."\" >";
              echo "<a href=\"".$field_cta1_link[0]['url']."\">";
                echo "<img alt=\"\" src=\"".drupal_get_path('theme', 'hfstacks') . "/assets/img/cta-image.png\" data-url-path=\"".$field_cta1_image_url."\" style=\"background-image:url(".$field_cta1_image_url.")\" typeof=\"foaf:Image\">";
              echo "</a>";
            echo "</span>";
            echo "<span class=\"wrap-details\">";
              echo "<span class=\"cta-title\">";
                echo "<a href=\"".$field_cta1_link[0]['url']."\">";
                  echo $field_cta1_title[0]['value'];
                echo "</a>";
              echo "</span>";

              echo "<span class=\"teaser-cont\">";

              if (!empty($field_intro_text_cta1)) {
                echo "<div class=\"cta-description\">";
                  echo $field_intro_text_cta1[0]['value'];
                echo "</div>";
              }


            // get all fields values if additional links exist
              if (!empty($field_additional_link_cta1)) {
                echo "<div class=\"item-list\">";
                  echo "<ul>";
                  foreach ($field_additional_link_cta1 as $add_links) {
                    echo "<li>";
                      echo "<a href=\"".$add_links['url']."\" target=\"_blank\">".$add_links['title']."</a>";
                    echo "</li>";
                  }
                  echo "</ul>";
                echo "</div>";
              }
            echo "</span>";
          echo "</span>";
        echo "</div>";
      }

      $field_cta2_title = field_get_items('node', $node, 'field_cta2_title');
      $field_cta2_image = field_get_items('node', $node, 'field_cta2_image');
      $field_cta2_image_url = $field_cta2_image[0]['uri'] ? file_create_url($field_cta2_image[0]['uri']) : ''.base_path().drupal_get_path('theme', 'hfstacks').'/assets/img/no-img.png';
      $field_cta2_link = field_get_items('node', $node, 'field_cta2_link');
      $field_intro_text_cta2 = field_get_items('node', $node, 'field_intro_text_cta2');
      $field_additional_link_cta2 = field_get_items('node', $node, 'field_additional_link_cta2');
      // Check if URL is avaible
      $is_imgURL2 = !empty($field_cta2_image[0]['uri']) ? "imgURL" : "no-imgURL";

      if ((!empty($field_cta2_title)) || (!empty($field_cta2_image))) {
        echo "<div class=\"views-field views-field-nothing large-3 columns\">";
          echo "<span class=\"field-content\">";
            echo "<span class=\"imgHolder ".$is_imgURL2."\">";
              echo "<a href=\"".$field_cta2_link[0]['url']."\">";
                echo "<img alt=\"\" src=\"".drupal_get_path('theme', 'hfstacks') . "/assets/img/cta-image.png\" data-url-path=\"".$field_cta2_image_url."\" style=\"background-image:url(".$field_cta2_image_url.")\" typeof=\"foaf:Image\">";
              echo "</a>";
            echo "</span>";
            echo "<span class=\"wrap-details\">";
              echo "<span class=\"cta-title\">";
                echo "<a href=\"".$field_cta2_link[0]['url']."\">";
                  echo $field_cta2_title[0]['value'];
                echo "</a>";
              echo "</span>";

              echo "<span class=\"teaser-cont\">";

                if (!empty($field_intro_text_cta2)) {
                  echo "<div class=\"cta-description\">";
                    echo $field_intro_text_cta2[0]['value'];
                  echo "</div>";
                }

                // get all fields values if additional links exist
                if (!empty($field_additional_link_cta2)) {
                  echo "<div class=\"item-list\">";
                    echo "<ul>";
                    foreach ($field_additional_link_cta2 as $add_links) {
                      echo "<li>";
                        echo "<a href=\"".$add_links['url']."\" target=\"_blank\">".$add_links['title']."</a>";
                      echo "</li>";
                    }
                    echo "</ul>";
                  echo "</div>";
                }
              echo "</span>";
            echo "</span>";
          echo "</span>";
        echo "</div>";
      }

      $field_cta3_title = field_get_items('node', $node, 'field_cta3_title');
      $field_cta3_image = field_get_items('node', $node, 'field_cta3_image');
      $field_cta3_image_url = $field_cta3_image[0]['uri'] ? file_create_url($field_cta3_image[0]['uri']) : ''.base_path().drupal_get_path('theme', 'hfstacks').'/assets/img/no-img.png';
      $field_cta3_link = field_get_items('node', $node, 'field_cta3_link');
      $field_intro_text_cta3 = field_get_items('node', $node, 'field_intro_text_cta3');
      $field_additional_link_cta3 = field_get_items('node', $node, 'field_additional_link_cta3');
      // Check if URL is avaible
      $is_imgURL3 = !empty($field_cta3_image[0]['uri']) ? "imgURL" : "no-imgURL";

      if ((!empty($field_cta3_title)) || (!empty($field_cta3_image))) {
        echo "<div class=\"views-field views-field-nothing large-3 columns\">";
          echo "<span class=\"field-content\">";
            echo "<span class=\"imgHolder ".$is_imgURL3."\">";
              echo "<a href=\"".$field_cta3_link[0]['url']."\">";
                echo "<img alt=\"\" src=\"".drupal_get_path('theme', 'hfstacks') . "/assets/img/cta-image.png\" data-url-path=\"".$field_cta3_image_url."\" style=\"background-image:url(".$field_cta3_image_url.")\" typeof=\"foaf:Image\">";
              echo "</a>";
            echo "</span>";

            echo "<span class=\"wrap-details\">";
              echo "<span class=\"cta-title\">";
                echo "<a href=\"".$field_cta3_link[0]['url']."\">";
                  echo $field_cta3_title[0]['value'];
                echo "</a>";
              echo "</span>";

              echo "<span class=\"teaser-cont\">";

                if (!empty($field_intro_text_cta3)) {
                  echo "<div class=\"cta-description\">";
                    echo $field_intro_text_cta3[0]['value'];
                  echo "</div>";
                }

                // get all fields values if additional links exist
                if (!empty($field_additional_link_cta3)) {
                  echo "<div class=\"item-list\">";
                    echo "<ul>";
                      foreach ($field_additional_link_cta3 as $add_links) {
                        echo "<li>";
                          echo "<a href=\"".$add_links['url']."\" target=\"_blank\">".$add_links['title']."</a>";
                        echo "</li>";
                      }
                    echo "</ul>";
                  echo "</div>";
                }
              echo "</span>";
            echo "</span>";
          echo "</span>";
        echo "</div>";
      }

      $field_cta4_title = field_get_items('node', $node, 'field_cta4_title');
      $field_cta4_image = field_get_items('node', $node, 'field_cta4_image');
      $field_cta4_image_url = $field_cta4_image[0]['uri'] ? file_create_url($field_cta4_image[0]['uri']) : ''.base_path().drupal_get_path('theme', 'hfstacks').'/assets/img/no-img.png';
      $field_cta4_link = field_get_items('node', $node, 'field_cta4_link');
      $field_intro_text_cta4 = field_get_items('node', $node, 'field_intro_text_cta4');
      $field_additional_link_cta4 = field_get_items('node', $node, 'field_additional_link_cta4');
      // Check if URL is avaible
      $is_imgURL4 = !empty($field_cta4_image[0]['uri']) ? "imgURL" : "no-imgURL";

      if ((!empty($field_cta4_title)) || (!empty($field_cta4_image))) {
        echo "<div class=\"views-field views-field-nothing large-3 columns\">";
          echo "<span class=\"field-content\">";
            echo "<span class=\"imgHolder ".$is_imgURL4."\">";
              echo "<a href=\"".$field_cta4_link[0]['url']."\">";
                echo "<img alt=\"\" src=\"".drupal_get_path('theme', 'hfstacks') . "/assets/img/cta-image.png\" data-url-path=\"".$field_cta4_image_url."\" style=\"background-image:url(".$field_cta4_image_url.")\" typeof=\"foaf:Image\">";
              echo "</a>";
            echo "</span>";

            echo "<span class=\"wrap-details\">";
              echo "<span class=\"cta-title\">";
                echo "<a href=\"".$field_cta4_link[0]['url']."\">";
                  echo $field_cta4_title[0]['value'];
                echo "</a>";
              echo "</span>";

              echo "<span class=\"teaser-cont\">";

                if (!empty($field_intro_text_cta4)) {
                  echo "<div class=\"cta-description\">";
                    echo $field_intro_text_cta4[0]['value'];
                  echo "</div>";
                }

                // get all fields values if additional links exist
                if (!empty($field_additional_link_cta4)) {
                  echo "<div class=\"item-list\">";
                    echo "<ul>";
                      foreach ($field_additional_link_cta4 as $add_links) {
                        echo "<li>";
                          echo "<a href=\"".$add_links['url']."\" target=\"_blank\">".$add_links['title']."</a>";
                        echo "</li>";
                      }
                    echo "</ul>";
                  echo "</div>";
                }
              echo "</span>";
            echo "</span>";
          echo "</span>";
        echo "</div>";
      }
      ?>
    </div>
  </div>
<?php elseif($node->type == 'resource_list'): ?>
  <div class="sg-block coverflow">
    <div class="inner-content">
      <?php
      // get field collections from node
      $field_items = field_get_items('node', $node, 'field_items');

      // get all fields values if collection exists
      if (!empty($field_items)) {
        foreach ($field_items as $id) {
          echo "<div class=\"views-row\">";
            // load the field collection item entity
            $field_collection_item = field_collection_item_load($id['value']);

            // wrap the entity and make it easier to get the values of fields
            $field_wrapper = entity_metadata_wrapper('field_collection_item', $field_collection_item);

            // all values from a field collection
            $field_label   = $field_wrapper->field_title->value();
            $field_link   = $field_wrapper->field_hard_link->value();
            $field_isbn   = $field_wrapper->field_isbn->value();
            $field_upc   = $field_wrapper->field_upc->value();
            $field_bibid   = $field_wrapper->field_bibid->value();
            $field_image  = $field_wrapper->field_resource_image->value(); // an array of image data

            $image_url    = $field_image['uri'] ? file_create_url($field_image['uri']) : '';

            echo "<div class=\"views-field views-field-field-isbn\">";
              echo "<a href=\"".$field_link."\">";
                echo "<span data-cover-isbn=\"".$field_isbn."\">";
                  echo "<img src=\"".$image_url."\">";
                echo "</span>";
              echo "</a>";
            echo "</div>";

            echo "<div class=\"views-field views-field-field-title\">";
              echo "<strong class=\"field-content\">";
                echo "<strong>";
                  echo "<a href=\"".$field_link."\">".$field_label."</a>";
                echo "</strong>";
              echo "</strong>";
            echo "</div>";

            echo "<div class=\"views-field views-field-field-author\">";
              echo "<div class=\"field-content\"></div>";
            echo "</div>";
          echo "</div>";
        }
      }
      ?>
    </div>
  </div>
<?php elseif($node->type == 'slider'): ?>
  <div class="big-slider">
    <div class="inner-content">
      <div id="slider-<?php echo $node->nid; ?>" class="view-content">
        <?php
        // get field collections from node
        $field_slideshow = field_get_items('node', $node, 'field_slideshow');

        // get all fields values if collection exists
        if (!empty($field_slideshow)) {
          foreach ($field_slideshow as $id) {
            echo '<div class="views-row">';
            // load the field collection item entity
            $field_collection_item = field_collection_item_load($id['value']);
            // wrap the entity and make it easier to get the values of fields
            $field_wrapper = entity_metadata_wrapper('field_collection_item', $field_collection_item);

            // all values from a field collection
            $field_link   = $field_wrapper->field_slideshow_link->value();
            $field_body   = $field_wrapper->field_body->value();
            $field_image  = $field_wrapper->field_slideshow_image->value(); // an array of image data

            $image_url    = $field_image['uri'] ? file_create_url($field_image['uri']) : '';

            echo '<a class="img-link" href="'.$field_link['url'].'"></a>';
            echo '<div class="img-wrapper">';
            echo '<img src="'.$image_url.'" />';
            if(!empty($field_body['value'])) {
              echo '<div class="views-field-field-body">';
              echo $field_body['value'];
              echo '</div>';
            }

            echo '</div>';
            echo "</div>";
          }
        }
        ?>
      </div>
    </div>
  </div>
<?php elseif($node->type == 'slider_mini'): ?>
  <div class="mini-slider">
    <div class="inner-content">
      <div id="minislider-<?php echo $node->nid; ?>" class="slider-content">
        <?php
        // get field collections from node
        $field_slideshow_mini = field_get_items('node', $node, 'field_slideshow_mini');

        // get all fields values if collection exists
        if (!empty($field_slideshow_mini)) {
          foreach ($field_slideshow_mini as $id) {
            echo '<div class="views-row">';
            // load the field collection item entity
            $field_collection_item = field_collection_item_load($id['value']);
            // wrap the entity and make it easier to get the values of fields
            $field_wrapper = entity_metadata_wrapper('field_collection_item', $field_collection_item);

            // all values from a field collection
            $field_label   = $field_wrapper->field_title->value();
            $field_link   = $field_wrapper->field_slideshow_mini_link->value();
            $field_image  = $field_wrapper->field_slideshow_mini_image->value(); // an array of image data

            $image_url    = $field_image['uri'] ? file_create_url($field_image['uri']) : '';

            echo '<a class="img-link" href="'.$field_link['url'].'"></a>';
            echo '<div class="img-wrapper">';
            echo '<img src="'.$image_url.'" />';
            echo '</div>';
            echo '<span class="ttl">&nbsp;&nbsp;'.$field_label.'</span>';
            echo "</div>";
          }
        }
        ?>
      </div>
    </div>
  </div>
<?php else: ?>
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <?php print $user_picture; ?>
    <?php print render($title_prefix); ?>
    <?php if (!$page && !$nodeblock): ?>
      <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>

    <?php if ($display_submitted): ?>
      <div class="submitted">
        <?php
        print t('Submitted by !username on !datetime',
          array('!username' => $name, '!datetime' => $date));
        ?>
      </div>
    <?php endif; ?>

    <div class="content"<?php print $content_attributes; ?>>
      <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
      ?>
    </div>
    <?php //print render($content['links']); ?>
    <?php //print render($content['comments']); ?>
  </div>
<?php endif; ?>
