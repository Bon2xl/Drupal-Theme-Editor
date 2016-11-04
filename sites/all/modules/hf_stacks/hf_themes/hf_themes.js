(function ($, Drupal) { 
  Drupal.behaviors.hf_themes = { 
    attach: function(context, settings) {
      var basePath = Drupal.settings.basePath;
      var pathToTheme = Drupal.settings.pathToTheme;

			// 
      var themeForm = $("#hf-themes-admin-form");
      var item = $(".form-type-radio.form-item-themes");
      var checkedInput = themeForm.find("input:checked");

      // Append active class in the parent and append active label
      checkedInput.parent().addClass("theme-active");
      checkedInput.parent().find(".img").append("<span class='lbl-active'>Active</h1>");

      item.click(function() {
      	item.removeClass("selected");
      	$(this).addClass("selected");
      });
    }
  };
})(jQuery, Drupal); 