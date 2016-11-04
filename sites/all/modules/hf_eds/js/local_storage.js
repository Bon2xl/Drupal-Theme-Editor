jQuery(document).ready(function() {

  //Make sure that the saved array item is at least initialized
  if('localStorage' in window && window['localStorage'] !== null){
    var store = window.localStorage;
    //Get existing saved items
    var item_list;
    if(!store["saved_items"]){
      item_list = [];
      store["saved_items"] = JSON.stringify(item_list);
    }
  }

  //Checking to see if on the saved items page
  if(jQuery('#saved-items').length){
    var store = window.localStorage;
    var item_list;
    if(store["saved_items"]){
      item_list = JSON.parse(store["saved_items"]);
    }

    if(item_list.length == 0){
      jQuery('#saved-items').html("No Saved Items");
    } else {
      var pathname = window.location.pathname + "/ajax-content";
      jQuery.post(pathname, {elements: item_list}, function(post_result){
        jQuery('#saved-items').html(post_result);
      })
    }
    //jQuery('#saved-items').html(JSON.stringify(item_list));
  }

  if(jQuery('#saved_items_number').length){
    updateItemCount();
  }

  //Check to see if the search results have already been selected
  jQuery(".select_item_checkbox").each(function(){
    if(checkIfSelected(jQuery(this).attr('id'))){
      jQuery(this).prop('checked', true);
    }
  });
});


/**
 * add item from users saved search list
 */
function saveSearchToggle(button, title, url) {
  // ajax call
  $.ajax({
    type: 'POST',
    url: Drupal.settings.basePath + 'eds/savesearch/add',
    data: {'TITLE':title,'URL':url},
    success: function(data) {
      $(button).addClass('added');
      $(button).text('Remove From Saved Search');
      $(button).find('a').css("font-weight", "bold");
      $(button).attr("onclick","deleteSearchToggle(this, '"+title+"', '"+url+"')");
    }
  });
}

/**
 * delete item from users saved search list
 */
function deleteSearchToggle(button, id) {
  // ajax call
  $.ajax({
    type: 'POST',
    url: Drupal.settings.basePath + 'eds/savesearch/delete',
    data: {'ID':id},
    success: function(data) {
      $(button).addClass('added');
      $(button).text('Save This Search');
      $(button).find('a').css("font-weight", "bold");
      $(button).attr("onclick","saveSearchToggle(this, '"+title+"', '"+url+"')");
    }
  });
}

/**
 * delete item from users saved search
 */
function deleteSearchListToggle(button, id) {
  // ajax call
  $.ajax({
    type: 'POST',
    url: Drupal.settings.basePath + 'eds/savesearch/delete',
    data: {'ID':id},
    success: function(data) {
      $(button).addClass('deleted');
      $(button).text('Deleted');
      $(button).contents().unwrap();
    }
  });
}


/**
 * add items from users saved list
 */
function saveItemToggle(button, accessionNumber, databaseId) {
  // ajax call
  $.ajax({
    type: 'POST',
    url: Drupal.settings.basePath + 'eds/savelist/add',
    data: {'AN':accessionNumber,'DB':databaseId},
    success: function(data) {
      $(button).addClass('added');
      $(button).text('Remove from saved list');
      $(button).attr("onclick","deleteItemToggle(this, '"+accessionNumber+"', '"+databaseId+"')");
    }
  });
}


/**
 * remove items from users saved list
 */
function deleteItemToggle(button, accessionNumber, databaseId) {
  // ajax call
  $.ajax({
    type: 'POST',
    url: Drupal.settings.basePath + 'eds/savelist/delete',
    data: {'AN':accessionNumber,'DB':databaseId},
    success: function(data) {
      $(button).removeClass('added');
      $(button).text('Add to saved list');
      $(button).attr("onclick","saveItemToggle(this, '"+accessionNumber+"', '"+databaseId+"')");
    }
  });
}


/**
 * On the search page there is a selected items count. This function
 * if for updating that number. It is updated on the search page load
 * as well as every time one of the "select item" boxes is clicked
 */
function updateItemCount(){
  if('localStorage' in window && window['localStorage'] !== null){
    var store = window.localStorage;
    if(store["saved_items"]){
      item_list = JSON.parse(store["saved_items"]);
    } else {
      item_list = [];
    }
    var string = '<span class="lbl">Selected items:</span> (<a href="' + Drupal.settings.basePath + 'eds/saved-items?query=' + getParameterByName('query') + '">' + item_list.length + '</a>)';
    jQuery('#saved_items_number').html(string);
  }
}



/**
 * This function is for selecting all of the "select" boxes on the search page.
 * It's called by the select all box. The box states need to get checked before
 * the click function because it wasn't getting the the proper checked state
 * after click the state needs to be changed back to the proper state because
 * the click function changes it. It's convoluded but it works so meh.
 */
function selectAllItems(checkbox){
  if(checkbox.checked){
    jQuery(".select_item_checkbox").each(function(){
      if(!jQuery(this).is(':checked')){
        jQuery(this).prop('checked', true);
        jQuery(this).click();
        jQuery(this).prop('checked', true);
      }
    });
  } else {
    jQuery(".select_item_checkbox").each(function(){
      if(jQuery(this).is(':checked')){
        jQuery(this).prop('checked', false);
        jQuery(this).click();
        jQuery(this).prop('checked', false);
      }
    });
  }
}


/*
 * This function is for checking if a search result has already been selected or not. 
 * It will take the ID of the div and compare it to values in local storage. it returns
 * true if found and false it it wasn't
 */
function checkIfSelected(divId){
  if('localStorage' in window && window['localStorage'] !== null){
    var store = window.localStorage;
    if(store["saved_items"].length > 0){
      var list = JSON.parse(store['saved_items']);
      for(var i=0; i < list.length; i++){
        if(divId == list[i]){
          return true;
        }
      }
      return false;
    }
  }
}


function getParameterByName(name) {
    name = name.replace(/[\[]/, "\\[").replace(/[\]]/, "\\]");

    var regex = new RegExp("[\\?&]" + name + "=([^&#]*)"),
        results = regex.exec(location.search);
    return results == null ? "" : decodeURIComponent(results[1].replace(/\+/g, " "));
}
