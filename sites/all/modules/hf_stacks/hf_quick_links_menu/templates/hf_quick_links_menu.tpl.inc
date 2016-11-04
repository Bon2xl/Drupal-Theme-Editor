<?php 
//global $base_url;   // Will point to http://www.example.com
//global $base_path;  // Will point to at least "/" or the subdirectory where the drupal in 

/**
	* hf_location_bar block callback
	*/
function hf_quick_links_menu_callback() {
	$output .= "<div class='hf-quick-links-menu-container'>";
	$output .= theme('links', array('links' => menu_navigation_links('quick-links-menu')));
	$output .= "</div>";
	return $output;
}




