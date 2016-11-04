<div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
    <?php $reviews = $block->reviews; ?>
    <?php foreach($reviews as $obj): ?>

    <div class="inner-block">
        <?php print render($title_prefix); ?>
        <?php if ($block->subject): ?>
            <h2<?php print $title_attributes; ?>><?php print $obj['title'] ?></h2>
        <?php endif;?>
        <?php print render($title_suffix); ?>

        <div class="content"<?php print $content_attributes; ?>>
            <p><?php print $obj['content'] ?></p>

            <?php if($obj['author_nickname']): ?>
                <p>Reviewer: <?php print $obj['author_nickname']; ?></p>
            <?php endif;?>

            <?php if($obj['review_city']): ?>
                <p>Review city: <?php print $obj['review_city']; ?></p>
            <?php endif; ?>

            <?php if($obj['review_rating']): ?>
                <p>Review Rating: <?php print $obj['review_rating']; ?></p>
            <?php endif; ?>

        </div>
    </div>

    <?php endforeach; ?>

</div>