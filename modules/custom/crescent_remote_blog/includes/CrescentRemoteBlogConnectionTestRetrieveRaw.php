<?php
/**
 * Created by PhpStorm.
 * User: Sergey Grigorenko (svipsa@gmail.com)
 * Date: 07.09.15
 * Time: 13:27
 */

/**
 * Test node load from a Drupal Services REST connection.
 */
class CrescentRemoteBlogConnectionTestRetrieveRaw implements ClientsConnectionTestingInterface {

  /**
   * The labels for the test.
   */
  function testLabels() {
    return array(
      'label' => t('Test blog post retrieval'),
      'description' => t('Load a blog post from the connection.'),
      'button' => t('Load blog posts'),
    );
  }

  /**
   * Creates the form element for the test.
   *
   * This gets a form element with the basics in place. If your test needs input
   * parameters, add form elements here.
   *
   * @param $element
   *  A form element for the test's settings and button.
   *
   * @return
   *  The form element with the test's additions.
   */
  function testForm($element) {
    $element['params']['count'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of blog posts'),
      '#size' => 6,
      '#default_value' => 1,
      '#required' => TRUE,
    );

    return $element;
  }

  /**
   * Validate test form input.
   */
  function formValidate(&$button_form_values) {
    if (!is_numeric($button_form_values['params']['count'])) {
      form_set_error('buttons[post_retrieve_raw][params][count]', t('Count must be numeric.'));
    }
  }

  /**
   * Execute the test.
   *
   * Connection test handlers should return the raw data they got back from the
   * connection for display to the user.
   *
   * @param $connection
   *  The connection handler.
   * @param $button_form_values
   *  The form values for the test form element. The values for elements added
   *  to the form are in $button_form_values['params'].
   *
   * @return
   *  Data from the remote connection. This is output to the form as raw data.
   */
  function test($connection, &$button_form_values) {
    // Must be cast to integer for faffiness of XMLRPC and Services.
    $count = (int) $button_form_values['params']['count'];

    try {
      $entity = $connection->makeRequest("?offset=0&limit=" . $count, 'GET');
    }
    catch (Exception $e) {
      drupal_set_message(t('Could not retrieve a node from the remote site, got error message "@message".', array(
        '@message' => $e->getMessage(),
      )), 'warning');
      //dsm($e);

      return;
    }

    if (is_object($entity) && isset($entity->nid)) {
      drupal_set_message(t('Sucessfully retrieved entity %title (eid @eid).', array(
        '%title' => $entity->title,
        '@eid'  => $entity->id,
      )));
    }

    return $entity;
  }

}