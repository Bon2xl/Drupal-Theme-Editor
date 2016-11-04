jQuery(document).ready(function($){
	
    jQuery.fn.exists = function () { return this.length > 0 };
    if($('body.page-admin-appearance').length > 0) {
		/* THEME SETTINGS: COLOR PICKER */
		$('#edit-background-color').ColorPicker({
				onSubmit: function(hsb, hex, rgb, el) {
					$(el).val(hex);
					$(el).ColorPickerHide();
				},
				onBeforeShow: function () {
					$(this).ColorPickerSetColor(this.value);
				}
			}).bind('keyup', function(){
				$(this).ColorPickerSetColor(this.value);
			});
	
		$('.colorpicker_submit').text('Submit');
    }
});
