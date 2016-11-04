/************************************************
slider.js
************************************************/
function slider() {
	$(".big-slider .views-field-field-body").on('click',function() {
		hrefLink = $(this).parent().prev().attr("href");
		window.location.href = hrefLink;
	});
}

slider();
