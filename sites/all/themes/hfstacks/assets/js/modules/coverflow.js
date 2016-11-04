/************************************************
coverflow.js
************************************************/
function coverflow($className) {
  var numVal;
  var elemDIV = $($className + ' .inner-content');
  elemDIV.each(function(i) {
    if (!$(this).hasClass("slick-initialized")) {
      $centerMode = false;
      $numToScroll_III = 2;
      // If medical page
      if ($('body').hasClass("page-layout-b")) {
        numToShow = 2;
        numToScroll = 3;
        numToScroll_II = 3;
      } else if ($('body').hasClass("theme-metals")) {
        numToShow = 5;
        numToScroll = 1;
        numToScroll_II = 1;
        $centerMode = true;
      } else if ($('body').hasClass("theme-textures")) {
        numToShow = 3;
        numToScroll = 3;
        numToScroll_II = 3;
      } else if ($('body').hasClass("theme-crayons")) {
        numToShow = 3;
        numToScroll = 3;
        numToScroll_II = 3;
        if($(this).parents().hasClass("panel-col-top") || $(this).parents().hasClass("panel-col-bottom")) {
          numToShow = 6;
          numToScroll = 6;
          numToScroll_II = 6;
        }
      } else if ($('body').hasClass("theme-caltech")) {
        numToShow = 3;
        numToScroll = 3;
        numToScroll_II = 3;
        if($(this).parents().hasClass("panel-col-top") || $(this).parents().hasClass("panel-col-bottom")) {
          numToShow = 6;
          numToScroll = 6;
          numToScroll_II = 6;
        }
      } else {
        numToShow = 6;
        numToScroll = 6;
        numToScroll_II = 3;
      }

      $(this).slick({
        dots: false,
        infinite: false,
        arrows: true,
        speed: 300,
        slidesToShow: numToShow,
        slidesToScroll: numToScroll,
        dots: false,
        centerMode: $centerMode,
        infinite: true,
        responsive: [
          {
            breakpoint: 1024,
            settings: {
              slidesToShow: 3,
              slidesToScroll: numToScroll_II,
              infinite: true,
            }
          },
          {
            breakpoint: 480,
            settings: {
              slidesToShow: $numToScroll_III,
              slidesToScroll: $numToScroll_III
            }
          }
        ]
      });
    }
  });
}

coverflow('.coverflow');
