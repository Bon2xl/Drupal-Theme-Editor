<div class="ajaxResult bnt-container">
	<!--  Unique ID for DIV that corresponds to the $delta of the block. Needed for AJAX to append to this DIV -->
	<div id="ajax<?php echo str_replace(" ", "-", $delta); ?>" class="bnt-inner">
		<div class="bnt-ttl">
			<!--  The specific heading of the block (e.g., Books, Academic Journals, etc.) -->
			<h2><?php echo $sourceType; ?></h2>
		</div>
		<div class="bnt-item">
			<div class="bnt-content"></div>
			<div class="ajax-loader">
				<img src=" <?php echo drupal_get_path('module', 'hf_search_bento') . '/images/ajax-loader.gif'; ?>">
			</div>
		</div>
	</div>
</div>