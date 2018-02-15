(function ($) {

  if (typeof Drupal != 'undefined') {
    Drupal.behaviors.projectName = {
      attach: function (context, settings) {
        init();
      },

      completedCallback: function () {
        // Do nothing. But it's here in case other modules/themes want to override it.
      }
    }
  }

  $(function () {
    if (typeof Drupal == 'undefined') {
      init();
    }

    $(window).load(function () {
      initTabsBg();
      initDropdownMenu();
      initBtnMenu();
    });
  });

  function init() {
    mobileDetect();
    initTabs();
    initTopMenu();
    initContactTabs();
    //initFlexSlider();
  }

  function initFlexSlider() {
    $('.flexslider').flexslider({
      animation: "slide",
      prevText: "",           //String: Set the text for the "previous" directionNav item
      nextText: ""
    });
  }

  function initBtnMenu() {

    var $width = $(window).outerWidth();

    $(window).on('resize', function () {
      $width = $(window).outerWidth();
    });

    var $expanded = $('.nav .expanded > a');

    $expanded.on('click touch', function (e) {
      if ($width < 980) {
        e.preventDefault();

        var $this = $(this),
          $parent = $this.parent('li'),
          $menu = $parent.children('.menu');

        if ($this.hasClass('opened')) {
          $this.removeClass('opened');
          $menu.hide()

        } else {
          $this.addClass('opened');
          $menu.show();
        }
      } else {
        return;
      }
    })
  }

  function initTabs() {

    if ($(window).outerWidth() > 980) return;

    var $wrapper = $('.quicktabs-wrapper');

    if ($wrapper.hasClass('quicktabs-wrapper-processed')) return;

    $wrapper.addClass('quicktabs-wrapper-processed');

    var $list = $wrapper.find('.item-list'),
      $nav = $list.find('.quicktabs-tabs');

    $list.prepend('<span class="title-nav">' + $list.find('.quicktabs-tabs li.active').html() + '</span>');
    var $title = $wrapper.find('.title-nav');

    $title.on('click touch', function (e) {
      e.preventDefault();
    })

    $list.on('click touch', function () {

      if ($list.hasClass('active')) {
        $list.removeClass('active');
        $nav.slideUp();

      } else {
        $list.addClass('active');
        $nav.slideDown();
      }
    });

    $nav.find('li a').on('click touch', function () {
      $list.removeClass('active');
      $nav.slideUp();
      $title.html($(this).clone());
    })
  }

  function mobileDetect() {
    if (navigator.userAgent.match(/Android/i)
      || navigator.userAgent.match(/webOS/i)
      || navigator.userAgent.match(/iPhone/i)
      || navigator.userAgent.match(/iPad/i)
      || navigator.userAgent.match(/iPod/i)
      || navigator.userAgent.match(/BlackBerry/i)
      || navigator.userAgent.match(/Windows Phone/i)
    ) {
      $('body').addClass('mobile-device');
    }
  }

  function initTopMenu() {


    $('.hamburger-wrapper').on('click touch', function (e) {

      e.preventDefault();

      if ($('.header-bottom').hasClass('active')) {
        $('.header-bottom').removeClass('active');
        $('.header-top').slideUp();
      } else {
        $('.header-bottom').addClass('active');
        $('.header-top').slideDown();
      }
    })
  }

  function initTabsBg() {
    var $wrapper = $('.b-tabs-wrapper');

    if ($('body').hasClass('mobile-device')) return;

    if (!$wrapper.length || $wrapper.hasClass('tabs-wrapper-processed')) return;

    $wrapper.addClass('tabs-wrapper-processed');

    var height = 0;

    height += $wrapper.find('.quicktabs-tabs').outerHeight(true);

    if ($wrapper.siblings('.content').children().length > 0) {
      height += $wrapper.siblings('.content').outerHeight(true);
    }

    height += $wrapper.siblings('.title').outerHeight(true);

    if ($(window).outerWidth() < 980) {
      return;
    } else {
      $wrapper.parent().prepend('<span style="height: ' + height + 'px;" class="bg"></span>');
    }
  }

  function initContactTabs() {
    var $wrapper = $('.b-tabs');

    if (!$wrapper.length || $wrapper.hasClass('tabs-processed')) return;

    $wrapper.addClass('tabs-processed');

    var $controlsWrapper = $wrapper.find('.control-wrapper');
    var $controlsListWrapper = $controlsWrapper.find('.contacts-states');
    var $controlsInnerWrapper = $controlsListWrapper.find(' ul');

    var config = {
      listWrapperClassName: 'list-wrapper',
      titleClassName: 'list-title',
      mapDescWrapperClassName: 'map-desc-wrapper',
      prefix: 'map-'
    };

    var isMobile = window.matchMedia("only screen and (max-width: 979px)");

    $controlsListWrapper.each(addStatesBg);
    $controlsListWrapper.each(addMapIcon);

    if (isMobile.matches) {
      $controlsListWrapper.each(addIcon);
      addTitle($controlsInnerWrapper, 'Select city');
    } else {
      $controlsListWrapper.prepend("<li data-state-id='state-ALL'><a href='state-ALL'>All States</a></li>");
    }

    addTitle($controlsListWrapper, 'Select A Location');

    function addTitle(el, title) {
      if (!el.parent().hasClass(config.listWrapperClassName)) {
        el.wrap('<div class="' + config.listWrapperClassName + '"></div>');
        el.parent().prepend('<div class="' + config.titleClassName + '">' + title + '</div>');
      }
    }

    $controlsWrapper.on('click touch', checkTarget);
    $(".map .map-desc-wrapper .map-desc").on('click touch', checkTarget);

    $('html').on('click touch', function (e) {
      var $target = $(e.target);

      if (!$target.closest('.' + config.listWrapperClassName).length) {
        hideDDlist();
      }
    });

    function checkTarget(e) {
      e.preventDefault();

      var $target = $(e.target);
      var $targetParent = $target.parent();

      if ($target.hasClass(config.titleClassName)) {
        checkActiveList($target);
      } else if ($targetParent.attr('data-state-id') && !$targetParent.hasClass('active')) {
        showMap($target);
        addActiveListItem($targetParent);
        if (isMobile.matches) {
          appendCities($target);
        }
        addText($target, $target.text());
        hideCites($target);
        hideMapDesc($target);
        hideDDlist();
        //addActiveStateBg($target, $targetParent.attr('data-state-id'));
        showStateCites($target);
        if ($targetParent.attr('data-state-id') == 'state-ALL') {
          showAllStatesMap($target);
        }
      } else if ($targetParent.attr('data-city-id') && !$targetParent.hasClass('active')) {
        showMap($target);
        addActiveListItem($targetParent);
        addText($target, $target.text());
        showCity($target, $targetParent.attr('data-city-id'));
        hideMapDesc($target);
        showMapDesc($target, $targetParent.attr('data-city-id'));
        hideDDlist();
      } else if ($targetParent.hasClass('link-show-all')) {
        setDefaultStateBg($target);
        showAllLocations($target);
      } else if ($targetParent.hasClass('map-desc') && $targetParent.hasClass('active')) {
        showCityOnClick($target);
      }
    }

    function showStateCites(el) {
      var $stateCitesList = el.siblings('ul');
      var $cites = $stateCitesList.find("li");
      hideMapDesc(el);
      $cites.each(function () {
        var $this = $(this);
        var id = $this.attr('data-city-id');
        el.parents('.control-wrapper').siblings('.map').find('#' + config.prefix + id).addClass('active');
      });
    }

    function hideDDlist() {
      $wrapper.find('.' + config.listWrapperClassName).removeClass('active');
    }

    function addText(el, text) {
      el.parents('ul').siblings('.' + config.titleClassName).text(text);
    }

    function addActiveListItem(el) {
      el.parents('.contacts-states').find('li').removeClass('active');
      el.siblings('li').removeClass('active');
      el.addClass('active');
    }

    function appendCities(el) {
      var $listWrapper = el.parents('.' + config.listWrapperClassName);
      var $allListWrappers = $listWrapper.siblings('.' + config.listWrapperClassName);

      if ($allListWrappers.length > 0) {
        $allListWrappers.last().remove();
      }

      el.parents('.control-wrapper').siblings('.map').show();
      $listWrapper.parent().append(el.siblings('.' + config.listWrapperClassName).clone());
    }

    function addIcon() {
      var $this = $(this);
      var icon = $this.attr('data-icon');

      $this.parents('.control-wrapper').siblings('.view-contact').find('.map-icon').html('<img alt="" src="' + icon + '">');
    }

    function addStatesBg() {
      var $list = $(this);
      var $listItems = $list.find('> li');
      var bg = $list.attr('data-bg-color').replace('#', '');

      $controlsWrapper.eq($list.parents('.quicktabs-tabpage').index()).siblings('.map').find('.map-img').maphilight({
        fillOpacity: 0,
        strokeColor: 'f2f2f2',
        strokeWidth: 0,
        stroke: false,
        fillColor: bg
      });

      $listItems.each(function () {
        var $this = $(this);
        var id = $this.attr('data-state-id').toLowerCase();
        var $currentArea = $this.parents('.control-wrapper').siblings('.map').find('#' + id);

        $currentArea.addClass('active');
        $currentArea.attr('data-maphilight', '{"fillColor":"' + bg + '"}');
        $currentArea.data('maphilight', '{"fillColor":"' + bg + '"}');

        var data = $currentArea.data('maphilight');
        data = JSON.parse(data);
        data.alwaysOn = true;
        data.fillOpacity = 1;
        data.strokeWidth = 2;
        data.stroke = true;
        $currentArea.data('maphilight', data).trigger('alwaysOn.maphilight');
      });
    }

    function addActiveStateBg(el, id) {
      setDefaultStateBg(el);

      var id = id.toLowerCase();
      var bg = el.parents('ul').attr('data-highlited-color').replace('#', '');
      var $currentArea = el.parents('.control-wrapper').siblings('.map').find('#' + id);

      $currentArea.attr('data-maphilight', '{"fillColor":"' + bg + '"}');
      $currentArea.data('maphilight', '{"fillColor":"' + bg + '"}');

      var data = $currentArea.data('maphilight');
      data = JSON.parse(data);
      data.alwaysOn = true;
      data.fillOpacity = 1;
      data.strokeWidth = 2;
      data.stroke = true;
      $currentArea.data('maphilight', data).trigger('alwaysOn.maphilight');
    }

    function setDefaultStateBg(el) {
      var $wrapper = el.parents('.control-wrapper');
      var $wrapperList = $wrapper.find('.' + config.listWrapperClassName).first();
      var bg = $wrapperList.find('> ul').attr('data-bg-color').replace('#', '');
      var $areas = $wrapper.siblings('.map').find('area.active');

      $areas.each(function () {
        var $currentArea = $(this);

        $currentArea.attr('data-maphilight', '{"fillColor":"' + bg + '"}');
        $currentArea.data('maphilight', '{"fillColor":"' + bg + '"}');

        var data = $currentArea.data('maphilight');
        data = JSON.parse(data);
        data.alwaysOn = true;
        data.fillOpacity = 1;
        data.strokeWidth = 2;
        data.stroke = true;
        $currentArea.data('maphilight', data).trigger('alwaysOn.maphilight');
      });
    }

    function showCityOnClick(el) {
      var $parent = el.parent(".map-desc");
      var parentId = $parent.attr("id");
      var id = parentId.replace(config.prefix, '');
      $parent.parent(".map-desc-wrapper").find(".map-desc.selected").removeClass('selected');
      $parent.addClass('selected');
      el.parents('.map').siblings('.view-contact').find('.views-row').removeClass('active');
      el.parents('.map').siblings('.view-contact').find('#' + id).parent().addClass('active');
    }

    function addMapIcon() {
      var $this = $(this);
      var $listOfCities = $this.find('li li');
      var icon = $this.attr('data-map-icon');
      var $wrapper = $this.parents('.control-wrapper').siblings('.map');
      var stringToAppend = '<div class="' + config.mapDescWrapperClassName + '">';

      $listOfCities.each(function () {
        var $this = $(this);
        var state = $this.parent('ul').siblings('a').text();
        stringToAppend += '<div id="' + config.prefix + $this.attr('data-city-id') +
        '" style="left: ' + $this.attr('data-coords-left') + 'px; top: ' +
        (parseInt($this.attr('data-coords-top')) + 25) + 'px;" class="map-desc active">' +
        '<img src="' + icon + '" alt=""/>';
        stringToAppend += '<div class="pulse"></div>';
        stringToAppend += '<span class="city">' + $this.text() + ', ' + state + '</span></div>';
      });

      stringToAppend += '</div>';

      $wrapper.append(stringToAppend);
    }

    function showMapDesc(el, id) {
      //hideMapDesc(el);
      el.parents('.control-wrapper').siblings('.map').find('#' + config.prefix + id).addClass('active');
      el.parents('.control-wrapper').siblings('.map').find('#' + config.prefix + id).addClass('selected');
    }

    function hideMapDesc(el) {
      el.parents('.control-wrapper').siblings('.map').find('.map-desc').removeClass('active');
      el.parents('.control-wrapper').siblings('.map').find('.map-desc').removeClass('selected');
    }

    function showCity(el, id) {
      hideCites(el);
      el.parents('.control-wrapper').siblings('.view-contact').find('#' + id).parent().addClass('active');
    }

    function hideCites(el) {
      el.parents('.control-wrapper').siblings('.view-contact').find('.views-row').removeClass('active show-all');
      el.parents('.control-wrapper').siblings('.view-contact').find('.views-row').removeClass('selected');
    }

    function checkActiveList(el) {
      var $parent = el.closest('.list-wrapper');

      if ($parent.hasClass('active')) {
        $parent.removeClass('active');
      } else {
        $parent.addClass('active');
      }
    }

    function showAllLocations(el) {
      var $listWrapper = el.parent().siblings('.' + config.listWrapperClassName);

      if ($listWrapper.length > 1) {
        $listWrapper.last().remove();
      }

      $listWrapper.find('.' + config.titleClassName).first().text('Select A Location');
      $listWrapper.find('> ul > li').removeClass('active');

      el.parents('.control-wrapper').siblings('.view-contact').find('.views-row').addClass('active show-all');
      el.parents('.control-wrapper').siblings('.map').hide().find('.map-desc').addClass('active');
    }

    function showMap(el) {
      el.parents('.control-wrapper').siblings('.map').show();
    }

    function showAllStatesMap(el) {
      var $mapDesc = el.parents('.control-wrapper').siblings('.map').find('.map-desc-wrapper .map-desc');
      $mapDesc.addClass('active');
    }
  }

  function initDropdownMenu() {
    var $elem = $('.site-header .expanded');

    $elem.on('click', function () {

      if ($(this).hasClass('opened')) {
        $(this).removeClass('opened');
        $(this).find('.menu').hide();

      } else {
        $(this).addClass('opened');
        $(this).find('.menu').show();
      }
    })

    $elem.on('mouseout', function(){
      $(this).removeClass('opened');
      $(this).find('.menu').hide();
    })
  }

})(jQuery);