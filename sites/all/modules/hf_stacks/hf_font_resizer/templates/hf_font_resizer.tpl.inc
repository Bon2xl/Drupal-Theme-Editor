<?php 
global $theme;

/**
	* hf_font_resizer block callback
	*/
function hf_font_resizer_view_page_callback() {
	// Build template

	$fontResizerVar = variable_get('stacks_font_resizer');
	if (!empty($fontResizerVar)) {
		$output = '<div class="font-resizer">';
		   $output .= '<div class="toggle-resizer"><i class="fa fa-font" aria-hidden="true"></i></div>';
		   $output .= '<div class="rf-wrapper">';
		      $output .= '<div class="fUp"><i class="fa fa-font" aria-hidden="true"></i><i class="fa fa-plus" aria-hidden="true"></i></div>';
		      $output .= '<div class="fDown"><i class="fa fa-font" aria-hidden="true"></i><i class="fa fa-minus" aria-hidden="true"></i></div>';
		   $output .= '</div>';
		$output .= '</div>';
		return $output;
	}
}

