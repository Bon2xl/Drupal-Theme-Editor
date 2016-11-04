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
if(drupal_lookup_path('alias', current_path()) == strtolower($node->title) || current_path() == "node/" . $node->nid):

?>
  <!--   Current path is the node's home page so it displays as a listing -->
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>


  <div class="content"<?php print $content_attributes; ?>>
    <?php
    $items = field_get_items('node', $node, 'field_flipster_info');

    foreach ($items as $item) {
      $field_collection_item = field_collection_item_load($item['value']);
      //dpm($field_collection_item);
      $field_wrapper = entity_metadata_wrapper('field_collection_item', $field_collection_item);

      $field_title = $field_wrapper->field_flipster_title->value();
      $field_category = $field_wrapper->field_flipster_category->value();
      $field_publisher = $field_wrapper->field_flipster_publisher->value();
      $field_image = $field_wrapper->field_image_url->value();
      $field_issn = $field_wrapper->field_flipster_issn->value();
      $field_url = $field_wrapper->field_url->value();
      $field_description = $field_wrapper->field_flipster_description->value();

      print "<div class=\"large-12 columns\">";
      print "<div class=\"large-2 columns\">";
      if($field_image != '') {
        print "<img src=\"" . $field_image .  "\" width=\"100\">";
      }
      print "</div>";
      print "<div class=\"large-10 columns\">";
      print "<p><strong>Title:</strong> ". $field_title . "</p>";
      print "<p><strong>Category:</strong> ". $field_category . "</p>";
      if($field_publisher) {
        print "<p><strong>Publisher:</strong> ". $field_publisher . "</p>";
      }
      if($field_issn) {
        print "<p><strong>ISSN:</strong> ". $field_issn . "</p>";
      }
      if($field_description) {
        print "<p><strong>Description:</strong> ". $field_description . "</p>";
      }
      print "</div>";
      print "</div>";
      print "<hr>";
    }
    ?>
  </div>

</div>

<?php else: ?>
<!--    Node outputs as a Slider as current path is not the Node's main page -->
<div class="sg-block coverflow flipster">
  <div class="inner-content">
    <?php

    $field_items = field_get_items('node', $node, 'field_flipster_info');
    if(!empty($field_items)) {
      foreach($field_items as $id) {

        $field_collection_item = field_collection_item_load($id['value']);
        $field_wrapper = entity_metadata_wrapper('field_collection_item', $field_collection_item);

        $field_title = $field_wrapper->field_flipster_title->value();
        $field_image = $field_wrapper->field_image_url->value();
        $field_issn = $field_wrapper->field_flipster_issn->value();
        $field_url = $field_wrapper->field_url->value();

        if($field_image != '') {
          print "<div class=\"views-row\">";
          print "<div class=\"views-field\">";
          //print "<a href=\"".$field_url."\" target=\"_blank\">";
          print "<img src=\"". $field_image . "\">";
          //print "</a>";
          print "</div>";

          print "<div class=\"views-field views-field-field-title\">";
          print "<div class=\"field-content\">";
          //print "<a href=\"". $field_url . "\">".$field_title."</a>";
          print "<a href='javascript:void(0)' style='cursor:default'>".$field_title."</a>";
          print "</div>";
          print "</div>";
          print "</div>";
        }

      }
    }
    ?>
  </div>
</div>
<?php endif; ?>
