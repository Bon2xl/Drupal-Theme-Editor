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