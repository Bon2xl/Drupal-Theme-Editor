<div class="row views-basic-row">
	<?php /*
	<div class="personal-info patron-info small-12 medium-12 large-12 large-centered columns">
		<div class="drop-down-wrapper">
			<a href="#" class="data-link"><i class="fi-torso"></i></a>
			<div class="data-dropdown views-row">
				<h4>Personal Information</h4>
				<span class="address"><i class="fi-address-book"></i>
					<?php
						 if (!empty($vars['address'])) {
						 print $vars['address'];
						 }
					 ?>
				</span> |
				<span class="phone-number"><i class="fi-telephone"></i>
					<?php
						if (!empty($vars['phone'])) {
						 print $vars['phone'];
					 	}
					 ?>
				</span> |
				<span class="barcode"><i class="fi-results"></i>
					<?php
					 	if (!empty($vars['barcode'])) {
						 print $vars['barcode'];
						}
					 ?>
				</span>
			</div>
		</div>
	</div> 
	*/ ?>
	<div class="patron-info small-12 medium-12 large-12 large-centered columns views-basic-row">
		<div class="row">
			<div class="small-12 medium-12 large-4 columns">
				<div class="views-row">
					<h4><strong>Your Items</strong></h4>

					<ul class="no-bullet">
						<li><strong><?php print $vars['items_out']; ?></strong> - Out</li>
						<li><strong><?php print $vars['items_overdue']; ?></strong> - Overdue</li>
						<li><strong><?php print $vars['items_lost']; ?></strong> - Lost</li>
					</ul>

					<div class="btn-wrapper text-center"><a href="<?php print base_path(); ?>my-account/items" class="button small">View All Your Items</a></div>
				</div>
			</div>

			<div class="small-12 medium-12 large-4 columns">
				<div class="views-row">
					<h4><strong>Your Requests</strong></h4>

					<ul class="no-bullet">
						<li><strong><?php print $vars['holds_current']; ?></strong> - Current</li>
						<li><strong><?php print $vars['holds_shipped']; ?></strong> - Shipped</li>
						<li><strong><?php print $vars['holds_held']; ?></strong> - Held</li>
						<li><strong><?php print $vars['holds_unclaimed']; ?></strong> - Unclaimed</li>
						<li><strong><?php print $vars['holds_total']; ?></strong> - Total</li>
					</ul>

					<div class="btn-wrapper text-center"><a href="<?php print base_path(); ?>my-account/holds" class="button small">View All Requests</a></div>
				</div>
			</div>

			<div class="small-12 medium-12 large-4 columns">
				<div class="views-row">
					<h4><strong><?php print $vars['name_first'].' '.$vars['name_last']; ?></strong></h4>

					<ul class="no-bullet">
						<li><strong>Address:</strong> <?php print $vars['address']; ?></li>
						<li><strong>Email:</strong> <?php print $vars['email_address']; ?></li>
						<li><strong>Phone:</strong> <?php print $vars['phone']; ?></li>
						<li><strong>Barcode:</strong> <?php print $_SESSION['user_bar']; ?></li>
						<li><strong>Patron ID:</strong> <?php print $vars['patron_id']; ?></li>
					</ul>

					<hr />

					<p class="text-center"><strong>Current Fees:</strong> <?php
						if (isset($vars['current_fees'])) {
							$currentfees = (float)$vars['current_fees'];
						} else {
							$currentfees = 0.00;
						}
						// alter fees to display in international format for the en_US locale
						setlocale(LC_MONETARY, 'en_US');
						$currentfees = money_format('%!n', $currentfees);
						?>
						<span class="val">$<?php print $currentfees; ?></span></p>
						<div class="btn-wrapper text-center"><a href="<?php print base_path(); ?>my-account/read" class="button small">View Your Reading History</a></div>
				</div>
			</div>

			<?php include_once drupal_get_path('module', 'hf_stacks_auth').'/include/saved_items.inc'; ?>
		</div>

	</div>
</div>