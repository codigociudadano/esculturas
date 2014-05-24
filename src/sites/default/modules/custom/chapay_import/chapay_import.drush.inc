<?php

require_once 'Requester.php';

function chapay_import_drush_command() {
    $items['chapay-import-author'] = array(
        'description' => "Import content from chapay.",
        'options' => array(
            'status' => "Feature status, can be 'enabled', 'disabled'  or 'all'",
        ),
        'aliases' => array('import-authors'),
    );
    return $items;
}

function drush_chapay_import_author() {
    $totals = array(0, 0);
    for ($i = 1; $i < 250; $i++) {
        $url = "http://www.chapay.com.ar/?Seccion=autor&Id=" . $i;
        try {
            $xpath = chapay_import_get_xpath($url);
            if ($xpath) {
                $detail = chapay_import_get_table($xpath, '//*[@id="detalle"]');
                $imagen = chapay_import_get_attribute($xpath, 'src',  '//*[@id="detalle"]//*[@class="img"]//img');
                if (!empty($detail)) {
                    chapay_import_create_node($detail, $imagen, $url);
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

function chapay_import_create_node($details, $imagen, $url) {
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
        $dest = file_default_scheme() . '://image'; // Subdirectory name within files
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