(function ($, Drupal) {

  Drupal.behaviors.hf_eds = {
    attach: function (context, settings) {
      // result per page & sort by dropdown
      $(".display-settings-lbl", context).on('click',function(e){
        $(this).stop().parent().toggleClass("open").stop();
      });

      // move keyword to main
      $("div.keywords", context).prependTo(".large-9.main.columns");

      // Hide Filters if empty
      var keywords = $("div.keywords", context);
      var keywordsChild = keywords.find(".items").children().length;
      //console.log(keywordsChild);
      if (Number(keywordsChild) <= 0) {
        keywords.addClass("hide");
      }

		$('.js-loginbutton', context).on('click', function() {
			var targetModal = $('#' + $(this).data('revealId'));
			var bibID = $(this).data('bib-id');
			targetModal.find('#bib-id').val(bibID);
		});

      /************************************************
      holdButton.js
      ************************************************/
      if ($("body").hasClass("front") || $("body").hasClass("page-homepage") || $("body").hasClass("page-eds")) {
      	//Defines the functinality for the holdbutton
      	$('.js-holdbutton', context).on('click', function(){
      		//Reset the html so they don't get stale messages
      		var loadingGifUrl = Drupal.settings.basePath + 'sites/all/modules/hf_eds/images/loading.gif';
      		$('.js-hold-form').html('<img src="' + loadingGifUrl + '"/>');
      		var bibID = $(this).data('bib-id');
      		$('.js-modal-bib-id').text(bibID);
      		//Make the availability call
      		var pathname = Drupal.settings.basePath + "my-account/hold/" + bibID;
      		//Make sure the x can close the window
      		$('a.close-reveal-modal', context).on('click', function() {
      			$('#stacks-request').hide();
      			//$(this).foundation('reveal', 'close');
      		});
      		$.post(pathname, function(post_result){
      			$('.js-hold-form').html(post_result);
      			Drupal.attachBehaviors('.js-hold-form');
      		});
      		//$('#stacks-status').foundation('reveal', 'open'); // open modal
      		$('#stacks-request').show();
      	});

      	$('.js-hold-submit-button', context).on('click', function(){
      		//Make the availability call
      		var accessionNumber = $(this).data('accession-number');
      		var isVolume = $(this).data('volume');
      		var pickup = $('input[name=pickup_location]:checked').val();
      		var volumeChoice = $('input[name=volume_choice]:checked').val();
      		var makeCall = true;
      		var args = {make_call:makeCall, pickup:pickup, accession_number:accessionNumber, volume_choice:volumeChoice};
      		var pathname = Drupal.settings.basePath + "eds/hold/";

      		//Because this is all done via ajax you need to double check that all
      		//of the fields needed have been submitted
      		if(pickup){
      			//If it's a volume make sure that volume choice is defined
      			if(isVolume){
      				if(volumeChoice){
      					jQuery.post(pathname, {elements: args}, function(post_result){
      						$('.js-form-message').html("");
      						Drupal.attachBehaviors('.js-form-message');
      						$('.js-hold-form').html(post_result);
      						Drupal.attachBehaviors('.js-hold-form');
      					});
      				} else {
      					$('.js-form-message').html("<h2>Please select a volume</h2>");
      					Drupal.attachBehaviors('.js-form-message');
      				}
      			} else {
      				//if it's not a volume and pickup is set then it's good to go
      				jQuery.post(pathname, {elements: args}, function(post_result){
      					$('.js-form-message').html("");
      					Drupal.attachBehaviors('.js-form-message');
      					$('.js-hold-form').html(post_result);
      					Drupal.attachBehaviors('.js-hold-form');
      				});
      			}
      		} else {
      			$('.js-form-message').html("<h2>Please select a location</h2>");
      			Drupal.attachBehaviors('.js-form-message');
      		}
      		return false;
      	});
      }

      // datepicker placeholder
      $(".form-wrapper input[name='from_date']").attr("placeholder", "From:");
      $(".form-wrapper input[name='to_date']").attr("placeholder", "To:");

      //Custom search Sidebar
      searchSidebar = $(".block-hf-eds-search-filters", context);

      //if no child remove title and ul
      searchSidebar.find("ul").each(function (i) {
        if ($(this).children().length <= 0) {
          $(this).hide();
          $(this).prev("h3").hide();
        }
      });

      //toggle
      searchSidebar.find("h3").click(function () {
        if ($(this).next().children().length > 0) {
          $(this).toggleClass("toggle");
          $(this).next().toggleClass("open");
        }
      });

      // Open Filter
      $(".btn-filter").click( function() {
        searchSidebar.addClass("open");
      })

      // Back button, close filter
      searchSidebar.find(".btn-close").click( function() {
        searchSidebar.removeClass("open");
      })

      //extLink = $(".extLink", context);
      //extLink.attr('href').text('Download');
      //$('.extLink').attr('href').text('Download');
    }
  };

})(jQuery, Drupal);
