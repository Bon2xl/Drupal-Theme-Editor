/************************************************
bigSlider.js
************************************************/
function bigSlider() {
  // move row image source to row as background
  $(".big-slider .views-row").each(function() {
    var imgelem = "img";
    var imgsrc = $(this).find(imgelem).attr("src");
    $(this).css("backgroundImage","url("+imgsrc+")");
  });

  // remove big slider title
  $(".big-slider").parent().parent().prev().remove();
  //
  // // left and right corner for dots
  // $("slick-dots").insertBefore("span.left-corder");
  // $("slick-dots").insertAfter("span.right-corder");

}
bigSlider();
