<?php

/**
 * @file
 * Crescent base blocks
 */


/**
 * Implements hook_block_info().
 */
function crescent_latest_news_block_info() {
  $blocks = array();

  $blocks['crescent_latest_news'] = array(
    'info' => t('Crescent latest news: News'),
  );

  return $blocks;
}

/**
 * Implements hook_block_configure().
 */
function crescent_latest_news_block_configure($delta = '') {
  $form = array();

  switch ($delta) {
    case 'crescent_latest_news':
      $key = 'crescent_latest_news_';

      $form[$key . 'services_link'] = array(
        '#type' => 'textfield',
        '#title' => t('Services news feed link'),
        '#default_value' => variable_get($key . 'services_link', ''),
        '#description' => "Example: http://site.com/crescent-latest-news",
      );

      $form[$key . 'ameriflow_link'] = array(
        '#type' => 'textfield',
        '#title' => t('AmeriFlow news feed link'),
        '#default_value' => variable_get($key . 'ameriflow_link', ''),
        '#description' => "Example: http://site.com/crescent-latest-news",
      );

      $form[$key . 'sjb_link'] = array(
        '#type' => 'textfield',
        '#title' => t('SJB news feed link'),
        '#default_value' => variable_get($key . 'sjb_link', ''),
        '#description' => "Example: http://site.com/crescent-latest-news",
      );

      break;


  }

  return $form;
}

/**
 * Implements hook_block_save().
 */
function crescent_latest_news_block_save($delta = '', $edit = array()) {
  switch ($delta) {
    case 'crescent_latest_news':
      $key = 'crescent_latest_news_';
      variable_set($key . 'services_link', $edit[$key . 'services_link']);
      variable_set($key . 'ameriflow_link', $edit[$key . 'ameriflow_link']);
      variable_set($key . 'sjb_link', $edit[$key . 'sjb_link']);
      break;
  }
}

/**
 * Implements hook_block_view().
 */
function crescent_latest_news_block_view($delta = '') {
  $block = array();

  switch ($delta) {
    case 'crescent_latest_news':
      $block['subject'] = '';
      $block['content'] = _crescent_latest_news_block_content();
      break;
  }

  return $block;
}


/**
 * Get social top block content
 * @return string
 */
function _crescent_latest_news_block_content() {
  $key = 'crescent_latest_news_';
  $services_link = variable_get($key . 'services_link', "");
  $ameriflow_link = variable_get($key . 'ameriflow_link', "");
  $sjb_link = variable_get($key . 'sjb_link', "");

  if (empty($services_link) || empty($ameriflow_link) || empty($sjb_link)){
    return t("Empty links");
  }


  $blocks = array();

  if (!empty($services_link)){
    $post_data = _crescent_latest_news_load_post($services_link);
    if (!empty($post_data['url'])) {
      $post_data['block_title'] = t("Crescent Services");
      $blocks[] = theme("crescent_latest_news_block", array('post_data' => $post_data));
    }
  }

  if (!empty($ameriflow_link)){
    $post_data = _crescent_latest_news_load_post($ameriflow_link);
    if (!empty($post_data['url'])) {
      $post_data['block_title'] = t("AmeriFlow");
      $blocks[] = theme("crescent_latest_news_block", array('post_data' => $post_data));
    }
  }

  if (!empty($sjb_link)){
    $post_data = _crescent_latest_news_load_post($sjb_link);
    if (!empty($post_data['url'])) {
      $post_data['block_title'] = t("SJB Linings");
      $blocks[] = theme("crescent_latest_news_block", array('post_data' => $post_data));
    }
  }

  return theme("crescent_latest_news_blocks", array('blocks' => $blocks));
}


/**
 * Load blog post from server.
 *
 * @param $url
 * @return mixed
 */
function _crescent_latest_news_load_post($url){
  $request = drupal_http_request($url);
  return drupal_json_decode($request->data);
}