<?php

/**
 * Define la firma de los recursos disponibles para nodos.
 * 
 * Para mayor informacion de que singifica cada setting de la definicion de la resource 
 * ver la documentacion de la API de Services v3.x :
 * @url: https://drupal.org/node/783724
 * 
 * @return array
 */
function ew_node_resource_definition() {
  
  return array(
    'ew_node' => array(
      'operations' => array(
        'retrieve' => array(
          'help' => 'Retrieve a node',
          'file' => array(
              'type' => 'inc', 
              'module' => 'esculturas_webservices', 
              'name' => 'resources/node_resource'),
          'callback' => '_ew_node_resource_retrieve',
          'args' => array(
            array(
              'name' => 'nid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'int',
              'description' => 'The nid of the node to retrieve',
            ),
          ),          
          'access arguments' => array('view'),          
        ),
        'create' => array(
          'help' => 'Create a node',
          'file' => array(
            'type' => 'inc', 
            'module' => 'esculturas_webservices', 
            'name' => 'resources/node_resource'),
          'callback' => '_ew_node_resource_create',
          'args' => array(
            array(
              'name' => 'node',
              'optional' => FALSE,
              'source' => 'data',
              'description' => 'The node data to create',
              'type' => 'array',
            ),
          ),          
          'access arguments' => array('create'),          
        ),
        'update' => array(
          'help' => 'Update a node',
          'file' => array(
            'type' => 'inc', 
            'module' => 'esculturas_webservices', 
            'name' => 'resources/node_resource'),
          'callback' => '_ew_node_resource_update',
          'args' => array(
            array(
              'name' => 'nid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'int',
              'description' => 'The nid of the node to update',
            ),
            array(
              'name' => 'node',
              'optional' => FALSE,
              'source' => 'data',
              'description' => 'The node data to update',
              'type' => 'array',
            ),
          ),          
          'access arguments' => array('update'),
        ),
        'delete' => array(
          'help' => t('Delete a node'),
          'file' => array(
            'type' => 'inc', 
            'module' => 'esculturas_webservices', 
            'name' => 'resources/node_resource'),
          'callback' => '_ew_node_resource_delete',
          'args' => array(
            array(
              'name' => 'nid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'int',
              'description' => 'The nid of the node to delete',
            ),
          ),
          'access arguments' => array('delete'),
        ),
        'index' => array(
          'help' => 'List all nodes',
          'file' => array(
            'type' => 'inc', 
            'module' => 'escultura_webservices', 
            'name' => 'resources/node_resource'),
          'callback' => '_ew_node_resource_index',
          'args' => array(
            array(
              'name' => 'page',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'The zero-based index of the page to get, defaults to 0.',
              'default value' => 0,
              'source' => array('param' => 'page'),
            ),
            array(
              'name' => 'fields',
              'optional' => TRUE,
              'type' => 'string',
              'description' => 'The fields to get.',
              'default value' => '*',
              'source' => array('param' => 'fields'),
            ),
            array(
              'name' => 'parameters',
              'optional' => TRUE,
              'type' => 'array',
              'description' => 'Parameters array',
              'default value' => array(),
              'source' => array('param' => 'parameters'),
            ),
            array(
              'name' => 'pagesize',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'Number of records to get per page.',
              'default value' => variable_get('services_node_index_page_size', 20),
              'source' => array('param' => 'pagesize'),
            ),
          ),
          'access arguments' => array('access content'),
        ),
      ),      
    ),
  );  
  
}

/**
 * Funcion decoy para reusarla en lo que se necesite.
 */
function _ew_node_resource_retrieve() {
  return array('mensaje' => 'Sumbundrule!');
  
}