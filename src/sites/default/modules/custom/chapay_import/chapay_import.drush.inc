<?php

require_once 'Requester.php';

function chapay_import_drush_command() {
    $items['chapay-import-author'] = array(
        'description' => "Import content from chapay.",
        'options' => array(
        ),
        'aliases' => array('import-authors'),
    );
    $items['chapay-import-sculpture'] = array(
        'description' => "Import content from chapay.",
        'options' => array(
        ),
        'aliases' => array('import-sculpture'),
    );
    $items['chapay-import-clean'] = array(
        'description' => "deletes content.",
        'options' => array(
        ),
        'aliases' => array('import-clean'),
    );
    return $items;
}

function drush_chapay_import_clean() {
    $result = db_query("SELECT n.nid FROM {node} n WHERE n.type = :type",
        array('type' => 'autores')
    );

    $count = 0;
    while($nid = $result->fetchAssoc()) {
        node_delete($nid['nid']);
        $count++;
    }

    echo "Deleted $count autores\n";

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

function drush_chapay_import_author() {
    $totals = array(0, 0);
    for ($i = 1; $i < 250; $i++) {

        if (in_array($i, array(71, 109, 146, 205))) {
            continue; //Fails in these ids and takes a long time to get the error so we will skip these ids.
        }

        $url = "http://www.chapay.com.ar/?Seccion=autor&Id=" . $i;
        try {
            $xpath = chapay_import_get_xpath($url);
            if ($xpath) {
                $detail = chapay_import_get_table($xpath, '//*[@id="detalle"]');
                $imagen = chapay_import_get_attribute($xpath, 'src',  '//*[@id="detalle"]//*[@class="img"]//img');
                if (!empty($detail)) {
                    if (count($detail) == 1) {
                        if ($detail[0][0] == 'Apellido, Nombre' && empty($detail[0][1])) {
                            echo "This looks empty $url \n";
                            $totals[1]++;
                            continue;
                        }
                    }
                    chapay_import_create_author($detail, $imagen, $url);
                    echo "Imported $url \n";
                    $totals[0]++;
                } else {
                    echo "This looks empty $url \n";
                    $totals[1]++;
                }
            }
        } catch(Exception $e) {
            echo "This failed $url {$e->getMessage()}\n";
            $totals[1]++;
        }
    }
    echo "Imported " . $totals[0] . "\n";
    echo "Failed " . $totals[1] . "\n";
}

function drush_chapay_import_sculpture() {
    $totals = array(0, 0);
    for ($i = 1; $i < 432; $i++) {
        $url = "http://www.chapay.com.ar/?Seccion=escultura&Id=" . $i;
        try {
            $xpath = chapay_import_get_xpath($url);
            if ($xpath) {
                $detail = chapay_import_get_table($xpath, '//*[@id="detalle"]');
                $imagen = chapay_import_get_attribute($xpath, 'src',  '//*[@id="detalle"]//*[@class="img"]//img');
                if (!empty($detail)) {
                    chapay_import_create_sculpture($detail, $imagen, $url);
                    echo "Imported $url \n";
                    $totals[0]++;
                } else {
                    echo "This looks empty $url \n";
                    $totals[1]++;
                }
            }
        } catch(Exception $e) {
            echo "This failed $url {$e->getMessage()}\n";
            $totals[1]++;
        }
    }
    echo "Imported " . $totals[0] . "\n";
    echo "Failed " . $totals[1] . "\n";
}

function chapay_import_create_sculpture($details, $imagen, $url) {
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
    $body_post_body = '';

    foreach($details as $detail) {
        switch ($detail[0]) {
            case "Nombre":
                $node->title = $detail[1];
                break;
            case "Autor /es":
                $author = chapay_import_load_node_by_title($detail[1], 'autores');
                if (!empty($author->nid)) {
                    $node->field_autor['und'][0]['target_id'] = $author->nid;
                    $node->field_autor['und'][0]['entity'] = $author;
                }
                break;
            case "Material":
                $material = chapay_import_taxonomy_find_or_create($detail[1], 'material');
                if (!empty($material->tid)) {
                    $node->field_material['und'][0]['tid'] = $material->tid;
                }
                break;
            case "Tipo":
                $tipo = chapay_import_taxonomy_find_or_create($detail[1], 'tipo');
                if (!empty($tipo->tid)) {
                    $node->field_tipo['und'][0]['tid'] = $tipo->tid;
                }
                break;
            case "Fecha de inauguración":
                $date_parts = explode('.', $detail[1]);
                if (!empty($date_parts[2])) {
                    $year = $date_parts[2];
                    $node->field_ano['und'][0]['value'] = $year;
                }
                break;
            case "Ubicación":
                $node->field_ubicacion['und'][0]['value'] = $detail[1];
                $node->field_mapa['und'][0] = chapay_import_get_coords($detail[1]);
                break;
            case "Descripción":
                $body = $detail[1];
                break;
            default:
                if (!empty($detail[0]) && !empty($detail[1])) {
                    $body_post_body .= "<br />" . $detail[0] . ' : ' . $detail[1];
                }
        }
    }

    $node->body['und'][0]['value']  = $body . '<br />' . $body_post_body;
    $node->body['und'][0]['value'] .= "<br/> Fuente : <a href='$url' target='_blank' rel='no-follow''>Chapay</a>";

    //Image
    if ($imagen) {
        $url = "http://www.chapay.com.ar/" . $imagen;

        if ($wrapper = file_stream_wrapper_get_instance_by_uri('public://')) {
            $realpath = $wrapper->realpath();
        }

        $path = $realpath . '/' . time() . '.jpg';

        $requester = new Requester();
        $requester->save($path, $url);
        $file = new StdClass();
        $file->uid = 1;
        $file->uri = $path;
        $file->filemime = file_get_mimetype($file->uri);
        $file->status = 1;
        $dest = file_default_scheme() . '://' . time() . '.jpg'; // Subdirectory name within files
        $file = file_copy($file, $dest);
        $node->field_fotos['und'][0] = (array) $file;
    }

    node_submit($node);
    node_save($node);
}

function chapay_import_create_author($details, $imagen, $url) {
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
    $body_post_body = '';

    $term = false;

    foreach($details as $detail) {
        switch ($detail[0]) {
            case "Apellido, Nombre":
                $node->title = $detail[1];
                break;
            case "Origen":
                $terms = taxonomy_get_term_by_name($detail[1], 'nacionalidad');
                if (empty($terms)) {
                    $vocabulary = chapay_import_get_vocabulary_by_name('nacionalidad');
                    $term = new stdClass();
                    $term->name = $detail[1];
                    $term->vid = $vocabulary->vid;
                    taxonomy_term_save($term);
                } else {
                    $term = array_shift($terms);
                }
                break;
            case "Biografía":
                $body = $detail[1];
                break;
            default:
                if (!empty($detail[0]) && !empty($detail[1])) {
                    $body_post_body .= "<br />" . $detail[0] . ' : ' . $detail[1];
                }
        }
    }

    $node->body['und'][0]['value']  = $body . '<br />' . $body_post_body;
    $node->body['und'][0]['value'] .= "<br/> Fuente : <a href='$url' target='_blank' rel='no-follow''>Chapay</a>";

    //Image
    if ($imagen) {
        $url = "http://www.chapay.com.ar/" . $imagen;

        if ($wrapper = file_stream_wrapper_get_instance_by_uri('public://')) {
            $realpath = $wrapper->realpath();
        }

        $path = $realpath . '/' . time() . '.jpg';

        $requester = new Requester();
        $requester->save($path, $url);
        $file = new StdClass();
        $file->uid = 1;
        $file->uri = $path;
        $file->filemime = file_get_mimetype($file->uri);
        $file->status = 1;
        $dest = file_default_scheme() . '://' . time() . '.jpg' ; // Subdirectory name within files
        $file = file_copy($file, $dest);
        $node->field_fotos['und'][0] = (array) $file;
    }

    if (!empty($term->tid)) {
        $node->field_nacionalidad['und'][0]['tid'] = $term->tid;
    }

    node_submit($node);
    node_save($node);
}

function chapay_import_get_xpath($url) {
    $requester = new Requester();
    $result = $requester->get($url);

    if ($result) {
        $doc = new DOMDocument();
        @$doc->loadHTML($result, LIBXML_NOWARNING);
        $xpath = new DOMXpath($doc);
        return $xpath;
    }

    return false;
}

function chapay_import_get_attribute($xpath, $attribute, $query) {
    $elements = $xpath->query($query);
    $ret = '';

    if (!is_null($elements)) {
        foreach ($elements as $node) {
            $ret = $node->getAttribute($attribute);
        }
    }

    return $ret;
}

function chapay_import_get_value($xpath, $query) {
    $elements = $xpath->query($query);
    $ret = '';

    if (!is_null($elements)) {
        foreach ($elements as $node) {
            $ret = $node->nodeValue;
        }
    }

    return $ret;
}

function chapay_import_get_table($xpath, $query) {
    $elements = $xpath->query($query);
    $ret = array();

    if (!is_null($elements)) {
        foreach ($elements as $element) {
            $trs = $element->childNodes;
            foreach ($trs as $tr) {
                $tds = $tr->childNodes;
                $row = array();
                foreach ($tds as $td) {
                    $value = $td->nodeValue;
                    $value = trim($value);
                    if (!empty($value)) {
                        $row[] = $td->nodeValue;
                    }
                }
                $ret[] = $row;
            }
        }
    }
    return $ret;
}

function chapay_import_get_vocabulary_by_name($machine_name) {
    $vocabularies = taxonomy_get_vocabularies();
    foreach($vocabularies as $vocabulary) {
        if ($vocabulary->machine_name == $machine_name) {
            return $vocabulary;
        }
    }
    return false;
}

function chapay_import_taxonomy_find_or_create($term, $vocabulary) {
    $terms = taxonomy_get_term_by_name($term, $vocabulary);
    if (empty($terms)) {
        $vocabulary = chapay_import_get_vocabulary_by_name($vocabulary);
        $t = new stdClass();
        $t->name = $term;
        $t->vid = $vocabulary->vid;
        taxonomy_term_save($t);
    } else {
        $t = array_shift($terms);
    }
    return $t;
}

function chapay_import_load_node_by_title($title, $type) {
    $result = db_query("SELECT n.nid FROM {node} n WHERE n.title like :title AND n.type = :type",
        array('title' => '%' . $title . '%',
              'type' => $type)
    );

    if ($nid = $result->fetchAssoc()) {
        return node_load($nid['nid']);
    }

    return false;
}

function chapay_import_get_coords($address) {
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