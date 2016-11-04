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
	$slidesToShow = 5;
	if ($('body').hasClass("theme-metals")) {
	  $centerMode = true;
	}

	$('.resource-list-slider .view-content').slick({
	  slidesToShow: $slidesToShow,
	  slidesToScroll: $slidesToShow,
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
    ]
	});
}
