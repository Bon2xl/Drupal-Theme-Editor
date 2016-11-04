/**
 *
 */
(function($) {

	Drupal.behaviors.library_info = {
		attach: function() {

			$('#library-branch-select').live('change',function(context, settings) {
				var tabs = $('#library-info-tabs');
//				console.log($(this).val());
				if (!isNaN($(this).val())) {
					tabs.load(Drupal.settings.basePath + '_library_info_ajax/'+ $(this).val(), function(){

						// reloading foundation
						// todo: reload only the tabs
						jQuery(document, context).foundation();

					});
				} else {
					tabs.html('');
				}
			});
		}

	}
})(jQuery);