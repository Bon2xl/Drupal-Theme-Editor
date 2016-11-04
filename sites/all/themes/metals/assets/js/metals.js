(function ($, Drupal) { Drupal.behaviors.metals = { attach: function(context, settings) {
var basePath = Drupal.settings.basePath;
var pathToTheme = Drupal.settings.pathToTheme;

/************************************************
calloutImageTitle.js
************************************************/
function calloutImageTitle() {
  var callout = $(".cta-callout");
  $(".cta-callout .cta-title").each(function(index) {
  		var txt = $(this).text();
  		$(this).parent().parent().find(".imgHolder").prepend("<div class='ttl-img'>"+txt+"</div>");
  });
}

var count = $(".cta-callout .imgHolder .ttl-img").size();
if (count <= 0) {
  calloutImageTitle();
}


/************************************************
closeMobile.js
************************************************/
function closeMobile() {
  $(".btn-close-mobile").on("click.toggleCanvas", function(){
   $(".exit-off-canvas").click();
 }); 
}
closeMobile();

/************************************************
eventsFilter.js
************************************************/
function eventsFilter() {
  var elem = $("<a title='Events Filter' class='btn-filter'><i></i>Filter</a>");
  var elemClose = $("<a title='Close' class='btn-close-modal'>X</a>");
  $(".side-filter-ext").prepend(elem);
  $(".side-filter-ext .content").prepend(elemClose);

  $(".btn-filter").click( function() {
    $(this).parent().find(".content").addClass("active");
  });
  $(".btn-close-modal").click( function() {
    $(this).parent(".content").removeClass("active");
  });
}

if ($('body').hasClass("page-upcoming-events")) {
  eventsFilter();
  console.log("filter enabled")
}

/************************************************
ie9ReplaceSliderButton.js
************************************************/
function ieNineReplaceSliderButton() {
  $('.slick-prev').before("<span class='slick-prev dum'><img src='"+basePath+pathToTheme+"/assets/img/icon-arrow-left-black.png' /></span>");
  $('.slick-next').before("<span class='slick-next dum'><img src='"+basePath+pathToTheme+"/assets/img/icon-arrow-right-black.png' /></span>");
}

if ($('body').hasClass("ie9")) {
  ieNineReplaceSliderButton();
}


/************************************************
moveSearchButton.js
************************************************/
function moveSearchButton() {
  rowThree = $("#globalSearch .row div:nth-child(3) ");
  rowThree.addClass("js-search-submit");
}

moveSearchButton();

/************************************************
selectSearch.js
************************************************/
function selectSearch() {
  var select, selectOption, selectedVal;
  select = $(".selectSearchCat");
  selectOption = $(".selectSearchCat option");
  selectedVal = function() {
    return select.find(":selected").text();  
  }

  // Create wrappers
  $(".selectSearchWrapper").append("<div class='itemWrapper'></div>");

  // Populate Items
  selectOption.each(function() {
    $(".itemWrapper").append("<span class='item' data-val-type='"+this.value+"'>"+this.text+"</span>");
  });

  // Display selected item
  $(".lbl-select").text(selectedVal());

  // Hide Options
  select.find("option").hide();

  // Event: Select Item
  $(".selectSearchWrapper .item").click( function() {
    dataVal = $(this).attr("data-val-type");
    $(".selectSearchCat option").attr('selected', false);
    $(".selectSearchCat option[value='"+dataVal+"']").attr('selected', true).hide();

    // Append selected text to custom label
    $(".lbl-select").text(selectedVal());
  });

  $(".selectSearchWrapper").on({
    click: function() {
      $(".itemWrapper").toggleClass("show");
    },
    mouseleave: function() {
      $(".itemWrapper").removeClass("show");
    }
  });

}
// selectSearch();

/************************************************
slidersCenter.js
************************************************/
function slidersCenter() {
  // $('.coverflow .view-content').slick('unslick');
  // $('.coverflow .view-content').slick({
  //   centerMode: true,
  //   centerPadding: '60px',
  //   slidesToShow: 5,
  //   responsive: [
  //     {
  //       breakpoint: 768,
  //       settings: {
  //         arrows: false,
  //         centerMode: true,
  //         centerPadding: '40px',
  //         slidesToShow: 5
  //       }
  //     },
  //     {
  //       breakpoint: 480,
  //       settings: {
  //         arrows: false,
  //         centerMode: true,
  //         centerPadding: '40px',
  //         slidesToShow: 1
  //       }
  //     }
  //   ]
  // });
}

slidersCenter();

/************************************************
weeksInColumn.js
************************************************/
function weeksInColumn() {
  elem = $(".add-info", context);
  // Append col1 and col2
  elem.prev(".sked").prepend(
    $("<div class='col1'></div>"), 
    $("<div class='col2'></div>")
  );
  // Loop to each tab
  if (!elem.prev(".sked").hasClass("active")) {
    elem.each(function() {
      sked = $(this).prev(".sked")
      col1 = sked.find(".col1");
      col2 = sked.find(".col2");
      days = $(this).prev(".sked").find(".views-field");
      // Loop to each week and append to col1 and col2
      days.each(function(index) {
        if(index <= 3) {
          col1.append(this);
        }
        if(index >= 4 && index <= 6) {
          col2.append(this);
        }
        if(index === 6) {
          sked.addClass("active");
        }
      });
    });
  }
}
weeksInColumn();

}};})(jQuery, Drupal);