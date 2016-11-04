
<div class="row">
	<div class="personal-info">
		<div class="drop-down-wrapper">
			<a href="#" class="data-link"><i class="fi-torso"></i></a>
			<div class="data-dropdown">
				<h4>Personal Information</h4>
				<span class="address"><i class="fi-address-book"></i> <?php print $vars['variable']['AE'][0] ?></span>
				<span class="phone-number"><i class="fi-telephone"></i> <?php print $vars['variable']['AE'][0] ?></span>
				<span class="barcode"><i class="fi-results"></i> <?php print $vars['variable']['AE'][0] ?></span>
			</div>
		</div>
	</div>
	<div class="patron-info large-8 large-centered columns">
		<h4>Patron Information</h4>
		<ul>
			<li>
				<span class="lbl">Name:</span>
				<span class="val"><?php print $vars['variable']['AE'][0] ?></span>
			</li>
			<li>
				<span class="lbl">Account Type:</span>
				<span class="val"><?php print $vars['variable']['PS'][0] ?></span>
			</li>
			<li>
				<span class="lbl">Money owed:</span>
				<span class="val"><?php print $vars['variable']['BV'][0] ?></span>
			</li>
			<li>
				<span class="lbl">Hold Count:</span>
				<span class="val"><?php print $vars['fixed']['HoldCount'] ?></span>
			</li>
			<li>
				<span class="lbl">Overdue Count:</span>
				<span class="val"><?php print $vars['fixed']['OverdueCount'] ?></span>
			</li>
			<li>
				<span class="lbl">Charged Count:</span>
				<span class="val"><?php print $vars['fixed']['ChargedCount'] ?></span>
			</li>
			<li>
				<span class="lbl">Fine Count:</span>
				<span class="val"><?php print $vars['fixed']['FineCount'] ?></span>
			</li>
			<li>
				<span class="lbl">Recall Count:</span>
				<span class="val"><?php print $vars['fixed']['RecallCount'] ?></span>
			</li>
			<li>
				<span class="lbl">Unavailable Count:</span>
				<span class="val"><?php print $vars['fixed']['UnavailableCount'] ?></span>
			</li>
		</ul>
		<h4>Place Hold</h4>
		<?php
		$hold_form = drupal_get_form('hf_stacks_hold_form');
		print drupal_render($hold_form);
		?>
	</div>

	<?php include_once drupal_get_path('module', 'hf_stacks_auth').'/include/saved_items.inc'; ?>

	<?php // require_once DRUPAL_ROOT . '/includes/saved_items.inc'; ?>

</div>

<?php //print_r($vars); ?>
<?php //var_dump($vars); ?>

