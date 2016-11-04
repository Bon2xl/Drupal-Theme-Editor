<div id="patron-login-modal" class="reveal-modal" data-reveal>
	<div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
		<div class="inner-block">
			<?php print render($title_prefix); ?>
			<?php if ($block->subject): ?>
				<h2<?php print $title_attributes; ?>><?php print $block->subject ?></h2>
			<?php endif;?>
			<?php print render($title_suffix); ?>

			<div class="content"<?php print $content_attributes; ?>>
				<?php print $content ?>
			</div>
		</div>
	</div>
	<a class="btn-close close-reveal-modal" aria-label="Close">&#215;</a>
</div>