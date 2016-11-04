<?php
/**
 * Implements hook_drush_help().
 */
function stacks_updater_drush_help($command) {
  switch ($command) {
    case 'drush:stac-1569':
      return dt('Run commands for STAC-1569');
    case 'drush:caltech-0001':
      return dt('Run commands for CALTECH-0001');
    case 'drush:stac-1501':
      return dt('Run commands for STAC-1501');
    case 'drush:stac-1446':
      return dt('Run commands for STAC-1446');
    case 'drush:stac-1293':
      return dt('Run commands for STAC-1293');
    case 'drush:stac-1292':
      return dt('Run commands for STAC-1292');
    case 'drush:stac-1258':
      return dt('Run commands for STAC-1258');
    case 'drush:stac-1113':
      return dt('Run commands for STAC-1113');
    case 'drush:stac-1058':
      return dt('Run commands for STAC-1058');
  }
}

/**

 * Implements hook_drush_command().
 */
function stacks_updater_drush_command() {
  $items = array();

  $items['stac-1569'] = array(
    'description' => 'Create the permissions for Room Booking module',
    'aliases' => array('stac1569'),
  );
  $items['caltech-0001'] = array(
    'description' => 'Add External URL field to Event content type.',
    'aliases' => array('caltech0001'),
  );
  $items['stac-1501'] = array(
    'description' => 'Modify existing admin dashboard',
    'aliases' => array('stac1501'),
  );
  $items['stac-1446'] = array(
    'description' => 'Alter all phone fields to allow input of country code',
    'aliases' => array('stac1446'),
  );
  $items['stac-1293'] = array(
    'description' => 'Adding in a Room Booking item into the main menu',
    'aliases' => array('stac1293'),
  );
  $items['stac-1292'] = array(
    'description' => 'Adding in the Room Booking tiles into the dashboard',
    'aliases' => array('stac1292'),
  );
  $items['stac-1258'] = array(
    'description' => 'Add new fields to directory listing content type',
    'aliases' => array('stac1258'),
  );
  $items['stac-1113'] = array(
    'description' => 'Update webform to include captcha',
    'aliases' => array('stac1113'),
  );
  $items['stac-1058'] = array(
    'description' => 'Add new tile to dashboard',
    'aliases' => array('stac1058'),
  );

  return $items;
}