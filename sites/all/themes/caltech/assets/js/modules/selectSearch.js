/************************************************
selectSearch.js
************************************************/
function selectSearch() {
  var searchBoxWrap, searchBox, selectWrapper, select;
  searchBoxWrap = $(".searchBoxWrap");
  searchBox = $("#searchBox");
  selectWrapper = $("<ul class='selectWrapper js-selectWrapper'></ul>");
  selectOption = $(".selectSearchCat option");
  quickLinks = $(".hf-quick-links-menu-container");

  // build wrapper
  selectWrapper.appendTo("#globalSearch");

  // get options value
  if ($("#header .selectWrapper").length === 1) {
    $("#header .selectSearchCat option").each(function(index) {
      var active = (this.defaultSelected) ? 'active' : '';
      var qlinks = (quickLinks.length === 1) ? 1 : 0;
      var listWidth = 100/Number(selectOption.length+qlinks);  
      
      $("#header .selectWrapper").prepend("<li style='width:"+listWidth+"%;' class='item "+active+"' data-val-type='"+this.value+"'>"+this.text+"</li>");

      // Fix for panels
      if((index+1) === selectOption.length) {
        $("#header #globalSearch").addClass("custom-select");
      }

      // Add quick links and build links
      if((index+1) === selectOption.length) {
        if(quickLinks.length === 1) {
          $("#header .selectWrapper").append("<li style='width:"+listWidth+"%;' class='item quick-link' data-val-type=''>Quick links</li>");  
        }
      }
    });
  }

  $(".selectWrapper li").click( function(e) {
    e.preventDefault();
    $(this).parent().find('li').removeClass("active");
    $(this).addClass("active");

    // Check if element has class qick-link or not
    if(!$(this).hasClass('quick-link')) {
      dataVal = $(this).attr("data-val-type");
      $(".selectSearchCat option").attr('selected', false);
      $(".selectSearchCat option[value='"+dataVal+"']").prop('selected', 'selected');
      quickLinks.removeClass("show");
    } else {
      quickLinks.addClass("show");
    }
    
  });
}

if(!$("#header #globalSearch").hasClass("custom-select")) {
  selectSearch();
}



/************************************************
searchInputTab
************************************************/
function searchInputTab() {
  $(".selectWrapper li").prepend("<span class='bgtop js-bgtop'>");
}

if(!$("#globalSearch").hasClass("custom-select")) {
  searchInputTab();
}