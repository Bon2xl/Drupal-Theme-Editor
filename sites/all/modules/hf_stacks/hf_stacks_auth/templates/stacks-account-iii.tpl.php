
<div class="row">
	<div class="personal-info">
		<div class="drop-down-wrapper">
			<a href="#" class="data-link"><i class="fi-torso"></i></a>
			<div class="data-dropdown">
				<h4>Personal Information</h4>
				<span class="address"><i class="fi-address-book"></i> <?php print $vars['ADDRESS[pa]'] ?></span>
				<span class="phone-number"><i class="fi-telephone"></i> <?php print $vars['TELEPHONE[pt]'] ?></span>
				<span class="barcode"><i class="fi-results"></i> <?php print $vars['P BARCODE[pb]'] ?></span>
			</div>		
		</div>		
	</div>
	<div class="patron-info large-8 large-centered columns">
		<h4>Patron Information</h4>
		<ul>
			<li>
				<span class="lbl">Money owed:</span>
				<span class="val"><?php print $vars['MONEY OWED[p96]'] ?></span>
			</li>
			<li>
				<span class="lbl">Expiration Date:</span>
				<span class="val"><?php print $vars['EXP DATE[p43]'] ?></span>
			</li>
			<li>
				<span class="lbl">Current Items Checked Out:</span>
				<span class="val"><?php print $vars['CUR CHKOUT[p50]'] ?></span>
			</li>
			<li>
				<span class="lbl">Total Checkouts:</span>
				<span class="val"><?php print $vars['TOT CHKOUT[p48]'] ?></span>
			</li>
			<li>
				<span class="lbl">Total Checkouts:</span>
				<span class="val"><?php print $vars['TOT CHKOUT[p48]'] ?></span>
			</li>
			<li>
				<span class="lbl">Total Renew:</span>
				<span class="val"><?php print $vars['TOT RENWAL[p49]'] ?></span>
			</li>
		</ul>
	</div>
	<?php include_once drupal_get_path('module', 'hf_stacks_auth').'/include/saved_items.inc'; ?>
</div>

<?php /*
<pre>
	 //print_r($vars) ?>
</pre>
*/?>

