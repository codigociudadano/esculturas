<?php
/**
 * @file
 * esculturas_contexto.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function esculturas_contexto_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
