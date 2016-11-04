/************************************************
callout.js
************************************************/
function calloutFn() {
	var elemCallOut = $(".cta-callout");
	elemCallOut.find(".views-field").each( function() {
		var elem = $(this).find("img");
		var ctaSrc = elem.attr("data-url-path");
		$(this).find(".imgHolder").css("backgroundImage","url("+ctaSrc+")");
	});
}
calloutFn();
