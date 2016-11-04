/************************************************
eventsSignup.js
************************************************/
function eventsSignup() {
	if ( $("body").hasClass("node-type-event") || $(".ttl-signup-closed").length === 1 )	{
		$(".ttl-signup-closed").insertAfter(".field-name-field-event-image");
	}
}

eventsSignup();