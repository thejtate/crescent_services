<?php

/**
 * @file
 * Crescent base blocks
 */


/**
 * Implements hook_block_info().
 */
function crescent_base_block_info() {
  $blocks = array();

  $blocks['crescent_top_media'] = array(
    'info' => t('Crescent base: Top media'),
  );

  $blocks['crescent_enviro_edge'] = array(
    'info' => t('Crescent base: EnvireEdge'),
  );

  $blocks['crescent_login_btn'] = array(
    'info' => t('Crescent base: Login button'),
  );


  return $blocks;
}

/**
 * Implements hook_block_configure().
 */
function crescent_base_block_configure($delta = '') {
  $form = array();

  switch ($delta) {
    case 'crescent_top_media':
      $key = 'crescent_top_media_';
      $form[$key . 'image'] = array(
        '#name' => 'crescent_top_media_image',
        '#type' => 'managed_file',
        '#title' => t('Image'),
        '#default_value' => variable_get($key . 'image_fid', ''),
        '#upload_location' => 'public://crescent_base_block_images/',
        '#upload_validators' => array(
          'file_validate_extensions' => array('gif png jpg jpeg'),
        ),
      );
      $form[$key . 'text'] = array(
        '#type' => 'textfield',
        '#title' => t('Text'),
        '#default_value' => variable_get($key . 'text', ''),
      );
      $form[$key . 'embeded'] = array(
        '#type' => 'textarea',
        '#title' => t('Embeded code'),
        '#default_value' => variable_get($key . 'embeded', ''),
      );
      break;
    case 'crescent_enviro_edge':
      $key = 'crescent_enviro_edge_';


      $form[$key . 'image'] = array(
        '#name' => 'crescent_enviro_edge_image',
        '#type' => 'managed_file',
        '#title' => t('Logo Image'),
        '#default_value' => variable_get($key . 'image_fid', ''),
        '#upload_location' => 'public://crescent_base_block_images/',
        '#upload_validators' => array(
          'file_validate_extensions' => array('gif png jpg jpeg'),
        ),
      );

      $form[$key . 'find_link_container'] = array(
        '#type' => 'container',
        '#attributes' => array(),
        '#tree' => TRUE,
      );

      $find_link = variable_get($key . 'find_link', array('title', 'url'));
      $form[$key . 'find_link_container'][$key . 'find_link'] = array(
        '#type' => 'link_field',
        '#title' => t('Find Out More link'),
        '#field_name' => $key . 'find_link',
        '#language' => LANGUAGE_NONE,
        '#field_parents' => array(),
        '#delta' => 0,
        '#default_value' => $find_link,
      );


      $form[$key . 'text'] = array(
        '#type' => 'text_format',
        '#title' => t('Text'),
        '#default_value' => variable_get($key . 'text', ''),
      );

      $form[$key . 'login_link_container'] = array(
        '#type' => 'container',
        '#attributes' => array(),
        '#tree' => TRUE,
      );

      $login_link = variable_get($key . 'login_link', array('title', 'url'));
      $form[$key . 'login_link_container'][$key . 'login_link'] = array(
        '#type' => 'link_field',
        '#title' => t('Login link'),
        '#field_name' => $key . 'login_link',
        '#language' => LANGUAGE_NONE,
        '#field_parents' => array(),
        '#delta' => 0,
        '#default_value' => $login_link,
      );
      break;
    case 'crescent_login_btn':
      $key = 'crescent_login_btn_';
      $form[$key . 'login_link_container'] = array(
        '#type' => 'container',
        '#attributes' => array(),
        '#tree' => TRUE,
      );

      $login_link = variable_get($key . 'login_link', array('title', 'url'));
      $form[$key . 'login_link_container'][$key . 'login_link'] = array(
        '#type' => 'link_field',
        '#title' => t('Login link'),
        '#field_name' => $key . 'login_link',
        '#language' => LANGUAGE_NONE,
        '#field_parents' => array(),
        '#delta' => 0,
        '#default_value' => $login_link,
      );
      break;

  }

  return $form;
}

/**
 * Implements hook_block_save().
 */
function crescent_base_block_save($delta = '', $edit = array()) {
  switch ($delta) {
    case 'crescent_top_media':
      $key = 'crescent_top_media_';
      variable_set($key . 'text', $edit[$key . 'text']);
      variable_set($key . 'embeded', $edit[$key . 'embeded']);

      // Saving the file, setting it to a permanent state, setting a FID variable
      $file = file_load($edit[$key . 'image']);
      if (!empty($file)) {
        $file->status = FILE_STATUS_PERMANENT;
        file_save($file);
        $block = block_load('crescent_base', $delta);
        file_usage_add($file, 'crescent_base', 'block', $block->bid);
        variable_set($key . 'image_fid', $file->fid);
      }
      else {
        variable_set($key . 'image_fid', 0);
      }
      break;
    case 'crescent_enviro_edge':
      $key = 'crescent_enviro_edge_';
      variable_set($key . 'text', $edit[$key . 'text']['value']);
      variable_set($key . 'login_link', $edit[$key . 'login_link_container'][$key . 'login_link']);
      variable_set($key . 'find_link', $edit[$key . 'find_link_container'][$key . 'find_link']);

      // Saving the file, setting it to a permanent state, setting a FID variable
      $file = file_load($edit[$key . 'image']);
      if (!empty($file)) {
        $file->status = FILE_STATUS_PERMANENT;
        file_save($file);
        $block = block_load('crescent_base', $delta);
        file_usage_add($file, 'crescent_base', 'block', $block->bid);
        variable_set($key . 'image_fid', $file->fid);
      }
      else {
        variable_set($key . 'image_fid', 0);
      }

      break;
    case 'crescent_login_btn':
      $key = 'crescent_login_btn_';
      variable_set($key . 'login_link', $edit[$key . 'login_link_container'][$key . 'login_link']);
      break;
  }
}

/**
 * Implements hook_block_view().
 */
function crescent_base_block_view($delta = '') {
  $block = array();

  switch ($delta) {
    case 'crescent_top_media':
      $block['subject'] = '';
      $block['content'] = _crescent_base_crescent_top_media_content();
      break;
    case 'crescent_enviro_edge':
      $block['subject'] = '';
      $block['content'] = _crescent_base_crescent_enviro_edge_content();
      break;
    case 'crescent_login_btn':
      $block['subject'] = '';
      $block['content'] = _crescent_base_crescent_login_btn_content();
      break;
  }

  return $block;
}


/**
 * Get social top block content
 * @return string
 */
function _crescent_base_crescent_top_media_content() {
  $key = 'crescent_top_media_';
  $text = variable_get($key . 'text', "");
  $embeded = variable_get($key . 'embeded', "");

  // Capture the image file path and form into HTML with attributes
  $image_file = file_load(variable_get($key . 'image_fid', ''));
  $image_path = '';

  if (isset($image_file->uri)) {
    $image_path = $image_file->uri;
  }

  if (!empty($image_path)) {
    $image = theme_image(array(
      'path' => ($image_path),
      'alt' => $text,
      'title' => $text,
      'attributes' => array(),
    ));
  } else {
    $image = "";
  }

  $text = (!empty($text)) ? '<div class="site-container"><h1>' . $text . '</h1></div>' : '';

  $block = array(
    'text' => array(
      '#prefix' => '<div class="top-media">',
      '#type' => 'markup',
      '#markup' => $text,
    ),
    'image' => array(
      '#type' => 'markup',
      '#markup' => $image,
      '#suffix' => '<div class="bg-scrollable"></div>',
    ),
    'embeded' => array(
      '#type' => 'markup',
      '#markup' => $embeded,
      '#suffix' => '</div>',
    )
  );
  return $block;
}


function _crescent_base_crescent_enviro_edge_content() {
  $key = 'crescent_enviro_edge_';
  $text = variable_get($key . 'text', "");
  $login_link = variable_get($key . 'login_link', array('title', 'url'));
  $find_link = variable_get($key . 'find_link', array('title', 'url'));


  // Capture the image file path and form into HTML with attributes
  $image_file = file_load(variable_get($key . 'image_fid', ''));
  $image_path = '';

  if (isset($image_file->uri)) {
    $image_path = $image_file->uri;
  }

  $image = theme_image(array(
    'path' => ($image_path),
    'alt' => 'EnviroEdge',
    'title' => 'EnviroEdge',
    'attributes' => array(),
  ));


  $block = array(
    'text' => array(
      '#type' => 'markup',
      '#markup' => $text,
    ),
    'logo_image' => array(
      '#type' => 'markup',
      '#markup' => $image,
      '#prefix' => '<div class="logo">',
      '#suffix' => '</div>',
    ),
    'login_link' => array(
      '#type'  => 'link',
      '#title' => (isset($login_link['title'])) ? $login_link['title'] : "",
      '#href'  => (isset($login_link['url'])) ? $login_link['url'] : "",
      '#attributes' => array('class' => array('btn'), 'target' => '_blank'),
      '#prefix' => '<div class="login-btn">',
      '#suffix' => '</div>',
    ),
    'find_link' => array(
      '#type'  => 'link',
      '#title' => isset($find_link['title']) ? $find_link['title'] : "",
      '#href'  => isset($find_link['url']) ? $find_link['url'] : "",
      '#attributes' => array('class' => array('link'), 'target' => '_blank'),
    ),

  );

  return theme("crescent_base_enviro_edge_block", array('block' => $block));
}


function _crescent_base_crescent_login_btn_content(){
  $key = 'crescent_login_btn_';
  $login_link = variable_get($key . 'login_link', array('title', 'url'));

  $block = array(
    'login_link' => array(
      '#type'  => 'link',
      '#title' => (isset($login_link['title'])) ? $login_link['title'] : "",
      '#href'  => (isset($login_link['url'])) ? $login_link['url'] : "",
      '#attributes' => array('class' => array('btn')),
      '#prefix' => '<div class="login-btn">',
      '#suffix' => '</div>',
    ),
  );

  return $block;
}