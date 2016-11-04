/************************************************
calendarDayTitle.js
************************************************/
function calendarDayTitle() {
  if( $("body").hasClass('page-calendar-day') ) {
  	$('#page-title > .large-12').prepend('<h1 class="page-title">Calendar - Day</h1>');
  }
}
calendarDayTitle();
