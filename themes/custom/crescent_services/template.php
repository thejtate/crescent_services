<?php

/**
 * @file
 * template.php
 *
 * Contains theme override functions and preprocess functions for the theme.
 */

define("CRESCENT_SERVICES_ES_NID", 7);
define("CRESCENT_SERVICES_WS_NID", 0);
define("CRESCENT_SERVICES_WHO_WE_ARE_NID", 19);

/**
 * Implements hook_preprocess_html().
 */
function crescent_services_preprocess_html(&$vars) {
  $html5 = array(
    '#tag' => 'script',
    '#attributes' => array(
      'src' => base_path() . drupal_get_path('theme', 'crescent_services') . '/js/lib/html5.js',
    ),
    '#prefix' => '<!--[if (lt IE 9) & (!IEMobile)]>',
    '#suffix' => '</script><![endif]-->',
  );
  drupal_add_html_head($html5, 'crescent_services_html5');

  $vars['classes_array'][] = 'page';
  if ($node = menu_get_object()) {
    switch ($node->type) {
      case 'home':
        $vars['classes_array'][] = 'page-home';
        break;
      case 'health_safety':
        $vars['classes_array'][] = 'page-tabs';
        break;
      case 'fblog_post':
        $vars['classes_array'][] = 'page-news';
        break;
      case 'environmental_services':
        $vars['classes_array'][] = 'page-services';
        break;
      case 'water_services':
        $vars['classes_array'][] = 'page-water-services';
        break;
      case 'rentals':
        $vars['classes_array'][] = 'page-rentals';
        break;
      case 'who_we_are':
        $vars['classes_array'][] = 'page-about page-who-we-are';
        break;
      case 'contact':
        $vars['classes_array'][] = 'page-contact';
        break;
      case 'enviroedge':
        $vars['classes_array'][] = 'page-enviro';
        break;

    }
  }

  if (in_array("html__blog", $vars['theme_hook_suggestions'])) {
    $vars['classes_array'][] = 'page-news';
  }

  if (in_array("html__remote_blog_post", $vars['theme_hook_suggestions'])) {
    $vars['classes_array'][] = 'page-news';
  }
}

/**
 * Implements hook_preprocess_page().
 */
function crescent_services_preprocess_page(&$vars) {
  $vars['main_menu'] = (module_exists("fmenu")) ? fmenu_get_menu_tree('main-menu') : "";

  $vars['top_menu'] = theme('links__menu_top_menu', array(
    'links' => menu_navigation_links('menu-top-menu'),
  ));

  $vars['footer_menu'] = theme('links__menu_footer_menu', array(
    'links' => menu_navigation_links('menu-footer-menu'),
  ));

  if ($node = menu_get_object()) {
    switch ($node->type) {
      case 'home':
    }
  }
}


/**
 * Implements hook_preprocess_node().
 */
function crescent_services_preprocess_node(&$vars) {
  //$node = $vars['node'];
  switch ($vars['type']) {
    case 'es_item':
      if (isset($vars['view_mode']) && $vars['view_mode'] == 'full') {
        drupal_goto("node/" . CRESCENT_SERVICES_ES_NID);
      }

      if (isset($vars['content']['field_es_item_gallery']) && !empty($vars['content']['field_es_item_gallery'])) {
        $vars['add_class'] = 'text-slider';
      }
      break;
    case 'ws_item':
      if (isset($vars['view_mode']) && $vars['view_mode'] == 'full') {
        drupal_goto("node/" . CRESCENT_SERVICES_WS_NID);
      }

      if (isset($vars['content']['field_ws_item_gallery']) && !empty($vars['content']['field_ws_item_gallery'])) {
        $vars['add_class'] = 'text-slider';
      }
      break;
    case 'corporate_profile':
    case 'core_values':
    case 'about_us':
    case 'management_team':
      if (isset($vars['view_mode']) && $vars['view_mode'] == 'full') {
        drupal_goto("node/" . CRESCENT_SERVICES_WHO_WE_ARE_NID);
      }
      break;
    case 'contact':
      $vars['title_prefix'] = array(
        '#type' => 'markup',
        '#markup' => '<span class="bg"></span>',
      );
      break;
    case 'enviroedge_items':
      if (isset($vars['content']['field_ee_items_gallery']) && !empty($vars['content']['field_ee_items_gallery'])) {
        $vars['add_class'] = 'text-slider';
      }
      break;
  }
}


/**
 * Implements hook_preprocess_block().
 */
function crescent_services_preprocess_block(&$vars) {
  //kpr($vars);
}


/**
 * Theme function to output tablinks for classic Quicktabs style tabs.
 *
 * @ingroup themeable
 */
function crescent_services_qt_quicktabs_tabset($vars) {
  $variables = array(
    'attributes' => array(
      'class' => 'quicktabs-tabs quicktabs-style-' . $vars['tabset']['#options']['style'],
    ),
    'items' => array(),
  );
  $c = 1;

  foreach (element_children($vars['tabset']['tablinks']) as $key) {
    $item = array();
    if (is_array($vars['tabset']['tablinks'][$key])) {
      $tab = $vars['tabset']['tablinks'][$key];
      if ($key == $vars['tabset']['#options']['active']) {
        $item['class'] = array('active');
      }
      $item['class'][] = 'quicktabs-tabs-item-' . $c;
      $c++;
      $item['data'] = drupal_render($tab);
      $variables['items'][] = $item;
    }
  }
  return theme('item_list', $variables);
}


/**
 * Implements hook_preprocess_views_view().
 */
function crescent_services_preprocess_views_view(&$vars) {
  if (isset($vars['view']->name) && $vars['view']->name == "contact") {
    crescent_services_prepare_contact_map($vars);
  }
}

/**
 * Prepare map for contact page.
 * @param $vars
 */
function crescent_services_prepare_contact_map(&$vars) {
  $results = isset($vars['view']->result) ? $vars['view']->result : array();
  $states = array();
  $term_id = NULL;
  $term = NULL;
  $term_color = NULL;
  $term_map_image = NULL;
  $term_icon = NULL;
  $term_map_icon = NULL;
  //kpr($results);
  foreach ($results as $key => $value) {
    $state_key = isset($value->field_field_location_state[0]['raw']['value']) ? $value->field_field_location_state[0]['raw']['value'] : NULL;
    $state_value = isset($value->field_field_location_state[0]['rendered']['#markup']) ? $value->field_field_location_state[0]['rendered']['#markup'] : NULL;
    $city_value = isset($value->field_field_location_city[0]['rendered']['#markup']) ? $value->field_field_location_city[0]['rendered']['#markup'] : NULL;
    $city_marker_left = isset($value->field_field_location_marker_left[0]['raw']['value']) ? $value->field_field_location_marker_left[0]['raw']['value'] : NULL;
    $city_marker_top = isset($value->field_field_location_marker_top[0]['raw']['value']) ? $value->field_field_location_marker_top[0]['raw']['value'] : NULL;


    $nid = isset($value->nid) ? $value->nid : NULL;
    $tid = isset($value->taxonomy_term_data_node_tid) ? $value->taxonomy_term_data_node_tid : NULL;
    if ($term_id != $tid) {
      $term_id = $tid;
      $term = taxonomy_term_load($term_id);
      $term_color = field_get_items('taxonomy_term', $term, 'field_locations_color');
      $term_bg_color = field_get_items('taxonomy_term', $term, 'field_locations_bg_color');
      $term_map_image = field_get_items('taxonomy_term', $term, 'field_locations_map_image');
      $term_icon = field_get_items('taxonomy_term', $term, 'field_locations_icon');
      $term_map_icon = field_get_items('taxonomy_term', $term, 'field_locations_map_icon');
    }

    if (!empty($state_key) && !empty($state_value) && !empty($city_value) && !empty($nid)) {
      $states[$state_key]['state_name'] = $state_value;
      $states[$state_key]['city'][] = array(
        'nid' => $nid,
        'name' => $city_value,
        'left' => $city_marker_left,
        'top' => $city_marker_top
      );
    }
  }

  $map_color = isset($term_color[0]['rgb']) ? $term_color[0]['rgb'] : NULL;
  $map_bg_color = isset($term_bg_color[0]['rgb']) ? $term_bg_color[0]['rgb'] : NULL;
  $map_image_uri = isset($term_map_image[0]['uri']) ? $term_map_image[0]['uri'] : NULL;
  $map_image = file_create_url($map_image_uri);
  $icon_uri = isset($term_icon[0]['uri']) ? $term_icon[0]['uri'] : NULL;
  $icon = file_create_url($icon_uri);
  $map_icon_uri = isset($term_map_icon[0]['uri']) ? $term_map_icon[0]['uri'] : NULL;
  $map_icon = file_create_url($map_icon_uri);

  $vars['view']->map = array(
    'map_color' => $map_color,
    'map_bg_color' => $map_bg_color,
    'map_image' => $map_image,
    'icon' => $icon,
    'map_icon' => $map_icon,
    'states' => $states
  );
}

/**
 * Implements theme_qt_quicktabs().
 */
function crescent_services_qt_quicktabs($variables) {
  drupal_add_js(drupal_get_path('theme', 'crescent_services') . '/js/quicktabs_dlink.js');
  return theme_qt_quicktabs($variables);
}

/**
 * Implements hook_quicktabs_alter().
 */
function crescent_services_quicktabs_alter($info) {
  $param_name = isset($info->machine_name) ? $info->machine_name : '';
  $parametr = isset($_GET['qt']) ? $_GET['qt'] : '';
  if (is_numeric($parametr) && $param_name) {
    $_GET['qt-' . $param_name] = $parametr;
    unset($_GET['qt']);
  }
}