<?php
/**
 * Created by PhpStorm.
 * User: Sergey Grigorenko (svipsa@gmail.com)
 * Date: 07.09.15
 * Time: 12:50
 */


/****************************************************************************
 ** Web Service Clients
 ****************************************************************************/

/**
 * Implements hook_clients_connection_type_info().
 */
function crescent_remote_blog_clients_connection_type_info() {
  return array(
    'crescent_remote_blog_rest' => array(
      'label' => t('REST Data Services'),
      'description' => t('Connects to our data service using REST endpoints.'),
      'tests' => array(
        'post_retrieve_raw' => 'CrescentRemoteBlogConnectionTestRetrieveRaw',
      ),
      'interfaces' => array(
        'ClientsRemoteEntityInterface',
      ),
    ),
  );
}

/**
 * Implements hook_clients_default_connections().
 */
function crescent_remote_blog_clients_default_connections() {
  $connections['crescent_remote_blog_rest_conn'] = new clients_connection_crescent_remote_blog_rest(array(
    'endpoint' => 'http://crescent.funnelstaging.com/blog-server/views/server_blog_ameriflow.json',
    'configuration' => array(
      'username' => '',
      'password' => '',
      'debug' => 0,
      'credentials_storage' => 'connection_configuration',
    ),
    'label' => 'Crescent remote blog rest Service',
    'type' => 'crescent_remote_blog_rest',
  ), 'clients_connection');

  return $connections;
}

/**
 * Implements hook_clients_default_resources().
 */
function crescent_remote_blog_clients_default_resources() {
  $resources[CRESCENT_REMOTE_BLOG_ENTITY_TYPE] = new clients_resource_remote_entity(array(
    'component' => CRESCENT_REMOTE_BLOG_ENTITY_TYPE,
    'connection' => 'crescent_remote_blog_rest_conn',
    'label' => 'Resource for remote posts',
    'type' => 'remote_entity',
  ), 'clients_resource');
  return $resources;
}