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
            array(
              'name' => 'material',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'Filtro, material de la escultura.',
              // 'default value' => 20,
              'source' => array('param' => 'material'),
            ),
            array(
              'name' => 'tipo',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'Filtro, tipo de escultura.',
              // 'default value' => 20,
              'source' => array('param' => 'tipo'),
            ),
            array(
              'name' => 'lat',
              'optional' => TRUE,
              'type' => 'string',
              'description' => 'Filtro, geolocalizacion de la escultura.',
              // 'default value' => 20,
              'source' => array('param' => 'lat'),
            ),
            array(
              'name' => 'long',
              'optional' => TRUE,
              'type' => 'string',
              'description' => 'Filtro, geolocalizacion de la escultura.',
              // 'default value' => 20,
              'source' => array('param' => 'long'),
            ),
            array(
              'name' => 'dist',
              'optional' => TRUE,
              'type' => 'string',
              'description' => 'Filtro, geolocalizacion de la escultura, rango de distancia del punto proveido por lat y long (en metros).',
              'default value' => 100,
              'source' => array('param' => 'dist'),
            ),
            array(
              'name' => 'tag',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'Filtro, Taxonomia asignada a las esculturas.',
              // 'default value' => 20,
              'source' => array('param' => 'tag'),
            ),
            array(
              'name' => 'autor',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'Filtro, Autor de esculturas.',
              // 'default value' => 20,
              'source' => array('param' => 'autor'),
            ),
            array(
              'name' => 'evento',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'Numero de elementos por pagina.',
              // 'default value' => 20,
              'source' => array('param' => 'evento'),
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
define("EW_ESCULTURAS_DISTANCE_CONVERSION", 1/1000);
define("EW_ESCULTURAS_DISTANCE_REVERSE", 1000);

/**
 *
 *
 * @param string $page | numero de pagina a obtener.
 * @param string $pagesize | cantidad de resultados por pagina a obtener.
 * @return array
 */
function _ew_esculturas_resource_index($page, $pagesize, $material, $tipo, $lat, $long, $dist, $tag, $autor, $evento) {

  $page_val = isset($page)?$page:EW_ESCULTURAS_DEFAULT_PAGE;
  $pagesize_val = isset($pagesize)?$pagesize:EW_ESCULTURAS_DEFAULT_PAGESIZE;
  $filters = array();

  if($pagesize_val > EW_ESCULTURAS_MAX_PAGESIZE) {
    return services_error("pagesize should not be greater than ".EW_ESCULTURAS_MAX_PAGESIZE);
  }

  $query = db_select("node", "n")
              ->distinct(TRUE)
              ->fields("n", array("nid"))
              ->condition("n.status", "1")
              ->condition("n.type", "escultura");

   if(isset($material)) {
     $query->leftJoin("field_data_field_material", "fdfm", "(n.nid = fdfm.entity_id)");
     $query->condition("fdfm.field_material_tid", $material);
     $filters["material"]=$material;
   }

   if(isset($tipo)) {
     $query->leftJoin("field_data_field_tipo", "fdft", "(n.nid = fdft.entity_id)");
     $query->condition("fdft.field_tipo_tid", $tipo);
     $filters["tipo"]=$tipo;
   }

   if(isset($tag)) {
     $query->leftJoin("field_data_field_tags", "fdftg", "(n.nid = fdftg.entity_id)");
     $query->condition("fdftg.field_tags_tid", $tag);
     $filters["tag"]=$tag;
   }

   if(isset($autor)) {
     $query->leftJoin("field_data_field_autor", "fdfa", "(n.nid = fdfa.entity_id)");
     $query->condition("fdfa.field_autor_target_id", $autor);
     $filters["autor"]=$autor;
   }

   if(isset($evento)) {
     $query->leftJoin("field_data_field_evento", "fdfe", "(n.nid = fdfe.entity_id)");
     $query->condition("fdfe.field_evento_tid", $evento);
     $filters["evento"]=$evento;
   }

   if(isset($lat) || isset($long)) {
     if(!isset($lat) || !isset($long)) {
       return services_error("lat and long should be defined togheter.");
     }

     // From MTs to KMs.
     $dist_convert = $dist * EW_ESCULTURAS_DISTANCE_CONVERSION;

     $query->leftJoin("field_data_field_mapa", "fdfmp", "(n.nid = fdfmp.entity_id)");
     $query->addExpression("
       (  6371 * acos( cos( radians( :lat ))
               * cos( radians( fdfmp.field_mapa_lat ) )
               * cos( radians( fdfmp.field_mapa_lon )
         - radians( :long ) )
         + sin(radians( :lat ) )
               * sin(radians( fdfmp.field_mapa_lat ) ) ) )", "distance", array(":lat"=>$lat,":long"=>$long));
    $query->havingCondition("distance", $dist_convert, "<");
    $query->havingCondition("distance", 0, ">");
    $query->orderBy("distance", "ASC");

     $filters["lat"]=$lat;
     $filters["long"]=$long;
     $filters["dist"]=$dist;
   }

    // die((string) $query);

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
    "pagesize" => $pagesize,
    "filters"=>$filters
  ));

  if($page_val > 0 ) {
    $response["prev"] = ew_get_href(array(
      "entity"=>"esculturas",
      "page"=>$page_val-1,
      "pagesize"=>$pagesize,
      "filters"=>$filters
    ));
  }

  if($page_val < $max_pages) {
    $response["next"] = ew_get_href(array(
      "entity"=>"esculturas",
      "page"=>$page_val+1,
      "pagesize"=>$pagesize,
      "filters"=>$filters
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

      if(isset($row->distance)) {
        $resource->distance = $row->distance * EW_ESCULTURAS_DISTANCE_REVERSE;
      }

      $resource->image = file_create_url($fotos[0]['uri']);

      if(isset($autor) && isset($autor->nid)) {
        $resource->autor = array(
          "id" => $autor->nid,
          "href" => ew_get_href(array(
            "entity"=> "autores",
            "id"=> $autor->nid
          )),
          "name" => $autor->title
        );
      }

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
  $query = db_select("node", "n")
             ->fields("n", array("nid"))
             ->condition("n.nid", $id)
             ->condition("n.status", 1)
             ->condition("n.type", "escultura");

  ## TODO: Add Caching.

  $result = $query->execute()->fetchObject();

  $response = array();

  $response["href"] = ew_get_href(array(
    "entity"=>"esculturas",
    "id"=>$id
  ));

  if ($result) {
    $node = node_load($result->nid);
    $response["data"] = $node;
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
