; This file is currently used to document patches applied to modules but can be
; used to apply patches using drush make as well.

; Required
core = 7.x
api = 2

; Patches

; Geofield (geofield)

; Feeds Import Not Saving Geofield
; @see https://www.drupal.org/node/2534822
projects[geofield][patch][] = "https://www.drupal.org/files/issues/geofield-feeds_import_not_saving-2534822-46.patch"

; Media CKEditor (media_ckeditor)

; Media Browser Settings for "WYSIWYG" aren't respected with CKEditor Module (e.g. browser tabs)
; @see https://www.drupal.org/node/2333855
projects[media_ckeditor][patch][] = "https://www.drupal.org/files/issues/media_ckeditor-module-browser-tabs-2333855-13.patch"

; Redirect (redirect)

; Merge global redirect functions into Redirect module
; @see https://www.drupal.org/node/905914
projects[redirect][patch][] = "https://www.drupal.org/files/issues/redirect-n905914-227.patch"
