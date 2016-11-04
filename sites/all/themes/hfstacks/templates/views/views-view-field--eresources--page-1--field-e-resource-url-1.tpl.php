<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php
$proxy = '';
$url = '';
$patron = '';
$pin = '';
$form = '';
$title = '';

global $user;
if (!empty($user->name)) {
  $patron = explode('patron_', $user->name);
  $patron = isset($patron[1]) ? $patron[1] : '';
  $pin = isset($_SESSION['user_pin']) ? $_SESSION['user_pin'] : '';
}

if (!empty($row->field_field_ezproxy_url)) {
  $title = $row->field_field_e_resource_url[0][raw][title];

  $form = str_replace(' ', '', $title);
  $form = str_replace(';', '', $form);
  $form = str_replace(',', '', $form);

  $proxy = $row->field_field_ezproxy_url[0][raw][value];

  $url = $row->field_field_e_resource_url[0][raw][url];
}


//$proxy = 'http://ezproxy.aprpls.talonline.ca/login?';
//$url = 'http://library.pressdisplay.com';
//$patron = '20113001265534';
//$pin = '5105';

?>
<div class="eresources-group">
	<div class="eresources-items">
  <?php //dpm($row); ?>
	<?php //dpm($row->field_field_e_resource_url[0][raw][title]); ?>
		<?php //print $row->field_field_e_resource_url[0][raw][title]; ?>
		<a href="#" class="ezproxy-submit" onclick="document.forms['<?php print $form; ?>'].submit();"><?php print $title; ?></a>

    <form action="<?php print $proxy; ?>" name="<?php print $form; ?>" method="post" class="hide ezproxy">
      <input name="url" type="text" value="<?php print $url; ?>">
      <input name="user" type="text" value="<?php print $patron; ?>">
      <input name="pass" type="text" value="<?php print $pin; ?>">
    </form>
  </div>

</div>
