<?php 
global $base_url;
global $base_path;
global $theme;

/**
	* hf_location_bar block callback
	*/
function hf_basic_search_view_page_callback() {
	// Build template
	$output ='<a class="magnifier-icon" href="javascript:void(0)"></a>';
	$output .='<form method="get">';
		$output .='<input class="text" name="query" placeholder="What are you interested in?" title="Search" type="text" value="">';
		$output .='<input type="hidden" value="/solr" name="web">';
		$output .='<input class="submit" type="submit" value="Go">';
	$output .='</form>';


	return $output;
}

