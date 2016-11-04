<?php //print_r($vars); ?>
<?php if(!array_filter($vars)): ?>
<div class="views-module view-items">
  <div class="alert-box info radius">You have no items checked out at this time.</div>
</div>
<?php else: ?>
<div class="views-module view-items">
	<?php foreach ($vars as $key => $value) : ?>
		<?php
		$isbnCount = 0;
		$isbnNum = '';
		if (!empty($value['isbn'])) {
			if ($isbnCount == 0) {
				$isbnNum = $value['isbn'];
			}
		}
		?>
		<div class="views-row">
			<div class="book-jacket">
				<img src="http://contentcafe2.btol.com/ContentCafe/jacket.aspx?UserID=ebsco-test&Password=ebsco-test&Return=T&Type=S&Value=<?php print $isbnNum; ?>">
			</div>
			<div class="item-details">
				<h3 class="title">
					<strong class="highlight"><?php print $value['title']; ?></strong>
				</h3>
				<?php if (!empty($value['author'])): ?>
					<strong class="lbl">Authors : </strong>
					<?php print $value['author']; ?>
					<br />
				<?php endif ?>
				<?php if (!empty($value['format_description'])): ?>
					<strong class="lbl">Format : </strong>
					<?php print $value['format_description']; ?>
					<br />
				<?php endif ?>
				<?php if (!empty($value['call_number'])): ?>
					<strong class="lbl">Call Number : </strong>
					<?php print $value['call_number']; ?>
					<br />
				<?php endif ?>

				<?php if (!empty($value['barcode'])): ?>
					<strong class="lbl">Barcode : </strong>
					<?php print $value['barcode']; ?>
					<br />
				<?php endif ?>
				<?php if (!empty($value['bib_id'])): ?>
					<strong class="lbl">Bib ID : </strong>
					<?php print $value['bib_id']; ?>
					<br />
				<?php endif ?>

				<?php if (!empty($value['isbn'])): ?>
					<strong class="lbl">ISBN : </strong>
					<?php print $value['isbn']; ?>
					<br />
				<?php endif ?>
				<?php if (!empty($value['issn'])): ?>
					<strong class="lbl">ISSN : </strong>
					<?php print $value['issn']; ?>
					<br />
				<?php endif ?>
				<?php if (!empty($value['upc'])): ?>
					<strong class="lbl">UPC : </strong>
					<?php print $value['upc']; ?>
					<br />
				<?php endif ?>

				<?php if (!empty($value['renewal_count'])): ?>
					<strong class="lbl">Renewal Count : </strong>
					<?php print $value['renewal_count']; ?>
					<br />
				<?php else: ?>
					<strong class="lbl">Renewal Count : 0</strong>
					<br />
				<?php endif ?>
				<?php if (!empty($value['renewal_limit'])): ?>
					<strong class="lbl">Renewal Limit : </strong>
					<?php print $value['renewal_limit']; ?>
					<br />
				<?php endif ?>

				<?php if (!empty($value['checkout_date'])): ?>
					<strong class="lbl">Checkout Date : </strong>
					<?php print date("F j, Y, g:i a", strtotime($value['checkout_date'])); ?>
					<br />
				<?php endif ?>
				<?php if (!empty($value['due_date'])): ?>
					<strong class="lbl">Due Date : </strong>
					<?php print date("F j, Y, g:i a", strtotime($value['due_date'])); ?>
					<br />
				<?php endif ?>
				<?php if (!empty($value['format_description'])): ?>
					<strong class="lbl">Format : </strong>
					<?php print $value['format_description']; ?>
					<br />
				<?php endif ?>
			</div>
			<?php print "<div class='save-item-hold'><a href=\"/my-account/items/renew/".$value['item_id']."\" class=\"btn-renew\">Renew Item</a></div>" ?>
		</div>
	<?php endforeach; ?>
</div>
<?php endif ?>