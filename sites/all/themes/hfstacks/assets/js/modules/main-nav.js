/************************************************
main-nav.js
************************************************/

if($("body").hasClass("theme-hfstacks")) {
	mainNav();
	$(window).resize(function() {
		if(Foundation.utils.is_large_up()) {
			window.setTimeout(mainNav(), 10);
		}
	});	
}

function mainNav() {
	mainNAV = $(".main-nav");
	togMob = $(".toggle-mobile");
	if (mainNAV.position().top > 0) {
		mainNAV.addClass("hide");
		togMob.addClass("show");
	} else {
		mainNAV.removeClass("hide");
		togMob.removeClass("hide");
	}
}
