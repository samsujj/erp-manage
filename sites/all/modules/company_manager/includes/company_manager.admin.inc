<?php
/**
 * @file
 * The file for admin forms and functionality for the lawmakers entity
 */

/**
 * Implements hook_form().
 */
function company_manager_form($form, &$form_state, $contacts = NULL) {
    $form = array();

    $form['established_date'] = array(
        '#title' => t('established_date'),
        '#type' => 'textfield',
        '#default_value' => isset($contacts->established_date) ? $contacts->established_date : '',
        '#description' => t('established_date .'),
        '#required' => TRUE,
        '#maxlength' => 255,
    );

    $form['service_tax_number'] = array(
        '#title' => t('service_tax_number'),
        '#type' => 'textfield',
        '#default_value' => isset($contacts->service_tax_number) ? $contacts->service_tax_number : '',
        '#description' => t('service_tax_number.'),
        '#required' => TRUE,
        '#maxlength' => 255,
    );

    $form['tan_number'] = array(
        '#title' => t('tan_number'),
        '#type' => 'textfield',
        '#default_value' => isset($contacts->tan_number) ? $contacts->tan_number : '',
        '#description' => t('tan_number.'),
        '#required' => TRUE,
        '#maxlength' => 255,
    );
   $form['search_tag'] = array(
        '#title' => t('search_tags'),
        '#type' => 'hidden',
        '#description' => t(''),
        //'#options' => $options,
        //'#required' => TRUE,
        //'#default_value' => array("1", "2", "3","4")
    );



    field_attach_form('company_manager', $contacts, $form, $form_state);

    $form['actions'] = array(
        '#type' => 'actions',
        'submit' => array(
            '#type' => 'submit',
            '#value' => isset($contacts->company_id) ? t('Update Company') : t('Save Comapny'),
        ),
        'delete_link' => array(
            '#markup' => isset($contacts->company_id) ? l(t('Delete'), 'admin/content/company_manager/manage/' . $contacts->company_id . '/delete', array('attributes' => array('id' => array('company_manager-delete-' . $contacts->company_id), 'class' => array('button remove')), 'query' => array('destination' => 'admin/content/company_manager'))) : ''));
    return $form;
}

/**
 * Implements hook_form_validate().
 */
function company_manager_form_validate($form, &$form_state) {

/*
    $mail = $form_state['values']['email'];
    if (!valid_email_address($mail)) {
        form_set_error('[email]', t('The email address appears to be invalid.'));
    }

*/

}

/**
 * Implements hook_form_submit().
 */
function company_manager_form_submit($form, &$form_state) {

    $form_state['values']['search_tag']=$form_state['values']['established_date'].$form_state['values']['service_tax_number'].$form_state['values']['tan_number'];
    // var_dump($form_state['values']);
    // exit;
    $contactus = entity_ui_form_submit_build_entity($form, $form_state);
    $contactus->save();
    drupal_set_message(t('@tan_number comapany has been saved.', array('@tan_number' => $contactus->tan_number)));
    // $form_state['redirect'] = 'admin/content/lawmakers';
    $form_state['redirect'] = 'company_manager/' . $contactus->company_id;

}

/**
 * Confirmation before bulk deleting lawmakers.
 */
function company_manager_bulk_delete($form, &$form_state, $contact_ids) {
    $contact_ids = explode('|', $contact_ids);
    $contacts = contactus_load_multiple($contact_ids);

    $form = array();
    //$form_state['contact_ids'] = $contact_ids;
    //var_dump($form_state['contact_ids']);
    foreach($contact_ids as $cid){

        $form_state['contact_ids'][]=str_replace('company_id-','',$cid);

    }

    //var_dump($form_state['contact_ids']);

    $variables = array(
        'type' => 'ul',
        'items' => array(),
        'title' => '',
        'attributes' => array(),
    );

    foreach ($contacts as $contact) {
        echo $variables['items'][] = $contact->tan_number;
    }

    $form['summary'] = array(
        '#markup' => theme_item_list($variables),
    );

    return confirm_form($form, t('Delete all contacts?'), 'admin/content/company_manager', t('Placeholder description'), t('Delete all'), t('Cancel'));
}

/**
 * Implements hook_submit().
 */
function company_manager_bulk_delete_submit($form, &$form_state) {
    $contact_ids = $form_state['contact_ids'];
    //var_dump($contact_ids);
    //exit;
    company_manager_delete_multiple($contact_ids);

    drupal_set_message(t('contact deleted'));
    drupal_goto('admin/content/company_manager');
}
