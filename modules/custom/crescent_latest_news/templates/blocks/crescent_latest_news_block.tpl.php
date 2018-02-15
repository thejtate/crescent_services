<?php
/**
 * @file
 * Crescent base theme block
 */
?>

<?php
$block_title = (isset($post_data['block_title'])) ? $post_data['block_title'] : "";
$title = (isset($post_data['title'])) ? $post_data['title'] : "";
$date = (isset($post_data['date'])) ? $post_data['date'] : NULL;
$date = format_date($date, "custom", "M j, Y");
$teaser = (isset($post_data['teaser'])) ? $post_data['teaser'] : "";
$image_url = (isset($post_data['image_url'])) ? $post_data['image_url'] : "";
$body = (isset($post_data['body'])) ? $post_data['body'] : "";
$url = (isset($post_data['url'])) ? $post_data['url'] : "";
$extension = " " . l(t('@more_text', array('@more_text' => t("Read More"))), $url, array('html' => TRUE, 'attributes' => array('class' => array('more-link'))));
$teaser = preg_replace('#^(.*)(\s?)(</[^>]+>)$#Us', '$1' . $extension . '$3', $teaser);
?>

<div class="hd"><?php print $block_title; ?></div>
<h3><a href="<?php print $url; ?>"><?php print $title; ?></a></h3>
<div class="date"><?php print $date; ?></div>
<?php if (!empty($image_url)): ?>
  <img src="<?php print $image_url; ?>" alt="<?php print $title; ?>" width="298"
       height="157">
<?php endif; ?>
<?php print $teaser; ?>
