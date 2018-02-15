<?php
/**
 * Created by PhpStorm.
 * User: Sergey Grigorenko (svipsa@gmail.com)
 * Date: 09.09.15
 * Time: 14:43
 */

module_load_include("inc", "remote_entity", "includes/remote_entity.controller");

class RemoteEntityAPIBlogController extends RemoteEntityAPIDefaultController {

  /**
   * Overridden to retrieve entities from remote source if expired.
   *
   * Retrieving remote entities can be bypassed by setting the value of the
   * property $bypass_remote_retrieve on the controller object to TRUE.
   *
   * @see DrupalDefaultEntityController#load($ids, $conditions)
   */
  public function load($ids = array(), $conditions = array()) {
    $entities = parent::load($ids, $conditions);
    //dsm($entities, 'CONTROLLER load');

    // Check each entity for expiry, if the entity type supports it. We also
    // allow the controller setting to bypass this.
    if (!empty($this->entityInfo['expiry']) && !$this->bypass_remote_retrieve) {
      // Assemble a list of expired entities, to remote load them in bulk.
      $expired_entity_remote_ids = array();
      foreach ($entities as $id => $entity) {
        // A value of 0 for the expiry means it doesn't expire.
        if (!empty($entity->expires) && $entity->expires < REQUEST_TIME) {
          // Entity has expired.
          // If the entity is marked for remote save, skip this step.
          if (!empty($entity->needs_remote_save)) {
            continue;
          }

          $expired_entity_remote_ids[$id] = $entity->remote_id;
        }
      }

      // If any entities require a refresh from remote, remote load them.
      if ($expired_entity_remote_ids) {
        $resource = clients_resource_get_for_component('remote_entity', $this->entityType);
        // Load the remote entities. This in turn:
        // - calls the connection to build a RemoteEntityQuery
        // - calls us to take care of doing the packing and the saving.
        $refreshed_entities = $resource->remote_entity_load_multiple($expired_entity_remote_ids);

        // Replace the entities in the array, they are now stale.
        // Only return something if the entity exists: if nothing has come
        // back then the remote entity has vanished on the remote site.
        foreach ($refreshed_entities as $id => $refreshed_entity) {
          if (!empty($refreshed_entity)) {
            $entities[$id] = $refreshed_entity;
            unset($expired_entity_remote_ids[$id]);
          }


          // TODO: if the remote entity is gone, should we delete locally, or
          // is that overstepping our bounds and something to be figured out
          // on a case by case basis?
        }


        $this->remove($expired_entity_remote_ids);
      }
    }

    return $entities;
  }

  public function remove($ids = array()){
    foreach ($ids as $eid => $remote_id){
      // remove fields
      $field_name = 'field_' . CRESCENT_REMOTE_BLOG_ENTITY_TYPE . '_date';
      $values = array('eid' => $eid, 'type' => CRESCENT_REMOTE_BLOG_ENTITY_TYPE);
      $new_entity = entity_create(CRESCENT_REMOTE_BLOG_ENTITY_TYPE, $values);
      $info = field_info_field($field_name);
      $fields = array($info['id'] => $info['id']);
      field_sql_storage_field_storage_delete(CRESCENT_REMOTE_BLOG_ENTITY_TYPE, $new_entity, $fields);

      $field_name = 'field_' . CRESCENT_REMOTE_BLOG_ENTITY_TYPE . '_tags';
      $values = array('eid' => $eid, 'type' => CRESCENT_REMOTE_BLOG_ENTITY_TYPE);
      $new_entity = entity_create(CRESCENT_REMOTE_BLOG_ENTITY_TYPE, $values);
      $info = field_info_field($field_name);
      $fields = array($info['id'] => $info['id']);
      field_sql_storage_field_storage_delete(CRESCENT_REMOTE_BLOG_ENTITY_TYPE, $new_entity, $fields);

      // remove remote_entity
      db_delete(CRESCENT_REMOTE_BLOG_TABLE)
        ->condition('eid', $eid)
        ->execute();
    }
  }



  /**
   * Process a remote entity that has been retrieved by a RemoteEntityQuery.
   *
   * @param $remote_entities
   *  An array of raw remote entities, as retrieved from the remote connection
   *  with a RemoteEntityQuery.
   *
   * @return
   *  An array of fully loaded local entities, keyed by entity id.
   *
   * @see clients_resource_remote_entity::executeRemoteEntityQuery()
   */
  public function process_remote_entities($remote_entities) {
    // Set ourselves to bypass remote retrievals, as we don't want either the
    // load in pack() or the save operation (which calls load()!) to result in
    // circularity.
    $this->bypass_remote_retrieve = TRUE;
    $entities = array();
    foreach ($remote_entities as $remote_entity) {
      if (empty($remote_entity)){
        continue;
      }

      // Pack the remote entity into a local entity.
      $entity = $this->pack($remote_entity);

      // Set the expiry time before we save it.
      $this->set_expiry($entity);
      $this->save($entity);

      $entities[$entity->eid] = $entity;
    }

    // Invoke hook_remote_entity_process() on the entities.
    module_invoke_all('remote_entity_process', $entities, $this->entityType);

    // Remove the bypass.
    $this->bypass_remote_retrieve = FALSE;

    return $entities;
  }
}