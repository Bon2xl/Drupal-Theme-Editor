<?php
  // dpm($node);
  // dpm($content);
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

<!-- original -->
<?php print $user_picture; ?>

<?php print render($title_prefix); ?>
<?php if (!$page): ?>
  <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
<?php endif; ?>
<?php print render($title_suffix); ?>

<?php if ($display_submitted): ?>
  <div class="submitted">
    <?php print $submitted; ?>
  </div>
<?php endif; ?>
<!-- end original section -->

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <section class="reserves-details">
    <?php if(isset($node->field_course_date[LANGUAGE_NONE][0]['value'])) : ?>
      <div class="reserves-details-group">
        <span class="reserves-detail-title reserves-date">Course Date</span> <?php // print render($content['field_course_date']['#title']); ?>
        <span class="reserves-detail-info"><?php print render($content['field_course_date'][0]['#markup']); ?></span>
        <!-- <span class="reserves-detail-info"><?php print date('l, F d, Y - G:H', strtotime($node->field_course_date[LANGUAGE_NONE][0]['value'])); ?> *time is wrong & doesn't have end time</span> -->
      </div>
    <?php endif; ?>

    <?php if(isset($content['field_course_title'][0]['#title'])) : ?>
      <div class="reserves-details-group">
        <span class="reserves-detail-title reserves-course">Course</span> <?php // print render($content['field_course_title']['#title']); ?>
        <span class="reserves-detail-info"><?php print render($content['field_course_title'][0]['#title']); ?></span>
  <!--
        <span class="reserves-detail-info"><a href="<?php print render($content['field_course_title'][0]['#href']); ?>"><?php print render($content['field_course_title'][0]['#title']); ?></a> *fix link</span>
  -->
      </div>
    <?php endif; ?>

    <?php if(isset($node->field_course_id[LANGUAGE_NONE][0]['value'])) : ?>
      <div class="reserves-details-group">
        <span class="reserves-detail-title reserves-courseID">Course ID</span>
        <span class="reserves-detail-info"><?php print $node->field_course_id[LANGUAGE_NONE][0]['value']; ?></span>
      </div>
    <?php endif; ?>


    <?php if(isset($node->field_registrar_course_id[LANGUAGE_NONE][0]['value'])) : ?>
      <div class="reserves-details-group">
        <span class="reserves-detail-title reserves-course-regID">Registrar Course ID</span>
        <span class="reserves-detail-info"><?php print $node->field_registrar_course_id[LANGUAGE_NONE][0]['value']; ?></span>
      </div>
    <?php endif; ?>


    <?php if(isset($node->field_first_name_instructor[und][0]['value']) || ($node->field_last_name_instructor[und][0]['value'])) : ?>
      <div class="reserves-details-group">
        <span class="reserves-detail-title reserves-instructor">Instructor Name</span>
        <span class="reserves-detail-info"><?php print $node->field_first_name_instructor[und][0]['value'];?> <?php print $node->field_last_name_instructor[und][0]['value'];?></span>
      </div>
    <?php endif; ?>


    <?php if(isset($content['field_reserves_term'][0]['#title'])) : ?>
      <div class="reserves-details-group">
        <span class="reserves-detail-title reserves-term">Term</span>
        <span class="reserves-detail-info"><?php print render($content['field_reserves_term'][0]['#title']); ?></span>
      </div>
    <?php endif; ?>
<!--
    <div class="reserves-details-group">
      <span class="reserves-detail-title reserves-workflow">Workflow</span>
      <span class="reserves-detail-info"><?php print render($content['field_workflow'][0]['#markup']); ?></span>
    </div>
-->
    <?php hide($content['field_workflow']); ?>
  </section>

  <div class="reserves-content">
    <div class="reserves-body"><?php print render($content['body']['#items'][0]['value']); ?></div>
    <div class="reserves-attachment"><?php print render($content['field_attachment']); ?></div>
    <div class="reserves-share"><?php print render($content['sharethis']); ?></div>

    <?php if(isset($content['comments'])) : ?>
        <div class="reserves-comments">
          <?php
            // We hide the comments and links now so that we can render them later.
            hide($content['comments']);
            hide($content['links']);
          ?>

          <?php print render($content['links']); ?>
          <?php print render($content['comments']); ?>
        </div>
    <?php endif; ?>
  </div>
</div>