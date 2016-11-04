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