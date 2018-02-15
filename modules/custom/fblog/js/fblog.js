
/**
 * @file
 * fblog.js
 * js behaviors for blog tree archive.
 */

(function ($) {

    Drupal.behaviors.fBlogs = {
        attach: function (context, settings) {

            var parents = $('.fblog-archive .btn-arrow.active, .fblog-archive a.active', context).parents("ul:not(.fblog-archive-list)");

            if (parents.length) {
                parents.addClass('active');
                parents.parent().find(".btn-arrow:first").addClass('active');
            } else {
                var first = $('.fblog-archive ul:not(.fblog-archive-list):first', context);
                first.addClass('active');
                first.find(".btn-arrow:first").addClass('active');
                first.find("ul:first").addClass('active');
                $('.fblog-archive ul.fblog-archive-list', context).find(".btn-arrow:first").addClass('active');
            }

            $('.fblog-archive .btn-arrow', context).click(function (e) {
                $(this).toggleClass('active');
                $(e.target).nextAll('ul').toggleClass('active');
            });
        },

        completedCallback: function () {
            // Do nothing. But it's here in case other modules/themes want to override it.
        }

    }
})(jQuery);