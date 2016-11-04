/************************************************
ctaEqualHeight.js
containerClass: parent class container
rowClass: row class
************************************************/
function setEqualHeight(containerClass, rowClass) {
  $(containerClass).each(function() {
  	var tallestcolumn = 0;
  	$(rowClass).each(function() {
  		currentHeight = $(this).height();
  		if(currentHeight > tallestcolumn) {
  		  tallestcolumn  = currentHeight;
  		}
  	});
  	$(rowClass).height(tallestcolumn);
  });
}
setEqualHeight(".cta-callout .views-row", ".cta-callout .views-field .field-content");
$(window).resize(function() {
  setEqualHeight(".cta-callout .views-row", ".cta-callout .views-field .field-content");
});
