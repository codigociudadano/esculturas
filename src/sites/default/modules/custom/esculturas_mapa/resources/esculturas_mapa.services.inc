<?php

/**
 * @file
 *  Provee las configuraciones de los endpoints del webservice REST para todo 
 * lo relacionado al mapa de esculturas.
 */

/**
 * Implements hook_services_resources().
 */
function esculturas_mapa_services_resources() {
  $resources = array(
    'closest_nodes_by_coord' => array(
      'operations' => array(
        'index' => array(
          'help' => t('Get a list of closest nodes given position coordenates (lat, long).'),
          'file' => array(
            'type' => 'inc',
            'module' => 'esculturas_mapa',
            'name' => 'resources/esculturas_mapa.resources',
          ),
          'callback' => 'em_get_closest_nodes_by_coord',
          'access arguments' => array('em get closest nodes by coord'),
          'args' => array(
            array(
              'name' => 'lat',
              'optional' => FALSE,
              'type' => 'string',
              'description' => t('The latitude of the coordinate.'),
              'source' => array('param' => 'lat'),
            ),
            array(
              'name' => 'lon',
              'optional' => FALSE,
              'type' => 'string',
              'description' => t('The langitude of the coordinate.'),
              'source' => array('param' => 'lon'),
            ),
            array(
              'name' => 'dist',
              'optional' => TRUE,
              'type' => 'string',
              'description' => t('The distance to search the nodes.'),
              'default value' => '50',
              'source' => array('param' => 'dist'),
            ),
            array(
              'name' => 'qty_nodes',
              'optional' => TRUE,
              'type' => 'string',
              'description' => t('Quantity of nodes to return in result.'),
              'default value' => '5',
              'source' => array('param' => 'qty_nodes'),
            ),
          ),
        ),
      ),
    ),
  );
  return $resources;
}
