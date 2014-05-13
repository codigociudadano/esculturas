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
function ew_esculturas_resource_definition() {
  return array(
    'esculturas' => array(
      'operations' => array(
        'retrieve' => array(
          'help' => 'Obtener una escultura.',
          'file' => array(
              'type' => 'inc',
              'module' => 'esculturas_webservices',
              'name' => 'resources/esculturas_resource'),
          'callback' => '_ew_esculturas_resource_retrieve',
          'args' => array(
            array(
              'name' => 'id',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'int',
              'description' => 'Id de la escultura a obtener.',
            ),
          ),
          'access callback' => '_node_resource_access',
          'access arguments' => array('view'),
          'access arguments append' => TRUE,
        ),
        'index' => array(
          'help' => 'Listar Esculturas.',
          'file' => array(
            'type' => 'inc',
            'module' => 'esculturas_webservices',
            'name' => 'resources/esculturas_resource'),
          'callback' => '_ew_esculturas_resource_index',
          'args' => array(
            array(
              'name' => 'page',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'Numero de pagina.',
              'default value' => 0,
              'source' => array('param' => 'page'),
            ),
            array(
              'name' => 'pagesize',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'Numero de elementos por pagina.',
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

define("MAX_PAGESIZE", 100);

/**
 *
 *
 * @param string $page | numero de pagina a obtener.
 * @param string $pagesize | cantidad de resultados por pagina a obtener.
 * @return array
 */
function _ew_esculturas_resource_index($page = '0' ,$pagesize = '5') {
  $query = "SELECT n.nid AS id,
              n.title AS title
            FROM {node} n
            WHERE ((n.status = '1') AND (n.type IN  ('escultura')))";

  if($pagesize > MAX_PAGESIZE) {
    return services_error("pagesize should not be greater than ".MAX_PAGESIZE);
  }

  $result = db_query_range($query, $page, $pagesize, array());

  $response = array();
  if ($result) {
    while ($row = $result->fetchObject()) {
      $resource = new stdClass();
      //Open Node Base Info
      $node = node_load($row->id);
      // Author Info
      $autor_field = field_get_items('node', $node, 'field_autor');
      $autor = node_load($autor_field[0]["target_id"]);
      // Pictures Info
      $fotos = field_get_items('node', $node, 'field_fotos');
      //Tags Info
      $tags_field = field_get_items('node', $node, 'field_tags');
      foreach ($tags_field as $tag) {
        $tags_tids[] = $tag["tid"];
      }
      $tags_terms = taxonomy_term_load_multiple($tags_tids);
      $tags = array();
      foreach ($tags_terms as $tag_term) {
        $tag = new stdClass();
        $tag->id = $tag_term->tid;
        $tag->href = "/api/v1/esculturas/esculturas/tag/".$tag_term->tid;
        $tag->name = $tag_term->name;
        $tags[] = $tag;
      }

      // Fill resource info
      $resource->id = $row->id;
      $resource->href = "/api/v1/esculturas/esculturas/".$resource->id;
      $resource->name = $row->title;
      $resource->image = file_create_url($fotos[0]['uri']);
      $resource->autor = array(
        "id" => $autor->nid,
        "href" => "/api/v1/esculturas/autores/".$autor->nid,
        "name" => $autor->title
      );
      $resource->tags = $tags;

      $response[] = $resource;
    }
  }

  ## TODO: Add Caching.

  return $response;
}

/**
 *
 *
 * @param string $id | Id de la escultura a obtener.
 * @return array
 */
function _ew_esculturas_resource_retrieve($id) {
  $query = "SELECT n.nid AS id,
              n.title AS name
            FROM {node} n
            WHERE (n.nid = :id)
              AND ((n.status = '1')
              AND (n.type IN  ('escultura')))";

  ## TODO: Add Caching.

  $result = db_query($query, array(
      'id' => $id
  ))->fetchObject();

  if ($result) {
    $response = $result;
    ## TODO: Add more fields.
  }
  else {
    $response = services_error(t("Recurso con id:".$id." no encontrado."), 404);
  }

  return $response;
}
