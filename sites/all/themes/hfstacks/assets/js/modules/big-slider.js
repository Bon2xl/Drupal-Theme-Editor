/************************************************
big-slider.js
************************************************/
bgSlider();
function bgSlider() {
  var hasDots;
  hasDots = false;

  if ($("body").hasClass("theme-crayons")) {
    hasDots = true;
  }

  if (!$('.big-slider .view-content').hasClass("slick-initialized")) {
    $(".big-slider .view-content").slick({
      slidesToShow: 1,
      slidesToScroll: 1,
      dots: hasDots,
    });
  }
}
