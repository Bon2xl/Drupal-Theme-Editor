/************************************************
json-hbs.js
// Get JSON using handlebars
// ex: nid:50, hbsTemplatePath:'resource-list.hbs', containerIdCLass:'#stacks-modal'
jsonHBS(50, 'resource-list.hbs', '#stacks-modal');
************************************************/
var jsonHBS = function(nid, hbsTemplatePath, containerClass){
  $(containerClass+' .spinner').fadeIn("fast");
  $.getJSON(basePath+"resource-lists/"+nid, function(data) {
    $.ajax({
      url: basePath+'sites/all/themes/hfstacks/assets/hbs_templates/'+hbsTemplatePath,
      cache: false,
      dataType: "text",
      success: function(dataTpl) {
        source    = dataTpl;
        template  = Handlebars.compile(source);
        html = template(data);
        $(containerClass+' .spinner').fadeOut("slow");
        $(containerClass+' .content').html(html);
      },
      complete: function() {
        if (!$('#stacks-modal .coverflow .view-content').hasClass("slick-initialized")) {
          coverflowII('#stacks-modal .coverflow');
        }
      }
    });
  });
};

function coverflowII($className) {
  var elemDIV = $($className + ' .view-content');
  var $centerMode = false;
  var $infinite = true;
  if ($('body').hasClass("theme-metals")) {
    $centerMode = true;
    $infinite = true;
  }
  elemDIV.slick({
    infinite: true,
    arrows: true,
    speed: 300,
    slidesToShow: 7,
    slidesToScroll: 7,
    dots: true,
    infinite: $infinite,
    centerMode: $centerMode,
    responsive: [
      {
        breakpoint: 1024,
        settings: {
          slidesToShow: 3,
          slidesToScroll: 3,
        }
      },
      {
        breakpoint: 640,
        settings: {
          slidesToShow: 2,
          slidesToScroll: 2
        }
      },
      {
        breakpoint: 480,
        settings: {
          slidesToShow: 1,
          slidesToScroll: 1
        }
      }
    ]
  });
}
