/************************************************
fontResize.js
Drupal.settings.fontResizerEnable = check if font resizer is enabled in theme settings
************************************************/
var statusStr = Number(Drupal.settings.fontResizerEnable);
var isEnable = Boolean(statusStr);
if (isEnable) {
	// Build font sizer
	var fontSizer = '<div class="font-resizer">' +
		'<div class="toggle-resizer">' +
			'<i class="fa fa-font" aria-hidden="true"></i>' +
		'</div>' +
		'<div class="rf-wrapper">' +
			'<div class="fUp">' +
				'<i class="fa fa-font" aria-hidden="true"></i>' +
				'<i class="fa fa-plus" aria-hidden="true"></i>' +
			'</div>' +
			'<div class="fDown">' +
				'<i class="fa fa-font" aria-hidden="true"></i>' +
				'<i class="fa fa-minus" aria-hidden="true"></i>' +
			'</div>' +
	'</div>';

	// Position in each Theme/Template
	// hfstacks
	if ($(".font-resizer").length === 0) {
		if ($("body").hasClass("theme-hfstacks")) {
            $('#block-stacks-topicons-stacks-topicons').wrap("<li></li>").parent().appendTo(".top-menu .menu-block-wrapper > .menu");
			$(fontSizer).appendTo(".top-menu .menu-block-wrapper > .menu");
			$(".top-menu .font-resizer").wrap("<li id='repos-font-resizer'></li>");
			$(fontSizer).insertAfter(".toggle-mobile");
		// Catarina
		} else if ($("body").hasClass("theme-catarina") || $("body").hasClass("theme-crayons")) {
            $('#block-stacks-topicons-stacks-topicons').wrap("<li class='top-icon-databases-wrapper'></li>").parent().appendTo(".top-menu .menu-block-wrapper > .menu");
			$(fontSizer).appendTo(".top-menu .menu-block-wrapper > .menu");
			$(".top-menu .font-resizer").wrap("<li id='repos-font-resizer'></li>");
			$(fontSizer).insertAfter(".toggle-mobile");
		// Metals and up-coming theme
		} else if ($("body").hasClass("theme-caltech")) {
            $('#block-stacks-topicons-stacks-topicons').wrap("<li></li>").parent().appendTo(".top-menu .menu-block-wrapper > .menu");
			$(fontSizer).prependTo("#top-header > .row");
			$("#top-header .font-resizer").wrap("<div id='repos-font-resizer'></div>");
			// $(fontSizer).insertAfter(".toggle-mobile");
		} else {
			$(fontSizer).appendTo("#top-header");
		}
	}

	// Resizer Event
	$(".fUp").on('click', function(e) {
		e.preventDefault();
	  e.stopPropagation();

		var zoomPg, cuurZoomPG;
		zoomPg =  $("html").css("font-size");
		cuurZoomPG = parseFloat(zoomPg);
		limit = 19;
		// increase font if it's less than 1.3
		if(cuurZoomPG <= limit) {
			// remove min-font in fDown
			$(".fDown").removeClass("min-font");
			// increase size
			$("html").css("font-size", cuurZoomPG+1)

			// add max-font if it reaches max font
			if (cuurZoomPG === limit) {
				$(this).addClass("max-font");
			}
		}
	});
	//
	$(".fDown").on('click', function(e) {
		e.preventDefault();
	  e.stopPropagation();

		var zoomPg, cuurZoomPG, limit;
		zoomPg =  $("html").css("font-size");
		cuurZoomPG = parseFloat(zoomPg);
		limit = 14;
		// increase font if it's less than 1.3
		if(cuurZoomPG >= limit) {
			// remove min-font in fDown
			$(".fUp").removeClass("max-font");
			// increase size
			$("html").css("font-size", cuurZoomPG-1)

			// add max-font if it reaches max font
			if (cuurZoomPG === limit) {
				$(this).addClass("min-font");
			}
		}
	});

	$(".toggle-resizer").on('click', function(e) {
		$(".font-resizer").toggleClass("show-resizer");
	});

	$("#font-resizer").on('mouseleave', function(e) {
			e.preventDefault();
			e.stopPropagation();

			$(this).removeClass("show-resizer");
	});
}
