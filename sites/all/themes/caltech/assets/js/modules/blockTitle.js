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

