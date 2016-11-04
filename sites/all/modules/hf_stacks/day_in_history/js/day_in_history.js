/*
	Copyright:  Hybrid Forge 2010-12. All Rights Reserved.
	Author: 	Rod Miles (www.hybridforge.com)
	Modified by: Jeremy Smereka
	Date: 		August 2012
 
	Info: 		Day in History Block js
-------------------------------------------------------------*/

jQuery(document).ready(function($) {

	// Show or Hide Details
	$('.dihDesc .dihDescDetailsToggle').toggle(function() {
		// Show Full Details
		$(".dihDesc .dihDescDetails").animate({ height: 'toggle', opacity: '1' }, 250, 
			function() {
				//animation complete
				$(".dihDesc .dihDescDetailsToggle").attr("title","Hide Description");
				$(".dihDesc .dihDescDetailsToggle").addClass("hide");
				$(".dihDesc .dihDescDetailsToggle").removeClass("show");
				$(".dihDesc .dihDescDetailsToggle span").text("Hide");
			}
		);
		return false;
	}, function() {
		// Hide Full Details
		$(".dihDesc .dihDescDetails").animate({ height: 'toggle', opacity: '.25'}, 200,
			function() {
				//animation complete
				$(".dihDesc .dihDescDetailsToggle").attr("title","Show Description");
				$(".dihDesc .dihDescDetailsToggle").addClass("show");
				$(".dihDesc .dihDescDetailsToggle").removeClass("hide");
				$(".dihDesc .dihDescDetailsToggle span").text("Show");
			}
		);
		return false;
	});

});

