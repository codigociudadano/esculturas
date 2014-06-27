<?php

/**
 * @file
 * Provides function for form building for google_map_field_apikey
 */

/**
 *  Form builder for google_map_field_apikey settings page.
 */
function google_map_field_apikey_settings_form($form, &$form_state) {
  $form = array();

  $form['google_map_field_apikey'] = array(
    '#title' => t('Google Maps API key'),
    '#type' => 'textfield',
    '#description' => t('Enter your Google Maps API v3 key in this box.'),
    '#default_value' => variable_get('google_map_field_apikey', ''),
  );

  return system_settings_form($form);
}
