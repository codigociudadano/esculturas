<?php
/**
 * @file
 * esculturas_contexto.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function esculturas_contexto_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'autores_obras';
  $context->description = '';
  $context->tag = 'esculturas';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '*' => '*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-esculturas-block_1' => array(
          'module' => 'views',
          'delta' => 'esculturas-block_1',
          'region' => 'content_bottom',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('esculturas');
  $export['autores_obras'] = $context;

  return $export;
}
