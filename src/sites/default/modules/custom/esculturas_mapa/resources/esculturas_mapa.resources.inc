<?php

/**
 * @file
 * Este archivo es usado alojar todas las funcionalidades que utilizadas en las 
 * resources de las llamadas en sus correspondientes endpoints.
 */

/**
 * Obtiene los nodos mas cercanos (geográficamente) a traves de las coordenadas 
 * provistas. Se puede customizar el radio en el cual puede buscar y la cantidad 
 * de resultados a obtener.
 * 
 * El calculo de la distancia entre la coordenada provista en el parametro y las 
 * coordenadas de los distintos elementos esta basada en la formula Haversine para 
 * calculos en distancia en Kilometros, mas info en: http://en.wikipedia.org/wiki/Haversine_formula
 * 
 * Se puede encontrar info util en: https://developers.google.com/maps/articles/phpsqlsearch_v3#findnearsql
 * 
 * @param string $latitude
 * @param string $longitude
 * @param string $distance | distancia (en km) del radio donde buscar.
 * @param string $qty_nodes | cantidad de resultados a obtener.
 * @return array
 */
function em_get_closest_nodes_by_coord($latitude, $longitude, $distance = '50', $qty_nodes = '5') {
  
  $query = "SELECT n.nid,
              n.title AS node_title, 
              fm.field_mapa_lat AS node_latitude, 
              fm.field_mapa_lon AS node_longitude,
              ( 6371 * acos( cos( radians( :latitude )) * cos( radians( fm.field_mapa_lat ) ) * cos( radians( fm.field_mapa_lon ) - radians( :longitude ) ) + sin(radians( :latitude ) ) * sin(radians( fm.field_mapa_lat ) ) ) ) AS distance 
            FROM {node} n
            LEFT JOIN {field_data_field_mapa} fm ON n.nid = fm.entity_id 
              AND (fm.entity_type = 'node' AND fm.deleted = '0')
            WHERE ((n.status = '1') AND (n.type IN  ('escultura'))) 
            HAVING distance < :distance AND (distance > 0)
            ORDER BY distance ASC";  

  $result = db_query_range($query, 0, $qty_nodes, array(
    ':latitude' => $latitude,
    ':longitude' => $longitude,
    ':distance' => $distance,
  ));
  
  $response = array();
  if ($result) {
    while ($row = $result->fetchObject()) {
      $response[] = $row;
    }    
  }
  return $response;
}