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

if ($('.map-wrapper').length >= 1) {
  google.maps.event.addDomListener(window, 'load', initializeGMap);
}

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




/************************************************
Check tabs count
************************************************/
function locations() {
  uniTabs = $('.uni-tabs');
  viewsLocation = $(".view-branch-location");
  if (viewsLocation.length === 1) {
    if( viewsLocation.find(".views-row").length === 1) {
      uniTabs.addClass("single-location");    
    }
  } else if (viewsLocation.length >= 2) {
    console.log("Location's block must be duplicated");
  }

}
locations();








