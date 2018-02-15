<?php
/**
 * @file
 * Crescent base theme block
 */
?>

<div class="b-news latest-news-block">
  <div class="site-container">
    <h2><?php print t("Latest News") ?></h2>

    <div class="cols cols-three">
      <?php foreach ($blocks as $key => $block): ?>
        <div
          class="col col-<?php print ($key + 1); ?>"><?php print $block; ?></div>
      <?php endforeach; ?>
    </div>
  </div>
</div>


