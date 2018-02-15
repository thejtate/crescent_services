/**
 * Quick tabs url change.
 */
(function ($) {
  Drupal.behaviors.dlinkQuicktabs = {
    attach: function (context, settings) {
      $('.quicktabs-tabs li a', context).once('dlink', function () {
        $(this).unbind('click').bind('click', dlinkQuicktabsClick);
      });
    }
  };

  var dlinkQuicktabsClick = function () {
    var href = $(this).attr('href');
    var url = href.substring(0, href.indexOf('?') + 1);
    var start = href.indexOf('=') + 1;
    var end = href.indexOf('#');
    var tid = href.substring(start, end);
    history.pushState('', '', url + 'qt=' + tid);
    return false;
  }

})(jQuery);