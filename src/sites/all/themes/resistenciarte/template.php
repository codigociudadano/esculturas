<?php
/**
 * Created by PhpStorm.
 * User: alejandro
 * Date: 17/06/14
 * Time: 11:42
 */

/**
 * Override or insert variables into the html template.
 */
function resistenciarte_process_html(&$vars) {
// Add classes for the font styles
    global $base_path;
    $classes = explode(' ', $vars['classes']);
    $classes[] = theme_get_setting('font_family');
    $classes[] = theme_get_setting('font_size');
    $vars['classes'] = trim(implode(' ', $classes));
    $vars['base_path'] = $base_path;
}
