<?php
/**
 * Created by PhpStorm.
 * User: Sergey Grigorenko (svipsa@gmail.com)
 * Date: 07.09.15
 * Time: 12:49
 */

class CrescentRemoteEntityPost extends Entity {
  /**
   * Override defaultUri().
   */
  protected function defaultUri() {
    return array('path' => 'remote-blog-post/' . $this->remote_id);
  }
}