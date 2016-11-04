(function ($, Drupal) { Drupal.behaviors.selecttheme = { 
	attach: function(context, settings) {
		var basePath = Drupal.settings.basePath;
		var pathToTheme = Drupal.settings.pathToTheme;

		if($('body').hasClass('page-admin-appearance')) {
			var dropdownA = $('.dropdown-a');
			var dropdownB = $('.dropdown-b ul');
			
			// Loop in dropdown and get selected
			function loopInSelect() {
				otpLength = $("#edit-color-palette option").length;
				$("#edit-color-palette option").each(function(index) {
					var isSelected = $(this).attr('selected');
					var lbl = $(this).text();
					var val = $(this).val();
					var i = index+1;
					if (isSelected) {
						// append to dropdown and add active class
						dropdownA.append(lbl);
						$('.'+val).addClass('active');
					}

					if(i === otpLength) {
						dropdownA.addClass('loop-done');
					}
				});	
			}
			if(!dropdownA.hasClass('loop-done')) {
				loopInSelect();
			}


			// Click event and update dropdown
			dropdownB.find('li').click(function(event) {
				event.stopPropagation();
				var lbl = $(this).text();
				var cls = $(this).attr('class');
				dropdownA.text('');
				dropdownA.append(lbl);
				dropdownB.parent().toggleClass('active');

				// Remove active to all li
				dropdownB.find('li').removeClass('active');
				// Add active to all li
				$(this).addClass('active');

				// pass data-val to select
				// if data and val is match add selected if not remove selected
				$("#edit-color-palette option").each(function() {
					var val = $(this).val();
					if (val === cls) {
						$(this).prop("selected", true);
					} else {
						$(this).prop("selected", false);
					}
				});
			});

			// Toggle Event
			dropdownA.click(function(event) {
				event.stopPropagation();
				$(this).next().toggleClass('active');
			});

			// Close dropdown when click body
			$('body').click(function() {
				if($('.dropdown-b').hasClass('active')) {
					$('.dropdown-b').removeClass('active');	
				}
			});

	  }
	}
}})(jQuery, Drupal);