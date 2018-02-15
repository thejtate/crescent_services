<?php

/**
 * @file
 * Settings forms
 */

/**
 * Create settings form in drupal configuration setings section for module.
 */
function fblog_admin_settings() {
  $form['fblog_settings_archive'] = array(
    '#type' => 'fieldset',
    '#title' => t('Blog Archive'),
    '#collapsible' => TRUE,
  );

  $form['fblog_settings_archive']['fblog_settings_nodes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show post titles in Archive?'),
    '#default_value' => variable_get('fblog_settings_nodes', 0),
    '#description' => t('Select "Yes" for show node titles in archive tree.'),
  );

  $form['fblog_settings_archive']['fblog_settings_count_nodes'] = array(
    '#type' => 'textfield',
    '#size' => 3,
    '#title' => t('Number of post titles in Archive'),
    '#description' => t('0 - show all titles.'),
    '#default_value' => variable_get('fblog_settings_count_nodes', 10),
  );

  $form['fblog_settings_category'] = array(
    '#type' => 'fieldset',
    '#title' => t('Blog Category'),
    '#collapsible' => TRUE,
  );

  $form['fblog_settings_category']['fblog_settings_category_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show categories for blog?'),
    '#default_value' => variable_get('fblog_settings_category_active', 0),
    '#description' => t('Select "Yes" for show categories for blog post.'),
  );

  return system_settings_form($form, TRUE);
}
