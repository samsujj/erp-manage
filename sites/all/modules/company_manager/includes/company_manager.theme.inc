<?php
/**
 * @file
 * contactus.theme.inc
 */

/**
 * Theme lawmaker full page.
 */
function theme_company_manager_full($variables) {
  $output = '';
  $contacts = $variables['contact'];

  $output .= '<div class="contact_meta">';

  // Lazy...

  $output .= '<div class="contact-name">'  . trim($contacts->established_date)  . '</div>';
  $output .= '<div class="contact-email">'  . trim($contacts->service_tax_number)  . '</div>';
  $output .= '<div class="contact-phone">'  . trim($contacts->tan_number)  . '</div>';


  //$output .= '<div class="contact-enquiry_type">'  . trim($contacts->enquiry_type)  . '</div>';
  // $output .= '<div class="party">' . $lawmakers->party . ' ' . $lawmakers->state  . '  ' . $lawmakers->district . '</div>';

  if (user_access('administer company_manager entities') && isset($contacts->company_id)) {
    $edit_link = '<ul class="tabs primary"><li>';
    $edit_link .= l(t('Edit'), 'admin/content/company_manager/manage/' . $contacts->company_id, array('attributes' => array('class' => 'admin-edit-link')));
    $edit_link .= '</li></ul>';
    $output .= $edit_link;
  }

  $output .= '</div>';

  return $output;
}
