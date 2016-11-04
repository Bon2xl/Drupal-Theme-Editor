/************************************************
ellipsises.js
************************************************/
function ellipsises() {
  if($("body").hasClass("theme-caltech")) {
    $(".big-slider .views-field-field-body").dotdotdot({
      watch: "window",
      height: 100
    });

    $(".cta-description").dotdotdot({
      watch: "window",
      height: 50
    });
  }
}
ellipsises();
