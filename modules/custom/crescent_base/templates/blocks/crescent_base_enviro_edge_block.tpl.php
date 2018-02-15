<?php
/**
 * @file
 * Crescent base theme block
 */
?>

<div class="b-envire-edge">

   <?php print render($block['find_link']);?>

    <div class="site-container">
        <div class="hd">
            <?php print render($block['logo_image']);?>
            <?php print render($block['login_link']);?>
        </div>
        <div class="text">
            <?php print render($block['text']);?>
        </div>
    </div>
</div>


