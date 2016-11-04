/************************************************
events.js
************************************************/
function events() {
	var viewEmpty = $('.view-empty');
	var sectionWrapper = $('.section-wrapper');
	if($('body').hasClass('page-upcoming-events')) {
		if(viewEmpty.length === 1) {
			$('body').addClass('no-events');
		}
	}
}

events();