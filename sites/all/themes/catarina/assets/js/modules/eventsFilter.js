/************************************************
eventsFilter.js
************************************************/
function eventsFilter() {
  var elem = $("<a title='Events Filter' class='btn-filter'><i></i>Filter</a>");
  var elemClose = $("<a title='Close' class='btn-close-modal'>X</a>");
  $(".side-filter-ext").prepend(elem);
  $(".side-filter-ext .content").prepend(elemClose);

  $(".btn-filter").click( function() {
    $(this).parent().find(".content").addClass("active");
  });
  $(".btn-close-modal").click( function() {
    $(this).parent(".content").removeClass("active");
  });
}

if ($('body').hasClass("page-upcoming-events")) {
  eventsFilter();
  console.log("filter enabled")
}