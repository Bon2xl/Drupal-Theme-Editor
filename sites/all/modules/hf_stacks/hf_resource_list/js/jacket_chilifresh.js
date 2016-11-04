(function($) {
	Drupal.behaviors.hf_resource_list = {
		attach: function() {
//			$(".l-messages .large-12").append('<div class="messages status">The error message</div>');
//			console.log(Drupal.settings.hf_resource_list_jquery);

			if( Object.prototype.toString.call( Drupal.settings.hf_resource_list_jquery ) === '[object Array]' ) {

				for (var key in Drupal.settings.hf_resource_list_jquery) {
//					console.log(Drupal.settings.hf_resource_list_jquery[key]);
					$(Drupal.settings.hf_resource_list_jquery[key]).html(function(){

						var image = Drupal.settings.stacks_resource_list_chilifresh_url.replace('$isbn', $(this).data('cover-isbn'));
						image = image.replace('upc', '');

						image = '<img src="'+image+'">';
						return image;
					});
				}
			}

			$('.view-resource-list .field-name-field-isbn').append('<img src="http://placehold.it/100x142">');
		}
	}
})(jQuery);