(function ($) {
  Drupal.behaviors.hf_quick_links_menu = { 
    attach: function (context, settings) {
      $('.hf-quick-links-menu-container').appendTo('#globalSearch');
  }}
}(jQuery));