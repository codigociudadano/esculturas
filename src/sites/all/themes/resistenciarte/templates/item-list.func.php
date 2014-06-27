<?php
/**
 * @file
 * item-list.func.php
 */

/**
 * Overrides theme_item_list().
 */
function resistenciarte_item_list($variables) {
    $items = $variables['items'];
    $title = $variables['title'];
    $type = $variables['type'];
    $attributes = $variables['attributes'];

    $container = isset($variables['container-masonry']) ? ' id="' . $variables['container-masonry'] . '"' : '';

    $output = '<div' . $container. '>';
    if (isset($title) && $title !== '') {
        $output .= '<h3>' . $title . '</h3>';
    }

    if (!empty($items)) {
        $output .= "<$type" . drupal_attributes($attributes) . '>';
        $num_items = count($items);
        $i = 0;
        foreach ($items as $item) {
            $attributes = array();
            $children = array();
            $data = '';
            $i++;
            if (is_array($item)) {
                foreach ($item as $key => $value) {
                    if ($key == 'data') {
                        $data = $value;
                    }
                    elseif ($key == 'children') {
                        $children = $value;
                    }
                    else {
                        $attributes[$key] = $value;
                    }
                }
            }
            else {
                $data = $item;
            }
            if (count($children) > 0) {
                // Render nested list.
                $data .= theme('item_list', array(
                    'items' => $children,
                    'title' => NULL,
                    'type' => $type,
                    'attributes' => $attributes,
                ));
            }
            if ($i == 1) {
                $attributes['class'][] = 'item';
            }
            if ($i == $num_items) {
                $attributes['class'][] = 'item';
            }
            $output .= '<div ' . drupal_attributes($attributes) . '>' . $data . "</div>\n";
        }
        $output .= "</$type>";
    }
    $output .= '</div>';

    return $output .= theme('item_list', array(
            'items' => $scopeList,
            'title' => $scopeName,
            'type' => 'ul',
            'attributes' => array('id' => 'scope-list'),
            'container-masonry' => 'scope-list-wrapper',
        )
    );
}