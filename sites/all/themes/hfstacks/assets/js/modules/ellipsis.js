/************************************************
ellipsis.js
************************************************/
function ellipsis() {
  $(".cta-callout .cta-description").dotdotdot({
  	watch: "window"
  });

	if($("body").hasClass("theme-hfstacks") || $("body").hasClass("theme-metals")) {
	    $(".cta-callout .cta-title a").dotdotdot({
	    	watch: "window", 
	    	height: 70
	    });
	    console.log("stacks and metals");
	} else if($("body").hasClass("theme-catarina")) {
		$(".cta-callout .cta-title a").dotdotdot({
			watch: "window",
			height: 50
		});
	} else if($("body").hasClass("theme-crayons")) {
		$(".coverflow .views-field-field-title a").dotdotdot({
			watch: "window",
			height: 50
		});
	} else {
		$(".coverflow .views-field-field-title a").dotdotdot({
			watch: "window",
			height: 70
		});
	}
}
ellipsis();
