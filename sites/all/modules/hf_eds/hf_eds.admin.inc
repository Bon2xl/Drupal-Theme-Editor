<?php


function _hf_eds_form($form, &$form_state) {
  global $user;
  if (module_exists('domain_conf')) {
    $domain = domain_get_domain();
  }

  $stacks_search_internal_checkbox = variable_get('stacks_search_internal_checkbox', '');
  $stacks_search_eds_checkbox = variable_get('stacks_search_eds_checkbox', '');
  $stacks_search_external_checkbox = variable_get('stacks_search_external_checkbox', '');
  $stacks_search_external_checkbox_2 = variable_get('stacks_search_external_checkbox_2', '');
  $stacks_search_external_checkbox_3 = variable_get('stacks_search_external_checkbox_3', '');
  $stacks_search_bento_checkbox = variable_get('stacks_search_bento_checkbox', '');

  $form['stacks_search'] = array(
    '#type' => 'fieldset',
    '#title' => 'Search Platform & Form Settings',

    /**
     * search options
     */
    // internal search checkbox
    'search_internal_checkbox' => array(
      '#title' => 'Internal Search',
      '#type' => 'checkbox',
      '#default_value' => $stacks_search_internal_checkbox,
      '#prefix' => '<br /><h2>Search Form Options</h2><div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // internal search title
    'search_internal_textbox' => array(
      '#title' => '',
      '#type' => 'textfield',
      '#attributes' => array(
        'placeholder' => t('Title'),
      ),
      '#size' => 10,
      '#default_value' => variable_get('stacks_search_internal_title', ''),
      '#prefix' => '<div style="float:left;">',
      '#suffix' => '</div>',
    ),

    // EDS search checkbox
    'search_eds_checkbox' => array(
      '#title' => 'Ebsco EDS Search',
      '#type' => 'checkbox',
      '#default_value' => $stacks_search_eds_checkbox,
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // EDS search title
    'search_eds_textbox' => array(
      '#title' => '',
      '#type' => 'textfield',
      '#attributes' => array(
        'placeholder' => t('Title'),
      ),
      '#size' => 10,
      '#default_value' => variable_get('stacks_search_eds_title', ''),
      '#prefix' => '<div style="float:left;">',
      '#suffix' => '</div>',
    ),

    // external search checkbox 1
    'search_external_checkbox' => array(
      '#title' => 'External Search 1',
      '#type' => 'checkbox',
      '#default_value' => $stacks_search_external_checkbox,
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // external search title 1
    'search_external_textbox' => array(
      '#title' => '',
      '#type' => 'textfield',
      '#attributes' => array(
        'placeholder' => t('Title'),
      ),
      '#size' => 10,
      '#default_value' => variable_get('stacks_search_external_title', ''),
      '#prefix' => '<div style="float:left;">',
      '#suffix' => '</div>',
    ),
    // external search dropdown 1
    'search_external_select' => array(
      '#title' => '',
      '#type' => 'select',
      '#options' => array(
        '' => '- None -',
        'edsnative' => 'EDS Native 1',
        'edsnative2' => 'EDS Native 2',
        'edsnative3' => 'EDS Native 3',
        'iii' => 'III',
        'polaris' => 'Polaris',
        'sirsi' => 'Sirsi',
        'evergreen' => 'Evergreen',
        'oclc' => 'OCLC',
        'koha' => 'Koha',
        'exlibris' => 'ExLibris',
        'bibliocommons' => 'Bibliocommons',
        'vufind' => 'VuFind'
      ),
      '#default_value' => variable_get('stacks_search_external', ''),
      '#prefix' => '<div style="float:left; width:200px;">',
      '#suffix' => '</div>',
    ),

    // external search checkbox 2
    'search_external_checkbox_2' => array(
      '#title' => 'External Search 2',
      '#type' => 'checkbox',
      '#default_value' => $stacks_search_external_checkbox_2,
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // external search title 2
    'search_external_textbox_2' => array(
      '#title' => '',
      '#type' => 'textfield',
      '#attributes' => array(
        'placeholder' => t('Title'),
      ),
      '#size' => 10,
      '#default_value' => variable_get('stacks_search_external_title_2', ''),
      '#prefix' => '<div style="float:left;">',
      '#suffix' => '</div>',
    ),
    // external search dropdown 2
    'search_external_select_2' => array(
      '#title' => '',
      '#type' => 'select',
      '#options' => array(
        '' => '- None -',
        'edsnative' => 'EDS Native 1',
        'edsnative2' => 'EDS Native 2',
        'edsnative3' => 'EDS Native 3',
        'iii' => 'III',
        'polaris' => 'Polaris',
        'sirsi' => 'Sirsi',
        'evergreen' => 'Evergreen',
        'oclc' => 'OCLC',
        'koha' => 'Koha',
        'exlibris' => 'ExLibris',
        'bibliocommons' => 'Bibliocommons',
        'vufind' => 'VuFind'
      ),
      '#default_value' => variable_get('stacks_search_external_2', ''),
      '#prefix' => '<div style="float:left; width:200px;">',
      '#suffix' => '</div>',
    ),

    // external search checkbox 3
    'search_external_checkbox_3' => array(
      '#title' => 'External Search 3',
      '#type' => 'checkbox',
      '#default_value' => $stacks_search_external_checkbox_3,
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // external search title 3
    'search_external_textbox_3' => array(
      '#title' => '',
      '#type' => 'textfield',
      '#attributes' => array(
        'placeholder' => t('Title'),
      ),
      '#size' => 10,
      '#default_value' => variable_get('stacks_search_external_title_3', ''),
      '#prefix' => '<div style="float:left;">',
      '#suffix' => '</div>',
    ),
    // external search dropdown 3
    'search_external_select_3' => array(
      '#title' => '',
      '#type' => 'select',
      '#options' => array(
        '' => '- None -',
        'edsnative' => 'EDS Native 1',
        'edsnative2' => 'EDS Native 2',
        'edsnative3' => 'EDS Native 3',
        'iii' => 'III',
        'polaris' => 'Polaris',
        'sirsi' => 'Sirsi',
        'evergreen' => 'Evergreen',
        'oclc' => 'OCLC',
        'koha' => 'Koha',
        'exlibris' => 'ExLibris',
        'bibliocommons' => 'Bibliocommons',
        'vufind' => 'VuFind'
      ),
      '#default_value' => variable_get('stacks_search_external_3', ''),
      '#prefix' => '<div style="float:left; width:200px;">',
      '#suffix' => '</div>',
    ),

    // EDS  Bento checkbox
    'search_bento_checkbox' => array(
      '#title' => 'Bento Search',
      '#type' => 'checkbox',
      '#default_value' => $stacks_search_bento_checkbox,
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // Bento search title
    'search_bento_title' => array(
      '#title' => '',
      '#type' => 'textfield',
      '#attributes' => array(
        'placeholder' => t('Title'),
      ),
      '#size' => 10,
      '#default_value' => variable_get('stacks_search_bento_title', ''),
      '#prefix' => '<div style="float:left;">',
      '#suffix' => '</div>',
    ),
    // default search
    'system' => array(
      '#title' => 'Default Search on Form',
      '#type' => 'select',
      '#options' => array(
        'internal' => 'Internal',
        'eds' => 'Ebsco EDS',
        'external' => 'External 1',
        'external_2' => 'External 2',
        'external_3' => 'External 3',
        'bento' => 'Bento'
      ),
      '#default_value' => variable_get('stacks_search', ''),
      '#prefix' => '<div style="clear:both;">',
      '#suffix' => '</div>',
    ),
  );

  $form['config-tabs'] = array(
    '#title' => 'Configuration',
    '#type' => 'vertical_tabs',
    '#default_tab' => 'edit-'.variable_get('stacks_search', '')
  );

  $form['eds'] = array(
    '#type' => 'fieldset',
    '#title' => 'Ebsco EDS',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for Ebsco EDS based search',
    '#group' => 'config-tabs',

    // options
    'stacks_eds_server' => array(
      '#type' => 'textfield',
      '#title' => t('Server Address'),
      '#size' => 60,
      '#default_value' => variable_get('stacks_eds_server'),
      '#description' => t('Endpoint URL'),
    ),
    'stacks_eds_user' => array(
      '#type' => 'textfield',
      '#title' => t('Username'),
      '#size' => 60,
      '#default_value' => variable_get('stacks_eds_user'),
      //'#description' => t('URL which the catalogue goes to.'),
    ),
    'stacks_eds_pass' => array(
      '#type' => 'textfield',
      '#title' => t('Password'),
      '#size' => 60,
      '#default_value' => variable_get('stacks_eds_pass'),
      //'#description' => t('URL which the catalogue goes to.'),
    ),
    'stacks_eds_profile' => array(
      '#type' => 'textfield',
      '#title' => t('Profile'),
      '#size' => 60,
      '#default_value' => variable_get('stacks_eds_profile'),
      //'#description' => t('URL which the catalogue goes to.'),
    ),
    /*
    'stacks_eds_org' => array(
      '#type' => 'textfield',
      '#title' => t('Organization'),
      '#size' => 60,
      '#default_value' => variable_get('stacks_eds_org'),
      //'#description' => t('URL which the Advanced Search goes to.'),
    ),
    */
    // ILL Docuserve Request
    'stacks_search_eds_docuserve_checkbox' => array(
      '#title' => 'ILL Docuserve Request',
      '#type' => 'checkbox',
      '#default_value' => variable_get('stacks_search_eds_docuserve_checkbox', ''),
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // ILL Docuserve Request URL
    'stacks_search_eds_docuserve_url' => array(
      '#title' => '',
      '#type' => 'textfield',
      '#attributes' => array(
        'placeholder' => t('URL'),
      ),
      '#size' => 40,
      '#default_value' => variable_get('stacks_search_eds_docuserve_url', ''),
      '#prefix' => '<div style="float:left;">',
      '#suffix' => '</div>',
    ),
    // ILL Rush Request
    'stacks_search_eds_rush_checkbox' => array(
      '#title' => 'ILL Rush Request',
      '#type' => 'checkbox',
      '#default_value' => variable_get('stacks_search_eds_rush_checkbox', ''),
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // ILL Rush Request URL
    'stacks_search_eds_rush_url' => array(
      '#title' => '',
      '#type' => 'textfield',
      '#attributes' => array(
        'placeholder' => t('URL'),
      ),
      '#size' => 40,
      '#default_value' => variable_get('stacks_search_eds_rush_url', ''),
      '#prefix' => '<div style="float:left;">',
      '#suffix' => '</div>',
    ),
    // Search Limiters: FullText
    'stacks_search_eds_limiter_ft' => array(
      '#title' => 'Full Text',
      '#type' => 'checkbox',
      '#default_value' => variable_get('stacks_search_eds_limiter_ft', ''),
      '#prefix' => '<div style="clear:both;"><h3><strong>Limiters</strong></h3></div><div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // Search Limiters: References Available
    'stacks_search_eds_limiter_fr' => array(
      '#title' => 'References Available',
      '#type' => 'checkbox',
      '#default_value' => variable_get('stacks_search_eds_limiter_fr', ''),
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // Search Limiters: Peer Reviewed
    'stacks_search_eds_limiter_rv' => array(
      '#title' => 'Peer Reviewed',
      '#type' => 'checkbox',
      '#default_value' => variable_get('stacks_search_eds_limiter_rv', ''),
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // Search Limiters: Library Collection
    'stacks_search_eds_limiter_ft1' => array(
      '#title' => 'Library Collection',
      '#type' => 'checkbox',
      '#default_value' => variable_get('stacks_search_eds_limiter_ft1', ''),
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // Search Limiters: Catalog Only
    'stacks_search_eds_limiter_fc' => array(
      '#title' => 'Catalog Only',
      '#type' => 'checkbox',
      '#default_value' => variable_get('stacks_search_eds_limiter_fc', ''),
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),

    // Search Expanders: Thesaurus
    'stacks_search_eds_expander_thesaurus' => array(
      '#title' => 'Thesaurus',
      '#type' => 'checkbox',
      '#default_value' => variable_get('stacks_search_eds_expander_thesaurus', ''),
      '#prefix' => '<div style="clear:both;"><h3><strong>Expanders</strong></h3></div><div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // Search Expanders: Full Text
    'stacks_search_eds_expander_fulltext' => array(
      '#title' => 'Full Text',
      '#type' => 'checkbox',
      '#default_value' => variable_get('stacks_search_eds_expander_fulltext', ''),
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
    // Search Expanders: Enhanced Subject Precision
    'stacks_search_eds_expander_precision' => array(
      '#title' => 'Enhanced Subject Precision',
      '#type' => 'checkbox',
      '#default_value' => variable_get('stacks_search_eds_expander_precision', ''),
      '#prefix' => '<div style="float:left; width:200px; clear:both;">',
      '#suffix' => '</div>',
    ),
  );

  /*
  if (!empty(variable_get('hf_similartitles_novelist_password', ''))) {
    $form['eds']['stacks_eds_pass']['#attributes'] = array('placeholder' => '····················');
  }
  if (!empty(variable_get('hf_similartitles_novelist_password', ''))) {
    $form['eds']['stacks_eds_profile']['#attributes'] = array('placeholder' => '····················');
  }
  if (!empty(variable_get('stacks_eds_org', ''))) {
    $form['eds']['stacks_eds_org']['#attributes'] = array('placeholder' => '····················');
  }
  */

  $form['polaris'] = array(
    '#type' => 'fieldset',
    '#title' => 'Polaris',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for Polaris based search',
    '#group' => 'config-tabs',

    // options
    'stacks_search_polaris_catalogue_url' => array(
      '#title' => "Catalogue Search Base URL",
      '#type' => 'textfield',
      '#default_value' => variable_get('stacks_search_polaris_catalogue_url', '')
    ),
    'stacks_search_polaris_opac_url' => array(
      '#title' => "OPAC URL",
      '#type' => 'textfield',
      '#default_value' => variable_get('stacks_search_polaris_opac_url', '')
    )
  );

  $form['sirsi'] = array(
    '#type' => 'fieldset',
    '#title' => 'Sirsi',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for Sirsi based search',
    '#group' => 'config-tabs',

    // options
    'stacks_search_sirsi_catalogue_url' => array(
      '#title' => "Catalogue Search Base URL",
      '#type' => 'textfield',
      '#default_value' => variable_get('stacks_search_sirsi_catalogue_url', '')
    ),
    'stacks_search_sirsi_opac_url' => array(
      '#title' => "OPAC URL",
      '#type' => 'textfield',
      '#default_value' => variable_get('stacks_search_sirsi_opac_url', '')
    )
  );

  $form['edsnative'] = array(
    '#type' => 'fieldset',
    '#title' => 'EDS Native 1',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for EDS Native based search',
    '#group' => 'config-tabs',

    'stacks_eds_server_general' => array(
      '#type' => 'fieldset',
      '#title' => t('General'),

      // options
      'stacks_search_edsnative_guest' => array(
        '#type' => 'checkbox',
        '#title' => 'Enable Guest',
        '#default_value' => variable_get('stacks_search_edsnative_guest'),
      ),
      'stacks_search_edsnative_sso' => array(
        '#type' => 'checkbox',
        '#title' => 'Enable SSO',
        '#default_value' => variable_get('stacks_search_edsnative_sso'),
      ),
      'stacks_search_edsnative_uid' => array(
        '#type' => 'checkbox',
        '#title' => 'Force UID',
        '#default_value' => variable_get('stacks_search_edsnative_uid'),
      ),
      'stacks_search_edsnative_athens' => array(
        '#type' => 'checkbox',
        '#title' => 'Force Open Athens',
        '#default_value' => variable_get('stacks_search_edsnative_athens'),
      ),
      'stacks_search_edsnative_direct' => array(
        '#type' => 'radios',
        '#title' => 'Direct',
        '#options' => array(
          'true' => 'True',
          'false' => 'False',
        ),
        '#default_value' => variable_get('stacks_search_edsnative_direct'),
      ),
      'stacks_search_edsnative_catalogue_url' => array(
        '#title' => "Base URL",
        '#type' => 'textfield',
        '#default_value' => variable_get('stacks_search_edsnative_catalogue_url', '')
      ),
      'stacks_search_edsnative_profile' => array(
        '#type' => 'textfield',
        '#title' => t('Profile'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_profile'),
      )
    ),

    'stacks_eds_server_ipguest' => array(
      '#type' => 'fieldset',
      '#title' => t('IP, Guest'),

      'stacks_search_edsnative_site' => array(
        '#type' => 'textfield',
        '#title' => t('Site'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_site'),
      ),
      'stacks_search_edsnative_custid' => array(
        '#type' => 'textfield',
        '#title' => t('CustID'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_custid'),
      ),
      'stacks_search_edsnative_groupid' => array(
        '#type' => 'textfield',
        '#title' => t('GroupID'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_groupid'),
      )
    ),

    'stacks_eds_server_uid' => array(
      '#type' => 'fieldset',
      '#title' => t('IP, UID'),

      'stacks_search_edsnative_user' => array(
        '#type' => 'textfield',
        '#title' => t('Username'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_user'),
      ),
      'stacks_search_edsnative_pass' => array(
        '#type' => 'textfield',
        '#title' => t('Password'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_pass'),
      ),
      'stacks_search_edsnative_org' => array(
        '#type' => 'textfield',
        '#title' => t('Group'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_org'),
      ),
      'stacks_search_edsnative_scope' => array(
        '#type' => 'textfield',
        '#title' => t('Scope'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_scope'),
      )
    ),
  );

  $form['edsnative2'] = array(
    '#type' => 'fieldset',
    '#title' => 'EDS Native 2',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for EDS Native based search',
    '#group' => 'config-tabs',

    'stacks_eds_server_general2' => array(
      '#type' => 'fieldset',
      '#title' => t('General'),

      // options
      'stacks_search_edsnative_guest2' => array(
        '#type' => 'checkbox',
        '#title' => 'Enable Guest',
        '#default_value' => variable_get('stacks_search_edsnative_guest2'),
      ),
      'stacks_search_edsnative_sso2' => array(
        '#type' => 'checkbox',
        '#title' => 'Enable SSO',
        '#default_value' => variable_get('stacks_search_edsnative_sso2'),
      ),
      'stacks_search_edsnative_uid2' => array(
        '#type' => 'checkbox',
        '#title' => 'Force UID',
        '#default_value' => variable_get('stacks_search_edsnative_uid2'),
      ),
      'stacks_search_edsnative_athens2' => array(
        '#type' => 'checkbox',
        '#title' => 'Force Open Athens',
        '#default_value' => variable_get('stacks_search_edsnative_athens2'),
      ),
      'stacks_search_edsnative_direct2' => array(
        '#type' => 'radios',
        '#title' => 'Direct',
        '#options' => array(
          'true' => 'True',
          'false' => 'False',
        ),
        '#default_value' => variable_get('stacks_search_edsnative_direct2'),
      ),
      'stacks_search_edsnative_catalogue_url2' => array(
        '#title' => "Base URL",
        '#type' => 'textfield',
        '#default_value' => variable_get('stacks_search_edsnative_catalogue_url2', '')
      ),
      'stacks_search_edsnative_profile2' => array(
        '#type' => 'textfield',
        '#title' => t('Profile'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_profile2'),
      )
    ),

    'stacks_eds_server_ipguest2' => array(
      '#type' => 'fieldset',
      '#title' => t('IP, Guest'),

      'stacks_search_edsnative_site2' => array(
        '#type' => 'textfield',
        '#title' => t('Site'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_site2'),
      ),
      'stacks_search_edsnative_custid2' => array(
        '#type' => 'textfield',
        '#title' => t('CustID'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_custid2'),
      ),
      'stacks_search_edsnative_groupid2' => array(
        '#type' => 'textfield',
        '#title' => t('GroupID'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_groupid2'),
      )
    ),

    'stacks_eds_server_uid2' => array(
      '#type' => 'fieldset',
      '#title' => t('IP, UID'),

      'stacks_search_edsnative_user2' => array(
        '#type' => 'textfield',
        '#title' => t('Username'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_user2'),
      ),
      'stacks_search_edsnative_pass2' => array(
        '#type' => 'textfield',
        '#title' => t('Password'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_pass2'),
      ),
      'stacks_search_edsnative_org2' => array(
        '#type' => 'textfield',
        '#title' => t('Group'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_org2'),
      ),
      'stacks_search_edsnative_scope2' => array(
        '#type' => 'textfield',
        '#title' => t('Scope'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_scope2'),
      )
    ),
  );

  $form['edsnative3'] = array(
    '#type' => 'fieldset',
    '#title' => 'EDS Native 3',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for EDS Native based search',
    '#group' => 'config-tabs',

    'stacks_eds_server_general3' => array(
      '#type' => 'fieldset',
      '#title' => t('General'),

      // options
      'stacks_search_edsnative_guest3' => array(
        '#type' => 'checkbox',
        '#title' => 'Enable Guest',
        '#default_value' => variable_get('stacks_search_edsnative_guest3'),
      ),
      'stacks_search_edsnative_sso3' => array(
        '#type' => 'checkbox',
        '#title' => 'Enable SSO',
        '#default_value' => variable_get('stacks_search_edsnative_sso3'),
      ),
      'stacks_search_edsnative_uid3' => array(
        '#type' => 'checkbox',
        '#title' => 'Force UID',
        '#default_value' => variable_get('stacks_search_edsnative_uid3'),
      ),
      'stacks_search_edsnative_athens3' => array(
        '#type' => 'checkbox',
        '#title' => 'Force Open Athens',
        '#default_value' => variable_get('stacks_search_edsnative_athens3'),
      ),
      'stacks_search_edsnative_direct3' => array(
        '#type' => 'radios',
        '#title' => 'Direct',
        '#options' => array(
          'true' => 'True',
          'false' => 'False',
        ),
        '#default_value' => variable_get('stacks_search_edsnative_direct3'),
      ),
      'stacks_search_edsnative_catalogue_url3' => array(
        '#title' => "Base URL",
        '#type' => 'textfield',
        '#default_value' => variable_get('stacks_search_edsnative_catalogue_url3', '')
      ),
      'stacks_search_edsnative_profile3' => array(
        '#type' => 'textfield',
        '#title' => t('Profile'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_profile3'),
      )
    ),

    'stacks_eds_server_ipguest3' => array(
      '#type' => 'fieldset',
      '#title' => t('IP, Guest'),

      'stacks_search_edsnative_site3' => array(
        '#type' => 'textfield',
        '#title' => t('Site'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_site3'),
      ),
      'stacks_search_edsnative_custid3' => array(
        '#type' => 'textfield',
        '#title' => t('CustID'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_custid3'),
      ),
      'stacks_search_edsnative_groupid3' => array(
        '#type' => 'textfield',
        '#title' => t('GroupID'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_groupid3'),
      )
    ),

    'stacks_eds_server_uid3' => array(
      '#type' => 'fieldset',
      '#title' => t('IP, UID'),

      'stacks_search_edsnative_user3' => array(
        '#type' => 'textfield',
        '#title' => t('Username'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_user3'),
      ),
      'stacks_search_edsnative_pass3' => array(
        '#type' => 'textfield',
        '#title' => t('Password'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_pass3'),
      ),
      'stacks_search_edsnative_org3' => array(
        '#type' => 'textfield',
        '#title' => t('Group'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_org3'),
      ),
      'stacks_search_edsnative_scope3' => array(
        '#type' => 'textfield',
        '#title' => t('Scope'),
        '#size' => 60,
        '#default_value' => variable_get('stacks_search_edsnative_scope3'),
      )
    ),
  );

  $form['iii'] = array(
    '#type' => 'fieldset',
    '#title' => 'III',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for III based search',
    '#group' => 'config-tabs',

    // options
    'stacks_search_iii_catalogue_url' => array(
      '#title' => "Catalogue Search Base URL",
      '#type' => 'textfield',
      '#default_value' => variable_get('stacks_search_iii_catalogue_url', '')
    )
  );

  $form['evergreen'] = array(
    '#type' => 'fieldset',
    '#title' => 'Evergreen',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for Evergreen based search',
    '#group' => 'config-tabs',

    // options
    'stacks_search_evergreen_catalogue_url' => array(
      '#title' => "Catalogue Search Base URL",
      '#type' => 'textfield',
      '#default_value' => variable_get('stacks_search_evergreen_catalogue_url', '')
    )
  );

  $form['oclc'] = array(
    '#type' => 'fieldset',
    '#title' => 'OCLC',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for OCLC based search',
    '#group' => 'config-tabs',

    // options
    'stacks_search_oclc_catalogue_url' => array(
      '#title' => "Catalogue Search Base URL",
      '#type' => 'textfield',
      '#default_value' => variable_get('stacks_search_oclc_catalogue_url', '')
    )
  );

  $form['koha'] = array(
    '#type' => 'fieldset',
    '#title' => 'Koha',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for Koha based search',
    '#group' => 'config-tabs',

    // options
    'stacks_search_koha_catalogue_url' => array(
      '#title' => "Catalogue Search Base URL",
      '#type' => 'textfield',
      '#default_value' => variable_get('stacks_search_koha_catalogue_url', '')
    )
  );


  $form['exlibris'] = array(
    '#type' => 'fieldset',
    '#title' => 'ExLibris',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for ExLibris based search',
    '#group' => 'config-tabs',

    // options
    'stacks_search_exlibris_catalogue_url' => array(
      '#title' => "Catalogue Search Base URL",
      '#type' => 'textfield',
      '#default_value' => variable_get('stacks_search_exlibris_catalogue_url', '')
    )
  );

  $form['bibliocommons'] = array(
    '#type' => 'fieldset',
    '#title' => 'Bibliocommons',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for Bibliocommons based search',
    '#group' => 'config-tabs',

    // options
    'stacks_search_bibliocommons_catalogue_url' => array(
      '#title' => "Catalogue Search Base URL",
      '#type' => 'textfield',
      '#default_value' => variable_get('stacks_search_bibliocommons_catalogue_url', '')
    )
  );

  $form['vufind'] = array(
    '#type' => 'fieldset',
    '#title' => 'VuFind',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Details for VuFind based search',
    '#group' => 'config-tabs',

    // options
    'stacks_search_vufind_catalogue_url' => array(
      '#title' => "Catalogue Search Base URL",
      '#type' => 'textfield',
      '#default_value' => variable_get('stacks_search_vufind_catalogue_url', '')
    )
  );

  if($user->uid == 1) {
    $form['bento'] = array(
      '#type' => 'fieldset',
      '#title' => 'Bento',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => 'Configuration for Bento Search',
      '#group' => 'config-tabs',


      // options
      'stacks_search_bento_format' => array(
        '#title' => 'XML or Json',
        '#type' => 'select',
        '#options' => array(
          'json' => 'JSON',
          'xml' => 'XML',
        ),
        '#default_value' => variable_get('stacks_search_bento_format', 'json')
      ),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save Configuration'
  );

  return ($form);
}

// saving the variable for multidomains
function _hf_eds_form_submit($form, &$form_state) {

  if (module_exists('domain_conf')) {
    $domain = domain_get_domain();

    domain_conf_variable_set($domain['domain_id'], 'stacks_search',  $form_state['values']['system']);
    if ($form_state['values']['system'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search');
    }

    domain_conf_variable_set($domain['domain_id'], 'stacks_search_internal_checkbox',  $form_state['values']['search_internal_checkbox']);
    if ($form_state['values']['search_internal_checkbox'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_internal_checkbox');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_internal_title',  $form_state['values']['search_internal_textbox']);
    if ($form_state['values']['search_internal_textbox'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_internal_title');
    }

    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_checkbox',  $form_state['values']['search_eds_checkbox']);
    if ($form_state['values']['search_eds_checkbox'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_checkbox');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_title',  $form_state['values']['search_eds_textbox']);
    if ($form_state['values']['search_eds_textbox'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_title');
    }

    domain_conf_variable_set($domain['domain_id'], 'stacks_search_external_checkbox',  $form_state['values']['search_external_checkbox']);
    if ($form_state['values']['search_external_checkbox'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_external_checkbox');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_external_title',  $form_state['values']['search_external_textbox']);
    if ($form_state['values']['search_external_textbox'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_external_title');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_external',  $form_state['values']['search_external_select']);
    if ($form_state['values']['search_external_select'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_external');
    }

    domain_conf_variable_set($domain['domain_id'], 'stacks_search_external_checkbox_2',  $form_state['values']['search_external_checkbox_2']);
    if ($form_state['values']['search_external_checkbox_2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_external_checkbox_2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_external_title_2',  $form_state['values']['search_external_textbox_2']);
    if ($form_state['values']['search_external_textbox_2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_external_title_2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_external_2',  $form_state['values']['search_external_select_2']);
    if ($form_state['values']['search_external_select_2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_external_2');
    }

    domain_conf_variable_set($domain['domain_id'], 'stacks_search_external_checkbox_3',  $form_state['values']['search_external_checkbox_3']);
    if ($form_state['values']['search_external_checkbox_3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_external_checkbox_3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_external_title_3',  $form_state['values']['search_external_textbox_3']);
    if ($form_state['values']['search_external_textbox_3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_external_title_3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_external_3',  $form_state['values']['search_external_select_3']);
    if ($form_state['values']['search_external_select_3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_external_3');
    }

    // Bento
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_bento_checkbox',  $form_state['values']['search_bento_checkbox']);
    if ($form_state['values']['search_bento_checkbox'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_bento_checkbox');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_bento_title',  $form_state['values']['search_bento_title']);
    if ($form_state['values']['search_bento_title'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_bento_title');
    }

    // EDS API
    domain_conf_variable_set($domain['domain_id'], 'stacks_eds_server', $form_state['values']['stacks_eds_server']);
    if ($form_state['values']['stacks_eds_server'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_eds_server');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_eds_user', $form_state['values']['stacks_eds_user']);
    if ($form_state['values']['stacks_eds_user'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_eds_user');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_eds_pass', $form_state['values']['stacks_eds_pass']);
    if ($form_state['values']['stacks_eds_pass'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_eds_pass');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_eds_profile', $form_state['values']['stacks_eds_profile']);
    if ($form_state['values']['stacks_eds_profile'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_eds_profile');
    }
    /*
    domain_conf_variable_set($domain['domain_id'], 'stacks_eds_org', $form_state['values']['stacks_eds_org']);
    if ($form_state['values']['stacks_eds_org'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_eds_org');
    }
    */
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_docuserve_checkbox', $form_state['values']['stacks_search_eds_docuserve_checkbox']);
    if ($form_state['values']['stacks_search_eds_docuserve_checkbox'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_docuserve_checkbox');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_docuserve_url', $form_state['values']['stacks_search_eds_docuserve_url']);
    if ($form_state['values']['stacks_search_eds_docuserve_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_docuserve_url');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_rush_checkbox', $form_state['values']['stacks_search_eds_rush_checkbox']);
    if ($form_state['values']['stacks_search_eds_rush_checkbox'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_rush_checkbox');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_rush_url', $form_state['values']['stacks_search_eds_rush_url']);
    if ($form_state['values']['stacks_search_eds_rush_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_rush_url');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_limiter_ft', $form_state['values']['stacks_search_eds_limiter_ft']);
    if ($form_state['values']['stacks_search_eds_limiter_ft'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_limiter_ft');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_limiter_fr', $form_state['values']['stacks_search_eds_limiter_fr']);
    if ($form_state['values']['stacks_search_eds_limiter_fr'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_limiter_fr');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_limiter_rv', $form_state['values']['stacks_search_eds_limiter_rv']);
    if ($form_state['values']['stacks_search_eds_limiter_rv'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_limiter_rv');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_limiter_ft1', $form_state['values']['stacks_search_eds_limiter_ft1']);
    if ($form_state['values']['stacks_search_eds_limiter_ft1'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_limiter_ft1');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_limiter_fc', $form_state['values']['stacks_search_eds_limiter_fc']);
    if ($form_state['values']['stacks_search_eds_limiter_fc'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_limiter_fc');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_expander_thesaurus', $form_state['values']['stacks_search_eds_expander_thesaurus']);
    if ($form_state['values']['stacks_search_eds_expander_thesaurus'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_expander_thesaurus');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_expander_fulltext', $form_state['values']['stacks_search_eds_expander_fulltext']);
    if ($form_state['values']['stacks_search_eds_expander_fulltext'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_expander_fulltext');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_eds_expander_precision', $form_state['values']['stacks_search_eds_expander_precision']);
    if ($form_state['values']['stacks_search_eds_expander_precision'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_eds_expander_precision');
    }

    // Polaris
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_polaris_catalogue_url', $form_state['values']['stacks_search_polaris_catalogue_url']);
    if ($form_state['values']['stacks_search_polaris_catalogue_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_polaris_catalogue_url');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_polaris_advanced_url', $form_state['values']['stacks_search_polaris_advanced_url']);
    if ($form_state['values']['stacks_search_polaris_advanced_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_polaris_advanced_url');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_polaris_ctx', $form_state['values']['stacks_search_polaris_ctx']);
    if ($form_state['values']['stacks_search_polaris_ctx'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_polaris_ctx');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_polaris_page', $form_state['values']['stacks_search_polaris_page']);
    if ($form_state['values']['stacks_search_polaris_page'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_polaris_page');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_polaris_tom', $form_state['values']['stacks_search_polaris_tom']);
    if ($form_state['values']['stacks_search_polaris_tom'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_polaris_tom');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_polaris_opac_url', $form_state['values']['stacks_search_polaris_opac_url']);
    if ($form_state['values']['stacks_search_polaris_opac_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_polaris_opac_url');
    }

    // EDS Native 1
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_guest', $form_state['values']['stacks_search_edsnative_guest']);
    if ($form_state['values']['stacks_search_edsnative_guest'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_guest');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_uid', $form_state['values']['stacks_search_edsnative_uid']);
    if ($form_state['values']['stacks_search_edsnative_uid'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_uid');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_sso', $form_state['values']['stacks_search_edsnative_sso']);
    if ($form_state['values']['stacks_search_edsnative_sso'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_sso');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_athens', $form_state['values']['stacks_search_edsnative_athens']);
    if ($form_state['values']['stacks_search_edsnative_athens'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_athens');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_authtype', $form_state['values']['stacks_search_edsnative_authtype']);
    if ($form_state['values']['stacks_search_edsnative_authtype'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_authtype');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_direct', $form_state['values']['stacks_search_edsnative_direct']);
    if ($form_state['values']['stacks_search_edsnative_direct'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_direct');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_catalogue_url', $form_state['values']['stacks_search_edsnative_catalogue_url']);
    if ($form_state['values']['stacks_search_edsnative_catalogue_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_catalogue_url');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_user', $form_state['values']['stacks_search_edsnative_user']);
    if ($form_state['values']['stacks_search_edsnative_user'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_user');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_pass', $form_state['values']['stacks_search_edsnative_pass']);
    if ($form_state['values']['stacks_search_edsnative_pass'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_pass');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_scope', $form_state['values']['stacks_search_edsnative_scope']);
    if ($form_state['values']['stacks_search_edsnative_scope'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_scope');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_profile', $form_state['values']['stacks_search_edsnative_profile']);
    if ($form_state['values']['stacks_search_edsnative_profile'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_profile');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_org', $form_state['values']['stacks_search_edsnative_org']);
    if ($form_state['values']['stacks_search_edsnative_org'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_org');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_custid', $form_state['values']['stacks_search_edsnative_custid']);
    if ($form_state['values']['stacks_search_edsnative_custid'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_custid');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_groupid', $form_state['values']['stacks_search_edsnative_groupid']);
    if ($form_state['values']['stacks_search_edsnative_groupid'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_groupid');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_site', $form_state['values']['stacks_search_edsnative_site']);
    if ($form_state['values']['stacks_search_edsnative_site'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_site');
    }

    // EDS Native 2
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_guest2', $form_state['values']['stacks_search_edsnative_guest2']);
    if ($form_state['values']['stacks_search_edsnative_guest2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_guest2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_uid2', $form_state['values']['stacks_search_edsnative_uid2']);
    if ($form_state['values']['stacks_search_edsnative_uid2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_uid2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_sso2', $form_state['values']['stacks_search_edsnative_sso2']);
    if ($form_state['values']['stacks_search_edsnative_sso2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_sso2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_athens2', $form_state['values']['stacks_search_edsnative_athens2']);
    if ($form_state['values']['stacks_search_edsnative_athens2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_athens2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_authtype2', $form_state['values']['stacks_search_edsnative_authtype2']);
    if ($form_state['values']['stacks_search_edsnative_authtype2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_authtype2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_direct2', $form_state['values']['stacks_search_edsnative_direct2']);
    if ($form_state['values']['stacks_search_edsnative_direct2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_direct2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_catalogue_url2', $form_state['values']['stacks_search_edsnative_catalogue_url2']);
    if ($form_state['values']['stacks_search_edsnative_catalogue_url2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_catalogue_url2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_user2', $form_state['values']['stacks_search_edsnative_user2']);
    if ($form_state['values']['stacks_search_edsnative_user2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_user2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_pass2', $form_state['values']['stacks_search_edsnative_pass2']);
    if ($form_state['values']['stacks_search_edsnative_pass2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_pass2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_scope2', $form_state['values']['stacks_search_edsnative_scope2']);
    if ($form_state['values']['stacks_search_edsnative_scope2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_scope2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_profile2', $form_state['values']['stacks_search_edsnative_profile2']);
    if ($form_state['values']['stacks_search_edsnative_profile2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_profile2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_org2', $form_state['values']['stacks_search_edsnative_org2']);
    if ($form_state['values']['stacks_search_edsnative_org2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_org2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_custid2', $form_state['values']['stacks_search_edsnative_custid2']);
    if ($form_state['values']['stacks_search_edsnative_custid2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_custid2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_groupid2', $form_state['values']['stacks_search_edsnative_groupid2']);
    if ($form_state['values']['stacks_search_edsnative_groupid2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_groupid2');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_site2', $form_state['values']['stacks_search_edsnative_site2']);
    if ($form_state['values']['stacks_search_edsnative_site2'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_site2');
    }

    // EDS Native 3
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_guest3', $form_state['values']['stacks_search_edsnative_guest3']);
    if ($form_state['values']['stacks_search_edsnative_guest3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_guest3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_uid3', $form_state['values']['stacks_search_edsnative_uid3']);
    if ($form_state['values']['stacks_search_edsnative_uid3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_uid3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_sso3', $form_state['values']['stacks_search_edsnative_sso3']);
    if ($form_state['values']['stacks_search_edsnative_sso3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_sso3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_athens3', $form_state['values']['stacks_search_edsnative_athens3']);
    if ($form_state['values']['stacks_search_edsnative_athens3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_athens3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_authtype3', $form_state['values']['stacks_search_edsnative_authtype3']);
    if ($form_state['values']['stacks_search_edsnative_authtype3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_authtype3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_direct3', $form_state['values']['stacks_search_edsnative_direct3']);
    if ($form_state['values']['stacks_search_edsnative_direct3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_direct3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_catalogue_url3', $form_state['values']['stacks_search_edsnative_catalogue_url3']);
    if ($form_state['values']['stacks_search_edsnative_catalogue_url3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_catalogue_url3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_user3', $form_state['values']['stacks_search_edsnative_user3']);
    if ($form_state['values']['stacks_search_edsnative_user3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_user3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_pass3', $form_state['values']['stacks_search_edsnative_pass3']);
    if ($form_state['values']['stacks_search_edsnative_pass3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_pass3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_scope3', $form_state['values']['stacks_search_edsnative_scope3']);
    if ($form_state['values']['stacks_search_edsnative_scope3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_scope3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_profile3', $form_state['values']['stacks_search_edsnative_profile3']);
    if ($form_state['values']['stacks_search_edsnative_profile3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_profile3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_org3', $form_state['values']['stacks_search_edsnative_org3']);
    if ($form_state['values']['stacks_search_edsnative_org3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_org3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_custid3', $form_state['values']['stacks_search_edsnative_custid3']);
    if ($form_state['values']['stacks_search_edsnative_custid3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_custid3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_groupid3', $form_state['values']['stacks_search_edsnative_groupid3']);
    if ($form_state['values']['stacks_search_edsnative_groupid3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_groupid3');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_edsnative_site3', $form_state['values']['stacks_search_edsnative_site3']);
    if ($form_state['values']['stacks_search_edsnative_site3'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_edsnative_site3');
    }

    // Sirsi
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_sirsi_catalogue_url', $form_state['values']['stacks_search_sirsi_catalogue_url']);
    if ($form_state['values']['stacks_search_sirsi_catalogue_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_sirsi_catalogue_url');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_sirsi_opac_url', $form_state['values']['stacks_search_sirsi_opac_url']);
    if ($form_state['values']['stacks_search_sirsi_opac_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_sirsi_opac_url');
    }

    // Evergreen
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_evergreen_catalogue_url', $form_state['values']['stacks_search_evergreen_catalogue_url']);
    if ($form_state['values']['stacks_search_evergreen_catalogue_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_evergreen_catalogue_url');
    }

    // III
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_iii_catalogue_url', $form_state['values']['stacks_search_iii_catalogue_url']);
    if ($form_state['values']['stacks_search_iii_catalogue_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_iii_catalogue_url');
    }

    // OCLC
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_oclc_catalogue_url', $form_state['values']['stacks_search_oclc_catalogue_url']);
    if ($form_state['values']['stacks_search_oclc_catalogue_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_oclc_catalogue_url');
    }

    // Koha
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_koha_catalogue_url', $form_state['values']['stacks_search_koha_catalogue_url']);
    if ($form_state['values']['stacks_search_koha_catalogue_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_koha_catalogue_url');
    }

    // Ex Libris
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_exlibris_catalogue_url', $form_state['values']['stacks_search_exlibris_catalogue_url']);
    if ($form_state['values']['stacks_search_exlibris_catalogue_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_exlibris_catalogue_url');
    }

    // Biblio Commons
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_bibliocommons_catalogue_url', $form_state['values']['stacks_search_bibliocommons_catalogue_url']);
    if ($form_state['values']['stacks_search_bibliocommons_catalogue_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_bibliocommons_catalogue_url');
    }

    // Vufind
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_vufind_catalogue_url', $form_state['values']['stacks_search_vufind_catalogue_url']);
    if ($form_state['values']['stacks_search_vufind_catalogue_url'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_vufind_catalogue_url');
    }

    /*
     * All Bento Box Variables under Domain
     */
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_bento_format', $form_state['values']['stacks_search_bento_format']);
    if ($form_state['values']['stacks_search_bento_format'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_bento_format');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_bento_limit_eds', $form_state['values']['stacks_search_bento_limit_eds']);
    if ($form_state['values']['stacks_search_bento_limit_eds'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_bento_limit_eds');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_bento_limit_polaris', $form_state['values']['stacks_search_bento_limit_polaris']);
    if ($form_state['values']['stacks_search_bento_limit_polaris'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_bento_limit_polaris');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_bento_limit_sirsi', $form_state['values']['stacks_search_bento_limit_sirsi']);
    if ($form_state['values']['stacks_search_bento_limit_sirsi'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_bento_limit_sirsi');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_bento_solr', $form_state['values']['stacks_search_bento_solr']);
    if ($form_state['values']['stacks_search_bento_solr'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_bento_solr');
    }
    domain_conf_variable_set($domain['domain_id'], 'stacks_search_bento_limit_solr', $form_state['values']['stacks_search_bento_limit_solr']);
    if ($form_state['values']['stacks_search_bento_limit_solr'] == '') {
      domain_conf_variable_delete($domain['domain_id'], 'stacks_search_bento_limit_solr');
    }

    drupal_set_message('Settings saved on the current domain');
  } else {
    variable_set('stacks_search',  $form_state['values']['system']);
    if ($form_state['values']['system'] == '') {
      variable_del('stacks_search');
    }

    variable_set('stacks_search_internal_checkbox',  $form_state['values']['search_internal_checkbox']);
    if ($form_state['values']['search_internal_checkbox'] == '') {
      variable_del('stacks_search_internal_checkbox');
    }
    variable_set('stacks_search_internal_title',  $form_state['values']['search_internal_textbox']);
    if ($form_state['values']['search_internal_textbox'] == '') {
      variable_del('stacks_search_internal_title');
    }

    variable_set('stacks_search_eds_checkbox',  $form_state['values']['search_eds_checkbox']);
    if ($form_state['values']['search_eds_checkbox'] == '') {
      variable_del('stacks_search_eds_checkbox');
    }
    variable_set('stacks_search_eds_title',  $form_state['values']['search_eds_textbox']);
    if ($form_state['values']['search_eds_textbox'] == '') {
      variable_del('stacks_search_eds_title');
    }

    variable_set('stacks_search_external_checkbox',  $form_state['values']['search_external_checkbox']);
    if ($form_state['values']['search_external_checkbox'] == '') {
      variable_del('stacks_search_external_checkbox');
    }
    variable_set('stacks_search_external_title',  $form_state['values']['search_external_textbox']);
    if ($form_state['values']['search_external_textbox'] == '') {
      variable_del('stacks_search_external_title');
    }
    variable_set('stacks_search_external',  $form_state['values']['search_external_select']);
    if ($form_state['values']['search_external_select'] == '') {
      variable_del('stacks_search_external');
    }

    variable_set('stacks_search_external_checkbox_2',  $form_state['values']['search_external_checkbox_2']);
    if ($form_state['values']['search_external_checkbox_2'] == '') {
      variable_del('stacks_search_external_checkbox_2');
    }
    variable_set('stacks_search_external_title_2',  $form_state['values']['search_external_textbox_2']);
    if ($form_state['values']['search_external_textbox_2'] == '') {
      variable_del('stacks_search_external_title_2');
    }
    variable_set('stacks_search_external_2',  $form_state['values']['search_external_select_2']);
    if ($form_state['values']['search_external_select_2'] == '') {
      variable_del('stacks_search_external_2');
    }

    variable_set('stacks_search_external_checkbox_3',  $form_state['values']['search_external_checkbox_3']);
    if ($form_state['values']['search_external_checkbox_3'] == '') {
      variable_del('stacks_search_external_checkbox_3');
    }
    variable_set('stacks_search_external_title_3',  $form_state['values']['search_external_textbox_3']);
    if ($form_state['values']['search_external_textbox_3'] == '') {
      variable_del('stacks_search_external_title_3');
    }
    variable_set('stacks_search_external_3',  $form_state['values']['search_external_select_3']);
    if ($form_state['values']['search_external_select_3'] == '') {
      variable_del('stacks_search_external_3');
    }

    // Bento
    variable_set('stacks_search_bento_checkbox',  $form_state['values']['search_bento_checkbox']);
    if ($form_state['values']['search_bento_checkbox'] == '') {
      variable_del('stacks_bento_checkbox');
    }
    variable_set('stacks_search_bento_title',  $form_state['values']['search_bento_title']);
    if ($form_state['values']['search_bento_title'] == '') {
      variable_del('stacks_search_bento_title');
    }

    // EDS API
    variable_set('stacks_eds_server', $form_state['values']['stacks_eds_server']);
    if ($form_state['values']['stacks_eds_server'] == '') {
      variable_del('stacks_eds_server');
    }
    variable_set('stacks_eds_user', $form_state['values']['stacks_eds_user']);
    if ($form_state['values']['stacks_eds_user'] == '') {
      variable_del('stacks_eds_user');
    }
    variable_set('stacks_eds_pass', $form_state['values']['stacks_eds_pass']);
    if ($form_state['values']['stacks_eds_pass'] == '') {
      variable_del('stacks_eds_pass');
    }
    variable_set('stacks_eds_profile', $form_state['values']['stacks_eds_profile']);
    if ($form_state['values']['stacks_eds_profile'] == '') {
      variable_del('stacks_eds_profile');
    }
    /*
    variable_set('stacks_eds_org', $form_state['values']['stacks_eds_org']);
    if ($form_state['values']['stacks_eds_org'] == '') {
      variable_del('stacks_eds_org');
    }
    */
    variable_set('stacks_search_eds_docuserve_checkbox', $form_state['values']['stacks_search_eds_docuserve_checkbox']);
    if ($form_state['values']['stacks_search_eds_docuserve_checkbox'] == '') {
      variable_del('stacks_search_eds_docuserve_checkbox');
    }
    variable_set('stacks_search_eds_docuserve_url', $form_state['values']['stacks_search_eds_docuserve_url']);
    if ($form_state['values']['stacks_search_eds_docuserve_url'] == '') {
      variable_del('stacks_search_eds_docuserve_url');
    }
    variable_set('stacks_search_eds_rush_checkbox', $form_state['values']['stacks_search_eds_rush_checkbox']);
    if ($form_state['values']['stacks_search_eds_rush_checkbox'] == '') {
      variable_del('stacks_search_eds_rush_checkbox');
    }
    variable_set('stacks_search_eds_rush_url', $form_state['values']['stacks_search_eds_rush_url']);
    if ($form_state['values']['stacks_search_eds_rush_url'] == '') {
      variable_del('stacks_search_eds_rush_url');
    }
    variable_set('stacks_search_eds_limiter_ft', $form_state['values']['stacks_search_eds_limiter_ft']);
    if ($form_state['values']['stacks_search_eds_limiter_ft'] == '') {
      variable_del('stacks_search_eds_limiter_ft');
    }
    variable_set('stacks_search_eds_limiter_fr', $form_state['values']['stacks_search_eds_limiter_fr']);
    if ($form_state['values']['stacks_search_eds_limiter_fr'] == '') {
      variable_del('stacks_search_eds_limiter_fr');
    }
    variable_set('stacks_search_eds_limiter_rv', $form_state['values']['stacks_search_eds_limiter_rv']);
    if ($form_state['values']['stacks_search_eds_limiter_rv'] == '') {
      variable_del('stacks_search_eds_limiter_rv');
    }
    variable_set('stacks_search_eds_limiter_ft1', $form_state['values']['stacks_search_eds_limiter_ft1']);
    if ($form_state['values']['stacks_search_eds_limiter_ft1'] == '') {
      variable_del('stacks_search_eds_limiter_ft1');
    }
    variable_set('stacks_search_eds_limiter_fc', $form_state['values']['stacks_search_eds_limiter_fc']);
    if ($form_state['values']['stacks_search_eds_limiter_fc'] == '') {
      variable_del('stacks_search_eds_limiter_fc');
    }
    variable_set('stacks_search_eds_expander_thesaurus', $form_state['values']['stacks_search_eds_expander_thesaurus']);
    if ($form_state['values']['stacks_search_eds_expander_thesaurus'] == '') {
      variable_del('stacks_search_eds_expander_thesaurus');
    }
    variable_set('stacks_search_eds_expander_fulltext', $form_state['values']['stacks_search_eds_expander_fulltext']);
    if ($form_state['values']['stacks_search_eds_expander_fulltext'] == '') {
      variable_del('stacks_search_eds_expander_fulltext');
    }
    variable_set('stacks_search_eds_expander_precision', $form_state['values']['stacks_search_eds_expander_precision']);
    if ($form_state['values']['stacks_search_eds_expander_precision'] == '') {
      variable_del('stacks_search_eds_expander_precision');
    }

    // Polaris
    variable_set('stacks_search_polaris_catalogue_url', $form_state['values']['stacks_search_polaris_catalogue_url']);
    if ($form_state['values']['stacks_search_polaris_catalogue_url'] == '') {
      variable_del('stacks_search_polaris_catalogue_url');
    }
    variable_set('stacks_search_polaris_advanced_url', $form_state['values']['stacks_search_polaris_advanced_url']);
    if ($form_state['values']['stacks_search_polaris_advanced_url'] == '') {
      variable_del('stacks_search_polaris_advanced_url');
    }
    variable_set('stacks_search_polaris_ctx', $form_state['values']['stacks_search_polaris_ctx']);
    if ($form_state['values']['stacks_search_polaris_ctx'] == '') {
      variable_del('stacks_search_polaris_ctx');
    }
    variable_set('stacks_search_polaris_page', $form_state['values']['stacks_search_polaris_page']);
    if ($form_state['values']['stacks_search_polaris_page'] == '') {
      variable_del('stacks_search_polaris_page');
    }
    variable_set('stacks_search_polaris_tom', $form_state['values']['stacks_search_polaris_tom']);
    if ($form_state['values']['stacks_search_polaris_tom'] == '') {
      variable_del('stacks_search_polaris_tom');
    }
    variable_set('stacks_search_polaris_opac_url', $form_state['values']['stacks_search_polaris_opac_url']);
    if ($form_state['values']['stacks_search_polaris_opac_url'] == '') {
      variable_del('stacks_search_polaris_opac_url');
    }

    // EDS Native 1
    variable_set('stacks_search_edsnative_guest', $form_state['values']['stacks_search_edsnative_guest']);
    if ($form_state['values']['stacks_search_edsnative_guest'] == '') {
      variable_del('stacks_search_edsnative_guest');
    }
    variable_set('stacks_search_edsnative_uid', $form_state['values']['stacks_search_edsnative_uid']);
    if ($form_state['values']['stacks_search_edsnative_uid'] == '') {
      variable_del('stacks_search_edsnative_uid');
    }
    variable_set('stacks_search_edsnative_sso', $form_state['values']['stacks_search_edsnative_sso']);
    if ($form_state['values']['stacks_search_edsnative_sso'] == '') {
      variable_del('stacks_search_edsnative_sso');
    }
    variable_set('stacks_search_edsnative_athens', $form_state['values']['stacks_search_edsnative_athens']);
    if ($form_state['values']['stacks_search_edsnative_athens'] == '') {
      variable_del('stacks_search_edsnative_athens');
    }
    variable_set('stacks_search_edsnative_authtype', $form_state['values']['stacks_search_edsnative_authtype']);
    if ($form_state['values']['stacks_search_edsnative_authtype'] == '') {
      variable_del('stacks_search_edsnative_authtype');
    }
    variable_set('stacks_search_edsnative_direct', $form_state['values']['stacks_search_edsnative_direct']);
    if ($form_state['values']['stacks_search_edsnative_direct'] == '') {
      variable_del('stacks_search_edsnative_direct');
    }
    variable_set('stacks_search_edsnative_catalogue_url', $form_state['values']['stacks_search_edsnative_catalogue_url']);
    if ($form_state['values']['stacks_search_edsnative_catalogue_url'] == '') {
      variable_del('stacks_search_edsnative_catalogue_url');
    }
    variable_set('stacks_search_edsnative_user', $form_state['values']['stacks_search_edsnative_user']);
    if ($form_state['values']['stacks_search_edsnative_user'] == '') {
      variable_del('stacks_search_edsnative_user');
    }
    variable_set('stacks_search_edsnative_pass', $form_state['values']['stacks_search_edsnative_pass']);
    if ($form_state['values']['stacks_search_edsnative_pass'] == '') {
      variable_del('stacks_search_edsnative_pass');
    }
    variable_set('stacks_search_edsnative_scope', $form_state['values']['stacks_search_edsnative_scope']);
    if ($form_state['values']['stacks_search_edsnative_scope'] == '') {
      variable_del('stacks_search_edsnative_scope');
    }
    variable_set('stacks_search_edsnative_profile', $form_state['values']['stacks_search_edsnative_profile']);
    if ($form_state['values']['stacks_search_edsnative_profile'] == '') {
      variable_del('stacks_search_edsnative_profile');
    }
    variable_set('stacks_search_edsnative_org', $form_state['values']['stacks_search_edsnative_org']);
    if ($form_state['values']['stacks_search_edsnative_org'] == '') {
      variable_del('stacks_search_edsnative_org');
    }
    variable_set('stacks_search_edsnative_custid', $form_state['values']['stacks_search_edsnative_custid']);
    if ($form_state['values']['stacks_search_edsnative_custid'] == '') {
      variable_del('stacks_search_edsnative_custid');
    }
    variable_set('stacks_search_edsnative_groupid', $form_state['values']['stacks_search_edsnative_groupid']);
    if ($form_state['values']['stacks_search_edsnative_groupid'] == '') {
      variable_del('stacks_search_edsnative_groupid');
    }
    variable_set('stacks_search_edsnative_site', $form_state['values']['stacks_search_edsnative_site']);
    if ($form_state['values']['stacks_search_edsnative_site'] == '') {
      variable_del('stacks_search_edsnative_site');
    }

    // EDS Native 2
    variable_set('stacks_search_edsnative_guest2', $form_state['values']['stacks_search_edsnative_guest2']);
    if ($form_state['values']['stacks_search_edsnative_guest2'] == '') {
      variable_del('stacks_search_edsnative_guest2');
    }
    variable_set('stacks_search_edsnative_uid2', $form_state['values']['stacks_search_edsnative_uid2']);
    if ($form_state['values']['stacks_search_edsnative_uid2'] == '') {
      variable_del('stacks_search_edsnative_uid2');
    }
    variable_set('stacks_search_edsnative_sso2', $form_state['values']['stacks_search_edsnative_sso2']);
    if ($form_state['values']['stacks_search_edsnative_sso2'] == '') {
      variable_del('stacks_search_edsnative_sso2');
    }
    variable_set('stacks_search_edsnative_athens2', $form_state['values']['stacks_search_edsnative_athens2']);
    if ($form_state['values']['stacks_search_edsnative_athens2'] == '') {
      variable_del('stacks_search_edsnative_athens2');
    }
    variable_set('stacks_search_edsnative_authtype2', $form_state['values']['stacks_search_edsnative_authtype2']);
    if ($form_state['values']['stacks_search_edsnative_authtype2'] == '') {
      variable_del('stacks_search_edsnative_authtype2');
    }
    variable_set('stacks_search_edsnative_direct2', $form_state['values']['stacks_search_edsnative_direct2']);
    if ($form_state['values']['stacks_search_edsnative_direct2'] == '') {
      variable_del('stacks_search_edsnative_direct2');
    }
    variable_set('stacks_search_edsnative_catalogue_url2', $form_state['values']['stacks_search_edsnative_catalogue_url2']);
    if ($form_state['values']['stacks_search_edsnative_catalogue_url2'] == '') {
      variable_del('stacks_search_edsnative_catalogue_url2');
    }
    variable_set('stacks_search_edsnative_user2', $form_state['values']['stacks_search_edsnative_user2']);
    if ($form_state['values']['stacks_search_edsnative_user2'] == '') {
      variable_del('stacks_search_edsnative_user2');
    }
    variable_set('stacks_search_edsnative_pass2', $form_state['values']['stacks_search_edsnative_pass2']);
    if ($form_state['values']['stacks_search_edsnative_pass2'] == '') {
      variable_del('stacks_search_edsnative_pass2');
    }
    variable_set('stacks_search_edsnative_scope2', $form_state['values']['stacks_search_edsnative_scope2']);
    if ($form_state['values']['stacks_search_edsnative_scope2'] == '') {
      variable_del('stacks_search_edsnative_scope2');
    }
    variable_set('stacks_search_edsnative_profile2', $form_state['values']['stacks_search_edsnative_profile2']);
    if ($form_state['values']['stacks_search_edsnative_profile2'] == '') {
      variable_del('stacks_search_edsnative_profile2');
    }
    variable_set('stacks_search_edsnative_org2', $form_state['values']['stacks_search_edsnative_org2']);
    if ($form_state['values']['stacks_search_edsnative_org2'] == '') {
      variable_del('stacks_search_edsnative_org2');
    }
    variable_set('stacks_search_edsnative_custid2', $form_state['values']['stacks_search_edsnative_custid2']);
    if ($form_state['values']['stacks_search_edsnative_custid2'] == '') {
      variable_del('stacks_search_edsnative_custid2');
    }
    variable_set('stacks_search_edsnative_groupid2', $form_state['values']['stacks_search_edsnative_groupid2']);
    if ($form_state['values']['stacks_search_edsnative_groupid2'] == '') {
      variable_del('stacks_search_edsnative_groupid2');
    }
    variable_set('stacks_search_edsnative_site2', $form_state['values']['stacks_search_edsnative_site2']);
    if ($form_state['values']['stacks_search_edsnative_site2'] == '') {
      variable_del('stacks_search_edsnative_site2');
    }

    // EDS Native 3
    variable_set('stacks_search_edsnative_guest3', $form_state['values']['stacks_search_edsnative_guest3']);
    if ($form_state['values']['stacks_search_edsnative_guest3'] == '') {
      variable_del('stacks_search_edsnative_guest3');
    }
    variable_set('stacks_search_edsnative_uid3', $form_state['values']['stacks_search_edsnative_uid3']);
    if ($form_state['values']['stacks_search_edsnative_uid3'] == '') {
      variable_del('stacks_search_edsnative_uid3');
    }
    variable_set('stacks_search_edsnative_sso3', $form_state['values']['stacks_search_edsnative_sso3']);
    if ($form_state['values']['stacks_search_edsnative_sso3'] == '') {
      variable_del('stacks_search_edsnative_sso3');
    }
    variable_set('stacks_search_edsnative_athens3', $form_state['values']['stacks_search_edsnative_athens3']);
    if ($form_state['values']['stacks_search_edsnative_athens3'] == '') {
      variable_del('stacks_search_edsnative_athens3');
    }
    variable_set('stacks_search_edsnative_authtype3', $form_state['values']['stacks_search_edsnative_authtype3']);
    if ($form_state['values']['stacks_search_edsnative_authtype3'] == '') {
      variable_del('stacks_search_edsnative_authtype3');
    }
    variable_set('stacks_search_edsnative_direct3', $form_state['values']['stacks_search_edsnative_direct3']);
    if ($form_state['values']['stacks_search_edsnative_direct3'] == '') {
      variable_del('stacks_search_edsnative_direct3');
    }
    variable_set('stacks_search_edsnative_catalogue_url3', $form_state['values']['stacks_search_edsnative_catalogue_url3']);
    if ($form_state['values']['stacks_search_edsnative_catalogue_url3'] == '') {
      variable_del('stacks_search_edsnative_catalogue_url3');
    }
    variable_set('stacks_search_edsnative_user3', $form_state['values']['stacks_search_edsnative_user3']);
    if ($form_state['values']['stacks_search_edsnative_user3'] == '') {
      variable_del('stacks_search_edsnative_user3');
    }
    variable_set('stacks_search_edsnative_pass3', $form_state['values']['stacks_search_edsnative_pass3']);
    if ($form_state['values']['stacks_search_edsnative_pass3'] == '') {
      variable_del('stacks_search_edsnative_pass3');
    }
    variable_set('stacks_search_edsnative_scope3', $form_state['values']['stacks_search_edsnative_scope3']);
    if ($form_state['values']['stacks_search_edsnative_scope3'] == '') {
      variable_del('stacks_search_edsnative_scope3');
    }
    variable_set('stacks_search_edsnative_profile3', $form_state['values']['stacks_search_edsnative_profile3']);
    if ($form_state['values']['stacks_search_edsnative_profile3'] == '') {
      variable_del('stacks_search_edsnative_profile3');
    }
    variable_set('stacks_search_edsnative_org3', $form_state['values']['stacks_search_edsnative_org3']);
    if ($form_state['values']['stacks_search_edsnative_org3'] == '') {
      variable_del('stacks_search_edsnative_org3');
    }
    variable_set('stacks_search_edsnative_custid3', $form_state['values']['stacks_search_edsnative_custid3']);
    if ($form_state['values']['stacks_search_edsnative_custid3'] == '') {
      variable_del('stacks_search_edsnative_custid3');
    }
    variable_set('stacks_search_edsnative_groupid3', $form_state['values']['stacks_search_edsnative_groupid3']);
    if ($form_state['values']['stacks_search_edsnative_groupid3'] == '') {
      variable_del('stacks_search_edsnative_groupid3');
    }
    variable_set('stacks_search_edsnative_site3', $form_state['values']['stacks_search_edsnative_site3']);
    if ($form_state['values']['stacks_search_edsnative_site3'] == '') {
      variable_del('stacks_search_edsnative_site3');
    }

    // Sirsi
    variable_set('stacks_search_sirsi_catalogue_url', $form_state['values']['stacks_search_sirsi_catalogue_url']);
    if ($form_state['values']['stacks_search_sirsi_catalogue_url'] == '') {
      variable_del('stacks_search_sirsi_catalogue_url');
    }
    variable_set('stacks_search_sirsi_opac_url', $form_state['values']['stacks_search_sirsi_opac_url']);
    if ($form_state['values']['stacks_search_sirsi_opac_url'] == '') {
      variable_del('stacks_search_sirsi_opac_url');
    }

    // Evergreen
    variable_set('stacks_search_evergreen_catalogue_url', $form_state['values']['stacks_search_evergreen_catalogue_url']);
    if ($form_state['values']['stacks_search_evergreen_catalogue_url'] == '') {
      variable_del('stacks_search_evergreen_catalogue_url');
    }

    // III
    variable_set('stacks_search_iii_catalogue_url', $form_state['values']['stacks_search_iii_catalogue_url']);
    if ($form_state['values']['stacks_search_iii_catalogue_url'] == '') {
      variable_del('stacks_search_iii_catalogue_url');
    }

    // OCLC
    variable_set('stacks_search_oclc_catalogue_url', $form_state['values']['stacks_search_oclc_catalogue_url']);
    if ($form_state['values']['stacks_search_oclc_catalogue_url'] == '') {
      variable_del('stacks_search_oclc_catalogue_url');
    }

    // Koha
    variable_set('stacks_search_koha_catalogue_url', $form_state['values']['stacks_search_koha_catalogue_url']);
    if ($form_state['values']['stacks_search_koha_catalogue_url'] == '') {
      variable_del('stacks_search_koha_catalogue_url');
    }

    // Ex Libris
    variable_set('stacks_search_exlibris_catalogue_url', $form_state['values']['stacks_search_exlibris_catalogue_url']);
    if ($form_state['values']['stacks_search_exlibris_catalogue_url'] == '') {
      variable_del('stacks_search_exlibris_catalogue_url');
    }

    // Biblio Commons
    variable_set('stacks_search_bibliocommons_catalogue_url', $form_state['values']['stacks_search_bibliocommons_catalogue_url']);
    if ($form_state['values']['stacks_search_bibliocommons_catalogue_url'] == '') {
      variable_del('stacks_search_bibliocommons_catalogue_url');
    }

    // Vufind
    variable_set('stacks_search_vufind_catalogue_url', $form_state['values']['stacks_search_vufind_catalogue_url']);
    if ($form_state['values']['stacks_search_vufind_catalogue_url'] == '') {
      variable_del('stacks_search_vufind_catalogue_url');
    }

    /*
     * All Bento Box Variables
     */
    variable_set('stacks_search_bento_format', $form_state['values']['stacks_search_bento_format']);
    if ($form_state['values']['stacks_search_bento_format'] == '') {
      variable_del('stacks_search_bento_format');
    }
    variable_set('stacks_search_bento_limit_eds', $form_state['values']['stacks_search_bento_limit_eds']);
    if ($form_state['values']['stacks_search_bento_limit_eds'] == '') {
      variable_del('stacks_search_bento_limit_eds');
    }
    variable_set('stacks_search_bento_limit_polaris', $form_state['values']['stacks_search_bento_limit_polaris']);
    if ($form_state['values']['stacks_search_bento_limit_polaris'] == '') {
      variable_del('stacks_search_bento_limit_polaris');
    }
    variable_set('stacks_search_bento_limit_sirsi', $form_state['values']['stacks_search_bento_limit_sirsi']);
    if ($form_state['values']['stacks_search_bento_limit_sirsi'] == '') {
      variable_del('stacks_search_bento_limit_sirsi');
    }
    variable_set('stacks_search_bento_solr', $form_state['values']['stacks_search_bento_solr']);
    if ($form_state['values']['stacks_search_bento_solr'] == '') {
      variable_del('stacks_search_bento_solr');
    }
    variable_set('stacks_search_bento_limit_solr', $form_state['values']['stacks_search_bento_limit_solr']);
    if ($form_state['values']['stacks_search_bento_limit_solr'] == '') {
      variable_del('stacks_search_bento_limit_solr');
    }

    drupal_set_message('Settings saved');
  }
}

/**
 * Helper function to load solr indexes to dropdownlist under bento configuration.
 * @return array of available solr indexes that have been created.
 */
function load_solr_indexes() {
  $indexArray = array();
  $query = db_select('search_api_index', 's');
  $query->fields('s', array('machine_name', 'name'));
  $indexes = $query->execute()->fetchAll();

  foreach($indexes as $index) {
    if($index->machine_name != 'default_node_index') {
      $indexArray[$index->machine_name] = $index->name;
    }
  }


  return $indexArray;
}
