
/**
 * @file
 * fblog.js
 * js behaviors for blog tree archive.
 */

(function ($) {

    Drupal.behaviors.crescent_remote_blog = {
        attach: function (context, settings) {

            var parents = $('.crescent-remote-blog-archive .btn-arrow.active, .crescent-remote-blog-archive a.active', context).parents("ul:not(.crescent-remote-blog-archive-list)");

            if (parents.length) {
                parents.addClass('active');
                parents.parent().find(".btn-arrow:first").addClass('active');
            } else {
                var first = $('.crescent-remote-blog-archive ul:not(.crescent-remote-blog-archive-list):first', context);
                first.addClass('active');
                first.find(".btn-arrow:first").addClass('active');
                first.find("ul:first").addClass('active');
                $('.crescent-remote-blog-archive ul.crescent-remote-blog-archive-list', context).find(".btn-arrow:first").addClass('active');
            }

            $('.crescent-remote-blog-archive .btn-arrow', context).click(function (e) {
                $(this).toggleClass('active');
                $(e.target).nextAll('ul').toggleClass('active');
            });
        },

        completedCallback: function () {
            // Do nothing. But it's here in case other modules/themes want to override it.
        }

    }
})(jQuery);