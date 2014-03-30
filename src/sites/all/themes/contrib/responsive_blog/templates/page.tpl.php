<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/garland.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>
<div id="wrapper">
  <header id="header" class="clearfix">
    <?php if (theme_get_setting('image_logo','responsive_blog')): ?>
      <?php if ($logo): ?><div id="site-logo"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
      </a></div><?php endif; ?>
    <?php else: ?>
      <hgroup id="site-name-wrap">
        <h1 id="site-name">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
            <span><?php print $site_name; ?></span>
          </a>
        </h1>
        <?php if ($site_slogan): ?><h2 id="site-slogan"><?php print $site_slogan; ?></h2><?php endif; ?>
      </hgroup>
    <?php endif; ?>
    <?php if (theme_get_setting('socialicon_display', 'responsive_blog')): ?>
        <?php 
        $twitter_url = check_plain(theme_get_setting('twitter_url', 'responsive_blog')); 
        $facebook_url = check_plain(theme_get_setting('facebook_url', 'responsive_blog')); 
        $google_plus_url = check_plain(theme_get_setting('google_plus_url', 'responsive_blog')); 
        $pinterest_url = check_plain(theme_get_setting('pinterest_url', 'responsive_blog'));
        ?>
      <div class="social-profile">
        <ul>
          <?php if ($facebook_url): ?><li class="facebook">
            <a target="_blank" title="<?php print $site_name; ?> in Facebook" href="<?php print $facebook_url; ?>"><?php print $site_name; ?> Facebook </a>
          </li><?php endif; ?>
          <?php if ($twitter_url): ?><li class="twitter">
            <a target="_blank" title="<?php print $site_name; ?> in Twitter" href="<?php print $twitter_url; ?>"><?php print $site_name; ?> Twitter </a>
          </li><?php endif; ?>
          <?php if ($google_plus_url): ?><li class="google-plus">
            <a target="_blank" title="<?php print $site_name; ?> in Google+" href="<?php print $google_plus_url; ?>"><?php print $site_name; ?> Google+ </a>
          </li><?php endif; ?>
          <?php if ($pinterest_url): ?><li class="pinterest">
            <a target="_blank" title="<?php print $site_name; ?> in Pinterest" href="<?php print $pinterest_url; ?>"><?php print $site_name; ?> Twitter </a>
          </li><?php endif; ?>
          <li class="rss">
            <a target="_blank" title="<?php print $site_name; ?> in RSS" href="<?php print $front_page; ?>rss.xml"><?php print $site_name; ?> RSS </a>
          </li>
        </ul>
      </div>
    <?php endif; ?>
    <nav id="navigation" role="navigation">
      <div id="main-menu">
        <?php 
          if (module_exists('i18n_menu')) {
            $main_menu_tree = i18n_menu_translated_tree(variable_get('menu_main_links_source', 'main-menu'));
          } else {
            $main_menu_tree = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
          }
          print drupal_render($main_menu_tree);
        ?>
      </div>
    </nav>
  </header>

  <div id="preface-area" class="clearfix">
    <?php if($page['preface_first'] || $page['preface_middle'] || $page['preface_last']) : ?>
    <div id="preface-block-wrap" class="clearfix in<?php print (bool) $page['preface_first'] + (bool) $page['preface_middle'] + (bool) $page['preface_last']; ?>">
      <?php if($page['preface_first']): ?><div class="preface-block">
        <?php print render ($page['preface_first']); ?>
      </div><?php endif; ?>
      <?php if($page['preface_middle']): ?><div class="preface-block">
        <?php print render ($page['preface_middle']); ?>
      </div><?php endif; ?>
      <?php if($page['preface_last']): ?><div class="preface-block">
        <?php print render ($page['preface_last']); ?>
      </div><?php endif; ?>
    </div>
    <?php endif; ?>

    <?php print render($page['header']); ?>
  </div>

  <div id="main" class="clearfix">
    <div id="primary">
      <section id="content" role="main">
        <?php if ($is_front): ?>
        <?php if (theme_get_setting('slideshow_display','responsive_blog')): ?>
        <?php 
        $slide1_url = check_plain(theme_get_setting('slide1_url','responsive_blog'));
        $slide2_url = check_plain(theme_get_setting('slide2_url','responsive_blog'));
        $slide3_url = check_plain(theme_get_setting('slide3_url','responsive_blog'));
        $slide1_desc = check_markup(theme_get_setting('slide1_desc', 'responsive_blog'), 'full_html'); 
        $slide2_desc = check_markup(theme_get_setting('slide2_desc', 'responsive_blog'), 'full_html'); 
        $slide3_desc = check_markup(theme_get_setting('slide3_desc', 'responsive_blog'), 'full_html'); 
        ?>
        <div id="slider">
          <div id="slider-wrap">
            <div class="slides displayblock">
              <a href="<?php print url($slide1_url); ?>"><img width="644" height="320" src="<?php print base_path() . drupal_get_path('theme', 'responsive_blog') . '/images/slide-image-1.jpg'; ?>" class="pngfix"/></a>
              <?php if($slide1_desc) { print '<div class="featured-text">' . $slide1_desc . '</div>'; } ?><!-- .featured-text -->
            </div> <!-- .slides -->

            <div class="slides displaynone">
              <a href="<?php print url($slide2_url); ?>"><img width="644" height="320" src="<?php print base_path() . drupal_get_path('theme', 'responsive_blog') . '/images/slide-image-2.jpg'; ?>" class="pngfix"/></a>
              <?php if($slide1_desc) { print '<div class="featured-text">' . $slide2_desc . '</div>'; } ?><!-- .featured-text -->
            </div> <!-- .slides -->

            <div class="slides displaynone">
              <a href="<?php print url($slide3_url); ?>"><img width="644" height="320" src="<?php print base_path() . drupal_get_path('theme', 'responsive_blog') . '/images/slide-image-3.jpg'; ?>" class="pngfix"/></a>
              <?php if($slide1_desc) { print '<div class="featured-text">' . $slide3_desc . '</div>'; } ?><!-- .featured-text -->
            </div> <!-- .slides -->
          </div>
          <div id="nav-slider">
            <div class="nav-previous"><img class="pngfix" src="<?php print base_path() . drupal_get_path('theme', 'responsive_blog') . '/images/previous.png'; ?>" alt="next slide"></div>
            <div class="nav-next"><img class="pngfix" src="<?php print base_path() . drupal_get_path('theme', 'responsive_blog') . '/images/next.png'; ?>" alt="next slide"></div>
          </div>
        </div>
        <?php endif; ?>
        <?php endif; ?>

        <?php if (theme_get_setting('breadcrumbs')): ?><?php if ($breadcrumb): ?><div id="breadcrumbs"><?php print $breadcrumb; ?></div><?php endif;?><?php endif; ?>
        <?php print $messages; ?>
        <?php if ($page['content_top']): ?><div id="content_top"><?php print render($page['content_top']); ?></div><?php endif; ?>
        <div id="content-wrap">
          <?php print render($title_prefix); ?>
          <?php if ($title): ?><h1 class="page-title"><?php print $title; ?></h1><?php endif; ?>
          <?php print render($title_suffix); ?>
          <?php if (!empty($tabs['#primary'])): ?><div class="tabs-wrapper clearfix"><?php print render($tabs); ?></div><?php endif; ?>
          <?php print render($page['help']); ?>
          <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
          <?php print render($page['content']); ?>
        </div>
      </section> <!-- /#main -->
    </div>

    <?php if ($page['sidebar_first']): ?>
      <aside id="sidebar" role="complementary">
       <?php print render($page['sidebar_first']); ?>
      </aside> 
    <?php endif; ?>
  </div>

  <footer id="footer-bottom">
    <div id="footer-area" class="clearfix">
      <?php if ($page['footer_first'] || $page['footer_second'] || $page['footer_third']): ?>
        <div id="footer-block-wrap" class="clearfix in<?php print (bool) $page['footer_first'] + (bool) $page['footer_second'] + (bool) $page['footer_third']; ?>">
          <?php if($page['footer_first']): ?><div class="footer-block">
            <?php print render ($page['footer_first']); ?>
          </div><?php endif; ?>
          <?php if($page['footer_second']): ?><div class="footer-block">
            <?php print render ($page['footer_second']); ?>
          </div><?php endif; ?>
          <?php if($page['footer_third']): ?><div class="footer-block">
            <?php print render ($page['footer_third']); ?>
          </div><?php endif; ?>
        </div>
      <?php endif; ?>
      
      <?php print render($page['footer']); ?>
    </div>

    <div id="bottom" class="clearfix">
      <div class="copyright"><?php print t('Copyright'); ?> &copy; <?php echo date("Y"); ?>, <a href="<?php print $front_page; ?>"><?php print $site_name; ?></a></div>
      <div class="credit"><?php print t('Theme by'); ?>  <a href="http://www.devsaran.com" target="_blank">Devsaran</a></div>
    </div>
  </footer>

</div>






