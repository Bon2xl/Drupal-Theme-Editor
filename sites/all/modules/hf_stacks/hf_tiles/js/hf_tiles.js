(function ($, Drupal) { Drupal.behaviors.hf_tiles = { attach: function(context, settings) {

  $(".form-item-icon .form-radios").before("<div class='selected-icon no-icon'></div>");
  $(".form-item-icon .description").insertBefore(".form-item-icon .form-radios");

  // Check if has selected radio buttons
  is_checked = Number($(".form-item-icon .form-radios").find("input:checked").length);
  if (is_checked === 1) {
    $("selected-icon")
      .removeClass("no-icon")
      .addClass("has-icon")
      .text("");
  }

  // Click event
  $(".form-item-icon .description").click(function() {
    $(this).toggleClass('active');
    $(".form-item-icon .form-radios").toggleClass('active');
  });

}};})(jQuery, Drupal);
