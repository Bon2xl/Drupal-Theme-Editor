<?php

function hf_flipster_form($form, &$form_state) {

    $form['title'] = array(
        '#type' => 'textfield',
        '#title' => 'Flipster List Title',
        '#required' => TRUE,
         '#prefix' => '<h1>Flipster Lists</h1>' .
            '<p>Import desired lists of Flipster content to be displayed on Stacks.</p>' .
            '<ol>'.
            '<li>Log on to Flipster</li>' .
            '<li>Click on a selected Category or click View All to retrieve desired list of Flipster content. (e.g.<i>To get the latest 20 issues, click "View All" and select "Date Newest" under Relevance</i>)</li>' .
            '<li>Copy entire URL in the Address Field (e.g., http://web.a.ebscohost.com/eon/search/basic?sid=bbe9eed4-540a-4b93-9be4-7861e1a9dee5%40sessionmgr4002&vid=3&hid=4201)</li>' .
            '<li>Paste into field below and click submit</li>' .
            '</ol>' .
            '<br>'
    );
    $form['url'] = array(
        '#type' => 'textfield',
        '#title' => 'Flipster List URL',
        '#description' => 'Please insert a URL to build a Flipster List',
        '#required' => TRUE
    );


    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Submit URL'
    );

    return $form;
}

function hf_flipster_form_validate(&$form, &$form_state) {
    if ($form_state['values']['title'] == '') {
        form_set_error('title', t('Please enter a title for your list.'));
    } else {
        if ($form_state['values']['url'] == '') {
            form_set_error('url', t('Please enter a proper url.'));
//        } else {
//            if(!preg_match("/(http:\/\/web.a.ebscohost.com\/eon\/results.*)/", $form_state['values']['url']) && !preg_match("/(http:\/\/web.b.ebscohost.com\/eon\/results.*)/", $form_state['values']['url'])){
//                form_set_error('url', t('Please enter a valid Flipster url that begins with http://web.b.ebscohost.com/eon/results...'));
//            }
        }
    }
}

function hf_flipster_form_submit($form, $form_state) {
    hf_flipster_load($form_state['values']['url'], $form_state['values']['title']);

}
