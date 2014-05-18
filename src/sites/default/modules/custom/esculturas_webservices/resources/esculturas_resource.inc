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
          'documentation callback' => '_ew_esculturas_retrieve_doc',
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
          'documentation callback' => '_ew_esculturas_index_doc',
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

define("EW_ESCULTURAS_DEFAULT_PAGE", 0);
define("EW_ESCULTURAS_MAX_PAGESIZE", 100);
define("EW_ESCULTURAS_DEFAULT_PAGESIZE", 20);

/**
 *
 *
 * @param string $page | numero de pagina a obtener.
 * @param string $pagesize | cantidad de resultados por pagina a obtener.
 * @return array
 */
function _ew_esculturas_resource_index($page, $pagesize) {

  $page_val = isset($page)?$page:EW_ESCULTURAS_DEFAULT_PAGE;
  $pagesize_val = isset($pagesize)?$pagesize:EW_ESCULTURAS_DEFAULT_PAGESIZE;

  if($pagesize_val > EW_ESCULTURAS_MAX_PAGESIZE) {
    return services_error("pagesize should not be greater than ".EW_ESCULTURAS_MAX_PAGESIZE);
  }

  $query = db_select("node", "n")
              ->fields("n", array("nid"))
              ->condition("n.status", "1")
              ->condition("n.type", "escultura");

  $count = $query->countQuery()->execute()->fetchField();
  $max_pages = ceil($count/$pagesize_val) - 1;

  if($pagesize_val > EW_ESCULTURAS_MAX_PAGESIZE) {
    return services_error("pagesize should not be greater than ".EW_ESCULTURAS_MAX_PAGESIZE);
  }

  if($page_val > $max_pages) {
    return services_error("Page ".$page_val." is out of range. (Total Pages: ".$max_pages.")");
  }

  $result = $query->range($page_val*$pagesize_val, $pagesize_val)->execute();

  $response = array();

  $response["href"] = ew_get_href(array(
    "entity" => "esculturas",
    "page" => $page,
    "pagesize" => $pagesize
  ));

  if($page_val > 0 ) {
    $response["prev"] = ew_get_href(array(
      "entity"=>"esculturas",
      "page"=>$page_val-1,
      "pagesize"=>$pagesize
    ));
  }

  if($page_val < $max_pages) {
    $response["next"] = ew_get_href(array(
      "entity"=>"esculturas",
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

        $tag->href = ew_get_href(array(
          "entity" => "esculturas",
          "filters"=> array("tags"=>$tag_term->tid)
        ));

        $tag->name = $tag_term->name;
        $tags[] = $tag;
      }

      // Fill resource info
      $resource->id = $row->nid;

      $resource->href = ew_get_href(array(
        "entity"=> "esculturas",
        "id"=> $resource->id
      ));

      $resource->name = $node->title;

      $resource->image = file_create_url($fotos[0]['uri']);

      $resource->autor = array(
        "id" => $autor->nid,
        "href" => ew_get_href(array(
          "entity"=> "autores",
          "id"=> $autor->nid
        )),
        "name" => $autor->title
      );

      $resource->tags = $tags;

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

  $response = array(
    "href"=> ew_get_href(array(
      "entity"=>"esculturas",
      "id"=>$id
    ))
  );

  if ($result) {
    $response["data"] = $result;
    ## TODO: Add more fields.
  }
  else {
    $response = services_error(t("Recurso con id:".$id." no encontrado."), 404);
  }

  return $response;
}

/**
 * Documentacion de calback para operacion de retrieve.
 */
function _ew_esculturas_retrieve_doc() {
  $element = array(
    '#name' => t('Obtener escultura'),
    '#description' => t('Retorna la escultura segun Id pasado como parametro.'),
    '#request_url' => t('esculturas?id=11'),
    '#response' => '
      id: "11",
      href: "http://esculturas.local/api/v1/esculturas/11",
      name: "Uxor",
      image: "http://esculturas.local/sites/default/files/esculturas/imagefield_LvvddA.png",
      autor: {
        id: "16",
        href: "http://esculturas.local/api/v1/autores",
        name: "Diam Erat"
      },
      tags: [
        {
          id: "10",
          href: "http://esculturas.local/api/v1/esculturas?tags=10",
          name: "Humanidad"
        }
      ]',
    '#path' => 'esculturas',       
  );
  return $element;
}

/**
 * Documentacion de calback para operacion de retrieve.
 */
function _ew_esculturas_index_doc() {
  $element = array(
    '#name' => t('Obtener esculturas'),
    '#description' => t('Retorna la esculturas por pagina. El tamaño de la pagina es customizable.'),    
    '#request_url' => t('esculturas?page=1&pagesize=12'),    
    '#response' => '
      {
      id: "11",
      href: "http://esculturas.local/api/v1/esculturas/11",
      name: "Uxor",
      image: "http://esculturas.local/sites/default/files/esculturas/imagefield_LvvddA.png",
      autor: {
        id: "16",
        href: "http://esculturas.local/api/v1/autores",
        name: "Diam Erat"
      },
      tags: [
        {
          id: "10",
          href: "http://esculturas.local/api/v1/esculturas?tags=10",
          name: "Humanidad"
        }
      ]
      },
      {
      id: "11",
      href: "http://esculturas.local/api/v1/esculturas/11",
      name: "Uxor",
      image: "http://esculturas.local/sites/default/files/esculturas/imagefield_LvvddA.png",
      autor: {
        id: "16",
        href: "http://esculturas.local/api/v1/autores",
        name: "Diam Erat"
      },
      tags: [
        {
          id: "10",
          href: "http://esculturas.local/api/v1/esculturas?tags=10",
          name: "Humanidad"
        }
      ]
      }',
    '#path' => 'esculturas',       
  );
  return $element;
}
