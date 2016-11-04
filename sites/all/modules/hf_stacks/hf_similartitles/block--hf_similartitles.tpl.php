<div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
    <?php $arraystuff = $block->arraystuff; ?>
    <?php foreach($arraystuff as $obj): ?>
    <div class="inner-block">
        <?php print render($title_prefix); ?>
        <?php if ($obj->title): ?>
            <h2<?php print $title_attributes; ?>>Test<?php print $obj['title'] ?></h2>
        <?php endif;?>
        <?php print render($title_suffix); ?>

        <div class="content"<?php print $content_attributes; ?>>
            <img src="<?php print($obj['coverSmall']); ?>" />
            <p><?php print $obj['content']; ?></p>
            <p><?php print $obj['author']; ?></p>
        </div>
    </div>
    <?php endforeach; ?>
</div>