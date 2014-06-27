<?php
/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
function esculturas_form_system_theme_settings_alter(&$form, &$form_state) {

  $form['esculturas_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('esculturas Settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['esculturas_settings']['breadcrumbs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show breadcrumbs in a page'),
    '#default_value' => theme_get_setting('breadcrumbs','esculturas'),
    '#description'   => t("Check this option to show breadcrumbs in page. Uncheck to hide."),
  );
  $form['esculturas_settings']['slideshow'] = array(
    '#type' => 'fieldset',
    '#title' => t('Front Page Slideshow'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['esculturas_settings']['slideshow']['slideshow_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show slideshow'),
    '#default_value' => theme_get_setting('slideshow_display','esculturas'),
    '#description'   => t("Check this option to show Slideshow in front page. Uncheck to hide."),
  );
  $form['esculturas_settings']['slideshow']['slide'] = array(
    '#markup' => t('You can change the description and URL of each slide in the following Slide Setting fieldsets.'),
  );
  $form['esculturas_settings']['slideshow']['slide1'] = array(
    '#type' => 'fieldset',
    '#title' => t('Slide 1'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['esculturas_settings']['slideshow']['slide1']['slide1_head'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide Headline'),
    '#default_value' => theme_get_setting('slide1_head','esculturas'),
  );
  $form['esculturas_settings']['slideshow']['slide1']['slide1_desc'] = array(
    '#type' => 'textarea',
    '#title' => t('Slide Description'),
    '#default_value' => theme_get_setting('slide1_desc','esculturas'),
  );
  $form['esculturas_settings']['slideshow']['slide1']['slide1_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide URL'),
    '#default_value' => theme_get_setting('slide1_url','esculturas'),
  );
  $form['esculturas_settings']['slideshow']['slide2'] = array(
    '#type' => 'fieldset',
    '#title' => t('Slide 2'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['esculturas_settings']['slideshow']['slide2']['slide2_head'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide Headline'),
    '#default_value' => theme_get_setting('slide2_head','esculturas'),
  );
  $form['esculturas_settings']['slideshow']['slide2']['slide2_desc'] = array(
    '#type' => 'textarea',
    '#title' => t('Slide Description'),
    '#default_value' => theme_get_setting('slide2_desc','esculturas'),
  );
  $form['esculturas_settings']['slideshow']['slide2']['slide2_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide URL'),
    '#default_value' => theme_get_setting('slide2_url','esculturas'),
  );
  $form['esculturas_settings']['slideshow']['slide3'] = array(
    '#type' => 'fieldset',
    '#title' => t('Slide 3'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['esculturas_settings']['slideshow']['slide3']['slide3_head'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide Headline'),
    '#default_value' => theme_get_setting('slide3_head','esculturas'),
  );
  $form['esculturas_settings']['slideshow']['slide3']['slide3_desc'] = array(
    '#type' => 'textarea',
    '#title' => t('Slide Description'),
    '#default_value' => theme_get_setting('slide3_desc','esculturas'),
  );
  $form['esculturas_settings']['slideshow']['slide3']['slide3_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide URL'),
    '#default_value' => theme_get_setting('slide3_url','esculturas'),
  );
  $form['esculturas_settings']['slideshow']['slideimage'] = array(
    '#markup' => t('To change the Slide Images, Replace the slide-image-1.jpg, slide-image-2.jpg and slide-image-3.jpg in the images folder of the theme folder.'),
  );
}
