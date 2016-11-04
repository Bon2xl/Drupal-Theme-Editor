<?php

function hf_resource_list_admin_form($form, &$form_state) {
	$form = array();

	$jquery_selectors = implode("\n", variable_get('stacks_cover_jquery', ''));


	$form['book-covers'] = array(
		'#type' => 'fieldset',
		'#title' => 'Book Jackets',

		'instructions' => array(
			'#type' => 'markup',
			'#markup' => '<p>Covers will placed on dom elements containing data-cover-isbn attribute</p>' .
				'<p>Example: &lt;div data-cover-isbn="2321323"&gt;&lt;/div&gt;</p>'
		),

		// options
		'book-cover-provider' => array(
			'#title' => "Book Jacket Provider",
			'#type' => 'select',
			'#options' => array(
				'' => '- none -',
				'syndetics' => 'Syndetics',
				'contente_cafe' => 'Content Cafe',
        'chilifresh' => 'Chili Fresh',
			),
			'#default_value' => variable_get('stacks_cover_provider', '')
		),
		'book-cover-jquery-lookup' => array(
			'#title' => "Data lookup selectors",
			'#type' => 'textarea',
			'#default_value' => $jquery_selectors,
			'#description' => 'Enter the jquery selectors you want to look ISBN numbers from. One per line. These selectors will be replaced with images. <br>'.
					'Example: <br> <em>*[data-cover-isbn]</em> <br>.resource-list data-cover-isbn',
		)
	);

	$form['config-tabs'] = array(
		'#type' => 'vertical_tabs'
	);

	$form['syndetics-fieldset'] = array(
		'#type' => 'fieldset',
		'#title' => 'Syndetics configuration',
		'#description' => 'Enter a Syndetics URL for getting the book covers from. The URL can use SC.GIF, MC.GIF or LC.GIF (Image sizes).'.
			' Keep in mind that LC.GIF may return an HTML response if the cover cannot be found.',
		'#group' => 'config-tabs',

		'syndetics-url' => array(
			'#type' => 'textfield',
			'#title' => 'Syndetics URL',
      '#maxlength' => 512,
			'#default_value' => variable_get('stacks_resource_list_syndetics_url', ''),
			'#description' => 'Example: http://www.syndetics.com/index.aspx?type=hw7&client=CLIENTCODE&isbn=$isbn/MC.GIF&upc=$upc',
		)
	);

  /*
  if (!empty(variable_get('stacks_resource_list_syndetics_url', ''))) {
    $form['syndetics-fieldset']['syndetics-url']['#attributes'] = array('placeholder' => '····················');
  }
  */

	$form['content_cafe-fieldset'] = array(
		'#type' => 'fieldset',
		'#title' => 'Content Cafe configuration',
		'#description' => 'Enter a Content Care URL for getting the book covers from. The URL can use SC.GIF, MC.GIF or LC.GIF (Image sizes).',
		'#group' => 'config-tabs',

		'content_cafe-url' => array(
			'#type' => 'textfield',
			'#title' => 'Content Cafe URL',
      '#maxlength' => 512,
			'#default_value' => variable_get('stacks_resource_list_contentcafe_url', ''),
			'#description' => 'Example: http://contentcafe2.btol.com/ContentCafe/Single.aspx?userID=CLIENT-ID&password=CLIENT-PASSWORD&content=ReviewDetail&key=$isbn',
		)
	);

  /*
  if (!empty(variable_get('stacks_resource_list_contentcafe_url', ''))) {
    $form['content_cafe-fieldset']['content_cafe-url']['#attributes'] = array('placeholder' => '····················');
  }
  */

  $form['chili_fresh-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => 'Chili Fresh configuration',
    '#description' => 'Enter a Chili Fresh URL for getting the book covers from. The URL can use SC.GIF, MC.GIF or LC.GIF (Image sizes).',
    '#group' => 'config-tabs',

    'chili_fresh-url' => array(
      '#type' => 'textfield',
      '#title' => 'Chili Fresh URL',
      '#maxlength' => 512,
      '#default_value' => variable_get('stacks_resource_list_chilifresh_url', ''),
      '#description' => 'Example: http://content.chilifresh.com/?&amp;isbn=$isbn&amp;upc=[upc]&amp;size=S ',
    )
  );

  /*
  if (!empty(variable_get('stacks_resource_list_chilifresh_url', ''))) {
    $form['chili_fresh-fieldset']['chili_fresh-url']['#attributes'] = array('placeholder' => '····················');
  }
  */

	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save Configuration'
	);
	return $form;
}


function hf_resource_list_admin_form_submit($form, &$form_state) {
  if (!empty($form_state['values']['syndetics-url'])) {
    variable_set('stacks_resource_list_syndetics_url', $form_state['values']['syndetics-url']);
  }
  if (!empty($form_state['values']['content_cafe-url'])) {
    variable_set('stacks_resource_list_contentcafe_url', $form_state['values']['content_cafe-url']);
  }
  if (!empty($form_state['values']['chili_fresh-url'])) {
    variable_set('stacks_resource_list_chilifresh_url', $form_state['values']['chili_fresh-url']);
  }

	$jquery_selectors = explode("\n", $form_state['values']['book-cover-jquery-lookup']);
	variable_set('stacks_cover_jquery', $jquery_selectors);

	variable_set('stacks_cover_provider', $form_state['values']['book-cover-provider']);
}