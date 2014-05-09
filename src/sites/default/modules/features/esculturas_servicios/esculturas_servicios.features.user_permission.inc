<?php
/**
 * @file
 * esculturas_servicios.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function esculturas_servicios_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'em get closest nodes by coord'.
  $permissions['em get closest nodes by coord'] = array(
    'name' => 'em get closest nodes by coord',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'esculturas_webservices',
  );

  return $permissions;
}
