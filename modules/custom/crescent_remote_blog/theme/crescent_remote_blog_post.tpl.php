<?php


$post = $variables[CRESCENT_REMOTE_BLOG_ENTITY_TYPE];
$content['field_crescent_remote_blog_date']['#label_display'] = 'hidden';

$date = strtotime($post->entity_data->date);
$date = format_date($date, 'custom', "M j, Y");

$view_mode = (isset($variables['view_mode'])) ? $variables['view_mode'] : "full";
?>

<div class="remote-blog-post">
  <?php if ($view_mode == 'latest_news'): ?>

    <h3>
      <a href="<?php print url("remote-blog-post/" . $post->remote_id); ?>">
        <?php print $post->entity_data->title; ?>
      </a>
    </h3>

    <div class="date"><span
        class="date-display-single"><?php print $date; ?></span></div>

    <?php print $post->entity_data->teaser_image; ?>

    <?php
    $url = "remote-blog-post/" . $post->remote_id;
    $extension = " " . l(t('@more_text', array('@more_text' => t("Read More"))), $url, array(
        'html' => TRUE,
        'attributes' => array('class' => array('more-link'))
      ));
    $teaser = preg_replace('#^(.*)(\s?)(</[^>]+>)$#Us', '$1' . $extension . '$3', $post->entity_data->teaser);
    ?>
    <?php print $teaser; ?>


  <?php else: ?>
    <div class="date"><span
        class="date-display-single"><?php print $date; ?></span></div>
    <h3>
      <a href="<?php print url("remote-blog-post/" . $post->remote_id); ?>">
        <?php print $post->entity_data->title; ?>
      </a>
    </h3>

    <?php print $post->entity_data->teaser_image; ?>
    <?php print $post->entity_data->teaser; ?>

    <div class="btn-wrapp">
      <?php print l(t("See More"), "remote-blog-post/" . $post->remote_id, array("attributes" => array("class" => array("btn")))); ?>
    </div>
  <?php endif; ?>
</div>