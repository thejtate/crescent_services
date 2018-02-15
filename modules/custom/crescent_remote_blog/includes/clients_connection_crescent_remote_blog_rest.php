<?php
/**
 * Created by PhpStorm.
 * User: Sergey Grigorenko (svipsa@gmail.com)
 * Date: 07.09.15
 * Time: 12:54
 */

/**
 * Set up a client connection to our REST services.
 *
 *  @todo Make private functions private once development is done.
 */
class clients_connection_crescent_remote_blog_rest extends clients_connection_base implements ClientsConnectionAdminUIInterface, ClientsRemoteEntityInterface {

  /**************************************************************************
   * ClientsRemoteEntityInterface implementations.
   **************************************************************************/

  /**
   * Load a remote entity.
   *
   * @param $entity_type
   *   The entity type to load.
   * @param $id
   *   The (remote) ID of the entity.
   *
   * @return
   *  An entity object.
   */
  function remote_entity_load($entity_type, $id) {
    $query = $this->getRemoteEntityQuery('select');
    $query->base($entity_type);
    $query->entityCondition('entity_id', $id);
    $result = $query->execute();

    // There's only one. Same pattern as entity_load_single().
    return reset($result);
  }

  /**
   * Load all remote entities.
   *
   * @param $entity_type
   *   The entity type to load.
   *
   * @return
   *  An entity object.
   */
  function remote_entity_load_all($entity_type) {
    $query = $this->getRemoteEntityQuery('select');
    $query->base($entity_type);
    $remote_entities = $query->execute();

    if (!empty($remote_entities)) {
      $controller = entity_get_controller($entity_type);
      // The controller's process_remote_entities() doesn't care about the key
      // of the array of remote entities.
      $entities = $controller->process_remote_entities($remote_entities);

      return $entities;
    }

    return $remote_entities;
  }


  /**
   * Provide a map of remote property types to Drupal types.
   *
   * Roughly analogous to _entity_metadata_convert_schema_type().
   *
   * @return
   *   An array whose keys are remote property types as used as types for fields
   *   in hook_remote_entity_query_table_info(), and whose values are types
   *   recognized by the Entity Metadata API (as listed in the documentation for
   *   hook_entity_property_info()).
   *   If a remote property type is not listed here, it will be mapped to 'text'
   *   by default.
   */
  function entity_property_type_map() {
    return array(
      'EntityCollection' => 'list<string>',
    );
  }

  /**
   * Get a new RemoteEntityQuery object appropriate for the connection.
   *
   * @param $query_type
   *  (optional) The type of the query. Defaults to 'select'.
   *
   * @return
   *  A remote query object of the type appropriate to the query type.
   */
  function getRemoteEntityQuery($query_type = 'select') {
    switch ($query_type) {
      case 'select':
        return new CrescentRemoteEntityRestRemoteSelectQuery($this);
      case 'insert':
        return new CrescentRemoteEntityRestRemoteInsertQuery($this);
      case 'update':
        return new CrescentRemoteEntityRestRemoteUpdateQuery($this);
    }
  }



  /**************************************************************************
   * clients_connection_base overrides
   **************************************************************************/

  /**
   * Call a remote method with an array of parameters.
   *
   * This is intended for internal use from callMethod() and
   * clients_connection_call().
   * If you need to call a method on given connection object, use callMethod
   * which has a nicer form.
   *
   * Subclasses do not necessarily have to override this method if their
   * connection type does not make sense with this.
   *
   * @param $method
   *  The name of the remote method to call.
   * @param $method_params
   *  An array of parameters to passed to the remote method.
   *
   * @return
   *  Whatever is returned from the remote site.
   *
   * @throws Exception on error from the remote site.
   *  It's up to subclasses to implement this, as the test for an error and
   *  the way to get information about it varies according to service type.
   */
  function callMethodArray($method, $method_params = array()) {

    switch ($method) {
      case 'makeRequest':

        // Set the parameters.
        $resource_path = $method_params[0];
        $http_method = $method_params[1];
        $data = isset($method_params[2]) ? $method_params[2] : array();

        // Make the request.
        $results = $this->makeRequest($resource_path, $http_method, $data);
        break;
    }

    return $results;
  }




  /**************************************************************************
   * Local methods
   **************************************************************************/

  /**
   * Make a REST request.
   *
   * Originally from clients_connection_drupal_services_rest_7->makeRequest().
   * Examples:
   * Retrieve an event:
   *  makeRequest('event?eventId=ID', 'GET');
   * Update a node:
   *  makeRequest('node/NID', 'POST', $data);
   *
   * @param $resource_path
   *  The path of the resource. Eg, 'node', 'node/1', etc.
   * @param $http_method
   *  The HTTP method. One of 'GET', 'POST', 'PUT', 'DELETE'. For an explanation
   *  of how the HTTP method affects the resource request, see the Services
   *  documentation at http://drupal.org/node/783254.
   * @param $data = array()
   *  (Optional) An array of data to pass to the request.
   * @param boolean $data_as_headers
   *   Data will be sent in the headers if this is set to TRUE.
   *
   * @return
   *  The data from the request response.
   *
   *  @todo Update the first two test classes to not assume a SimpleXMLElement.
   */
  function makeRequest($resource_path, $http_method, $data = array(), $data_as_headers = FALSE) {

    // Tap into this function's cache if there is one.
    $request_cache_map = &drupal_static(__FUNCTION__);
    $context_path = "";

    // Set the options.
    $options = array(
      //'headers' => $this->getHeaders(),  // Define if you need it.
      'method'  => $http_method,
      'data'    => http_build_query($data, '', '&'),
    );

    // If cached, we have already issued this request during this page request so
    // just use the cached value.
    $request_path = $this->endpoint . $context_path . '/' . $resource_path;

    // Either get the data from the cache or send a request for it.
    if (isset($request_cache_map[$request_path])) {
      // Use the cached copy.
      $response = $request_cache_map[$request_path];
    } else {
      // Not cached yet so fire off the request.
      $response = drupal_http_request($request_path, $options);

      // And then cache to avoid duplicate calls within the page request.
      $request_cache_map[$request_path] = $response;
    }

    // Handle any errors and then return the response.
    $this->handleRestError($request_path, $response);
    return $response;
  }

  /**
   * Common helper for reacting to an error from a REST call.
   *
   * Originally from clients_connection_drupal_services_rest_7->handleRestError().
   * Gets the error from the response, logs the error message,
   * and throws an exception, which should be caught by the module making use
   * of the Clients connection API.
   *
   * @param $response
   *  The REST response data, decoded.
   *
   * @throws Exception
   */
  function handleRestError($request, $response) {

    // Report and throw an error if we get anything unexpected.
    if (!in_array($response->code, array(200, 201, 202, 204, 404))) {

      // Report error to the logs.
      watchdog('clients', 'Error with REST request (@req). Error was code @code with error "@error" and message "@message".', array(
        '@req'      => $request,
        '@code'     => $response->code,
        '@error'    => $response->error,
        '@message'  => isset($response->status_message) ? $response->status_message : '(no message)',
      ), WATCHDOG_ERROR);

      // Throw an error with which callers must deal.
      throw new Exception(t("Clients connection error, got message '@message'.", array(
        '@message' => isset($response->status_message) ? $response->status_message : $response->error,
      )), $response->code);
    }
  }

  /**
   * Save a remote entity.
   *
   * @param $entity_type
   *  The type of the entity.
   * @param $entity
   *  The entity to save.
   * @param $remote_properties
   *  (Optional) An array of properties to save. Values should be names of
   *  properties which are keys in the entity info 'property map' array. Only
   *  applies when updating rather than inserting. Client connection types may
   *  ignore this.
   *
   * @return
   *  If the entity is being created remotely, the new remote ID.
   */
  function remote_entity_save($entity_type, $entity, $remote_properties = array()) {
    // TODO: Implement remote_entity_save() method.
  }
}