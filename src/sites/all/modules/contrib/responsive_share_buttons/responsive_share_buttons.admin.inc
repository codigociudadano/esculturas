<?php

/**
 * @file
 * Functionality for Responsive share buttons administration.
 */

/**
 * Settings form as implemented by hook_menu.
 */
function responsive_share_buttons_settings($form, &$form_state) {
  $form['responsive_buttons'] = array(
      '#type' => 'fieldset',
      '#title' => t('Responsive Buttons'),
  );
  $button_options = array(
    'facebook' =>  t('Facebook'),
    'twitter' =>  t('Twitter'),
    'digg' =>  t('Digg'),
    'stumbleupon' =>  t('Stumbleupon'),
    'delicious' =>  t('Delicious'),
    'google' =>  t('Google +'),
  );
  $defaults = array_keys($button_options);
  $form['responsive_buttons']['responsive_share_buttons'] = array(
        '#type' => 'checkboxes',
        '#title' => t(''),
        '#options' => $button_options,
        // following will check all by default but will save state once form is saved
        '#default_value' => variable_get('responsive_share_buttons', $defaults),
        '#description' => t('Select the social services you want available for sharing.'),
  );
  //$form['responsive_share_buttons']['responsive_share_buttons_animate_speed'] = array(
  //  '#type' => 'select',
  //  '#title' => t('Animation speed'),
  //  '#multiple' => FALSE,
  //  '#description' => t('Speed of the open/close animation.'),
  //  '#options' => array(
  //    '200' => t('slow'),
  //    '400' => t('normal'),
  //    '600' => t('fast'),
  //  ),
  //  '#default_value' => variable_get('responsive_share_buttons_animate_speed'),
  //);
  return system_settings_form($form);
}