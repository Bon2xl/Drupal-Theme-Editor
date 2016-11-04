<?php 
global $base_url;   // Will point to http://www.example.com
global $base_path;  // Will point to at least "/" or the subdirectory where the drupal in 

/**
	* hf_location_bar block callback
	*/
function location_bar_view_page_callback() {
	global $theme;

	$getTodaysDate = strtolower(date("l"));
	$path = drupal_get_path('module', 'hf_locations');
	/* Get theme settings variable */
	$themeArr = variable_get('theme_'.$theme.'_settings');
	$is_enable = $themeArr['hf_location_bar']['Enable'];
	$is_rotating = $themeArr['hf_location_bar']['Rotate'];

	if (!empty($is_enable)) {
		// Using the TableSort Extender is what tells the the query object that we are sorting.
		$query = db_select('node', 't');
		$query->join('field_data_field_branch_' .$getTodaysDate. '', 'day', 't.vid = day.revision_id');
		$query->leftjoin('field_data_field_branch_email', 'email', 't.vid = email.revision_id');
		$query->leftjoin('field_data_field_branch_phone', 'phone', 't.vid = phone.revision_id');
		$query->fields('t', array('title', 'sticky', 'changed')); 
		$query->fields('day', array('field_branch_' .$getTodaysDate. '_value')); 
		$query->fields('email', array('field_branch_email_email'));
		$query->fields('phone', array('field_branch_phone_number'));
		$query->orderBy('t.changed', 'DESC');
		$query->condition('t.type', 'library_branch', '=');
		$query->condition('t.status', 1, '=');
	

		// Don't forget to tell the query object how to find the header information.
		$result1 = $query
				->range(0,20)
				->execute();

		 $result2 = $query
				->range(0,20)
				->execute();

		// Get Row count
		$row_count = $result1->rowCount();

		// Build template
		$output = '<div class="location-bar">';
		$output .= '<div class="row">';
		$output .= '<a class="show-all-locations" data-reveal-id="modal-all-locations"></a>';
		$output .= '<div class="items">';
		$output .= result_template($result1, $is_rotating, $row_count, false, false);
		$output .= '</div>';
		$output .= '</div>';
		$output .= '</div>';
		
		//Modal
		$output .= '<div id="modal-all-locations" class="reveal-modal" data-reveal aria-labelledby="Todays Hours" aria-hidden="true" role="dialog">';
			$output .= '<img src="/'.$path. '/img/img-library.jpg" />';
			$output .= '<div class="items">';
				$output .= '<h2>Today\'s Hours</h2>';
				$output .= '<a class="view-all" href="' .$base_path. '/about/hours">View all details</a>';
				$output .= result_template($result2, $is_rotating, $row_count, true, true);
			$output .= '</div>';
			$output .= '<a class="close-reveal-modal" aria-label="Close">&#215;</a>';
		$output .= '</div>';

		// add js
		if(!empty($is_rotating)) {
			drupal_add_js('/' .$path. '/js/hf_locations.js', array('type' => 'external', 'scope' => 'footer', 'weight' => 1));	
		}
		return $output;
	}
}


/**
	* Result items
	* If Rotate is enabled
	*	- query all items that has sticky or else, query the latest updated item
	*	- if query is empty, throw an error
	*/
function result_template($result, $is_rotating, $row_count, $is_phoneNumber = false, $is_modal) {
	$is_sticky = false;
	foreach ($result as $k=>$r) {
		// First check if rotating is enabled then get all items
		if($is_rotating && !$is_modal) {
			$output .= item_template($r, $is_phoneNumber);
		// if modal is checked get all items 
		} elseif($is_modal) {
			$output .= item_template($r, $is_phoneNumber);
		} else {
			// Check if there is sticky post, get the latest one
			if($r->sticky) {
				$stickyOutput .= item_template($r, $is_phoneNumber);
				$is_sticky = true;
				break;
			// Else get the latest updated location				
			} elseif($k == 0) {
				$output .= item_template($r, $is_phoneNumber);
			}
		}
	}

	if($is_sticky) {
		return $stickyOutput;
	} else {
		return $output;
	}
}


/**
	* Result items
	* Display html items
	*/
function item_template($r, $is_phoneNumber){
	$getTodaysDate = strtolower(date("l"));
	$day = 'field_branch_'.$getTodaysDate.'_value';

	if(isset($r->field_branch_phone_number)) {
		$phoneNumber = preg_replace('~.*(\d{3})[^\d]{0,7}(\d{3})[^\d]{0,7}(\d{4}).*~', '($1) $2-$3', $r->field_branch_phone_number);	
	}
	
	$output = '';
	$output .= '<div class="loc-item">';
		$output .= '<div class="wrap-left">';
			$output .= '<div class="title">' .$r->title. '</div>';
			$output .= '<div class="day">' .$r->$day. '</div>';
			// $output .= '<div class="btn-booking"><a href="javascript:void(0)">Book a Room</a></div>';
		$output .= '</div>';
		$output .= '<div class="wrap-right">';
			if($is_phoneNumber) {
				$output .= '<div class="number"><span class="lbl">Phone: </span><a href="tel:' .$phoneNumber. '">' .$phoneNumber. '</a></div>';
			}
			$output .= '<div class="email"><span class="lbl"><a href="' .$base_path. '/contact-us">Email Us</a></span></div>';
		$output .= '</div>';
	$output .= '</div>';
	return $output;
}

