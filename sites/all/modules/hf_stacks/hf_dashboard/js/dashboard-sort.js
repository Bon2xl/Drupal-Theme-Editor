(function ($, Drupal) {
  Drupal.behaviors.hf_dashboard_sort = { attach: function(context, settings) {

  var basePath = Drupal.settings.basePath;
  var pathToTheme = Drupal.settings.pathToTheme;

  $( "#sortable", context ).sortable();
  $( "#sortable", context ).on("sortupdate",function( event, ui ) {
    var sorted = $( this ).sortable( "serialize");
    localStorage.setItem('sorted', sorted)
  });

  if(localStorage.getItem("sorted") !== null) {
    var arrValuesForOrder = localStorage.getItem('sorted').substring(6).split("&div[]=");
    var $ul = $("#sortable", context);
    var $items = $("#sortable", context).children();
    $.each(arrValuesForOrder, function(key, val) {
      num = val - 1;
      $ul.append($("#sortable #div_"+val));
    });
  }

  // $("#sortable", context).disableSelection();
  $("#clear", context).click(function(){
    window.localStorage.removeItem("sorted");
  });

}};})(jQuery, Drupal);