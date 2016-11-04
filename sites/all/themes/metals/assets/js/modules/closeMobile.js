/************************************************
closeMobile.js
************************************************/
function closeMobile() {
  $(".btn-close-mobile").on("click.toggleCanvas", function(){
   $(".exit-off-canvas").click();
 }); 
}
closeMobile();