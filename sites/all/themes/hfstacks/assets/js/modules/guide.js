/************************************************
guide.js accordion
************************************************/
function guideAccordion() {
	if ($('body').hasClass('node-type-guide')) {
		$('.field-type-text').on('click', function(e) {
				$(this).next().toggleClass('active');
				$(this).parent().parent().next().toggleClass('active');
		});
	}
}
guideAccordion();

/************************************************
Mobile version
************************************************/
// Mobile version goes here