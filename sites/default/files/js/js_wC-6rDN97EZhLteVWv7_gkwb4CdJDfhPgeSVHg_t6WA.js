(function ($) {

Drupal.jQueryUiFilter = Drupal.jQueryUiFilter || {}

/**
 * Custom hash change event handling
 */
var _currentHash = location.hash;
Drupal.jQueryUiFilter.hashChange = function(func) {
  // Handle URL anchor change event in js
  // http://stackoverflow.com/questions/2161906/handle-url-anchor-change-event-in-js
  if ('onhashchange' in window) {
    $(window).bind('hashchange', func);
  }
  else {
    window.setInterval(function () {
      if (location.hash != _currentHash) {
        _currentHash = location.hash;
        func();
      }
    }, 100);
  }
}


/**
 * Apply jQuery UI filter widget options as the global default options.
 */
Drupal.jQueryUiFilter.globalOptions = function(widgetType) {
  Drupal.jQueryUiFilter.cleanupOptions(jQuery.extend(
    $.ui[widgetType].prototype.options,
    Drupal.settings.jQueryUiFilter[widgetType + 'Options'],
    Drupal.jQueryUiFilter[widgetType + 'Options']
  ));
}

/**
 * Get jQuery UI filter widget options.
 */
Drupal.jQueryUiFilter.getOptions = function(widgetType, options) {
  return Drupal.jQueryUiFilter.cleanupOptions(jQuery.extend(
    {}, // Using an empty object insures that new object is created and returned.
    Drupal.settings.jQueryUiFilter[widgetType + 'Options'],
    Drupal.jQueryUiFilter[widgetType + 'Options'],
    options || {}
  ));
}

/**
 * Cleanup jQuery UI filter options by converting 'true' and 'false' strings to native JavaScript Boolean value.
 */
Drupal.jQueryUiFilter.cleanupOptions = function(options) {
  // jQuery UI options that are Booleans must be converted from integers booleans
  for (var name in options) {
    if (typeof(options[name]) == 'string' && options[name] == '') {
      delete options[name];
    }
    else if (options[name] == 'false') {
      options[name] = false;
    }
    else if (options[name] === 'true') {
      options[name] = true;
    }
    else if (name === 'position' && options[name].indexOf(',') != -1) {
      options[name] = options[name].split(/\s*,\s*/);
    }
    else if (typeof(options[name]) == 'object') {
      options[name] = Drupal.jQueryUiFilter.cleanupOptions(options[name]);
    }
  }
  return options;
}

})(jQuery);
;
(function ($, Drupal) {

  Drupal.behaviors.hf_eds = {
    attach: function (context, settings) {
      // result per page & sort by dropdown
      $(".display-settings-lbl", context).on('click',function(e){
        $(this).stop().parent().toggleClass("open").stop();
      });

      // move keyword to main
      $("div.keywords", context).prependTo(".large-9.main.columns");

      // Hide Filters if empty
      var keywords = $("div.keywords", context);
      var keywordsChild = keywords.find(".items").children().length;
      //console.log(keywordsChild);
      if (Number(keywordsChild) <= 0) {
        keywords.addClass("hide");
      }

		$('.js-loginbutton', context).on('click', function() {
			var targetModal = $('#' + $(this).data('revealId'));
			var bibID = $(this).data('bib-id');
			targetModal.find('#bib-id').val(bibID);
		});

      /************************************************
      holdButton.js
      ************************************************/
      if ($("body").hasClass("front") || $("body").hasClass("page-homepage") || $("body").hasClass("page-eds")) {
      	//Defines the functinality for the holdbutton
      	$('.js-holdbutton', context).on('click', function(){
      		//Reset the html so they don't get stale messages
      		var loadingGifUrl = Drupal.settings.basePath + 'sites/all/modules/hf_eds/images/loading.gif';
      		$('.js-hold-form').html('<img src="' + loadingGifUrl + '"/>');
      		var bibID = $(this).data('bib-id');
      		$('.js-modal-bib-id').text(bibID);
      		//Make the availability call
      		var pathname = Drupal.settings.basePath + "my-account/hold/" + bibID;
      		//Make sure the x can close the window
      		$('a.close-reveal-modal', context).on('click', function() {
      			$('#stacks-request').hide();
      			//$(this).foundation('reveal', 'close');
      		});
      		$.post(pathname, function(post_result){
      			$('.js-hold-form').html(post_result);
      			Drupal.attachBehaviors('.js-hold-form');
      		});
      		//$('#stacks-status').foundation('reveal', 'open'); // open modal
      		$('#stacks-request').show();
      	});

      	$('.js-hold-submit-button', context).on('click', function(){
      		//Make the availability call
      		var accessionNumber = $(this).data('accession-number');
      		var isVolume = $(this).data('volume');
      		var pickup = $('input[name=pickup_location]:checked').val();
      		var volumeChoice = $('input[name=volume_choice]:checked').val();
      		var makeCall = true;
      		var args = {make_call:makeCall, pickup:pickup, accession_number:accessionNumber, volume_choice:volumeChoice};
      		var pathname = Drupal.settings.basePath + "eds/hold/";

      		//Because this is all done via ajax you need to double check that all
      		//of the fields needed have been submitted
      		if(pickup){
      			//If it's a volume make sure that volume choice is defined
      			if(isVolume){
      				if(volumeChoice){
      					jQuery.post(pathname, {elements: args}, function(post_result){
      						$('.js-form-message').html("");
      						Drupal.attachBehaviors('.js-form-message');
      						$('.js-hold-form').html(post_result);
      						Drupal.attachBehaviors('.js-hold-form');
      					});
      				} else {
      					$('.js-form-message').html("<h2>Please select a volume</h2>");
      					Drupal.attachBehaviors('.js-form-message');
      				}
      			} else {
      				//if it's not a volume and pickup is set then it's good to go
      				jQuery.post(pathname, {elements: args}, function(post_result){
      					$('.js-form-message').html("");
      					Drupal.attachBehaviors('.js-form-message');
      					$('.js-hold-form').html(post_result);
      					Drupal.attachBehaviors('.js-hold-form');
      				});
      			}
      		} else {
      			$('.js-form-message').html("<h2>Please select a location</h2>");
      			Drupal.attachBehaviors('.js-form-message');
      		}
      		return false;
      	});
      }

      // datepicker placeholder
      $(".form-wrapper input[name='from_date']").attr("placeholder", "From:");
      $(".form-wrapper input[name='to_date']").attr("placeholder", "To:");

      //Custom search Sidebar
      searchSidebar = $(".block-hf-eds-search-filters", context);

      //if no child remove title and ul
      searchSidebar.find("ul").each(function (i) {
        if ($(this).children().length <= 0) {
          $(this).hide();
          $(this).prev("h3").hide();
        }
      });

      //toggle
      searchSidebar.find("h3").click(function () {
        if ($(this).next().children().length > 0) {
          $(this).toggleClass("toggle");
          $(this).next().toggleClass("open");
        }
      });

      // Open Filter
      $(".btn-filter").click( function() {
        searchSidebar.addClass("open");
      })

      // Back button, close filter
      searchSidebar.find(".btn-close").click( function() {
        searchSidebar.removeClass("open");
      })

      //extLink = $(".extLink", context);
      //extLink.attr('href').text('Download');
      //$('.extLink').attr('href').text('Download');
    }
  };

})(jQuery, Drupal);
;
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
;
/**
 *
 */
(function($) {

	Drupal.behaviors.hf_eresources = {
		attach: function() {
//

			$(".login-link").attr('data-reveal-id', 'patron-login-modal');

			$('.ezproxy-submit').click(function(){
				$(this).siblings('.ezproxy').submit();

				return false;
			})
		}

	}
})(jQuery);;
(function ($, Drupal) { 
  Drupal.behaviors.hf_themes = { 
    attach: function(context, settings) {
      var basePath = Drupal.settings.basePath;
      var pathToTheme = Drupal.settings.pathToTheme;

			// 
      var themeForm = $("#hf-themes-admin-form");
      var item = $(".form-type-radio.form-item-themes");
      var checkedInput = themeForm.find("input:checked");

      // Append active class in the parent and append active label
      checkedInput.parent().addClass("theme-active");
      checkedInput.parent().find(".img").append("<span class='lbl-active'>Active</h1>");

      item.click(function() {
      	item.removeClass("selected");
      	$(this).addClass("selected");
      });
    }
  };
})(jQuery, Drupal); ;
(function ($, Drupal) { Drupal.behaviors.hf_tiles = { attach: function(context, settings) {

  $(".form-item-icon .form-radios").before("<div class='selected-icon no-icon'></div>");
  $(".form-item-icon .description").insertBefore(".form-item-icon .form-radios");

  // Check if has selected radio buttons
  is_checked = Number($(".form-item-icon .form-radios").find("input:checked").length);
  if (is_checked === 1) {
    $("selected-icon")
      .removeClass("no-icon")
      .addClass("has-icon")
      .text("");
  }

  // Click event
  $(".form-item-icon .description").click(function() {
    $(this).toggleClass('active');
    $(".form-item-icon .form-radios").toggleClass('active');
  });

}};})(jQuery, Drupal);
;
/*
--------------------------------------------------------------------------
(c) 2007 Lawrence Akka
 - jquery version of the spamspan code (c) 2006 SpamSpan (www.spamspan.com)

This program is distributed under the terms of the GNU General Public
Licence version 2, available at http://www.gnu.org/licenses/gpl.txt
--------------------------------------------------------------------------
*/

(function ($) { //Standard drupal jQuery wrapper.  See http://drupal.org/update/modules/6/7#javascript_compatibility
// load SpamSpan
Drupal.behaviors.spamspan = {
  attach: function(context, settings) {
    // get each span with class spamspan
    $("span.spamspan", context).each(function (index) {
      // Replace each <spam class="t"></spam> with .
      if ($('span.t', this).length) {
        $('span.t', this).replaceWith('.');
      }
      
      // For each selected span, set mail to the relevant value, removing spaces
      var _mail = ($("span.u", this).text() +
        "@" +
        $("span.d", this).text())
        .replace(/\s+/g, '');

      // Build the mailto URI
      var _mailto = "mailto:" + _mail;
      if ($('span.h', this).length) {
        // Find the header text, and remove the round brackets from the start and end
        var _headerText = $("span.h", this).text().replace(/^ ?\((.*)\) ?$/, "$1");
        // split into individual headers, and return as an array of header=value pairs
        var _headers = $.map(_headerText.split(/, /), function (n, i) {
          return (n.replace(/: /, "="));
        });

        var _headerstring = _headers.join('&');
        _mailto += _headerstring ? ("?" + _headerstring) : '';
      }

      // Find the anchor content, and remove the round brackets from the start and end
      var _anchorContent = $("span.a", this).html();
      if (_anchorContent) {
        _anchorContent = _anchorContent.replace(/^ ?\((.*)\) ?$/, "$1");
      }

      // create the <a> element, and replace the original span contents

      //check for extra <a> attributes
      var _attributes = $("span.e", this).html();
      var _tag = "<a></a>";
      if (_attributes) {
        _tag = "<a " + _attributes.replace("<!--", "").replace("-->", "") + "></a>";
      }

      $(this).after(
        $(_tag)
          .attr("href", _mailto)
          .html(_anchorContent ? _anchorContent : _mail)
          .addClass("spamspan")
      ).remove();
    });
  }
};
}) (jQuery);;
(function ($) {

Drupal.extlink = Drupal.extlink || {};

Drupal.extlink.attach = function (context, settings) {
  if (!settings.hasOwnProperty('extlink')) {
    return;
  }

  // Strip the host name down, removing ports, subdomains, or www.
  var pattern = /^(([^\/:]+?\.)*)([^\.:]{4,})((\.[a-z]{1,4})*)(:[0-9]{1,5})?$/;
  var host = window.location.host.replace(pattern, '$3$4');
  var subdomain = window.location.host.replace(pattern, '$1');

  // Determine what subdomains are considered internal.
  var subdomains;
  if (settings.extlink.extSubdomains) {
    subdomains = "([^/]*\\.)?";
  }
  else if (subdomain == 'www.' || subdomain == '') {
    subdomains = "(www\\.)?";
  }
  else {
    subdomains = subdomain.replace(".", "\\.");
  }

  // Build regular expressions that define an internal link.
  var internal_link = new RegExp("^https?://" + subdomains + host, "i");

  // Extra internal link matching.
  var extInclude = false;
  if (settings.extlink.extInclude) {
    extInclude = new RegExp(settings.extlink.extInclude.replace(/\\/, '\\'), "i");
  }

  // Extra external link matching.
  var extExclude = false;
  if (settings.extlink.extExclude) {
    extExclude = new RegExp(settings.extlink.extExclude.replace(/\\/, '\\'), "i");
  }

  // Extra external link CSS selector exclusion.
  var extCssExclude = false;
  if (settings.extlink.extCssExclude) {
    extCssExclude = settings.extlink.extCssExclude;
  }

  // Extra external link CSS selector explicit.
  var extCssExplicit = false;
  if (settings.extlink.extCssExplicit) {
    extCssExplicit = settings.extlink.extCssExplicit;
  }

  // Find all links which are NOT internal and begin with http as opposed
  // to ftp://, javascript:, etc. other kinds of links.
  // When operating on the 'this' variable, the host has been appended to
  // all links by the browser, even local ones.
  // In jQuery 1.1 and higher, we'd use a filter method here, but it is not
  // available in jQuery 1.0 (Drupal 5 default).
  var external_links = new Array();
  var mailto_links = new Array();
  $("a:not(." + settings.extlink.extClass + ", ." + settings.extlink.mailtoClass + "), area:not(." + settings.extlink.extClass + ", ." + settings.extlink.mailtoClass + ")", context).each(function(el) {
    try {
      var url = this.href.toLowerCase();
      if (url.indexOf('http') == 0
        && ((!url.match(internal_link) && !(extExclude && url.match(extExclude))) || (extInclude && url.match(extInclude)))
        && !(extCssExclude && $(this).parents(extCssExclude).length > 0)
        && !(extCssExplicit && $(this).parents(extCssExplicit).length < 1)) {
        external_links.push(this);
      }
      // Do not include area tags with begin with mailto: (this prohibits
      // icons from being added to image-maps).
      else if (this.tagName != 'AREA' 
        && url.indexOf('mailto:') == 0 
        && !(extCssExclude && $(this).parents(extCssExclude).length > 0)
        && !(extCssExplicit && $(this).parents(extCssExplicit).length < 1)) {
        mailto_links.push(this);
      }
    }
    // IE7 throws errors often when dealing with irregular links, such as:
    // <a href="node/10"></a> Empty tags.
    // <a href="http://user:pass@example.com">example</a> User:pass syntax.
    catch (error) {
      return false;
    }
  });

  if (settings.extlink.extClass) {
    Drupal.extlink.applyClassAndSpan(external_links, settings.extlink.extClass);
  }

  if (settings.extlink.mailtoClass) {
    Drupal.extlink.applyClassAndSpan(mailto_links, settings.extlink.mailtoClass);
  }

  if (settings.extlink.extTarget) {
    // Apply the target attribute to all links.
    $(external_links).attr('target', settings.extlink.extTarget);
  }

  Drupal.extlink = Drupal.extlink || {};

  // Set up default click function for the external links popup. This should be
  // overridden by modules wanting to alter the popup.
  Drupal.extlink.popupClickHandler = Drupal.extlink.popupClickHandler || function() {
    if (settings.extlink.extAlert) {
      return confirm(settings.extlink.extAlertText);
    }
   }

  $(external_links).click(function(e) {
    return Drupal.extlink.popupClickHandler(e);
  });
};

/**
 * Apply a class and a trailing <span> to all links not containing images.
 *
 * @param links
 *   An array of DOM elements representing the links.
 * @param class_name
 *   The class to apply to the links.
 */
Drupal.extlink.applyClassAndSpan = function (links, class_name) {
  var $links_to_process;
  if (Drupal.settings.extlink.extImgClass){
    $links_to_process = $(links);
  }
  else {
    var links_with_images = $(links).find('img').parents('a');
    $links_to_process = $(links).not(links_with_images);
  }
  $links_to_process.addClass(class_name);
  var i;
  var length = $links_to_process.length;
  for (i = 0; i < length; i++) {
    var $link = $($links_to_process[i]);
    if ($link.css('display') == 'inline' || $link.css('display') == 'inline-block') {
      if (class_name == Drupal.settings.extlink.mailtoClass) {
        $link.append('<span class="' + class_name + '"><span class="element-invisible"> ' + Drupal.settings.extlink.mailtoLabel + '</span></span>');
      }
      else {
        $link.append('<span class="' + class_name + '"><span class="element-invisible"> ' + Drupal.settings.extlink.extLabel + '</span></span>');
      }
    }
  }
};

Drupal.behaviors.extlink = Drupal.behaviors.extlink || {};
Drupal.behaviors.extlink.attach = function (context, settings) {
  // Backwards compatibility, for the benefit of modules overriding extlink
  // functionality by defining an "extlinkAttach" global function.
  if (typeof extlinkAttach === 'function') {
    extlinkAttach(context);
  }
  else {
    Drupal.extlink.attach(context, settings);
  }
};

})(jQuery);
;
(function($) {

Drupal.admin = Drupal.admin || {};
Drupal.admin.behaviors = Drupal.admin.behaviors || {};
Drupal.admin.hashes = Drupal.admin.hashes || {};

/**
 * Core behavior for Administration menu.
 *
 * Test whether there is an administration menu is in the output and execute all
 * registered behaviors.
 */
Drupal.behaviors.adminMenu = {
  attach: function (context, settings) {
    // Initialize settings.
    settings.admin_menu = $.extend({
      suppress: false,
      margin_top: false,
      position_fixed: false,
      tweak_modules: false,
      tweak_permissions: false,
      tweak_tabs: false,
      destination: '',
      basePath: settings.basePath,
      hash: 0,
      replacements: {}
    }, settings.admin_menu || {});
    // Check whether administration menu should be suppressed.
    if (settings.admin_menu.suppress) {
      return;
    }
    var $adminMenu = $('#admin-menu:not(.admin-menu-processed)', context);
    // Client-side caching; if administration menu is not in the output, it is
    // fetched from the server and cached in the browser.
    if (!$adminMenu.length && settings.admin_menu.hash) {
      Drupal.admin.getCache(settings.admin_menu.hash, function (response) {
          if (typeof response == 'string' && response.length > 0) {
            $('body', context).prepend(response);
          }
          var $adminMenu = $('#admin-menu:not(.admin-menu-processed)', context);
          // Apply our behaviors.
          Drupal.admin.attachBehaviors(context, settings, $adminMenu);
          // Allow resize event handlers to recalculate sizes/positions.
          $(window).triggerHandler('resize');
      });
    }
    // If the menu is in the output already, this means there is a new version.
    else {
      // Apply our behaviors.
      Drupal.admin.attachBehaviors(context, settings, $adminMenu);
    }
  }
};

/**
 * Collapse fieldsets on Modules page.
 */
Drupal.behaviors.adminMenuCollapseModules = {
  attach: function (context, settings) {
    if (settings.admin_menu.tweak_modules) {
      $('#system-modules fieldset:not(.collapsed)', context).addClass('collapsed');
    }
  }
};

/**
 * Collapse modules on Permissions page.
 */
Drupal.behaviors.adminMenuCollapsePermissions = {
  attach: function (context, settings) {
    if (settings.admin_menu.tweak_permissions) {
      // Freeze width of first column to prevent jumping.
      $('#permissions th:first', context).css({ width: $('#permissions th:first', context).width() });
      // Attach click handler.
      $modules = $('#permissions tr:has(td.module)', context).once('admin-menu-tweak-permissions', function () {
        var $module = $(this);
        $module.bind('click.admin-menu', function () {
          // @todo Replace with .nextUntil() in jQuery 1.4.
          $module.nextAll().each(function () {
            var $row = $(this);
            if ($row.is(':has(td.module)')) {
              return false;
            }
            $row.toggleClass('element-hidden');
          });
        });
      });
      // Collapse all but the targeted permission rows set.
      if (window.location.hash.length) {
        $modules = $modules.not(':has(' + window.location.hash + ')');
      }
      $modules.trigger('click.admin-menu');
    }
  }
};

/**
 * Apply margin to page.
 *
 * Note that directly applying marginTop does not work in IE. To prevent
 * flickering/jumping page content with client-side caching, this is a regular
 * Drupal behavior.
 */
Drupal.behaviors.adminMenuMarginTop = {
  attach: function (context, settings) {
    if (!settings.admin_menu.suppress && settings.admin_menu.margin_top) {
      $('body:not(.admin-menu)', context).addClass('admin-menu');
    }
  }
};

/**
 * Retrieve content from client-side cache.
 *
 * @param hash
 *   The md5 hash of the content to retrieve.
 * @param onSuccess
 *   A callback function invoked when the cache request was successful.
 */
Drupal.admin.getCache = function (hash, onSuccess) {
  if (Drupal.admin.hashes.hash !== undefined) {
    return Drupal.admin.hashes.hash;
  }
  $.ajax({
    cache: true,
    type: 'GET',
    dataType: 'text', // Prevent auto-evaluation of response.
    global: false, // Do not trigger global AJAX events.
    url: Drupal.settings.admin_menu.basePath.replace(/admin_menu/, 'js/admin_menu/cache/' + hash),
    success: onSuccess,
    complete: function (XMLHttpRequest, status) {
      Drupal.admin.hashes.hash = status;
    }
  });
};

/**
 * TableHeader callback to determine top viewport offset.
 *
 * @see toolbar.js
 */
Drupal.admin.height = function() {
  var $adminMenu = $('#admin-menu');
  var height = $adminMenu.outerHeight();
  // In IE, Shadow filter adds some extra height, so we need to remove it from
  // the returned height.
  if ($adminMenu.css('filter') && $adminMenu.css('filter').match(/DXImageTransform\.Microsoft\.Shadow/)) {
    height -= $adminMenu.get(0).filters.item("DXImageTransform.Microsoft.Shadow").strength;
  }
  return height;
};

/**
 * @defgroup admin_behaviors Administration behaviors.
 * @{
 */

/**
 * Attach administrative behaviors.
 */
Drupal.admin.attachBehaviors = function (context, settings, $adminMenu) {
  if ($adminMenu.length) {
    $adminMenu.addClass('admin-menu-processed');
    $.each(Drupal.admin.behaviors, function() {
      this(context, settings, $adminMenu);
    });
  }
};

/**
 * Apply 'position: fixed'.
 */
Drupal.admin.behaviors.positionFixed = function (context, settings, $adminMenu) {
  if (settings.admin_menu.position_fixed) {
    $adminMenu.addClass('admin-menu-position-fixed');
    $adminMenu.css('position', 'fixed');
  }
};

/**
 * Move page tabs into administration menu.
 */
Drupal.admin.behaviors.pageTabs = function (context, settings, $adminMenu) {
  if (settings.admin_menu.tweak_tabs) {
    var $tabs = $(context).find('ul.tabs.primary');
    $adminMenu.find('#admin-menu-wrapper > ul').eq(1)
      .append($tabs.find('li').addClass('admin-menu-tab'));
    $(context).find('ul.tabs.secondary')
      .appendTo('#admin-menu-wrapper > ul > li.admin-menu-tab.active')
      .removeClass('secondary');
    $tabs.remove();
  }
};

/**
 * Perform dynamic replacements in cached menu.
 */
Drupal.admin.behaviors.replacements = function (context, settings, $adminMenu) {
  for (var item in settings.admin_menu.replacements) {
    $(item, $adminMenu).html(settings.admin_menu.replacements[item]);
  }
};

/**
 * Inject destination query strings for current page.
 */
Drupal.admin.behaviors.destination = function (context, settings, $adminMenu) {
  if (settings.admin_menu.destination) {
    $('a.admin-menu-destination', $adminMenu).each(function() {
      this.search += (!this.search.length ? '?' : '&') + Drupal.settings.admin_menu.destination;
    });
  }
};

/**
 * Apply JavaScript-based hovering behaviors.
 *
 * @todo This has to run last.  If another script registers additional behaviors
 *   it will not run last.
 */
Drupal.admin.behaviors.hover = function (context, settings, $adminMenu) {
  // Delayed mouseout.
  $('li.expandable', $adminMenu).hover(
    function () {
      // Stop the timer.
      clearTimeout(this.sfTimer);
      // Display child lists.
      $('> ul', this)
        .css({left: 'auto', display: 'block'})
        // Immediately hide nephew lists.
        .parent().siblings('li').children('ul').css({left: '-999em', display: 'none'});
    },
    function () {
      // Start the timer.
      var uls = $('> ul', this);
      this.sfTimer = setTimeout(function () {
        uls.css({left: '-999em', display: 'none'});
      }, 400);
    }
  );
};

/**
 * Apply the search bar functionality.
 */
Drupal.admin.behaviors.search = function (context, settings, $adminMenu) {
  // @todo Add a HTML ID.
  var $input = $('input.admin-menu-search', $adminMenu);
  // Initialize the current search needle.
  var needle = $input.val();
  // Cache of all links that can be matched in the menu.
  var links;
  // Minimum search needle length.
  var needleMinLength = 2;
  // Append the results container.
  var $results = $('<div />').insertAfter($input);

  /**
   * Executes the search upon user input.
   */
  function keyupHandler() {
    var matches, $html, value = $(this).val();
    // Only proceed if the search needle has changed.
    if (value !== needle) {
      needle = value;
      // Initialize the cache of menu links upon first search.
      if (!links && needle.length >= needleMinLength) {
        // @todo Limit to links in dropdown menus; i.e., skip menu additions.
        links = buildSearchIndex($adminMenu.find('li:not(.admin-menu-action, .admin-menu-action li) > a'));
      }
      // Empty results container when deleting search text.
      if (needle.length < needleMinLength) {
        $results.empty();
      }
      // Only search if the needle is long enough.
      if (needle.length >= needleMinLength && links) {
        matches = findMatches(needle, links);
        // Build the list in a detached DOM node.
        $html = buildResultsList(matches);
        // Display results.
        $results.empty().append($html);
      }
    }
  }

  /**
   * Builds the search index.
   */
  function buildSearchIndex($links) {
    return $links
      .map(function () {
        var text = (this.textContent || this.innerText);
        // Skip menu entries that do not contain any text (e.g., the icon).
        if (typeof text === 'undefined') {
          return;
        }
        return {
          text: text,
          textMatch: text.toLowerCase(),
          element: this
        };
      });
  }

  /**
   * Searches the index for a given needle and returns matching entries.
   */
  function findMatches(needle, links) {
    var needleMatch = needle.toLowerCase();
    // Select matching links from the cache.
    return $.grep(links, function (link) {
      return link.textMatch.indexOf(needleMatch) !== -1;
    });
  }

  /**
   * Builds the search result list in a detached DOM node.
   */
  function buildResultsList(matches) {
    var $html = $('<ul class="dropdown admin-menu-search-results" />');
    $.each(matches, function () {
      var result = this.text;
      var $element = $(this.element);

      // Check whether there is a top-level category that can be prepended.
      var $category = $element.closest('#admin-menu-wrapper > ul > li');
      var categoryText = $category.find('> a').text()
      if ($category.length && categoryText) {
        result = categoryText + ': ' + result;
      }

      var $result = $('<li><a href="' + $element.attr('href') + '">' + result + '</a></li>');
      $result.data('original-link', $(this.element).parent());
      $html.append($result);
    });
    return $html;
  }

  /**
   * Highlights selected result.
   */
  function resultsHandler(e) {
    var $this = $(this);
    var show = e.type === 'mouseenter' || e.type === 'focusin';
    $this.trigger(show ? 'showPath' : 'hidePath', [this]);
  }

  /**
   * Closes the search results and clears the search input.
   */
  function resultsClickHandler(e, link) {
    var $original = $(this).data('original-link');
    $original.trigger('mouseleave');
    $input.val('').trigger('keyup');
  }

  /**
   * Shows the link in the menu that corresponds to a search result.
   */
  function highlightPathHandler(e, link) {
    if (link) {
      var $original = $(link).data('original-link');
      var show = e.type === 'showPath';
      // Toggle an additional CSS class to visually highlight the matching link.
      // @todo Consider using same visual appearance as regular hover.
      $original.toggleClass('highlight', show);
      $original.trigger(show ? 'mouseenter' : 'mouseleave');
    }
  }

  // Attach showPath/hidePath handler to search result entries.
  $results.delegate('li', 'mouseenter mouseleave focus blur', resultsHandler);
  // Hide the result list after a link has been clicked, useful for overlay.
  $results.delegate('li', 'click', resultsClickHandler);
  // Attach hover/active highlight behavior to search result entries.
  $adminMenu.delegate('.admin-menu-search-results li', 'showPath hidePath', highlightPathHandler);
  // Attach the search input event handler.
  $input.bind('keyup search', keyupHandler);
};

/**
 * @} End of "defgroup admin_behaviors".
 */

})(jQuery);
;
(function($) {

Drupal.admin = Drupal.admin || {};
Drupal.admin.behaviors = Drupal.admin.behaviors || {};

/**
 * @ingroup admin_behaviors
 * @{
 */

/**
 * Apply active trail highlighting based on current path.
 *
 * @todo Not limited to toolbar; move into core?
 */
Drupal.admin.behaviors.toolbarActiveTrail = function (context, settings, $adminMenu) {
  if (settings.admin_menu.toolbar && settings.admin_menu.toolbar.activeTrail) {
    $adminMenu.find('> div > ul > li > a[href="' + settings.admin_menu.toolbar.activeTrail + '"]').addClass('active-trail');
  }
};

/**
 * Toggles the shortcuts bar.
 */
Drupal.admin.behaviors.shortcutToggle = function (context, settings, $adminMenu) {
  var $shortcuts = $adminMenu.find('.shortcut-toolbar');
  if (!$shortcuts.length) {
    return;
  }
  var storage = window.localStorage || false;
  var storageKey = 'Drupal.admin_menu.shortcut';
  var $body = $(context).find('body');
  var $toggle = $adminMenu.find('.shortcut-toggle');
  $toggle.click(function () {
    var enable = !$shortcuts.hasClass('active');
    $shortcuts.toggleClass('active', enable);
    $toggle.toggleClass('active', enable);
    if (settings.admin_menu.margin_top) {
      $body.toggleClass('admin-menu-with-shortcuts', enable);
    }
    // Persist toggle state across requests.
    storage && enable ? storage.setItem(storageKey, 1) : storage.removeItem(storageKey);
    this.blur();
    return false;
  });

  if (!storage || storage.getItem(storageKey)) {
    $toggle.trigger('click');
  }
};

/**
 * @} End of "ingroup admin_behaviors".
 */

})(jQuery);
;