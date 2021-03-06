<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.templates.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
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
 * Page content (in order of occurrence in the default page.templates.php):
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
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.templates.php
 *
 * @ingroup themeable
 */
?>
<div class="container">
    <div class="row header">
        <div class="col-md-8"><?php if ($logo): ?>
                <a href="/">
                    <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
                </a>
            <?php endif; ?>
        </div>
        <div class="col-md-4">
            <div class="input-group">
                <input type="text" class="form-control" placeholder="Buscar">
                  <span class="input-group-btn">
                    <button class="btn btn-danger" type="button"><span class="glyphicon glyphicon-search"></span> </button>
                  </span>
            </div><!-- /input-group -->
        </div><!-- /.col-lg-6 -->
    </div><!-- /.row -->
    <div id="navbar" role="banner" class="<?php print $navbar_classes; ?>">
        <div class="navbar-wrapper">
            <!-- .btn-navbar is used as the toggle for collapsed navbar content -->
            <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
            </button>
        </div>

        <?php if (!empty($primary_nav) || !empty($secondary_nav) || !empty($page['navigation'])): ?>
            <div class="navbar-collapse collapse">
                <nav role="navigation">
                    <?php if (!empty($primary_nav)): ?>
                        <?php print render($primary_nav); ?>
                    <?php endif; ?>
                    <ul class="nav navbar-nav navbar-right">
                        <li>
                            <div class="leaf facebook">
                             <a href="#" onClick="window.open('https://www.facebook.com/sharer/sharer.php?u=' + location.href, '', 'height=550,width=525,left=100,top=100,menubar=0');">
                                    <i class="fa fa-facebook"></i>
                                </a>
                            </div><!--?php if (!empty($secondary_nav)): ?-->
                                <!--?php print render($secondary_nav); ?-->
                            <!--?php endif; ?--></li>
                        <li>
                          <div class="leaf twitter">
                              <a href="#" onClick="window.open('https://twitter.com/share?url='+location.href,'', 'height=550,width=525,left=100,top=100,menubar=0');return false;">
                                    <i class="fa fa-twitter"></i>
                                </a>
                          </div>
                        <li>
                           <div class="leaf google-plus">
                             <a href="#" onClick="window.open('https://plus.google.com/share?url='+location.href,'', 'height=550,width=525,left=100,top=100,menubar=0');return false;">
                                    <i class="fa fa-google-plus"></i>
                                </a>
                           </div>
                    </ul>
                    <?php if (!empty($page['navigation'])): ?>
                        <?php print render($page['navigation']); ?>
                    <?php endif; ?>
                </nav>
            </div>
        <?php endif; ?>
    </div>
</div>

<div class="main-container container">
    <?php if ($is_front): ?>
        <div class="my-slideshow">
            <!-- Indicators -->
            <ul class="bjqs">
                <li>
                    <img src="<?php echo base_path() . drupal_get_path('theme', 'resistenciarte') . '/images/slide1.png' ?>">
                    <h2 class="bjqs-caption">Descubra el “arte público” obteniendo información sobre la ubicación , artistas, historia, etc.</h2>
                </li>
                <li>
                    <img src="<?php echo base_path() . drupal_get_path('theme', 'resistenciarte') . '/images/slide3.png' ?>">
                    <h2 class="bjqs-caption">Lea más sobre los autores, sus biografías y sus obras en nuestra ciudad.</h2>
                </li>
                <li>
                    <img src="<?php echo base_path() . drupal_get_path('theme', 'resistenciarte') . '/images/slide2.png' ?>">
                    <h2 class="bjqs-caption">Aprenda sobre nuestros primeros monumentos urbanos y la historia de los mismos.</h2>
            </ul>
        </div>
    <?php endif; ?>

    <?php if (!$is_front): ?>
        <div class="row">

            <?php if (!empty($page['sidebar_first'])): ?>
                <aside class="col-sm-3" role="complementary">
                    <?php print render($page['sidebar_first']); ?>
                </aside>  <!-- /#sidebar-first -->
            <?php endif; ?>

            <section<?php print $content_column_class; ?>>
             <div class="well">
                <?php if (!empty($page['highlighted'])): ?>
                    <div class="highlighted jumbotron"><?php print render($page['highlighted']); ?></div>
                <?php endif; ?>
                <?php if (!empty($breadcrumb)): print $breadcrumb; endif;?>
                <a id="main-content"></a>
                <?php print render($title_prefix); ?>
                <?php if (!empty($title)): ?>
                    <h3 class="page-header"><?php print $title; ?></h3>
                <?php endif; ?>
                <?php print render($title_suffix); ?>
                <?php print $messages; ?>
                <?php if (!empty($tabs)): ?>
                    <?php print render($tabs); ?>
                <?php endif; ?>
                <?php if (!empty($page['help'])): ?>
                    <?php print render($page['help']); ?>
                <?php endif; ?>
                <?php if (!empty($action_links)): ?>
                    <ul class="action-links"><?php print render($action_links); ?></ul>
                <?php endif; ?>
                <?php print render($page['content']); ?>
                <?php if (!empty($page['content_bottom'])): ?>
                  <?php print render($page['content_bottom']); ?>
                <?php endif; ?>
                 </div>
            </section>

            <?php if (!empty($page['sidebar_second'])): ?>
                <aside class="col-sm-3" role="complementary">
                    <?php print render($page['sidebar_second']); ?>
                </aside>  <!-- /#sidebar-second -->
            <?php endif; ?>

        </div>
    <?php endif; ?>
</div>
<footer class="footer container">
    <div class="row">
        <div class="fcred col-sm-6">
          <span class="fcred-caption">
            <?= t('Desarrollado por')?> <a href="http://codigociudadano.cc" target="_blank"><?= t('Codigo Ciudadano') ?></a>
            <?= t(' con colaboracion de la ')?> <a href="http://fundacionurunday.org" target="_blank"><?= t('Fundación Urunday') ?></a>
          </span>
        </div>
        <div class="flinks col-sm-6">
            <div class="flinks-wrapper">
              <span class="flinks-caption"><?= t("ResistenciArte en tu celular:")?></span>
              <a href="https://play.google.com/store/apps/details?id=com.jmv.codigociudadano.resistenciarte" class="link-gplay"><img src="<?= $base_path.drupal_get_path('theme', 'resistenciarte').'/images/google_play_get.png'?>" alt="Disponible en Google Play"></a>
              <a href="http://www.windowsphone.com/s?appid=5e1cdb52-8ad9-4d38-987a-38ef7797054e" class="link-wpstore"><img src="<?= $base_path.drupal_get_path('theme', 'resistenciarte').'/images/wp_store_get.png'?>" alt="Descárgalo en la Tienda de Windows Phone"></a>
            </div>
        </div>
    </div>
</footer>
<script>

</script>
