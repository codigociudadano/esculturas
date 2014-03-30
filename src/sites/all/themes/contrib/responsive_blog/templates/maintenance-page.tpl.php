<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in page.tpl.php. Some may be left
 * blank but they are provided for consistency.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 */
?>
<!DOCTYPE html>
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">

<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  <!--[if lt IE 9]><script src="<?php print base_path() . drupal_get_path('theme', 'responsive_blog') . '/js/html5.js'; ?>"></script><![endif]-->
</head>

<body class="<?php print $classes; ?>" <?php print $attributes;?>>


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
  </header>

  <div id="main" class="clearfix">
    <div id="primary">
      <section id="content" role="main">
        <div id="content-wrap">
          <?php print $messages; ?>
          <a id="main-content"></a>
          <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
          <?php print $content; ?><br/><br/>
        </div>
      </section> <!-- /#main -->
    </div>
  </div>
  
</div>

</body>
</html>
