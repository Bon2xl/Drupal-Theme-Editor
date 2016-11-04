/************************************************
hide-parent-class
// this adds a .js-hide to the parent class of hidden buttons
// views forms just hide the submit button but leave it rendered
************************************************/

$('input.js-hide').parent('div.views-submit-button').addClass('js-hide');
