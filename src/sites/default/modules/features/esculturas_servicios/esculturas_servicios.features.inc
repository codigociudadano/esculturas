<?php
/**
 * @file
 * esculturas_servicios.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function esculturas_servicios_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}
