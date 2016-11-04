/**
 *
 */
(function($) {

	Drupal.behaviors.hf_eresources = {
		attach: function() {
//

			$(".login-link").attr('data-reveal-id', 'patron-login-modal');

			$('.ezproxy-submit').click(function(){
				$(this).siblings('.ezproxy').submit();

				return false;
			})
		}

	}
})(jQuery);