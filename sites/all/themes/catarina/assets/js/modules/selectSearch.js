/************************************************
selectSearch.js
************************************************/
function selectSearch() {
  var select, selectOption, selectedVal;
  select = $(".selectSearchCat");
  selectOption = $(".selectSearchCat option");
  selectedVal = function() {
    return select.find(":selected").text();  
  }

  // Create wrappers
  $(".selectSearchWrapper").append("<div class='itemWrapper'></div>");

  // Populate Items
  selectOption.each(function() {
    $(".itemWrapper").append("<span class='item' data-val-type='"+this.value+"'>"+this.text+"</span>");
  });

  // Display selected item
  $(".lbl-select").text(selectedVal());

  // Hide Options
  select.find("option").hide();

  // Event: Select Item
  $(".selectSearchWrapper .item").click( function() {
    dataVal = $(this).attr("data-val-type");
    $(".selectSearchCat option").attr('selected', false);
    $(".selectSearchCat option[value='"+dataVal+"']").attr('selected', true).hide();

    // Append selected text to custom label
    $(".lbl-select").text(selectedVal());
  });

  $(".selectSearchWrapper").on({
    click: function() {
      $(".itemWrapper").toggleClass("show");
    },
    mouseleave: function() {
      $(".itemWrapper").removeClass("show");
    }
  });

}
// selectSearch();