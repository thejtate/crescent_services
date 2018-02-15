<?php
/**
 * Created by PhpStorm.
 * User: Sergey Grigorenko (svipsa@gmail.com)
 * Date: 07.09.15
 * Time: 12:45
 */



/****************************************************************************
 ** Entity APIs
 ****************************************************************************/

/**
 * Implements hook_entity_info().
 *
 * @todo Add 'bundles' for different types of remote content.
 * @todo Add 'entity keys' => 'needs remote save' if remote saving required.
 * @todo Remove 'static cache' and 'field cache' settings after development.
 */
function crescent_remote_blog_entity_info() {
    $entities[CRESCENT_REMOTE_BLOG_ENTITY_TYPE] = array(
      // Core properties.
      'label' => t('Remote blog post'),
      'controller class' => 'RemoteEntityAPIBlogController',
      'base table' => CRESCENT_REMOTE_BLOG_TABLE,
      'uri callback' => 'entity_class_uri',
      'label callback' => 'remote_entity_entity_label',
      'fieldable' => TRUE,
      'entity keys' => array(
        'id' => 'eid',
        'label' => 'title',
      ),
      'view modes' => array(
        'full' => array(
          'label' => t('Full content'),
          'custom settings' => FALSE,
        ),
        'teaser' => array(
          'label' => t('Teaser'),
          'custom settings' => FALSE,
        ),
        'latest_news' => array(
          'label' => t('Latest news'),
          'custom settings' => FALSE,
        ),
      ),
      'static cache' => FALSE,
      'field cache' => FALSE,

      // Entity API properties.
      'entity class' => 'CrescentRemoteEntityPost',
      'module' => 'crescent_remote_blog',
      'metadata controller class' => 'RemoteEntityAPIDefaultMetadataController',
      'views controller class' => 'EntityDefaultViewsController',

      // Remote Entity API properties.
      'remote base table' => CRESCENT_REMOTE_BLOG_TABLE,
      'remote entity keys' => array(
        'remote id' => 'nid',
        'label' => 'title',
      ),
      'expiry' => array(
        // Number of seconds before a locally cached instance must be refreshed
        // from the remote source.
        'expiry time' => 3000,
        //'expiry time' => 10,
        // A boolean indicating whether or not to delete expired local entities
        // on cron.
        'purge' => FALSE,
      ),
    );

  // Get the property map data.
  $remote_properties = crescent_remote_blog_get_remote_properties();

  // Assign each map to its corresponding entity.
  foreach ($entities as $key => $einfo) {
    $entities[$key]['property map'] =
      drupal_map_assoc(array_keys($remote_properties[$key]));
  }

  // Return all of the entity information.
  return $entities;
}



/**
 * Implements hook_entity_property_info_alter().
 *
 * This is needed to use wrappers to access the remote entity
 * data in the entity_data property of remote entities.
 *
 * @see: Page 107 of the Programming Drupal 7 Entities book.  The code below is
 *   a variation on it.
 * @todo: Remove whenever this gets added to the remote_entity module.
 */
function crescent_remote_blog_entity_property_info_alter(&$info) {
  $entity_types = array(CRESCENT_REMOTE_BLOG_ENTITY_TYPE);
  $remote_properties = crescent_remote_blog_get_remote_properties();

  // Assign the property data to each entity.
  foreach ($entity_types as $entity_type) {
    $properties = &$info[$entity_type]['properties'];
    $entity_data = &$properties['entity_data'];
    $pp = &$remote_properties[$entity_type];
    $entity_data['type'] = 'remote_entity_' . $entity_type;

    // Set the default getter callback for each property.
    foreach ($pp as $key => $pinfo) {
      $pp[$key]['getter callback'] = 'entity_property_verbatim_get';
    }

    // Assign the updated property info to the entity info.
    $entity_data['property info'] = $pp;
  }
}



/**
 * Get remote property information for remote entities.
 *
 * @return
 *   An array of property information keyed by entity type.
 */
function crescent_remote_blog_get_remote_properties() {

  // Initialize a list of entity properties.
  $properties = array();
    // Define properties for the entity type.
    $properties[CRESCENT_REMOTE_BLOG_ENTITY_TYPE] = array(

      // Post information.
      'nid' => array(
        'label' => 'Remote Post ID',
        'type' => 'integer',
        'description' => 'The remote attribute "id".',
        'views' => array(
          'filter' => 'crescent_remote_blog_views_handler_filter_event_id',
        ),
      ),
      'title' => array(
        'label' => 'Title',
        'type' => 'text',
        'description' => 'The remote attribute "teaser".',
      ),
      'date' => array(
        'label' => 'Date',
        'type' => 'date',
        'description' => 'The remote attribute "date".',
        'views' => array(
          'filter' => 'crescent_remote_blog_views_handler_filter_event_date',
        ),
      ),
      'teaser' => array(
        'label' => 'Teaser',
        'type' => 'text',
        'description' => 'The remote attribute "teaser".',
      ),
      'teaser_image' => array(
        'label' => 'Teaser image',
        'type' => 'text',
      ),
      'body' => array(
        'label' => 'Body',
        'type' => 'text',
      ),
      'tags' => array(
        'label' => 'Tags',
        'type' => 'text',
      ),
    );

  // Return all of the defined property info.
  return $properties;
}