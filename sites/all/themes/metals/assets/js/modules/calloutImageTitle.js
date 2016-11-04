/************************************************
calloutImageTitle.js
************************************************/
function calloutImageTitle() {
  var callout = $(".cta-callout");
  $(".cta-callout .cta-title").each(function(index) {
  		var txt = $(this).text();
  		$(this).parent().parent().find(".imgHolder").prepend("<div class='ttl-img'>"+txt+"</div>");
  });
}

var count = $(".cta-callout .imgHolder .ttl-img").size();
if (count <= 0) {
  calloutImageTitle();
}
