<?php

/**
 * Implements hook_views_data_alter()
 */
function entityreference_filter_views_data_alter(&$data) {
  foreach ($data as $table_name => $table_info) {
    foreach ($table_info as $field_name => $field_info) {
      // Apply to entity reference and term reference fields only.
      if ((strpos($field_name, '_target_id') === FALSE) && (strpos($field_name, '_tid') === FALSE) && ($field_name !== 'nid') && ($field_name !== 'tid') && ($field_name !== 'uid')) {
        continue;
      }
      if (!empty($field_info['filter']['handler']) && $field_info['filter']['handler'] != 'entityreference_filter_view_result') {
        $filter = $field_info;
        $filter['title'] = (!empty($field_info['filter']['title']) ? $field_info['filter']['title'] : $field_info['title']) . ' (entityreference filter)';
        $filter['filter']['handler'] = 'entityreference_filter_view_result';
        $filter['filter']['proxy'] = $field_info['filter']['handler'];
        $filter['filter']['field'] = $field_name;
        unset($filter['argument'], $filter['field'], $filter['relationship'], $filter['sort'], $filter['filter']['title']);
        $data[$table_name][$field_name . '_entityreference_filter'] = $filter;
      }
    }
  }
}
