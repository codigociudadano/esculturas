<?php


function esculturas_mapa_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'location') . '/handlers',
    ),
    'handlers' => array(
      'location_handler_argument_location_proximity' => array(
        'parent' => 'views_handler_argument',
      ),
    ),
  );
}

function esculturas_mapa_views_data() {
  $data['field_mapa']['table']['group']  = t('Google Map Field');
  $data['field_mapa']['table']['join'] = array(
    'field_data_field_mapa' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  $data['field_mapa']['bid'] = array(
    'title' => t('Field mapa'),
    'help' => t('The field mapa table.'),
    'relationship' => array(
      'base' => 'node',
      'handler' => 'views_handler_relationship',
      'label' => t('field mapa'),
    ),
  );
  
  
  
  
//  $data['field_mapa']['distance'] = array(
//    'group' => t('Field mapa'),
//    'title' => t('Distance / Proximity'),
//    'help' => t("The distance from the selected location and either the current user or a specific location."),
//    'relationship' => array(
//      'handler' => 'views_handler_relationship',
//      'base' => 'field_data_field_mapa ',
//      'base field' => 'entity_id',
//      'label' => t('Get the actual distance from a content revision.'),
//      'group' => t('Field mapa'),
//      'title' => t('Field mapa distance'),
//    ),
//    'argument' => array(
//      'handler' => 'location_handler_argument_location_proximity',
//    ),
//  );
  return $data;
}