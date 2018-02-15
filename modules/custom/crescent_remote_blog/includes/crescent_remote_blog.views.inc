<?php
/**
 * @file
 * crescent_remote_blog.views.inc
 */

/**
 * Implements hook_views_default_views().
 */
function crescent_remote_blog_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'remote_blog';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'crbps';
  $view->human_name = 'Remote Blog';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Remote Blog';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'teaser';
  /* Field: Remote blog post: Remote blog post ID */
  $handler->display->display_options['fields']['eid']['id'] = 'eid';
  $handler->display->display_options['fields']['eid']['table'] = 'crbps';
  $handler->display->display_options['fields']['eid']['field'] = 'eid';
  /* Sort criterion: Remote blog post: Date (field_crbp_date) */
  $handler->display->display_options['sorts']['field_crbp_date_value']['id'] = 'field_crbp_date_value';
  $handler->display->display_options['sorts']['field_crbp_date_value']['table'] = 'field_data_field_crbp_date';
  $handler->display->display_options['sorts']['field_crbp_date_value']['field'] = 'field_crbp_date_value';
  $handler->display->display_options['sorts']['field_crbp_date_value']['order'] = 'DESC';
  /* Contextual filter: Remote blog post: Tags (field_crbp_tags) */
  $handler->display->display_options['arguments']['field_crbp_tags_tid']['id'] = 'field_crbp_tags_tid';
  $handler->display->display_options['arguments']['field_crbp_tags_tid']['table'] = 'field_data_field_crbp_tags';
  $handler->display->display_options['arguments']['field_crbp_tags_tid']['field'] = 'field_crbp_tags_tid';
  $handler->display->display_options['arguments']['field_crbp_tags_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_crbp_tags_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_crbp_tags_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_crbp_tags_tid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Remote blog post: Date (field_crbp_date) */
  $handler->display->display_options['arguments']['field_crbp_date_value']['id'] = 'field_crbp_date_value';
  $handler->display->display_options['arguments']['field_crbp_date_value']['table'] = 'field_data_field_crbp_date';
  $handler->display->display_options['arguments']['field_crbp_date_value']['field'] = 'field_crbp_date_value';
  $handler->display->display_options['arguments']['field_crbp_date_value']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['field_crbp_date_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_crbp_date_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_crbp_date_value']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'blog';

  $export['remote_blog'] = $view;


  $view = new view();
  $view->name = 'remote_blog_latest_news';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'crbps';
  $view->human_name = 'Remote Blog: Latest news';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Latest news';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '2';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'latest_news';
  /* Field: Remote blog post: Remote blog post ID */
  $handler->display->display_options['fields']['eid']['id'] = 'eid';
  $handler->display->display_options['fields']['eid']['table'] = 'crbps';
  $handler->display->display_options['fields']['eid']['field'] = 'eid';
  /* Sort criterion: Remote blog post: Date (field_crbp_date) */
  $handler->display->display_options['sorts']['field_crbp_date_value']['id'] = 'field_crbp_date_value';
  $handler->display->display_options['sorts']['field_crbp_date_value']['table'] = 'field_data_field_crbp_date';
  $handler->display->display_options['sorts']['field_crbp_date_value']['field'] = 'field_crbp_date_value';
  $handler->display->display_options['sorts']['field_crbp_date_value']['order'] = 'DESC';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  $export['remote_blog_latest_news'] = $view;



  $view = new view();
  $view->name = 'remote_blog_tags_block';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Remote Blog tags blocks';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'BROWSE BY TAG';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Taxonomy term: Remote blog post using Tags */
  $handler->display->display_options['relationships']['reverse_field_crbp_tags_crbp']['id'] = 'reverse_field_crbp_tags_crbp';
  $handler->display->display_options['relationships']['reverse_field_crbp_tags_crbp']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['relationships']['reverse_field_crbp_tags_crbp']['field'] = 'reverse_field_crbp_tags_crbp';
  $handler->display->display_options['relationships']['reverse_field_crbp_tags_crbp']['required'] = TRUE;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Contextual filter: Taxonomy term: Term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'summary';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '1';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'unformatted_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['base_path'] = 'blog';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'crescent_remote_blog_tags' => 'crescent_remote_blog_tags',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  $export['remote_blog_tags_block'] = $view;



  return $export;
}
