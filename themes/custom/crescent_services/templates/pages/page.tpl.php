<?php
$right_sidebar = render($page['right_sidebar']);
?>


<div class="outer-wrapper">
  <header id="site-header" class="site-header">
    <div class="header-top">
      <?php if ($top_menu): ?>
        <div class="menu">
          <?php print $top_menu; ?>
        </div>
      <?php endif; ?>
    </div>
    <div class="header-bottom">
      <div class="site-container">

        <?php if ($logo): ?>
          <div class="logo">
            <a href="<?php print $front_page; ?>"
               title="<?php print t('Home'); ?>"
               rel="home" id="logo">
              <img src="<?php print $logo; ?>"
                   alt="<?php print t('Home'); ?>"/>
            </a>
          </div>
        <?php endif; ?>

        <?php print render($page['header']); ?>
        <?php if ($main_menu): ?>
          <div class="hamburger-wrapper">
            <a href="#" class="hamburger"></a>
          </div>
          <nav class="nav">
            <?php print $main_menu; ?>
          </nav>
        <?php endif; ?>

      </div>
    </div>
  </header>

  <?php if ($top_media = render($page['top_media'])): ?>
    <?php print $top_media; ?>
  <?php endif; ?>

  <?php print render($page['content_top']); ?>

  <?php if ($messages = render($messages)): ?>
    <?php print $messages; ?>
  <?php endif; ?>
  <?php if ($tabs = render($tabs)): ?>
    <div class="tabs">
      <?php print $tabs; ?>
    </div>
  <?php endif; ?>

  <div class="inner-wrapper site-container">
    <div class="content-wrapper <?php if ($right_sidebar) {
      print 'with-sidebar';
    } ?>">


      <?php print render($page['content']); ?>

      <?php if ($right_sidebar): ?>
        <aside class="sidebar">
          <?php print $right_sidebar; ?>
        </aside>
      <?php endif; ?>

    </div>
  </div>

  <?php print render($page['content_bottom']); ?>

  <footer id="site-footer" class="site-footer">
    <div class="site-container">
      <div class="logo"><a href="<?php print url('<front>'); ?>"><img
            src="<?php print base_path() . path_to_theme(); ?>/images/logo-min.png"
            alt=""></a>
      </div>

      <?php if ($footer_menu): ?>
        <div class="menu">
          <?php print $footer_menu; ?>
        </div>
      <?php endif; ?>

      <?php print render($page['footer']); ?>
    </div>
  </footer>
</div>