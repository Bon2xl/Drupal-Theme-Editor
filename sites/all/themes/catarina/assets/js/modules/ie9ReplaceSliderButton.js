/************************************************
ie9ReplaceSliderButton.js
************************************************/
function ieNineReplaceSliderButton() {
  $('.slick-prev').before("<span class='slick-prev dum'><img src='"+basePath+pathToTheme+"/assets/img/icon-arrow-left-black.png' /></span>");
  $('.slick-next').before("<span class='slick-next dum'><img src='"+basePath+pathToTheme+"/assets/img/icon-arrow-right-black.png' /></span>");
}

if ($('body').hasClass("ie9")) {
  ieNineReplaceSliderButton();
}
