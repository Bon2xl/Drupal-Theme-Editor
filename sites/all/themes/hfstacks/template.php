<?php

function hfstacks_preprocess_html(&$variables) {
  $basePath = $GLOBALS['base_path'];

  /**
  * Theme name
  */
  global $theme;
  $themeName = $theme;
  $variables['classes_array'][] = 'theme-'.$themeName.'';

  /**
  * Get background
  */
  $bgImgFull = theme_get_setting('background_image_full');
  $bgGallery = theme_get_setting('background_image_gallery');
  $bgGalleryClean = trim($bgGallery);

  if (isset($bgImgFull) && $bgImgFull >= 1) {
    // Original image
    $file = file_load(theme_get_setting('background_image_full'));
    $uri = $file->uri;
    $filename = $file->filename;

    // Resize for Mobile
    $image_style = image_style_path('mobile_background', $uri);
    $image_style_create = image_style_create_derivative($filename, $uri, $image_style);

    // Original Size
    drupal_add_css('.desktop .main-background { background-image:url('.file_create_url($uri).')!important; }', 'inline');
    drupal_add_css('.mobile .main-background { background-image:url('.file_create_url($image_style).')!important; }', 'inline');
    $variables['classes_array'][] = 'image-bg-enable';
    $variables['style'][] = drupal_add_css();

  } elseif(!empty($bgGalleryClean) && is_string($bgGalleryClean)) {
    // change background image
    $variables['classes_array'][] = 'image-bg-enable';
    drupal_add_css('.main-background { background-image:url('.$basePath.'sites/all/themes/hfstacks/assets/admin_module/gallery/img/'.$bgGalleryClean.'.jpg)!important; }', 'inline');
  }

  /**
  * Background Color
  */
  if(theme_get_setting('background_color') != NULL) {
    if ($themeName == 'hfstacks') {
      $printBody = 'body, ';
    }
    $color = '' .$printBody. '.main-background { background-color: #'.theme_get_setting('background_color').' !important; }';
    drupal_add_css($color, 'inline', array('every_page' => TRUE, 'preprocess' => TRUE));
    $variables['classes_array'][] = 'solid-bg-enable';
  }

  /**
  * Palette settings
  */
  $color = theme_get_setting('color_palette');
  $wide_foundation = theme_get_setting('foundation_wide');
  drupal_add_css( path_to_theme() . '/assets/css/palette_'.$color.'.css', array('weight' => 10, 'group' => CSS_THEME) );
  $variables['classes_array'][] = "palette_".$color;

  /**
  * Background Fade Effect
  */
  $bg_fadeout = theme_get_setting('background_fadeout');
  $bg_color = theme_get_setting('background_color');

  if(strlen($bg_fadeout['Yes']) === 3 && $bg_fadeout['Yes'] === 'Yes') {
    $variables['classes_array'][] = 'background_fadeout_enable';
    if(theme_get_setting('background_color') != NULL) {
      drupal_add_css('.background_fadeout_enable .main-gradient { background:linear-gradient(to bottom, rgba(255, 255, 255, 0) 30%, #'.$bg_color.' 70%)!important; }', 'inline');
    } else {
      drupal_add_css('.background_fadeout_enable .main-gradient { background:linear-gradient(to bottom, rgba(255, 255, 255, 0) 30%, #E8E8E8 70%)!important; }', 'inline');
    }
    $variables['style'][] = drupal_add_css();
  }

  /**
  * Custom CSS
  */
  $hf_custom_css = theme_get_setting('hf_custom_css');
  if (isset($hf_custom_css)) {
    if (file_exists(file_load($hf_custom_css))) {
      $file = file_load($hf_custom_css)->uri;
      $filePath = file_create_url($file);
      drupal_add_css($basePath."/".$filePath, array('weight' => 10, 'type' => 'external'));
    }
  }

  /**
  * Scripts
  */
  drupal_add_js('jQuery.extend(Drupal.settings, { "pathToTheme": "' . path_to_theme() . '" });', 'inline');
  $variables['scripts'][] = drupal_add_js();
}


function hfstacks_preprocess_page(&$vars) {
  global $base_url;

  $api_key = variable_get('hf_stacks_maps_api_key', '');
  if (!empty($api_key)) {
    drupal_add_js('//maps.googleapis.com/maps/api/js?key='.$api_key.'', 'external');
  }

  // load up custom css file
  $hf_custom_css = file_load(theme_get_setting('hf_custom_css'));
  if (!empty($hf_custom_css)) {
    $hf_custom_css = $hf_custom_css->uri;
    $hf_custom_css = drupal_realpath($hf_custom_css);
    $hf_custom_css = str_replace($_SERVER['DOCUMENT_ROOT'].'/','',$hf_custom_css);
    drupal_add_css($base_url.'/'.$hf_custom_css, array('type' => 'external'));
  }
}

// Overwrite Status Message
function hfstacks_status_messages($variables) {
  $display = $variables ['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    $output .= "<div class=\"l-messages row\">\n";
    $output .= "<div class=\"large-12 columns\">\n";
    $output .= "<div class=\"messages $type\">\n";
    if (!empty($status_heading [$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading [$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= reset($messages);
    }
    $output .= "</div>\n";
    $output .= "</div>\n";
    $output .= "</div>\n";
  }
  return $output;
}

// Breadcrumbs
function hfstacks_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $crumbs = '';

  if (!empty($breadcrumb)) {
    $crumbs = '<div class="large-12 columns">';
    $crumbs .= '<div class="breadcrumb">';
    $crumbs .= '<ul>';

    foreach($breadcrumb as $value) {
     $crumbs .= '<li>'.$value.'</li>';
    }

    $crumbs .= '</ul>';
    $crumbs .= '</div>';
    $crumbs .= '</div>';
  }
  return $crumbs;
}

// Internal Search Results
function hfstacks_preprocess_search_result(&$vars) {
  // remove user & date from search results
  $vars['info'] = "";
}
