<?php

function urunday_import_drush_command() {
    $items['urunday-import-sculpture'] = array(
        'description' => "Import content from urunday.",
        'options' => array(
        ),
        'aliases' => array('uis'),
    );
    $items['urunday-import-clean'] = array(
        'description' => "deletes content.",
        'options' => array(
        ),
        'aliases' => array('uic'),
    );
    return $items;
}

function drush_urunday_import_clean() {
    $count =0;
    $result = db_query("SELECT n.nid FROM {node} n WHERE n.type = :type",
        array('type' => 'escultura')
    );

    while($nid = $result->fetchAssoc()) {
        node_delete($nid['nid']);
        $count++;
    }

    echo "Deleted $count esculturas\n";

}

function drush_urunday_import_sculpture() {
    $totals = array();

    if (($handle = fopen(dirname(__FILE__) . "/data/data.csv", "r")) === FALSE) {
        echo "Cant open file";
        return;
    }

    while (($data = fgetcsv($handle, 1000, "|", '"')) !== FALSE) {
        try {

            if (!empty($data)) {
                $coords = FALSE;
                if (!empty($data[8])) {
                    $parts = explode(',', $data[8]);
                    $coords = array('lat' => $parts[0], 'lon' => $parts[1]);
                }

                $detail = array(
                  'titulo' => $data[1],
                  'autor' => $data[3],
                  'fecha' => $data[2],
                  'nacionalidad' => $data[4],
                  'material' => $data[5],
                  'tipo' => 'Desconocido',
                  'foto' => $data[6],
                  'direccion' => $data[7],
                  'coordenadas' => $coords,
                  'otros' => $data[9] . '<br />' . $data[10] . '<br />' . $data[11] . '<br />',
                );
                urunday_import_create_sculpture($detail);
                echo "Imported\n";
                $totals[0]++;
            } else {
                echo "This looks empty\n";
                $totals[1]++;
            }
        } catch(Exception $e) {
            echo "This failed{$e->getMessage()}\n";
            $totals[1]++;
        }
    }
    echo "Imported " . $totals[0] . "\n";
    echo "Failed " . $totals[1] . "\n";
}

function urunday_import_create_sculpture($detail) {

    $node = urunday_import_load_node_by_title($detail['titulo'], 'escultura');

    if (!$node) {
        $node = new stdClass;
        $node->type = 'escultura';
        $node->created = time();
        $node->changed = time();
        $node->timestamp = time();
        $node->body['und'][0]['format'] = 'full_html';
        $node->status = 1;
        $node->promote = 1;
        $node->sticky = 0;
        $node->revision = 0;
        $node->language = LANGUAGE_NONE;
        $node->body['und'][0]['value'] = "";
    }

    $node->title = $detail['titulo'];

    $author = urunday_import_create_author($detail);
    if (!empty($author->nid)) {
        $node->field_autor['und'][0]['target_id'] = $author->nid;
        $node->field_autor['und'][0]['entity'] = $author;
    }

    $material = urunday_import_taxonomy_find_or_create($detail['material'], 'material');
    if (!empty($material->tid)) {
        $node->field_material['und'][0]['tid'] = $material->tid;
    }

    $tipo = urunday_import_taxonomy_find_or_create($detail['tipo'], 'tipo');
    if (!empty($tipo->tid)) {
        $node->field_tipo['und'][0]['tid'] = $tipo->tid;
    }

    $date_parts = explode('-', $detail['fecha']);
    if (!empty($date_parts[2])) {
        $year = $date_parts[2];
        $node->field_ano['und'][0]['value'] = $year;
    }

    $node->field_ubicacion['und'][0]['value'] = $detail['direccion'];
    if (empty($detail['coordenadas'])) {
        $node->field_mapa['und'][0] = urunday_import_get_coords($detail['direccion']);
    } else {
        $node_map = array(
            'lat' => $detail['coordenadas']['lat'],
            'lon' => $detail['coordenadas']['lon'],
            'map_width' => null,
            'map_height' => null,
            'zoom' => 17,
            'name' => '',
        );

        $node->field_mapa['und'][0] = $node_map;
    }

    $body = $detail['otros'];

    $node->body['und'][0]['value'] .= $body;
    $node->body['und'][0]['value'] .= "<br/> Fuente : Fundación Urunday";

    //Image
    if ($detail['foto']) {
        $foto_path =  dirname(__FILE__) . '/data/fotos/' . $detail['foto'];
        if (file_exists($foto_path)) {
            $file = new StdClass();
            $file->uid = 1;
            $file->uri = $foto_path;
            $file->filemime = file_get_mimetype($file->uri);
            $file->status = 1;
            $dest = file_default_scheme() . '://' . time() . '.jpg'; // Subdirectory name within files
            $file = file_copy($file, $dest);
            $node->field_fotos['und'][0] = (array) $file;
        }
    }

    node_submit($node);
    node_save($node);
}

function urunday_import_create_author($detail) {

    $nodeExists = urunday_import_load_node_by_title($detail['autor'], 'autores');

    if ($nodeExists) {
        return $nodeExists; //Node Already Exists
    }

    $node = new stdClass;
    $node->type = 'autores';
    $node->created = time();
    $node->changed = time();
    $node->timestamp = time();
    $node->body['und'][0]['format'] = 'full_html';
    $node->status = 1;
    $node->promote = 1;
    $node->sticky = 0;
    $node->revision = 0;
    $node->language = LANGUAGE_NONE;

    $node->title = $detail['autor'];

    $terms = taxonomy_get_term_by_name($detail['nacionalidad'], 'nacionalidad');
    if (empty($terms)) {
        $vocabulary = urunday_import_get_vocabulary_by_name('nacionalidad');
        $term = new stdClass();
        $term->name = $detail[1];
        $term->vid = $vocabulary->vid;
        taxonomy_term_save($term);
    } else {
        $term = array_shift($terms);
    }

    $body = 'Sin Datos';

    $node->body['und'][0]['value']  = $body;

    if (!empty($term->tid)) {
        $node->field_nacionalidad['und'][0]['tid'] = $term->tid;
    }

    node_submit($node);
    node_save($node);
    return $node;
}

function urunday_import_get_vocabulary_by_name($machine_name) {
    $vocabularies = taxonomy_get_vocabularies();
    foreach($vocabularies as $vocabulary) {
        if ($vocabulary->machine_name == $machine_name) {
            return $vocabulary;
        }
    }
    return false;
}

function urunday_import_taxonomy_find_or_create($term, $vocabulary) {
    $terms = taxonomy_get_term_by_name($term, $vocabulary);
    if (empty($terms)) {
        $vocabulary = urunday_import_get_vocabulary_by_name($vocabulary);
        $t = new stdClass();
        $t->name = $term;
        $t->vid = $vocabulary->vid;
        taxonomy_term_save($t);
    } else {
        $t = array_shift($terms);
    }
    return $t;
}

function urunday_import_load_node_by_title($title, $type) {
    $result = db_query("SELECT n.nid FROM {node} n WHERE n.title like :title AND n.type = :type",
        array('title' => '%' . $title . '%',
              'type' => $type)
    );

    if ($nid = $result->fetchAssoc()) {
        return node_load($nid['nid']);
    }

    return false;
}

function urunday_import_get_coords($address) {
    $node_map = array(
        'lat' => '0',
        'lon' => '0',
        'map_width' => null,
        'map_height' => null,
        'zoom' => 17,
        'name' => '',
    );

    $requester = new Requester();
    $dir = urlencode($address . " Resistencia Chaco Argentina");
    $result = $requester->get("http://maps.google.com/maps/api/geocode/json?address=$dir&sensor=false");
    if ($result) {
        $coords = json_decode($result);
        if (!empty($coords->results[0]->geometry->location->lat)) {
            $node_map['lat'] = $coords->results[0]->geometry->location->lat;
        }
        if (!empty($coords->results[0]->geometry->location->lng)) {
            $node_map['lon'] = $coords->results[0]->geometry->location->lng;
        }
    }

    return $node_map;
}