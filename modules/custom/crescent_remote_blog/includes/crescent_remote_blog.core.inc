<?php
/**
 * Created by PhpStorm.
 * User: Sergey Grigorenko (svipsa@gmail.com)
 * Date: 07.09.15
 * Time: 12:45
 */


/****************************************************************************
 ** Drupal Core
 ****************************************************************************/

/**
 * Implements hook_menu().
 */
function crescent_remote_blog_menu() {
  $items = array();

  $items['remote-blog-post/%crescent_remote_blog_post'] = array(
    'title' => 'Remote Blog post',
    'page callback' => 'crescent_remote_blog_post_view',
    'page arguments' => array(1),
    'access arguments' => array('access content'),
  );


  $items['remote-blog-post/load-all'] = array(
    'page callback' => 'crescent_remote_blog_load_all',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
  );

  return $items;
}


function crescent_remote_blog_load_all(){
  $resource = clients_resource_get_for_component('remote_entity', CRESCENT_REMOTE_BLOG_ENTITY_TYPE);
  $connection = $resource->getConnection();
  $connection->remote_entity_load_all(CRESCENT_REMOTE_BLOG_ENTITY_TYPE);
  return "";
}



/**
 * Menu autoloader wildcard for path 'event/REMOTE_ID'.
 *
 * @see hook_menu() documentation.
 * @param $remote_id
 *   The remote ID of the record to load.
 * @return
 *   The loaded object, or FALSE on failure.
 */
function crescent_remote_blog_post_load($remote_id) {
  return remote_entity_load_by_remote_id(CRESCENT_REMOTE_BLOG_ENTITY_TYPE, $remote_id);
}

/**
 * Page callback for path 'event/%remote_id'.
 *
 * @param $event
 *   The auto-loaded object.
 * @return
 *   The themed output for the event page.
 */
function crescent_remote_blog_post_view($post) {
  $post = (isset($post->entity_data)) ? $post->entity_data : $post;
  $fullname = $post->title;
  drupal_set_title($fullname);
  $post_output = theme('crescent_remote_blog_post_view', array(
    'post' => $post,
  ));
  return $post_output;
}



/**
 * Implements hook_theme().
 */
function crescent_remote_blog_theme() {
  return array(
    'crescent_remote_blog_post_view' => array(
      'variables' => array('post' => NULL),
      'template' => 'theme/crescent_remote_blog_post_view',
    ),
    CRESCENT_REMOTE_BLOG_ENTITY_TYPE => array(
      'variables' => array('post' => NULL),
      'template' => 'theme/crescent_remote_blog_post',
    ),

    'crescent_remote_blog_post_by_month' => array(
      'variables' => array('archive' => NULL, 'blog_base_path' => 'blog'),
      'template' => 'theme/crescent_remote_blog_post_by_month',
    ),

  );
}