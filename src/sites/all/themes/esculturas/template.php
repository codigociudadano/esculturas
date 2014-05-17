<?php

/**
 * Override or insert variables into the page template.
 */
function esculturas_preprocess_page(&$vars) {

}

/**
 * Override or insert variables into the node template.
 */
function esculturas_preprocess_node(&$variables) {
  $node = $variables['node'];
  $variables['fb_comments'] = '';
  if (in_array($node->type, array('escultura', 'autores', 'eventos'))) {
    $variables['fb_comments'] = esculturas_get_fb_comments();
  }
}

function esculturas_get_fb_comments() {
    return '<div class="comments">
    <div class="fb-comments" data-href="http://www.resistenciarte.org"
         data-width="100%"
         data-numposts="20"
         data-colorscheme="light"></div>
    </div>';
}