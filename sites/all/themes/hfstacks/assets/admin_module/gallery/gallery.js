(function ($, Drupal) { Drupal.behaviors.gallery = { 
	attach: function(context, settings) {
		var basePath = Drupal.settings.basePath;
		var pathToTheme = Drupal.settings.pathToTheme;

		if($('body').hasClass('page-admin-appearance')) {
			inputFld = $('.field-type-gallery-input');
			inputFldVal = inputFld.val();
			btnGalleryImg = $('.btn-gallery-img');

			// Check if gallery has value
			if(jQuery.type(inputFldVal) === 'string' && inputFldVal.length >= 4) {
				// loop through the item
				$('.gallery-images .item').each(function() {
					dataVal = $(this).attr('data-img');
					if(inputFldVal === dataVal) {
						$(this).parent().find(".selected").removeClass("selected");
						$(this).addClass("selected");

						// Add remove button
						if(!btnGalleryImg.hasClass("active")) {
							btnGalleryImg.addClass("active");
						} 
					}
				});
			}

			// Click event in items
	    $('.gallery-images .item').click( function() {
    		thisData = $(this).attr("data-img");

    		// Change input value
    		inputFld.val(thisData);

    		// Add border on click
    		$(this).parent().find(".selected").removeClass("selected");
    		$(this).addClass("selected");

    		// Add remove button
    		if(!btnGalleryImg.hasClass("active")) {
    			btnGalleryImg.addClass("active");
    		} 
	    });

  		// Click event in items
      btnGalleryImg.click( function() {
      	$('.gallery-images .selected').removeClass("selected");
      	inputFld.val("");
      	btnGalleryImg.removeClass("active");
      });
	  }

	}
}})(jQuery, Drupal);