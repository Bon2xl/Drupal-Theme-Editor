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