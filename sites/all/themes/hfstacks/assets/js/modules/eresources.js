/************************************************
eresources.js toggle
************************************************/
$(".page-eresources-az .eresource-title").wrapInner('<a></a>');
$(".view-eresources").find(".eresource-title a").click(function(e){
	e.preventDefault();
	$(this).parent().parent().toggleClass("active");
});

