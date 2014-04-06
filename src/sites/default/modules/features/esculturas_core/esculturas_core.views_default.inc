<?php
/**
 * @file
 * esculturas_core.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function esculturas_core_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'autores';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Autores';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Autores';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Enviar';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Reiniciar';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '9';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« primera';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ anterior';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'siguiente ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'última »';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['columns'] = '3';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Campo: Contenido: Fotos */
  $handler->display->display_options['fields']['field_fotos']['id'] = 'field_fotos';
  $handler->display->display_options['fields']['field_fotos']['table'] = 'field_data_field_fotos';
  $handler->display->display_options['fields']['field_fotos']['field'] = 'field_fotos';
  $handler->display->display_options['fields']['field_fotos']['label'] = '';
  $handler->display->display_options['fields']['field_fotos']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_fotos']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_fotos']['settings'] = array(
    'image_style' => 'listados',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_fotos']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_fotos']['delta_offset'] = '0';
  /* Campo: Contenido: Título */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Contenido: Título */
  $handler->display->display_options['sorts']['title_1']['id'] = 'title_1';
  $handler->display->display_options['sorts']['title_1']['table'] = 'node';
  $handler->display->display_options['sorts']['title_1']['field'] = 'title';
  /* Filter criterion: Contenido: Publicado */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Contenido: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'autores' => 'autores',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'autores';
  $translatables['autores'] = array(
    t('Master'),
    t('Autores'),
    t('more'),
    t('Enviar'),
    t('Reiniciar'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« primera'),
    t('‹ anterior'),
    t('siguiente ›'),
    t('última »'),
    t('Page'),
  );
  $export['autores'] = $view;

  $view = new view();
  $view->name = 'esculturas';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Esculturas';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Esculturas';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Enviar';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Reiniciar';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '9';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« primera';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ anterior';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'siguiente ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'última »';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['columns'] = '3';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Campo: Contenido: Fotos */
  $handler->display->display_options['fields']['field_fotos']['id'] = 'field_fotos';
  $handler->display->display_options['fields']['field_fotos']['table'] = 'field_data_field_fotos';
  $handler->display->display_options['fields']['field_fotos']['field'] = 'field_fotos';
  $handler->display->display_options['fields']['field_fotos']['label'] = '';
  $handler->display->display_options['fields']['field_fotos']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_fotos']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_fotos']['settings'] = array(
    'image_style' => 'listados',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_fotos']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_fotos']['delta_offset'] = '0';
  /* Campo: Contenido: Título */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Contenido: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Contenido: Publicado */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Contenido: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'escultura' => 'escultura',
  );
  /* Filter criterion: Contenido: Título */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Nombre ';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Contenido: Tipo (field_tipo) */
  $handler->display->display_options['filters']['field_tipo_tid']['id'] = 'field_tipo_tid';
  $handler->display->display_options['filters']['field_tipo_tid']['table'] = 'field_data_field_tipo';
  $handler->display->display_options['filters']['field_tipo_tid']['field'] = 'field_tipo_tid';
  $handler->display->display_options['filters']['field_tipo_tid']['value'] = '';
  $handler->display->display_options['filters']['field_tipo_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_tipo_tid']['expose']['operator_id'] = 'field_tipo_tid_op';
  $handler->display->display_options['filters']['field_tipo_tid']['expose']['label'] = 'Tipo';
  $handler->display->display_options['filters']['field_tipo_tid']['expose']['operator'] = 'field_tipo_tid_op';
  $handler->display->display_options['filters']['field_tipo_tid']['expose']['identifier'] = 'field_tipo_tid';
  $handler->display->display_options['filters']['field_tipo_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_tipo_tid']['vocabulary'] = 'tipo';
  /* Filter criterion: Contenido: Material (field_material) */
  $handler->display->display_options['filters']['field_material_tid']['id'] = 'field_material_tid';
  $handler->display->display_options['filters']['field_material_tid']['table'] = 'field_data_field_material';
  $handler->display->display_options['filters']['field_material_tid']['field'] = 'field_material_tid';
  $handler->display->display_options['filters']['field_material_tid']['value'] = '';
  $handler->display->display_options['filters']['field_material_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_material_tid']['expose']['operator_id'] = 'field_material_tid_op';
  $handler->display->display_options['filters']['field_material_tid']['expose']['label'] = 'Material';
  $handler->display->display_options['filters']['field_material_tid']['expose']['operator'] = 'field_material_tid_op';
  $handler->display->display_options['filters']['field_material_tid']['expose']['identifier'] = 'field_material_tid';
  $handler->display->display_options['filters']['field_material_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_material_tid']['vocabulary'] = 'material';
  /* Filter criterion: Contenido: Año del Evento (field_ano) */
  $handler->display->display_options['filters']['field_ano_value']['id'] = 'field_ano_value';
  $handler->display->display_options['filters']['field_ano_value']['table'] = 'field_data_field_ano';
  $handler->display->display_options['filters']['field_ano_value']['field'] = 'field_ano_value';
  $handler->display->display_options['filters']['field_ano_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ano_value']['expose']['operator_id'] = 'field_ano_value_op';
  $handler->display->display_options['filters']['field_ano_value']['expose']['label'] = 'Año ';
  $handler->display->display_options['filters']['field_ano_value']['expose']['operator'] = 'field_ano_value_op';
  $handler->display->display_options['filters']['field_ano_value']['expose']['identifier'] = 'field_ano_value';
  $handler->display->display_options['filters']['field_ano_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'esculturas';
  $translatables['esculturas'] = array(
    t('Master'),
    t('Esculturas'),
    t('more'),
    t('Enviar'),
    t('Reiniciar'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« primera'),
    t('‹ anterior'),
    t('siguiente ›'),
    t('última »'),
    t('Nombre '),
    t('Tipo'),
    t('Material'),
    t('Año '),
    t('Page'),
  );
  $export['esculturas'] = $view;

  return $export;
}
