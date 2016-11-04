/************************************************
mini-slider.js
************************************************/
miniSlider();
function miniSlider() {
  if (!$('.mini-slider .slider-content').hasClass("slick-initialized")) {
    $centerMode = false;
    $numToScroll = 5;
    $numToScroll_II = 3;
    $infinite = true;
    if ($('body').hasClass("theme-metals")) {
      $centerMode = true;
      $numToScroll = 5;
      $numToScroll_II = 3;
    } else if ($('body').hasClass("theme-crayons")) {
      if($('.mini-slider .slider-content').parents().hasClass("panel-col-fist") || $('.mini-slider .slider-content').parents().hasClass("panel-col-last")) {
        $numToScroll = 3;
        $numToScroll_II = 2;
      }
    } else if ($('body').hasClass("theme-caltech")) {
      $centerMode = false;
      $numToScroll = 4;
      $numToScroll_II = 3;
      $infinite = false;
      if($('.mini-slider .slider-content').parents().hasClass("panel-col-fist") || $('.mini-slider .slider-content').parents().hasClass("panel-col-last")) {
        $numToScroll = 3;
        $numToScroll_II = 2;
      }
    }


    $('.mini-slider .slider-content').slick({
      slidesToShow: $numToScroll,
      slidesToScroll: $numToScroll,
      centerMode: $centerMode,
      infinite: $infinite,
      responsive: [
        {
          breakpoint: 1024,
          settings: {
            slidesToShow: 3,
            slidesToScroll: $numToScroll_II,
            dots: true
          }
        },
        {
          breakpoint: 600,
          settings: {
            slidesToShow: 3,
            slidesToScroll: $numToScroll_II
          }
        },
        {
          breakpoint: 480,
          settings: {
            slidesToShow: 1,
            slidesToScroll: 1
          }
        }
        // You can unslick at a given breakpoint now by adding:
        // settings: "unslick"
        // instead of a settings object
      ]
    });
    $(".mini-slider .img-wrapper img").each(function() {
      var imgsrc = $(this).attr("src");
      $(this).parent().css("backgroundImage","url("+imgsrc+")");
    });
  }

}
