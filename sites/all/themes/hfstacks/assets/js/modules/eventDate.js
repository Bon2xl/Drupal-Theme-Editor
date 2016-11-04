/************************************************
eventDate.js
For date repeating create a popup;
************************************************/

function eventDate() {
  // Calendar listing
  var viewElm, viewCount, ttl, btnRepeater;
  viewElm = $('.view-calendar');
  viewCount = viewElm.length;
  // check if views calendar exist
  if(viewCount >= 1) {
    $('.view-calendar .views-row').each(function(index) {
      spanCount = $(this).find('.month span').length;
      divCount = $(this).find('.month div').length;
      viewsDate = $(this).find('.views-date');
      // check if there's a repeat rule on each row
      if(spanCount >= 2 || divCount >= 2) {
        viewsDate.addClass("popup-enabled");
        viewsDate.prepend('<div class="btn-multi-date">Multi date</div>');
      }
    });
  }

  // Calendar Node
  function calendarNode() {
    var fieldItem, fieldItemCount;
    fieldDate = $('.field-name-field-event-date');
    fieldItem = fieldDate.find(".field-item");
    fieldItemCount = fieldItem.length;

    if(fieldItemCount >= 2) {
      fieldDate.addClass("popup-enabled");
      fieldDate.find(".field-items").before('<div class="btn-multi-date">Multi date</div>');
    }
  }
  if($("body").hasClass("node-type-event")) {
    calendarNode();
  }

  //Event block homepage
  function homepageNode() {

    $('.panel-display .field-name-field-event-date').each(function(){
      var fieldItem, fieldItemCount;
      fieldDate = $(this);
      fieldItem = fieldDate.find(".field-item");
      fieldItemCount = fieldItem.length;

      if(fieldItemCount >= 2) {
        fieldDate.addClass("popup-enabled");
        fieldDate.find(".field-items").before('<div class="btn-multi-date">Multi date</div>');
      }
    });
  }

  if($("body").hasClass("page-homepage")) {
    homepageNode();

    // wrap all blocks within their own section
    $('.panel-display h2.blk-title').each(function() {
      $(this).next().andSelf().wrapAll('<section class="panels-section" />');
    });

    $('section.panels-section').each(function() {
      $(this).find('.pane-block').removeClass('panel-pane');
    });

    // remove .inside wrapper div from panels (which messes up foundation grid)
    $('.panel-panel .inside').replaceWith(function () {
      return this.childNodes;
    });

    // style event blocks
    $('.panel-panel .sidebar').each(function() {
      $(this).find('.field-type-image').wrap('<div class="small-12 medium-6 columns" />');
      $(this).find('.field-type-datetime').nextAll().andSelf().wrapAll('<div class="small-12 medium-6 columns" />');
    });
    $('.panel-2col-stacked .sidebar').removeClass('columns medium-4 large-3');
    $('.panel-2col-stacked .node-content').removeClass('medium-8 large-9').addClass('small-12');

    // // wrap panel two cols in section
    // $('.panel-2col-stacked .panel-col-first, .panel-2col-stacked .panel-col-last').wrapAll('<div class="panel-event-section" />');

    // strip panel classes & replace with foundation grid on 6 col sections
    $('.panel-2col-stacked .panel-col-first, .panel-2col-stacked .panel-col-last').each(function() {
      $(this).addClass('columns small-12 medium-6');
      $(this).find('.node-event').addClass('panel-event-block');
      $(this).find('.big-slider').parent().addClass('panel-slider-block');
    });

    // events full width in panels
    $('.panel-col-bottom, .panel-col-top').each(function() {
      $(this).removeClass('panel-panel');
      $(this).find('.node-event').parent().addClass('columns small-12');
      $(this).find('.node-event').addClass('panel-event-block');

      // add wrapper class to .big-slider within panels
      $(this).find('.big-slider').closest('.pane-block').addClass('columns small-12');
      $(this).find('.big-slider').closest('.pane-content').addClass('panel-slider-block');
    });


    // $('.panel-2col-stacked .panel-panel .panels-section').each(function() {
    //   $('.pane-content').addClass('panel-event-block');
    // });
  }



  // event multi-date select
  function panelEventsToggle() {
    $('.popup-enabled').on('click', function(e) {
      $(this).toggleClass("showMonth");
      e.preventDefault();
    });
  }

  function panelEventHover() {
    $('.popup-enabled').on({
      'click': function(event) {
        $(this).addClass('showMonth');
      },
      'mouseleave': function(event) {
        $(this).removeClass('showMonth');
      }
    });
  }

  if($('body').hasClass('mobile')) {
    panelEventsToggle();
  } else {
    panelEventHover();
  };

}

eventDate();