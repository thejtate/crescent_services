<?php

$date = strtotime($post->date);
$date = format_date($date, 'custom', "M j, Y");

?>


<div class="blog-wrapper remote-blog-post">
  <div class="date"><span
      class="date-display-single"><?php print $date; ?></span></div>
  <h3><?php print $post->title; ?></h3>

  <?php print $post->teaser_image; ?>
  <?php print $post->body; ?>
</div>