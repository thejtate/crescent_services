(function ($) {

    Drupal.behaviors.captchaFunnel = {
        attach: function (context) {
            $.each(Drupal.settings.funnel_captcha, function(formId, value) {

                $('#' + formId, context).once('funnel-captcha', function(key, form){
                    var $form = $(form),
                        $humanToken = $form.find('[name="human_token"]');
                    $humanToken.val(value);
                });
            });

            $('.funnel-reload-captcha', context).not('.processed').bind('click', function () {
                $(this).addClass('processed');
                var $form = $(this).parents('form');
                // send post query for getting new captcha data
                var date = new Date();
                var url = this.href + '?' + date.getTime();
                $.get(
                    url,
                    {},
                    function (response) {
                        if(response.status == 1) {
                            $('.captcha', $form).find('img').attr('src', response.data.url);
                            $('input[name=captcha_sid]', $form).val(response.data.sid);
                            $('input[name=captcha_token]', $form).val(response.data.token);
                            $('input[name=human_token]', $form).val(response.data.human_token);
                        }
                        else {
                            alert(response.message);
                        }
                    },
                    'json'
                );
                return false;
            });

        }
    };

})(jQuery);