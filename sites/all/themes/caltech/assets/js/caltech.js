(function ($, Drupal) { Drupal.behaviors.caltech = { attach: function(context, settings) {
var basePath = Drupal.settings.basePath;
var pathToTheme = Drupal.settings.pathToTheme;

/************************************************
basicSearch.js
************************************************/
function basicSearch() {
	$('.magnifier-link').click(function(e) {
		e.preventDefault();
		e.stopPropagation();
		if($("#search-block-form").hasClass('active')) {
			$("#search-block-form").removeClass('active');
		} else {
			$("#search-block-form").addClass('active');	
			$("#search-block-form .form-text").focus();
		}

	});

	$("#search-block-form .form-text, #search-block-form .form-submit").click(function(e){
		e.stopPropagation();
	});

	$(document).click(function() {
		$("#search-block-form").removeClass('active');
	})
}

basicSearch();


/************************************************
blockTitle.js
************************************************/
function blockTitle() {
  elem = ".panel-panel .big-slider, .panel-panel .coverflow, .panel-panel .cta-callout, .panel-panel .mini-slider";
  $(elem)
    .parent()
    .parent()
    .prev(".blk-title")
    .hide();

  $(".panel-display  .coverflow").each(function(index) {
		blkTitle = $(this).parent().parent().prev(".blk-title").text();
		$(this).prepend("<h4 class='blk-title-inline eq"+index+"'><span>"+blkTitle+"</span></div>");
  });
}

blockTitle();



/************************************************
ellipsises.js
************************************************/
function ellipsises() {
  if($("body").hasClass("theme-caltech")) {
    $(".big-slider .views-field-field-body").dotdotdot({
      watch: "window",
      height: 100
    });

    $(".cta-description").dotdotdot({
      watch: "window",
      height: 50
    });
  }
}
ellipsises();


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

/************************************************
slider.js
************************************************/
function slider() {
	$(".big-slider .views-field-field-body").on('click',function() {
		hrefLink = $(this).parent().prev().attr("href");
		window.location.href = hrefLink;
	});
}

slider();


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