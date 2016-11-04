(function ($) {
  Drupal.behaviors.hf_dashboard_flip = { attach: function (context, settings) {

    // console.log(Drupal.settings);
    $(document).foundation();

    // ** UNCOMMENT WHEN READY FOR MODAL TUTORIALS
    // $('#firstModal', context).foundation('reveal', 'open');

    // 3d card transition
    $('.flip-btn').click(function () {
      $('.sortees').removeClass('active');
      $('.card').removeClass('flipped');
      $('.flip-btn').removeClass('btn-hide');
      $(this).addClass('btn-hide');
      $(this).siblings().children('.card').addClass('flipped');
      $(this).parent().addClass('active');

      return false;
    });
    $('.close-btn').click(function (e) {
      $('.sortees').removeClass('active');
      $('.flip-btn').removeClass('btn-hide');
      $(this).parent().parent().removeClass('flipped');
      return false;
    });

    // Load Welcome Screen
    // 
    var modalPopup = localStorage.getItem('modalPopup');
    if ( modalPopup !== null ) {
      console.log("null value");
    } else {
      $('#firstModal').foundation('reveal', 'open');
      localStorage.setItem('modalPopup', true);
    }
  }}
}(jQuery));