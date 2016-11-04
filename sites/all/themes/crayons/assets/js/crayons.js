(function ($, Drupal) { Drupal.behaviors.crayons = { attach: function(context, settings) {
var basePath = Drupal.settings.basePath;
var pathToTheme = Drupal.settings.pathToTheme;

/************************************************
bigSlider.js
************************************************/
function bigSlider() {
  // move row image source to row as background
  $(".big-slider .views-row").each(function() {
    var imgelem = "img";
    var imgsrc = $(this).find(imgelem).attr("src");
    $(this).css("backgroundImage","url("+imgsrc+")");
  });

  // remove big slider title
  $(".big-slider").parent().parent().prev().remove();
  //
  // // left and right corner for dots
  // $("slick-dots").insertBefore("span.left-corder");
  // $("slick-dots").insertAfter("span.right-corder");

}
bigSlider();


/************************************************
selectPlaceholder.js
************************************************/
function selectPlaceholder() {
  $("#searchBox").attr('placeholder', "Search");
}
selectPlaceholder();


/************************************************
calendarDayTitle.js
************************************************/
function calendarDayTitle() {
  if( $("body").hasClass('page-calendar-day') ) {
  	$('#page-title > .large-12').prepend('<h1 class="page-title">Calendar - Day</h1>');
  }
}
calendarDayTitle();


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


/************************************************
ellipsis.js
************************************************/
function ellipsis() {
  $(".cta-callout .cta-description").dotdotdot({
  	watch: "window"
  });
}
ellipsis();


/************************************************
blockTitle.js
************************************************/
function blockTitle() {

}
blockTitle();


/************************************************
selectSearch.js
***********************************************/
function selectSearch() {
  var searchBoxWrap, searchBox, selectWrapper, select;
  searchBoxWrap = $(".searchBoxWrap");
  searchBox = $("#searchBox");
  selectWrapper = $("<ul class='selectWrapper js-selectWrapper'></ul>");
  selectOption = $(".selectSearchCat option");

  // build wrapper
  selectWrapper.insertBefore("#globalSearch > .row");

  // get options value
  if ($("#header .selectWrapper").length === 1) {
    $("#header .selectSearchCat option").each(function(index) {
      var active = (this.defaultSelected) ? 'active' : '';
      $("#header .selectWrapper").append("<li class='item "+active+"' data-val-type='"+this.value+"'>"+this.text+"</li>");

      // Fix for panels
      if((index+1) === selectOption.length) {
        $("#header #globalSearch").addClass("custom-select");
      }
    });
  }

    $(".selectWrapper li").click( function(e) {
      e.preventDefault();
      dataVal = $(this).attr("data-val-type");
      $(this).parent().find('li').removeClass("active");
      $(this).addClass("active");
      $(".selectSearchCat option").attr('selected', false);
      $(".selectSearchCat option[value='"+dataVal+"']").prop('selected', 'selected');
    });
}

/*if(!$("#header #globalSearch").hasClass("custom-select")) {
  selectSearch();
}*/

/************************************************
searchInputTab
************************************************/
function searchInputTab() {
  $(".selectWrapper li").prepend("<span class='bgtop js-bgtop'>");
}

/*if(!$("#globalSearch").hasClass("custom-select")) {
  searchInputTab();
}*/


}};})(jQuery, Drupal);