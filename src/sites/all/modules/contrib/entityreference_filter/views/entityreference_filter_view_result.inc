<?php

class entityreference_filter_view_result extends views_handler_filter_in_operator {

  function option_definition() {
    $options = parent::option_definition();
    $options['reference_display'] = array('default' => '');
    return $options;
  }

  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);

    if (!empty($form_state['exposed'])) {
      // Run time.
      $values = $this->get_value_options();
      if (empty($values)) {
        // Hide the form element.
        //TODO: add a configuration for this option.
        if (isset($form['value'])) {
          $form['value']['#prefix'] = '<div class="element-hidden">';
          $form['value']['#suffix'] = '</div>';
        }
      }
      return;
    }
    else {
      // Configuration via View UI time. Don't show value selection widget.
      $form['value']['#access'] = FALSE;
    }

    $displays = views_get_applicable_views('entityreference display');
    // Filter views that list the entity type we want, and group the separate
    // displays by view.
    $options = array();
    $field_base_table = '';
    if (isset($this->definition['field_name'])) {
      $field_name = $this->definition['field_name'];
      //TODO set $field_base_table to the table of referenced entity.
    }
    foreach ($displays as $data) {
      list($view, $display_name) = $data;
      if ((empty($field_base_table)) || ($view->base_table == $field_base_table)) {
        $options[$view->name . ':' . $display_name] = $view->name . ' - ' . $view->display[$display_name]->display_title;
      }
    }

    $form['reference_display'] = array(
      '#type' => 'select',
      '#title' => t('View used to select the entities'),
      '#required' => TRUE,
      '#options' => $options,
      '#default_value' => $this->options['reference_display'],
      '#description' => '<p>' .
        t('Choose the view and display that select the entities that can be referenced.<br />Only views with a display of type "Entity Reference" are eligible.') . '</p>',
    );

    if (empty($this->options['reference_display'])) {
      $form['reference_display']['#description'] .= '<p>' . t('Entity list will be available after saving this setting.') . '</p>';
    }
  }

  function value_submit($form, &$form_state) {
    $form_state['values']['options']['value'] = NULL;
  }

  function get_value_options() {
    if (isset($this->value_options)) {
      return $this->value_options;
    }
    $this->value_options = $this->get_configured_views_result();
    return $this->value_options;
  }

  function get_configured_views_result() {
    if (empty($this->options['reference_display'])) {
      return array();
    }
    list($view_name, $display_name) = explode(':', $this->options['reference_display']);
    // Check that the view is valid and the display still exists.
    $view = views_get_view($view_name);
    if (!$view || !isset($view->display[$display_name]) || !$view->access($display_name)) {
      watchdog('entityreference', 'The view %view_name is no longer eligible for the filter.', array('%view_name' => $view_name), WATCHDOG_WARNING);
      return array();
    }
    $view->set_display($display_name);
    // Make sure the query is not cached.
    $view->is_cacheable = FALSE;
    $view->set_items_per_page(0);
    // Make the display render the result as array.
    $view->display_handler->set_option('entityreference_options', array('limit' => 0));
    $result = $view->execute_display($display_name, $this->view->args);
    if ($result) {
      return $result;
    }
    return array();
  }

  function query() {
    // Recalculate values if the filter is not exposed.
    if (empty($this->options['exposed'])) {
      $this->value = array_keys($this->get_configured_views_result());
      if (empty($this->value)) {
        // If the result is empty, add zero value item to ensure SQL validity.
        $this->value = array(0);
      }
    }
    parent::query();
  }

}
