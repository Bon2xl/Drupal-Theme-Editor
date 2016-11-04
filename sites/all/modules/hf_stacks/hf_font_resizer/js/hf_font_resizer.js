(function ($) {
  Drupal.behaviors.hf_basic_search = { 
    attach: function (context, settings) {
    	/************************************************
        fontResize.js
        ************************************************/
        // insert toggle mobile
        $('.font-resizer').clone().insertBefore( $(".toggle-mobile") );

        // Resizer Event
        $(".fUp").on('click', function(e) {
            e.preventDefault();
          e.stopPropagation();

            var zoomPg, cuurZoomPG;
            zoomPg =  $("html").css("font-size");
            cuurZoomPG = parseFloat(zoomPg);
            limit = 19;
            // increase font if it's less than 1.3
            if(cuurZoomPG <= limit) {
                // remove min-font in fDown
                $(".fDown").removeClass("min-font");
                // increase size
                $("html").css("font-size", cuurZoomPG+1)

                // add max-font if it reaches max font
                if (cuurZoomPG === limit) {
                    $(this).addClass("max-font");
                }
            }
        });
        //
        $(".fDown").on('click', function(e) {
            e.preventDefault();
          e.stopPropagation();

            var zoomPg, cuurZoomPG, limit;
            zoomPg =  $("html").css("font-size");
            cuurZoomPG = parseFloat(zoomPg);
            limit = 14;
            // increase font if it's less than 1.3
            if(cuurZoomPG >= limit) {
                // remove min-font in fDown
                $(".fUp").removeClass("max-font");
                // increase size
                $("html").css("font-size", cuurZoomPG-1)

                // add max-font if it reaches max font
                if (cuurZoomPG === limit) {
                    $(this).addClass("min-font");
                }
            }
        });

        $(".toggle-resizer").on('click', function(e) {
            $(this).next().toggleClass("show-resizer");
        });

        $("#font-resizer").on('mouseleave', function(e) {
                e.preventDefault();
                e.stopPropagation();

                $(this).removeClass("show-resizer");
        });
    }}
}(jQuery));