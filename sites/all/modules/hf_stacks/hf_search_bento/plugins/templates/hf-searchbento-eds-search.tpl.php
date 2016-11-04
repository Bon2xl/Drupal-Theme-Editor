<div class="ajaxResult bnt-container">
	<!--  Unique ID for DIV that corresponds to the $delta of the block. Needed for AJAX to append to this DIV -->
	<div id="ajax<?php echo str_replace(" ", "-", $delta); ?>" class="bnt-inner">
		<div class="bnt-ttl">
			<!--  The specific heading of the block (e.g., Books, Academic Journals, etc.) -->
			<?php
			if (!empty($title)) {
				echo "<h2>".$title."</h2>";
			} else {
				echo "<h2>".$sourceType."</h2>";
			}
			?>
		</div>
		<div class="bnt-item">
			<div class="bnt-content"></div>
			<!--  This seeMore Button will conditionally appear based on logic within the javascript file    -->
			<a class="bnt-see-more" id="seeMoreButton<?php echo str_replace(" ", "-", $sourceType);?>" href="#">See More...</a>
			<div class="ajax-loader">
				<img src=" <?php echo drupal_get_path('module', 'hf_search_bento') . '/images/ajax-loader.gif'; ?>">
			</div>
		</div>
	</div>
</div>