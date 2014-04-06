<?php
/**
 * @file
 * esculturas_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function esculturas_core_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function esculturas_core_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function esculturas_core_node_info() {
  $items = array(
    'autores' => array(
      'name' => t('Autores'),
      'base' => 'node_content',
      'description' => t('Autores de las Obras'),
      'has_title' => '1',
      'title_label' => t('Nombre'),
      'help' => '',
    ),
    'escultura' => array(
      'name' => t('Escultura'),
      'base' => 'node_content',
      'description' => t('Content Type para Esculturas'),
      'has_title' => '1',
      'title_label' => t('Titulo'),
      'help' => '',
    ),
    'eventos' => array(
      'name' => t('Eventos'),
      'base' => 'node_content',
      'description' => t('Eventos donde se realizaron obras, por ejemplo las bienales.'),
      'has_title' => '1',
      'title_label' => t('Nombre del Evento'),
      'help' => '',
    ),
  );
  return $items;
}
