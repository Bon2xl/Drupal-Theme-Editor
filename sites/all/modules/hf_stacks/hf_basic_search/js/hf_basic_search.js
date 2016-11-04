(function ($) {
  Drupal.behaviors.hf_basic_search = { 
    attach: function (context, settings) {
    	function basicSearch() {
    		searchBlok = $("#block-hf-basic-search-hf-basic-search");
            magnifier = $('<div class="magnifier-icon"></div>');

            searchBlok.find(".content").prepend(magnifier);

    		$('.magnifier-icon').click(function(e) {
    			e.preventDefault();
    			e.stopPropagation();
    			if(searchBlok.hasClass('active')) {
    				searchBlok.removeClass('active');
    			} else {
    				searchBlok.addClass('active');	
    				$("#block-hf-basic-search-hf-basic-search .text").focus();
    			}
    		});

    		$("#block-hf-basic-search-hf-basic-search").click(function(e){
    			e.stopPropagation();
    		});

    		$(document).click(function() {
    			searchBlok.removeClass('active');
    		})
    	}
    	basicSearch();
    }}
}(jQuery));