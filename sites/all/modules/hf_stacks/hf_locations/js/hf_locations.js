(function ($) {
  Drupal.behaviors.hf_locations = { 
    attach: function (context, settings) {
      $('.location-bar .items').slick({
        dots: false,
        infinite: true,
        speed: 300,
        fade: true,
        cssEase: 'linear',
        slidesToShow: 1,
        slidesToScroll: 1,
        autoplay: true,
        autoplaySpeed: 6000,
        arrows: false,
      });
  }}
}(jQuery));