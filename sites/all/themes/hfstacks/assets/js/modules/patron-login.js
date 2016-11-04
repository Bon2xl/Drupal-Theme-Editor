/************************************************
patron-login.js
************************************************/
$("#top-header .menu a:contains('Login')").attr('data-reveal-id', 'patron-login-modal');
$(".mobile-menu .menu a:contains('Login')").click(function (e) {
  e.preventDefault();
  $(this).attr('data-reveal-id', 'patron-login-modal');
})