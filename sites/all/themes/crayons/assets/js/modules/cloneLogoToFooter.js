/************************************************
cloneLogoToFooter.js
************************************************/
function cloneLogoToFooter() {
  $("#footer .section").prepend("<div class='ft-brand-logo'></div>");
  $("#logo img").clone().appendTo(".ft-brand-logo");
  $(".site-brand").addClass("fixed-repeat");
}

if($(".site-brand").hasClass(".fixed-repeat")) {
  cloneLogoToFooter();
}
