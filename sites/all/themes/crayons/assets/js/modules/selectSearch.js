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
