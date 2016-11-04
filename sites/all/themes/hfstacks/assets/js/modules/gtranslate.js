/************************************************
gtranslate.js - allowing placeholder form field attribute
************************************************/
if (!$("#searchBox").hasClass('placeholder-enabled')) {
    var searchBox = $("#searchBox");
    var searchBoxTxt = searchBox.attr("placeholder");
    var elem = $('<div id="placeholders" style="display:none;">'+searchBoxTxt+'</div>');
    $(elem).insertAfter("#searchBox"); // hidden placeholder
    $("#searchBox").addClass("placeholder-enabled");    
    setTimeout(updateTxt, 2800);
}

function updateTxt() {
    var holdTxt = $("#placeholders").text();
    $("#searchBox").attr("placeholder", holdTxt);
}

$('.gTranslate').on('change', function() {
    setTimeout(updateTxt, 2000);
});


// Find all placeholders
// var placeholders = document.querySelectorAll('input[placeholder]');
// console.log(placeholders);

// if (placeholders.length) {
//     // convert to array
//     placeholders = Array.prototype.slice.call(placeholders);

//     // copy placeholder text to a hidden div
//     var div = $('<div id="placeholders" style="display:none;"></div>');

//     placeholders.forEach(function(input){
//         var text = input.placeholder;
//         div.append('<div>' + text + '</div>');
//     });

//     $('body').append(div);

//     // save the first placeholder in a closure
//     var originalPH = placeholders[0].placeholder;

//     $('.gTranslate').on('change', function() {
//         // if (isTranslated()) {
//             updatePlaceholders();
//             originalPH = placeholders[0].placeholder;
//         // }
//     });

//     // hoisted ---------------------------
//     function isTranslated() { // true if the text has been translated
//         var currentPH = $($('#placeholders > div')[0]).text();
//         return !(originalPH == currentPH);
//     }

//     function updatePlaceholders() {
//         $('#placeholders > div').each(function(i, div){
//             placeholders[i].placeholder = $(div).text();
//         });
//     }
// }
