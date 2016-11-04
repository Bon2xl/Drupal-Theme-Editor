(function ($) {
	Drupal.behaviors.stacks_topicons = { 
		attach: function (context, settings) {
			mobileMenu = $(".menu-block-4 > .menu");

			if($('.top-icon-roombooking').length === 1) {
				mobileMenu.prepend('<li class="top-icon-roombooking"><a href="/roombooking">Room Booking</a></li>')
				console.log("teste");
			}

			if($('.top-icon-calendar').length === 1) {
				mobileMenu.prepend('<li class="top-icon-calendar"><a href="/upcoming-events">Calendar</a></li>')
				console.log("teste");
			}

			if($('.top-icon-databases').length === 1) {
				mobileMenu.prepend('<li class="top-icon-databases-menu"><a href="/databases">Databases</a></li>')
				console.log("teste");
			}
		}
	}
}(jQuery));