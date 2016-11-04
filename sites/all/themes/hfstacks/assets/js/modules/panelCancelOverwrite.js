/************************************************
panelCancelOverwrite.js
This script overwrite panels cancel button
************************************************/
function panelCancelOverwrite() {
	if($('body').hasClass('panels-ipe')) {
		$("#panels-ipe-cancel").click(function() {
			location.reload();
		});	
	}	
}

panelCancelOverwrite();