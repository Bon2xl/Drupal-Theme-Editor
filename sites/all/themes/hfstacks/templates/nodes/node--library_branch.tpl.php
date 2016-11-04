<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<?php $maps_key = variable_get('hf_stacks_maps_api_key', ''); ?>
<?php if (!empty($maps_key)):?>
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <?php print render($title_prefix); ?>
    <?php if (!$page): ?>
      <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>

    <div class="content"<?php print $content_attributes; ?>>
      <?php
        if (!empty($content['group_branch_group_location']['field_branch_street_address'])) {
          print "<h2>Address</h2>";
        }
        print render($content['group_branch_group_location']['field_branch_street_address']);
        print render($content['group_branch_group_location']['field_branch_city']);
        print render($content['group_branch_group_location']['field_branch_postal_code_zip']);
        print render($content['group_branch_group_location']['field_branch_state_province']);
        print render($content['group_branch_group_location']['field_branch_country']);
      ?>

      <?php
        if (!empty($content['field_branch_phone'])) {
          print "<h2>Contact Info</h2>";
        }
        print render($content['field_branch_phone']);
        print render($content['field_branch_fax']);
        print render($content['field_branch_email']);
      ?>

      <?php
        if ( (!empty($content['field_branch_sunday'])) || (!empty($content['field_branch_monday'])) || (!empty($content['field_branch_tuesday'])) || (!empty($content['field_branch_wednesday'])) || (!empty($content['field_branch_thursday'])) || (!empty($content['field_branch_friday'])) || (!empty($content['field_branch_saturday'])) ) {
          print "<h2>Hours</h2>";
        }
        print render($content['field_branch_sunday']);
        print render($content['field_branch_monday']);
        print render($content['field_branch_tuesday']);
        print render($content['field_branch_wednesday']);
        print render($content['field_branch_thursday']);
        print render($content['field_branch_friday']);
        print render($content['field_branch_saturday']);
      ?>

      <?php if(!empty($content['field_google_places_query'])): ?>
        <?php
          $lat = $content['field_google_places_query']['#object']->field_branch_geocode['und'][0]['lat'];
          $long = $content['field_google_places_query']['#object']->field_branch_geocode['und'][0]['lon'];

          $city = $content['field_google_places_query']['#object']->field_branch_city['und'][0]['value'];
          $city = str_replace(' ', '+', $city);
          $country = $content['field_google_places_query']['#object']->field_branch_country['und'][0]['value'];
          $country = str_replace(' ', '+', $country);
          $zip = $content['field_google_places_query']['#object']->field_branch_postal_code_zip['und'][0]['value'];
          $zip = str_replace(' ', '+', $zip);
          $state = $content['field_google_places_query']['#object']->field_branch_state_province['und'][0]['value'];
          $state = str_replace(' ', '+', $state);
          $address = $content['field_google_places_query']['#object']->field_branch_street_address['und'][0]['value'];
          $address2 = str_replace(' ', '+', $address);

          $map_address = $address2 . '+' . $city . '+' . $state . '+' . $zip . '+' . $country;
        ?>

        <!-- google map -->
        <h2>Map</h2>

        <div id="gmap_canvas" style="width:100%; height:300px;">Loading map...</div>
        <script type="text/javascript">
          function init_map() {
            var myOptions = {
              zoom: 14,
              center: new google.maps.LatLng(<?php echo $lat; ?>, <?php echo $long; ?>),
              mapTypeId: google.maps.MapTypeId.ROADMAP
            };
            map = new google.maps.Map(document.getElementById("gmap_canvas"), myOptions);
            marker = new google.maps.Marker({
              map: map,
              position: new google.maps.LatLng(<?php echo $lat; ?>, <?php echo $long; ?>)
            });
            infowindow = new google.maps.InfoWindow({
              content: "<?php echo $address; ?>"
            });
            google.maps.event.addListener(marker, "click", function () {
              infowindow.open(map, marker);
            });
            infowindow.open(map, marker);
          }
          google.maps.event.addDomListener(window, 'load', init_map);
        </script>
      </div>

    <?php endif; ?>
  </div>
<?php endif; ?>