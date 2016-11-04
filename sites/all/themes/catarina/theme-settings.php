<?php

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
global $theme_path;

function catarina_form_system_theme_settings_alter(&$form, $form_state) {
	$form['stacks_fieldset'] = array(
		'#type' => 'fieldset',
		'#title' => 'Stacks General Configuration'
	);

	// Create the form widgets using Forms API
	$form['stacks_fieldset']['color_palette'] = array(
		'#title' => t('Select a theme'),
			'#type' => 'select',
			'#options' => array(
          'autumn_mist' => 'Autumn Mist',
          'back_to_school' => 'Back to School',
          'bare_essentials' => 'Bare Essentials',
          'classy_casual' => 'Classy Casual',
          'calm_concrete' => 'Calm Concrete',
					'catarina' => 'Corporate Keener',
          'dragon_fire' => 'Dragon Fire',
					'drift_wood' => 'Drift Wood',
          'great_white' => 'Great White',
          'lady_business' => 'Lady Business',
          'mountain_sunset' => 'Mountain Sunset',
          'night_frost' => 'Night Frost',
          'summer_lawn' => 'Summer Lawn',
          'sweet_sugar' => 'Sweet Sugar',
          'time_travel' => 'Time Travel',
          'the_reef' => 'The Reef',
          'tropical_swell' => 'Tropical Swell',
          'urban_skyline' => 'Urban Skyline',
			),
			'#default_value' => theme_get_setting('color_palette'),
			'#field_prefix' => '
				<div class="dropdown-a"></div>
				<div class="dropdown-b">
					<ul>
            <li class="autumn_mist">
              <span class="prim"></span>
              <span class="secnd"></span>
              Autumn Mist
            </li>
            <li class="back_to_school">
              <span class="prim"></span>
              <span class="secnd"></span>
              Back to School
            </li>
            <li class="bare_essentials">
              <span class="prim"></span>
              <span class="secnd"></span>
              Bare Essentials
            </li>
            <li class="classy_casual">
              <span class="prim"></span>
              <span class="secnd"></span>
              Classy Casual
            </li>
            <li class="calm_concrete">
              <span class="prim"></span>
              <span class="secnd"></span>
              Calm Concrete
            </li>
						<li class="catarina">
							<span class="prim"></span>
							<span class="secnd"></span>
							Corporate Keener
						</li>
            <li class="dragon_fire">
              <span class="prim"></span>
              <span class="secnd"></span>
              Dragon Fire
            </li>
            <li class="drift_wood">
              <span class="prim"></span>
              <span class="secnd"></span>
              Drift Wood
            </li>
            <li class="lady_business">
              <span class="prim"></span>
              <span class="secnd"></span>
              Lady Business
            </li>
            <li class="great_white">
              <span class="prim"></span>
              <span class="secnd"></span>
              Great White
            </li>
            <li class="mountain_sunset">
              <span class="prim"></span>
              <span class="secnd"></span>
              Mountain Sunset
            </li>
            <li class="night_frost">
              <span class="prim"></span>
              <span class="secnd"></span>
              Night Frost
            </li>
            <li class="summer_lawn">
              <span class="prim"></span>
              <span class="secnd"></span>
              Summer Lawn
            </li>
            <li class="sweet_sugar">
              <span class="prim"></span>
              <span class="secnd"></span>
              Sweet Sugar
            </li>
            <li class="time_travel">
              <span class="prim"></span>
              <span class="secnd"></span>
              Time Travel
            </li>
            <li class="the_reef">
              <span class="prim"></span>
              <span class="secnd"></span>
              The Reef
            </li>
            <li class="tropical_swell">
              <span class="prim"></span>
              <span class="secnd"></span>
              Tropical Swell
            </li>
            <li class="urban_skyline">
              <span class="prim"></span>
              <span class="secnd"></span>
              Urban Skyline
						</li>
					</ul>
				</div>
			',
		  '#attached' => array(
		  	'css' => array(drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/selecttheme/selecttheme.css'),
	      'js' => array(drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/selecttheme/selecttheme.js'),
	    )

	);

	// Create the form widgets using Forms API
	// $form['stacks_fieldset']['foundation_wide'] = array (x
	// 		'#type' => 'checkbox',
	// 		'#title' => t('Expand the theme to 1150'),
	// 		'#default_value' => theme_get_setting('foundation_wide')
	// );

	$form['stacks_fieldset']['background_color'] = array(
    '#type' => 'textfield',
    '#field_prefix' => '#',
    '#title' => t('Background color:'),
    '#maxlength' => 7,
    '#description' => t('Select a background color.'),
    '#default_value' => theme_get_setting('background_color'),
		'#attached' => array(
			'css' => array(drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/color/admin.css'),
			'js' => array(
				drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/color/colorpicker.js',
				drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/color/admin.js',
			),
		),
	);

	$form['stacks_fieldset']['background_image_gallery'] = array (
	  '#title' => t('Choose Background Image from Gallery'),
	  '#type' => 'textfield',
	  // '#disabled' => TRUE,
	  '#field_prefix' => '
	  	<div class="gallery-images">
  			<div class="item" data-img="library" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/library.jpg");"></div>
  			<div class="item" data-img="water" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/water.jpg");"></div>
  			<div class="item" data-img="leaf" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/leaf.jpg");"></div>
  			<div class="item" data-img="sky" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/sky.jpg");"></div>
  			<div class="item" data-img="stars" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/stars.jpg");"></div>
  			<div class="item" data-img="balloon" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/balloon.jpg");"></div>
        <div class="item" data-img="umbrella" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/umbrella.jpg");"></div>
        <div class="item" data-img="underwater-leaf" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/underwater-leaf.jpg");"></div>
        <div class="item" data-img="autumn-forest" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/autumn-forest.jpg");"></div>
        <div class="item" data-img="escalator" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/escalator.jpg");"></div>
        <div class="item" data-img="waves" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/waves.jpg");"></div>
  			<div class="item" data-img="ground" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/ground.jpg");"></div>
  		</div>
	  	<a href="javscript:void(0)" class="btn-gallery-img button">Remove</a>
	  ',
	  '#description' => t('The selected image will be displayed as the page background.'),
	  '#default_value' => theme_get_setting('background_image_gallery'),
	  '#attributes' => array(
		  'class' => array(
	      'field-type-gallery-input'
	    )
	  ),
	  '#attached' => array(
	  	'css' => array(drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/gallery.css'),
      'js' => array(drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/gallery.js'),
    ),
	);

  // background image
  $default_file_dir = 'public://background_image_full';
  $folder = file_prepare_directory($default_file_dir, FILE_CREATE_DIRECTORY);
  $settings_theme = $form_state['build_info']['args'][0];
  if ($folder) {
    $background_image_full = theme_get_setting('background_image_full');
    // BUG: Force file to be permanent.
    if (!empty($background_image_full)) {
      _fix_permanent_file('background_image_full', $settings_theme);
    }

    $form['stacks_fieldset']['background_image_full'] = array(
      '#title' => t('Background Image'),
      '#type' => 'managed_file',
      '#description' => t('The uploaded image will be displayed as the page background.'),
      '#default_value' => theme_get_setting('background_image_full'),
      '#upload_location' => 'public://background_image_full/',
      '#upload_validators' => array(
        'file_validate_extensions' => array('gif png jpg jpeg')
      )
    );
  }

  // background fadeout
	$form['stacks_fieldset']['background_fadeout'] = array (
		'#title' => t('Background Image Fade Effect?'),
		'#type' => 'checkboxes',
		'#options' => drupal_map_assoc(array(t('Yes'))),
		'#default_value' => theme_get_setting('background_fadeout'),
		'#description' => t('Enabling this option will add a fade effect over your choice of background.')
	);

  // custom css file
	if(user_access('administer custom css')) {
    $default_file_dir = 'public://custom_css';
    $folder = file_prepare_directory($default_file_dir, FILE_CREATE_DIRECTORY);
    $settings_theme = $form_state['build_info']['args'][0];

    if ($folder) {
      $hf_custom_css = theme_get_setting('hf_custom_css');
      // BUG: Force file to be permanent.
      if (!empty($hf_custom_css)) {
        _fix_permanent_file('hf_custom_css', $settings_theme);
      }

      // load up custom css file to build download link
      $hf_custom_css = file_load(theme_get_setting('hf_custom_css'));
      if (!empty($hf_custom_css)) {
        $hf_custom_css = $hf_custom_css->uri;
        $hf_custom_css = drupal_realpath($hf_custom_css);
        $hf_custom_css = str_replace($_SERVER['DOCUMENT_ROOT'].'/','',$hf_custom_css);
      }

      $form['stacks_fieldset']['hf_custom_css'] = array(
        '#title' => t('CSS file'),
        '#type' => 'managed_file',
        '#upload_validators' => array('file_validate_extensions' => array('css')),
        '#default_value' => theme_get_setting('hf_custom_css'),
        '#upload_location' => 'public://custom_css',
        '#description' => t('1. Download CSS template to customize. <br />2. Upload edited <a download href="'.$hf_custom_css.'">CSS Template</a>')
      );
    }
	}
}