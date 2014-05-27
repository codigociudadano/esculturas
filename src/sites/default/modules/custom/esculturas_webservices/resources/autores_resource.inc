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
function ew_autores_resource_definition() {
  return array(
    'autores' => array(
      'operations' => array(
        'retrieve' => array(
          'help' => 'Obtener un autor.',
          'file' => array(
              'type' => 'inc',
              'module' => 'esculturas_webservices',
              'name' => 'resources/autores_resource'),
          'callback' => '_ew_autores_resource_retrieve',
          'args' => array(
            array(
              'name' => 'id',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'int',
              'description' => 'Id del autor a obtener.',
            ),
            array(
              'name' => 'esculturas',
              'optional' => TRUE,
              'type' => 'boolean',
              'description' => 'Inculir listado de esculturas del autor.',
              'default value' => FALSE,
              'source' => array('param' => 'esculturas'),
            ),
          ),
          'access callback' => '_node_resource_access',
          'access arguments' => array('view'),
          'access arguments append' => TRUE,
        ),
        'index' => array(
          'help' => 'Listar Autores.',
          'file' => array(
            'type' => 'inc',
            'module' => 'esculturas_webservices',
            'name' => 'resources/autores_resource'),
          'callback' => '_ew_autores_resource_index',
          'args' => array(
            array(
              'name' => 'page',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'Numero de pagina.',
              // 'default value' => 0,
              'source' => array('param' => 'page'),
            ),
            array(
              'name' => 'pagesize',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'Numero de elementos por pagina.',
              // 'default value' => 20,
              'source' => array('param' => 'pagesize'),
            ),
          ),
          'access arguments' => array('access content'),
        ),
      ),
    ),
  );

}

define("EW_AUTORES_DEFAULT_PAGE", 0);
define("EW_AUTORES_MAX_PAGESIZE", 100);
define("EW_AUTORES_DEFAULT_PAGESIZE", 20);

/**
 *
 *
 * @param string $page | numero de pagina a obtener.
 * @param string $pagesize | cantidad de resultados por pagina a obtener.
 * @return array
 */
function _ew_autores_resource_index($page, $pagesize) {

  $page_val = isset($page)?$page:EW_AUTORES_DEFAULT_PAGE;
  $pagesize_val = isset($pagesize)?$pagesize:EW_AUTORES_DEFAULT_PAGESIZE;

  if($pagesize_val > EW_AUTORES_MAX_PAGESIZE) {
    return services_error("pagesize should not be greater than ".EW_AUTORES_MAX_PAGESIZE);
  }

  $query = db_select("node", "n")
              ->fields("n", array("nid"))
              ->condition("n.status", "1")
              ->condition("n.type", "autores");

  $count = $query->countQuery()->execute()->fetchField();
  $max_pages = ceil($count/$pagesize_val) - 1;

  if($pagesize_val > EW_AUTORES_MAX_PAGESIZE) {
    return services_error("pagesize should not be greater than ".EW_AUTORES_MAX_PAGESIZE);
  }

  if($page_val > $max_pages) {
    return services_error("Page ".$page_val." is out of range. (Total Pages: ".$max_pages.")");
  }

  $result = $query->range($page_val*$pagesize_val, $pagesize_val)->execute();

  $response = array();

  $response["href"] = ew_get_href(array(
    "entity" => "autores",
    "page" => $page,
    "pagesize" => $pagesize
  ));

  if($page_val > 0 ) {
    $response["prev"] = ew_get_href(array(
      "entity"=>"autores",
      "page"=>$page_val-1,
      "pagesize"=>$pagesize
    ));
  }

  if($page_val < $max_pages) {
    $response["next"] = ew_get_href(array(
      "entity"=>"autores",
      "page"=>$page_val+1,
      "pagesize"=>$pagesize
    ));
  }

  $response["max_pages"] = $max_pages;

  $response["data"] = array();

  if ($result) {

    while ($row = $result->fetchObject()) {
      //Init response
      $resource = new stdClass();
      //Open Node Base Info
      $node = node_load($row->nid);
      // Pictures Info
      $fotos = field_get_items('node', $node, 'field_fotos');

      // Fill resource info
      $resource->id = $row->nid;

      $resource->href = ew_get_href(array(
        "entity"=> "autores",
        "id"=> $resource->id
      ));

      $resource->name = $node->title;

      if(isset($fotos[0])){
        $resource->image = file_create_url($fotos[0]['uri']);
      }
      else {
        global $base_url;
        $resource->image = $base_url."/".drupal_get_path("theme", "esculturas")."/images/default.png";
      }

      $response["data"][] = $resource;
    }
  }

  /**
   * @todo: Add Caching.
   */

  return $response;
}

/**
 *
 *
 * @param string $id | Id de la autor a obtener.
 * @return array
 */
function _ew_autores_resource_retrieve($id, $esculturas) {
  $query = db_select("node", "n")
             ->fields("n", array("nid"))
             ->condition("n.nid", $id)
             ->condition("n.status", 1)
             ->condition("n.type", "autores");

  ## TODO: Add Caching.

  $result = $query->execute()->fetchObject();

  $response = array();

  $response["href"] = ew_get_href(array(
    "entity"=>"autores",
    "id"=>$id
  ));

  if ($result) {
    $node = node_load($result->nid);
    $response["data"] = $node;

    if($esculturas) {
      $response["esculturas"] = _ew_esculturas_resource_index(0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, $node->nid, NULL, TRUE);
    }
  }
  else {
    $response = services_error(t("Recurso con id:".$id." no encontrado."), 404);
  }

  return $response;
}
