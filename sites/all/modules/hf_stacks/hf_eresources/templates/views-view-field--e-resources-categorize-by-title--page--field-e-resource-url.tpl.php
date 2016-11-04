<?php
/**
 * This template is used to print a single field in a view. It is not
 * actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the
 * template is perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php
//var_dump($row->field_field_e_resource_url[0]['raw']['url']);
$link = $row->field_field_e_resource_url[0]['raw'];
$url = $row->field_field_ezproxy_url;
$whitelist = variable_get('hf_eresources_whitelist');
$ip_address = ip_address();
$user_local = FALSE;


for ($i = 0; $i < count($whitelist); $i++) {
	if ($ip_address <= $whitelist[$i]['e'] && $whitelist[$i]['s'] <= $ip_address) {
		$user_local = TRUE;
	}
}

// example return for $link:
//  'url' => string 'http://infotrac.galegroup.com/itweb/reginaplweb?db=BNA' (length=54)
//  'title' => string 'BNA' (length=3)
//  'attributes' =>
//    array (size=0)
//      empty
//			'display_url' => string 'http://infotrac.galegroup.com/itweb/reginaplweb?db=BNA' (length=54)
//  'html' => boolean true

if ( (!user_is_logged_in()) && ($user_local == FALSE) ): ?>
	<strong> <?php print $link['title'] ?></strong><br>
	<a href="/" class="login-link">Login required</a>
<?php else: ?>

	<?php
	global $user;
	// detecting patron

	$patron = explode('patron_', $user->name);
	$patron = isset($patron[1]) ? $patron[1] : '';
	$pin = isset($_SESSION['pin']) ? $_SESSION['pin'] : '';
	?>
	<a href="#" class="ezproxy-submit"><strong><?php print $link['title'] ?></strong></a>
	<form action="<?php print $url[0]['raw']['value'] ?>" method="post" class="hide ezproxy">
		<input name="url" type="text" value="<?php print $link['url'] ?>">
		<input name="user" type="text" value="<?php print $patron ?>">
		<input name="pass" type="password" value="<?php print $pin ?>">
	</form>

<?php endif ?>
