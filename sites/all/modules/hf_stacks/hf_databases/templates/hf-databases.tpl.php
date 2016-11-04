<?php $param = drupal_get_query_parameters(); ?>

<aside class="large-3 sidebar-first columns sidebar" role="complementary">
	<?php print drupal_render(drupal_get_form('hf_databases_form_search')); ?>
	<?php print drupal_render(drupal_get_form('hf_databases_form_filter')); ?>
	<?php print hf_databases_featured_databases(); ?>

</aside>
<div class="large-9 main columns">
	<!-- Carousel of Database Images go Here   -->
	<?php print hf_databases_logo_slider_load(); ?>
	<div class="view-eresources">
		<div class="eresources-group">
			<?php if(!isset($param['search'])) { ?>
				<?php foreach($vars as $category=>$databases) {?>
					<?php if($category == 'None') { ?>
						<?php if($param['filter'] == 'all' || $param['filter'] == null) { ?>
							<?php foreach($databases as $database)  { ?>
								<!-- Display all Categories and Listings (Accordions and Direct Links) -->
								<div class="view-resource-single">
									<h3><a href="<?php echo $database->field_ezproxy_url_value; ?>"><?php echo t($database->title); ?></a></h3>
								</div>
							<?php } //End of Foreach of Databases with All Filter ?>
						<?php } else { ?>
							<!--   Category Accordion with Databases Listed Inside, any listings without a database will be under Unlisted    -->
							<div class="view-eresources">
								<div class="e-resources-group">
									<h3 class="eresource-title"><a href="#"><?php echo t('Unlisted'); ?></a></h3>
									<div class="eresources-items">
										<?php foreach($databases as $database) { ?>
											<div class="views-row">
												<h5><a href="<?php echo $database->field_ezproxy_url_value; ?>"><?php echo t($database->title); ?></a></h5>
												<p><?php echo t($database->body_value); ?></p>
												<a href="<?php echo $database->field_ezproxy_url_value; ?>"><?php echo $database->field_ezproxy_url_value; ?></a>
											</div>
										<?php } //End of Foreach of Databases with Categories ?>
									</div>
								</div>
							</div>
						<?php } ?>
					<?php } else { ?>
						<!--   Filter is NOT 'all'     -->
						<div class="view-eresources">
							<div class="eresources-group">
								<?php if($databases[0]->uri !== null && $param['filter'] !== 'title') { ?>
									<h3 class="eresource-title">
										<a href="#">
											<span class="db-logo"><img src="<?php echo file_create_url($databases[0]->uri);?>"/></span>
											<span class="db-cat-name"><?php echo $category; ?></span>
										</a>
									</h3>
								<?php } else { ?>
									<h3 class="eresource-title"><a href="#"><?php echo $category; ?></a></h3>
								<?php } ?>

								<div class="eresources-items">
									<?php foreach($databases as $database) { ?>
										<div class="views-row">
											<h5><a href="<?php echo $database->field_ezproxy_url_value; ?>"><?php echo t($database->title); ?></a></h5>
											<p><?php echo t($database->body_value); ?></p>
										</div>
									<?php } //End of Foreach of Databases with Categories ?>
								</div>
							</div>
						</div>
					<?php } // End of Condition Checking for Category ?>
				<?php } //End of Full Iteration ?>

			<?php } else { ?>

				<?php foreach($vars as $database) { ?>

					<!-- Search Query is Entered and Database Listings are listed without accordions -->
					<div class="view-resource-single">
						<h3><a href="<?php echo $database->field_ezproxy_url_value; ?>"><?php echo t($database->title); ?></a></h3>
					</div>

				<?php } //End of Foreach of Vars when No Query Entered ?>



			<?php } //End of Search Param Check ?>
		</div>
	</div>
</div>
