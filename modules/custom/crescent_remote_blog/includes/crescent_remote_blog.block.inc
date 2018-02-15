<?php
/**
 * Created by PhpStorm.
 * User: Sergey Grigorenko (svipsa@gmail.com)
 * Date: 07.09.15
 * Time: 12:45
 */


/**
 * Implements hook_block_info().
 */
function crescent_remote_blog_block_info() {
  $blocks = array();
  $blocks['crescent_remote_blog_archive'] = array('info' => t('Remote Blog: Archive'));
  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function crescent_remote_blog_block_view($delta) {
  $block = array();
  switch ($delta) {
    case 'crescent_remote_blog_archive':
      $block = crescent_remote_blog_get_blog_archive();
      break;
  }
  return $block;
}

/**
 * Get archive of blog posts.
 * @return string
 *   html
 */
function crescent_remote_blog_get_blog_archive() {
  $query = db_select('field_data_field_crbp_date', 'fdate');

  $query->addExpression("DATE_FORMAT(field_crbp_date_value, '%M')", 'month');
  $query->addExpression("DATE_FORMAT(field_crbp_date_value, '%m')", 'month_digits');
  $query->addExpression("DATE_FORMAT(field_crbp_date_value, '%Y')", 'year');
  $query->addExpression("count(entity_id)", 'count');

  $query->leftJoin('crbps', 'n', 'n.eid = fdate.entity_id');
  $query->condition('n.deleted', 0);

  $query->groupBy('year');
  $query->groupBy('month_digits');
  $query->orderBy('year', 'desc');
  $query->orderBy('month_digits', 'desc');

  $rows = $query->execute()->fetchAll();

  $year_count = array();
  foreach ($rows as $row) {
    $year_count[$row->year] = (isset($year_count[$row->year])) ? $year_count[$row->year] + $row->count : $row->count;
  }

  $archive_data = array();
  foreach ($rows as $row) {
    $row->year_count = (isset($year_count[$row->year])) ? $year_count[$row->year] : 0;
    $archive_data[$row->year][$row->month] = $row;
  }


  $block['subject'] = t('Browse by month/Year');
  $block['content'] = theme('crescent_remote_blog_post_by_month', array(
    'archive' => $archive_data,
    'blog_base_path' => 'blog'
  ));
  return $block;
}