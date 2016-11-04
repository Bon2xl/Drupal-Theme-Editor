(function ($, Drupal) { Drupal.behaviors.hfstacks = { attach: function(context, settings) {
var basePath = Drupal.settings.basePath;
var pathToTheme = Drupal.settings.pathToTheme;

/************************************************
basic-search-dropdown.js
************************************************/
var magnifierLink, btnClose;

// create magnifier elem
magnifierLink = $("<a class='magnifier-link'></a>");
magnifierLink.insertBefore("#top-header .basic-search .content");
// create magnifier close
btnClose = $("<a class='btn-close'></a>");
btnClose.insertBefore("#top-header .basic-search .content form");

// Toggle switch
$('.magnifier-link').on('click', function() {
	$(this).addClass('active');
	$(this).next().addClass('show');
	$('.top-nav').addClass('hideThis');
});

// close basic search
$('.btn-close').on('click', function() {
	$('.magnifier-link').removeClass('active');
	$('.magnifier-link').next().removeClass('show');
	$('.top-nav').removeClass('hideThis');
});

/************************************************
big-slider.js
************************************************/
bgSlider();
function bgSlider() {
  if (!$('.big-slider .view-content').hasClass("slick-initialized")) {
    $(".big-slider .view-content").slick({
      slidesToShow: 1,
      slidesToScroll: 1,
    });
  }

  // $(".big-slider .views-row").each(function() {
  //   var imgelem = ".views-field-field-slideshow-image img";
  //   var imgsrc = $(this).find(imgelem).attr("src");
  //   $(this).css("backgroundImage","url("+imgsrc+")");
  // });
}


/************************************************
callout.js
************************************************/
function calloutFn() {
	var elemCallOut = $(".cta-callout");
	elemCallOut.find(".views-field").each( function() {
		var elem = $(this).find("img");
		var ctaSrc = elem.attr("src");
		$(this).find(".imgHolder").css("backgroundImage","url("+ctaSrc+")");
	});
}
calloutFn();

/************************************************
coverflow.js
************************************************/
function coverflow($className) {
  var numVal;
  var elemDIV = $($className + ' .inner-content');
  if (!elemDIV.hasClass("slick-initialized")) {
    $centerMode = false;
    // If medical page
    if ($('body').hasClass("page-layout-b")) {
      numToShow = 2;
      numToScroll = 3;
      numToScroll_II = 3;
    } else if ($('body').hasClass("theme-metals")) {
      numToShow = 3;
      numToScroll = 1;
      numToScroll_II = 1;
      $centerMode = true;
    } else {
      numToShow = 6;
      numToScroll = 6;
      numToScroll_II = 3;
    }
  

    elemDIV.slick({
      dots: false,
      infinite: false,
      arrows: true,
      speed: 300,
      slidesToShow: numToShow,
      slidesToScroll: numToScroll,
      dots: false,
      centerMode: $centerMode,
      infinite: true,
      responsive: [
        {
          breakpoint: 1024,
          settings: {
            slidesToShow: 3,
            slidesToScroll: numToScroll_II,
            infinite: true,
          }
        },
        {
          breakpoint: 480,
          settings: {
            slidesToShow: 1,
            slidesToScroll: 1
          }
        }
      ]
    });
  }
}

coverflow('.coverflow');  



/************************************************
ctaEqualHeight.js
containerClass: parent class container
rowClass: row class
************************************************/
function setEqualHeight(containerClass, rowClass) {
  $(containerClass).each(function() {
  	var tallestcolumn = 0;
  	$(rowClass).each(function() {
  		currentHeight = $(this).height();
  		if(currentHeight > tallestcolumn) {
  		  tallestcolumn  = currentHeight;
  		}
  	});
  	$(rowClass).height(tallestcolumn);
  });
}
setEqualHeight(".cta-callout .views-row", ".cta-callout .views-field .field-content");
$(window).resize(function() {
  setEqualHeight(".cta-callout .views-row", ".cta-callout .views-field .field-content");
});


/************************************************
datepicker.js
************************************************/
$( ".form-wrapper .datepicker", context ).datepicker({
	showButtonPanel: true,
  changeMonth: true,
  changeYear: true
});

/************************************************
disable-slick-slider.js
************************************************/
// $(".panels-ipe-startedit, .panels-ipe-cancel, .panels-ipe-save").click(function (){
//   console.log("unslick slider!");
//   $('#tabs-wrapper .inner, .resource-list-slider .view-content, #book_similar-titles').slick("unslick");
//   $('#tabs-wrapper .inner, .resource-list-slider .view-content, #book_similar-titles').slick();
// });

/************************************************
don't allow empty or space only searches
************************************************/
function checkSearchInput() {
  var trimVal = $.trim($('#searchBox').val());
  if (trimVal.length != 0) {
    $('#searchSubmit').attr('disabled', false);
    $('#globalSearch').addClass("active");
  } else {
    $('#searchSubmit').attr('disabled', true);
    $('#globalSearch').removeClass("active");
  }
}

checkSearchInput();
$('#searchBox').keyup(checkSearchInput);

/************************************************
eresources.js toggle
************************************************/
$(".page-eresources-az .eresource-title").wrapInner('<a></a>');
$(".view-eresources").find(".eresource-title a").click(function(e){
	e.preventDefault();
	$(this).parent().parent().toggleClass("active");
});



/************************************************
eventDate.js
For date repeating create a popup;
************************************************/
function eventDate() {
	var viewElm, viewCount, ttl, btnRepeater;
	viewElm = $('.view-calendar');
	viewCount = viewElm.length;
	// check if views calendar exist
	if(viewCount >= 1) {
		$('.view-calendar .views-row').each(function(index) {
			spanCount = $(this).find('.month span').length;
			divCount = $(this).find('.month div').length;
			viewsDate = $(this).find('.views-date');
			// check if there's a repeat rule on each row
			if(spanCount >= 2 || divCount >= 2) {
				viewsDate.addClass("popup-enabled");
				viewsDate.prepend('<div class="btn-multi-date">Multi date</div>');
				$(this).find(".popup-enabled");
			}
		});
	}

	// toggle popup
	$('.popup-enabled').on({
		'click': function(event) {
			$(this).addClass('showMonth');
		},
		'mouseleave': function(event) {
			$(this).removeClass('showMonth');
		}
	});
}
eventDate();

/************************************************
fontResize.js
************************************************/
// Build font sizer
var fontSizer = '<div id="font-resizer">' +
	'<div class="fUp">' +
		'<i class="fa fa-font" aria-hidden="true"></i>' +
		'<i class="fa fa-plus" aria-hidden="true"></i>' +
	'</div>' +
	'<div class="fDown">' +
		'<i class="fa fa-font" aria-hidden="true"></i>' +
		'<i class="fa fa-minus" aria-hidden="true"></i>' +
	'</div>' +
'<div>';
$(fontSizer).appendTo("#top-header");

// Resizer Event

$(".fUp").on('click', function() {
	var zoomPg, cuurZoomPG;
	zoomPg =  $("html").css("zoom");
	cuurZoomPG = parseFloat(zoomPg);
	// increas font if its less that 1.3
	if(cuurZoomPG <= 1.3) {
		// remove min-font in fDown
		$(".fDown").removeClass("min-font");
		// increase size
		$("html").css("zoom", cuurZoomPG+.1)

		// add max-font if it reaches max font
		if (cuurZoomPG === 1.3) {
			$(this).addClass("max-font");
		}
	}
})


/************************************************
for-demo.js
************************************************/
if($('body').hasClass('node-type-directory-listing')) {
    $(".field-name-field-job-title-listing").removeClass('clearfix');
}


/************************************************
gtranslate.js - allowing placeholder form field attribute
************************************************/
// Find all placeholders
var placeholders = document.querySelectorAll('input[placeholder]');

if (placeholders.length) {
    // convert to array
    placeholders = Array.prototype.slice.call(placeholders);

    // copy placeholder text to a hidden div
    var div = $('<div id="placeholders" style="display:none;"></div>');

    placeholders.forEach(function(input){
        var text = input.placeholder;
        div.append('<div>' + text + '</div>');
    });

    $('body').append(div);

    // save the first placeholder in a closure
    var originalPH = placeholders[0].placeholder;

    // check for changes and update as needed
    setInterval(function(){
        if (isTranslated()) {
            updatePlaceholders();
            originalPH = placeholders[0].placeholder;
        }
    }, 500);

    // hoisted ---------------------------
    function isTranslated() { // true if the text has been translated
        var currentPH = $($('#placeholders > div')[0]).text();
        return !(originalPH == currentPH);
    }

    function updatePlaceholders() {
        $('#placeholders > div').each(function(i, div){
            placeholders[i].placeholder = $(div).text();
        });
    }
}


/************************************************
guide.js accordion
************************************************/
function guideAccordion() {
	if ($('body').hasClass('node-type-guide')) {
		$('.field-type-text').on('click', function(e) {
				$(this).next().toggleClass('active');
				$(this).parent().parent().next().toggleClass('active');
		});
	}
}
guideAccordion();

/************************************************
Mobile version
************************************************/
// Mobile version goes here

/************************************************
hide-parent-class
// this adds a .js-hide to the parent class of hidden buttons
// views forms just hide the submit button but leave it rendered
************************************************/

$('input.js-hide').parent('div.views-submit-button').addClass('js-hide');


/************************************************
jQuery placeholder
https://github.com/mathiasbynens/jquery-placeholder
************************************************/
$('input, textarea').placeholder();

 

/***************************************************************
featured-views.js: featured column image to div background cover
***************************************************************/
// $('.coverflow .views-field-field-isbn').addClass('active');
// $('.coverflow .views-field-field-isbn.active').each( function() {
//   var dis = $(this);
//   var imgSrc = dis.find('img').attr('src');
//   dis.css('background-image', 'url('+imgSrc+')');
// });

// // hide parent container if image isn't found to keep all elements centered
// $(".coverflow .views-field-field-isbn a[href='']").parent().parent().hide();

/************************************************
json-hbs.js
// Get JSON using handlebars
// ex: nid:50, hbsTemplatePath:'resource-list.hbs', containerIdCLass:'#stacks-modal'
jsonHBS(50, 'resource-list.hbs', '#stacks-modal');
************************************************/
var jsonHBS = function(nid, hbsTemplatePath, containerClass){
  $(containerClass+' .spinner').fadeIn("fast");
  $.getJSON(basePath+"resource-lists/"+nid, function(data) {
    $.ajax({
      url: basePath+'sites/all/themes/hfstacks/assets/hbs_templates/'+hbsTemplatePath,
      cache: false,
      dataType: "text",
      success: function(dataTpl) {
        source    = dataTpl;
        template  = Handlebars.compile(source);
        html = template(data);
        $(containerClass+' .spinner').fadeOut("slow");
        $(containerClass+' .content').html(html);
      },
      complete: function() {
        if (!$('#stacks-modal .coverflow .view-content').hasClass("slick-initialized")) {
          coverflowII('#stacks-modal .coverflow');
        }
      }
    });
  });
};

function coverflowII($className) {
  var elemDIV = $($className + ' .view-content');
  var $centerMode = false;
  var $infinite = true;
  if ($('body').hasClass("theme-metals")) {
    $centerMode = true;
    $infinite = true;
  }
  elemDIV.slick({
    infinite: true,
    arrows: true,
    speed: 300,
    slidesToShow: 7,
    slidesToScroll: 7,
    dots: true,
    infinite: $infinite,
    centerMode: $centerMode,
    responsive: [
      {
        breakpoint: 1024,
        settings: {
          slidesToShow: 3,
          slidesToScroll: 3,
        }
      },
      {
        breakpoint: 640,
        settings: {
          slidesToShow: 2,
          slidesToScroll: 2
        }
      },
      {
        breakpoint: 480,
        settings: {
          slidesToShow: 1,
          slidesToScroll: 1
        }
      }
    ]
  });
}


/************************************************
main-nav.js
************************************************/
// $(window).resize(function() {
// 	function mainNav() {
// 		if ($(".main-nav").offset().top >= 130) {
// 			console.log($(".main-nav").offset().top);	
// 			if (!$(".main-nav").hasClass("hide")) {
// 				$(".main-nav").addClass("hide");	
// 			}
// 		} else if ($(".main-nav").offset().top <= 131) {
// 			$(".main-nav").removeClass("hide");
// 		}
// 	}
// 	mainNav();
// });

/************************************************
masonary.js
************************************************/
function masonaryFun() {
  $('.masonary').masonry({
    // options
    itemSelector: '.block-item'
  });
}

$(window).on('load', function(){
	if ($("body").hasClass("node-type-guide")) {
		masonaryFun();
	}
});

/************************************************
mini-slider.js
************************************************/
miniSlider();
function miniSlider() {
  if (!$('.mini-slider .slider-content').hasClass("slick-initialized")) {
    $centerMode = false;
    $numToScroll = 5;
    $numToScroll_II = 3;
    if ($('body').hasClass("theme-metals")) {
      $centerMode = true;
      $numToScroll = 1;
      $numToScroll_II = 1;
    }
    $('.mini-slider .slider-content').slick({
      slidesToShow: 5,
      slidesToScroll: $numToScroll,
      centerMode: $centerMode,
      infinite: true,
      responsive: [
        {
          breakpoint: 1024,
          settings: {
            slidesToShow: 3,
            slidesToScroll: $numToScroll_II,
            dots: true
          }
        },
        {
          breakpoint: 600,
          settings: {
            slidesToShow: 3,
            slidesToScroll: $numToScroll_II
          }
        },
        {
          breakpoint: 480,
          settings: {
            slidesToShow: 1,
            slidesToScroll: 1
          }
        }
        // You can unslick at a given breakpoint now by adding:
        // settings: "unslick"
        // instead of a settings object
      ]
    });
    $(".mini-slider .img-wrapper img").each(function() {
      var imgsrc = $(this).attr("src");
      $(this).parent().css("backgroundImage","url("+imgsrc+")");
    });
  }

}


/************************************************
don't allow empty or space only searches
************************************************/
function moveAdminBar() {
  $("#admin-menu").prependTo("body");
}

moveAdminBar();


/************************************************
panelCancelOverwrite.js
This script overwrite panels cancel button
************************************************/
function panelCancelOverwrite() {
	if($('body').hasClass('panels-ipe')) {
		$("#panels-ipe-cancel").click(function() {
			location.reload();
		});	
	}	
}

panelCancelOverwrite();

/************************************************
patron-login.js
************************************************/
$("#top-header .menu a:contains('Login')").attr('data-reveal-id', 'patron-login-modal');
$(".mobile-menu .menu a:contains('Login')").click(function (e) {
  e.preventDefault();
  $(this).attr('data-reveal-id', 'patron-login-modal');
})

/************************************************
resource-list.js
************************************************/
$(".resource-list-slider .views-row").each( function(i) {
	THIS = $(this);
	var isbnNum = THIS.find(".field-name-field-isbn .field-item").text();
	$(this).find(".img").css('background-image', 'url("http://www.syndetics.com/index.aspx?type=hw7&client=sils&isbn='+isbnNum+'/MC.GIF&=$upc")');
});

// Enable Slick Slider
if (!$('.resource-list-slider .view-content').hasClass("slick-initialized")) {
	$centerMode = false;
	if ($('body').hasClass("theme-metals")) {
	  $centerMode = true;
	}
	$('.resource-list-slider .view-content').slick({
	  slidesToShow: 5,
	  slidesToScroll: 5,
	  centerMode: $centerMode,
	  dots: false,

	  responsive: [
	      {
	          breakpoint: 1024,
	          settings: {
	              slidesToShow: 3,
	              slidesToScroll: 3,
	              infinite: true,
	          }
	      },
	      {
	          breakpoint: 600,
	          settings: {
	              slidesToShow: 3,
	              slidesToScroll: 3
	          }
	      },
	      {
	          breakpoint: 480,
	          settings: {
	              slidesToShow: 1,
	              slidesToScroll: 1
	          }
	      }
	      // You can unslick at a given breakpoint now by adding:
	      // settings: "unslick"
	      // instead of a settings object
	    ]
	});
}



// Get books
$(".resource-list-slider .open-modal").click( function(evt){
	evt.preventDefault();
	var elem = Number($(this).attr("data-id")); // get nid ID
	var ttl = $(this).parent().find(".views-field-title .field-content").text();

	// For Catarina theme
	if ($('body').hasClass('palette_catarina')) {
		$('#stacks-modal .coverflow .view-content', context).slick("unslick");
	}

	$('#stacks-modal h2').text(ttl); // title
	jsonHBS(elem, 'resource-list.hbs', '#stacks-modal'); // call handlebars function
	$('#stacks-modal').foundation('reveal', 'open'); // open modal
});

// Close the modal
$('a.close-stacks-modal').on('click', function() {
	$('#stacks-modal').foundation('reveal', 'close');
	$('#stacks-modal .content').html(' ');
});

if (!$('#book_similar-titles').hasClass("slick-initialized")) {
	$('#book_similar-titles').slick({
	  slidesToShow: 8,
		slidesToScroll: 8,
		dots: false,
    responsive: [
        {
            breakpoint: 1024,
            settings: {
                slidesToShow: 5,
                slidesToScroll: 5,
                infinite: true,
                dots: true
            }
        },
        {
            breakpoint: 600,
            settings: {
                slidesToShow: 3,
                slidesToScroll: 3
            }
        },
        {
            breakpoint: 480,
            settings: {
                slidesToShow: 2,
                slidesToScroll: 2
            }
        }
        // You can unslick at a given breakpoint now by adding:
        // settings: "unslick"
        // instead of a settings object
    ]
	});
}


/************************************************
Collect map data in each row tabs and assign to arrPins
************************************************/
var rowElm, arrPins = [];
rowElm = $(".uni-tabs .view-content .views-row");
rowElm.each(function (index) {
  attr = $(this).find(".gmap_data").data('map');
  arrPins.push(attr);
});

/************************************************
initialized the map
************************************************/
function initializeGMap() {
  obj = arrPins[0];
  if (obj != undefined) {
    $title = obj.title;
    $lat = Number(obj.lat);
    $long = Number(obj.long);
    $opt = 14;
  } else {
    $title = 'Location not selected';
    $lat = 53.5557956;
    $long = -113.6340293;
    $opt = 1;
    $('.uni-map-inline').addClass('hideMap');
  }
  

  var options = {
    zoom: $opt,
    scrollwheel: false,
    center: new google.maps.LatLng($lat, $long),
    mapTypeId: google.maps.MapTypeId.ROADMAP
  }
  map = new google.maps.Map(document.getElementById("gmap_canvas"), options);

  marker = new google.maps.Marker({
    map: map,
    position: new google.maps.LatLng($lat, $long)
  });

  infowindow = new google.maps.InfoWindow({
    content: $title
  });

  google.maps.event.addListener(marker, "click", function () {
    infowindow.open(map, marker);
  });
  infowindow.open(map, marker);
}
google.maps.event.addDomListener(window, 'load', initializeGMap);

/************************************************
Update PIN in google map
************************************************/
function updateGMap(rowNum) {
  obj = arrPins[rowNum];
  if (obj != undefined) {
    $lat = Number(obj.lat);
    $long = Number(obj.long);
    $title = obj.title;

    marker.setPosition(new google.maps.LatLng($lat, $long));
    map.panTo( new google.maps.LatLng($lat, $long) );
    map.setZoom(14);
    infowindow.setContent($title);
    $('.uni-map-inline').removeClass('hideMap').addClass('showMap');
  } else {
    console.warn('geocode not avail');
    $('.uni-map-inline').removeClass('showMap').addClass('hideMap');
  }
}

/************************************************
uni-tabs.js
// Tabs 
************************************************/
function uniTabs() {
  var rowCount, uniTabsRow;

  uniTabsRow = $(".view-branch-location .views-row");
  rowCount = uniTabsRow.length - 1;

  // Create tabs
  uniTabsRow.each( function(index) {
    var num, ttl, link;
    num = Number(index + 1);
    ttl = $(this).find(".branch-name").html();
    lnk = "<a class='tabs-ttl' rel='views-row-"+num+"'>"+ttl+"</a>";
    // Generate tab link 
    $(lnk).appendTo('#tabs-wrapper .inner'); 

    // Add Active class to first row
    if (index === 0) {
      $(this).addClass("active");
    }
   
    if (index == rowCount) {
      $('#tabs-wrapper .inner', context).slick({
        dots: false,
        infinite: false,
        arrows: true,
        speed: 300,
        dots: false,
        slidesToShow: 4,
        slidesToScroll: 4,
        responsive: [
          {
            breakpoint: 1024,
            settings: {
                slidesToShow: 3,
                slidesToScroll: 3,
                infinite: true,
            }
          },
          {
            breakpoint: 600,
            settings: {
                slidesToShow: 2,
                slidesToScroll: 2
            }
          },
          {
            breakpoint: 480,
            settings: {
                slidesToShow: 1,
                slidesToScroll: 1
            }
          }
        ]
      });
    }
  });

  // First tabs set to active
  $("#tabs-wrapper .slick-track .tabs-ttl:first-child", context).addClass('active');

  // Click event for tabs
  $("#tabs-wrapper .tabs-ttl", context).on('click', function (){
    var This, getRel, rowNum;
    
    This = $(this);
    getRel = This.attr("rel");
    getRelLength = Number(getRel.length);
    rowNum = Number(getRel.substring(10,getRelLength) - 1); 

    // Add active to click event
    $("#tabs-wrapper .tabs-ttl", context).removeClass('active');
    This.addClass('active');

    // Remove active class
    uniTabsRow.removeClass("active");

    // Add active class
    $("."+getRel).addClass("active");
    
    // Update each location map
    updateGMap(rowNum);
    
  });

  // ****************************
  // Swipe Event Detection
  // ****************************
  $('#tabs-wrapper .inner', context).on('beforeChange', function(event, slick, currentSlide, nextSlide){
    var cuurSl = currentSlide + 1;
    var nextSl = nextSlide + 1;
    // on swipe move active to current 
    $('#tabs-wrapper .inner', context).find(".tabs-ttl.active").removeClass("active");
    $('#tabs-wrapper .inner', context).find(".tabs-ttl[rel=views-row-"+nextSl+"]").addClass("active");

    // on swipe changes tabs
    $(".uni-tabs .view-content").find(".views-row.active").removeClass("active");
    $(".uni-tabs .view-content").find(".views-row-"+nextSl+"").addClass("active");

    // Update each location map
    updateGMap(nextSlide);
  });
}

if (!$('#tabs-wrapper .inner').hasClass("slick-initialized")) {
  uniTabs();
}









}};})(jQuery, Drupal);