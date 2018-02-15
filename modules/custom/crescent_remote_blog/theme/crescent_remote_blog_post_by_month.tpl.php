<?php
/**
 * @file
 * crescent-remote-blogs_post_by_month.tpl.php
 * theme archive blog
 */
?>
<div class="crescent-remote-blog-archive">
  <?php if (isset($archive) && is_array($archive)) : ?>
    <ul class="crescent-remote-blog-archive-list">
      <?php foreach ($archive as $year => $months): ?>
        <?php $month_first = reset($months); ?>
        <li>
          <?php if (!empty($months)) : ?>
            <?php
            $class = "";
            if (current_path() == $blog_base_path . '/all/' . $year) {
              $class = "active";
            }
            ?>
            <span class="btn-arrow <?php print $class; ?>"></span>
          <?php endif; ?>
          <a href="<?php print url($blog_base_path . '/all/' . $year); ?>" class="link-dropdown"><?php print $year; ?> <span
              class="number">(<?php print $month_first->year_count; ?>)</span></a>
          <ul class="<?php print $class; ?>">
            <?php foreach ($months as $month_name => $data): ?>
              <li>
                <?php if (isset($data->nodes) && is_array($data->nodes)) : ?>
                  <?php
                  $class = "";
                  if (current_path() == $blog_base_path . '/all/' . $data->year . '-' . $data->month_digits) {
                    $class = "active";
                  }
                  ?>
                  <span class="btn-arrow <?php print $class; ?>"></span>
                <?php endif; ?>
                <?php print l($month_name, $blog_base_path . '/all/' . $data->year . '-' . $data->month_digits, array("attributes" => array("class" => array("link-dropdown")))); ?>
                <span class="number">(<?php print $data->count; ?>)</span>

                <?php if (isset($data->nodes) && is_array($data->nodes)): ?>
                  <ul class="<?php print $class; ?>">
                    <?php foreach ($data->nodes as $nid => $title): ?>
                      <li><?php print l($title, 'node/' . $nid); ?></li>
                    <?php endforeach; ?>
                  </ul>
                <?php endif; ?>
              </li>
            <?php endforeach; ?>
          </ul>
        </li>
      <?php endforeach; ?>
    </ul>
  <?php endif; ?>
</div>