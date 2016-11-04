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

function caltech_form_system_theme_settings_alter(&$form, $form_state) {

	$form['stacks_fieldset'] = array(
		'#type' => 'fieldset',
		'#title' => 'Stacks General Configuration'
	);

	// Create the form widgets using Forms API
	$form['stacks_fieldset']['color_palette'] = array(
		'#title' => t('Select a theme'),
			'#type' => 'select',
			'#options' => array(
					'caltech' => 'Default',
			),
			'#default_value' => theme_get_setting('color_palette'),
			'#field_prefix' => '
				<div class="dropdown-a"></div>
				<div class="dropdown-b">
					<ul>
						<li class="caltech">
							<span class="prim"></span>
							<span class="secnd"></span>
							Default
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
	// $form['stacks_fieldset']['foundation_wide'] = array (
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
  			<div class="item" data-img="arch-books" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/arch-books.jpg");"></div>
  			<div class="item" data-img="bird-sparrow" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/bird-sparrow.jpg");"></div>
  			<div class="item" data-img="blur" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/blur.jpg");"></div>
  			<div class="item" data-img="dry-leaves" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/dry-leaves.jpg");"></div>
  			<div class="item" data-img="forest" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/forest.jpg");"></div>
  			<div class="item" data-img="landscape" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/landscape.jpg");"></div>
  			<div class="item" data-img="library" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/library.jpg");"></div>
  			<div class="item" data-img="night" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/night.jpg");"></div>
  			<div class="item" data-img="ocean-rock" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/ocean-rock.jpg");"></div>
  			<div class="item" data-img="old-books" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/old-books.jpg");"></div>
  			<div class="item" data-img="pinecone" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/pinecone.jpg");"></div>
  			<div class="item" data-img="seattle" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/seattle.jpg");"></div>
  			<div class="item" data-img="star-grass" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/star-grass.jpg");"></div>
  			<div class="item" data-img="suns" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/suns.jpg");"></div>
  			<div class="item" data-img="stars" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/stars.jpg");"></div>
  			<div class="item" data-img="tree-two" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/tree-two.jpg");"></div>
  			<div class="item" data-img="trees-one" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/trees-one.jpg");"></div>
  			<div class="item" data-img="wave" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/wave.jpg");"></div>
  			<div class="item" data-img="whiteside-mountain" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/whiteside-mountain.jpg");"></div>
  			<div class="item" data-img="wood-planks" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/wood-planks.jpg");"></div>
  			<div class="item" data-img="bridge" style="background-image: url(/'. drupal_get_path('theme', 'hfstacks') . '/assets/admin_module/gallery/img/bridge.jpg");"></div>
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
  if(module_exists('hf_locations')) {
    $form['stacks_fieldset']['hf_location_bar'] = array (
      '#title' => t('Location Bar with today\'s hours'),
      '#type' => 'checkboxes',
      '#options' => drupal_map_assoc(array(t('Enable'), t('Rotate'))),
      '#default_value' => theme_get_setting('hf_location_bar'),
      '#description' => t('Disabling rotation will show the latest location with "Sticky at top of lists" selected in publishing options.')
    );
  }
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

      // load up custom css file
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