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