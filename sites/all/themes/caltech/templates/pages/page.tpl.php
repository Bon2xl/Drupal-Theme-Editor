<?php
/* HF locations bar */
$block = module_invoke('hf_locations', 'block_view', 'hf_location_bar');
print render($block['content']); 
?>

<!-- Top Header -->
<div id="top-header">
  <?php print render($page['top_header']); ?>
</div>
<!-- End Top Header -->
<div class="main-wrapper <?php print $classes; ?>">
  <!-- Header -->
  <div id="before-header">
  
  </div>
  <!-- Header -->
  <div id="header">
    <div class="header-row row">
      <div class="large-12 columns">
        <div class="section">
          <!-- Name and Slogan -->
          <div class="site-brand">
            <?php if ($logo): ?>
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
                <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
              </a>
            <?php endif; ?>

            <?php if ($site_name || $site_slogan): ?>
              <div id="name-and-slogan">
                <?php if ($site_name): ?>
                  <?php if ($title): ?>
                    <div id="site-name"><strong>
                      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
                    </strong></div>
                  <?php else: /* Use h1 when the content title is empty */ ?>
                    <h1 id="site-name">
                      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
                    </h1>
                  <?php endif; ?>
                <?php endif; ?>

                <?php if ($site_slogan): ?>
                  <div id="site-slogan"><?php print $site_slogan; ?></div>
                <?php endif; ?>
              </div>
            <?php endif; ?>
          </div>
          <!-- End Name and Slogan -->
          <a class="toggle-mobile right-off-canvas-toggle" href="#" ><span>Menu</span></a>
          <?php print render($page['header']); ?>
        </div>
      </div>
    </div>

    <!-- Search Region -->
    <?php print render($page['search']); ?>
    <!-- End Search Region -->

    <?php
    /* HF Quick links menu */
    $block = module_invoke('hf_quick_links_menu', 'block_view', 'hf_quick_links_menu_blocks');
    print render($block['content']);
    ?>

    <div class="main-gradient"></div>
    <div class="main-background"></div>
  </div>
  <!-- End Header -->

  <!-- Breadcrumbs & Messages -->
  <?php if  ($breadcrumb): ?><div id="breadcrumb" class="row"><?php //print $breadcrumb; ?></div><?php endif; ?>
  <?php if ($show_messages && $messages): print $messages; endif; ?>
  <!-- End Breadcrumbs & Messages -->

  

  <!-- Before Content -->
  <?php print render($page['before_content']); ?>
  <!-- End Before Content -->

  <!-- Main Wrapper -->
  <div id="content-wrapper" class="row">
    <div class="large-12 columns">
      <div class="section-wrapper clearfix">
        <?php if(!drupal_is_front_page()) : ?>
          <div id="page-title" class="row full-width">
            <div class="large-12 columns">
              <?php print render($title_prefix); ?><?php if ($title): ?><h1 class="page-title"><?php print $title; ?><?php endif; ?></h1>
              <?php print render($title_suffix); ?>
            </div>
          </div>
        <?php endif; ?>
        <!-- Tabs -->
        <div id="tabs-and-link" class="row full-width">
          <div class="large-12 columns">
            <div class="section">
              <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
              <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
            </div>
          </div>
        </div>
        <!-- Tabs -->
        <!-- Main Content -->
        <div id="main" class="row full-width clearfix">
          <?php if ($page['sidebar_left']): print render($page['sidebar_left']); endif; ?>
          <?php if ($page['sidebar_left'] && $page['sidebar_right']): ?>
            <div class="main-content large-6 columns">
          <?php elseif ($page['sidebar_left'] || $page['sidebar_right']) : ?>
            <div class="main-content large-9 columns">
          <?php else : ?>
            <div class="main-content large-12 columns">
          <?php endif; ?>
              <?php print render($page['content']); ?>
            </div>
          <?php if ($page['sidebar_right']): print render($page['sidebar_right']); endif; ?>
        </div>
        <!-- End Main Content -->
      </div>
    </div>
  </div>

  <!-- End Main Wrapper -->

  <?php print render($page['after_content']); ?>
  <?php print render($page['sub_footer']); ?>
  <?php print render($page['footer']) ?>
</div>
<?php print render($page['mobile_menu']) ?>
<!-- Modals -->
<div id="stacks-modal" class="reveal-modal" data-reveal aria-labelledby="stacks-modal" aria-hidden="true" role="dialog">
  <span class="spinner"><i class="fa fa-spinner fa-spin fa-2x"></i></span>
  <h2></h2>
  <div class="content"></div>
  <a class="close-reveal-modal close-stacks-modal" aria-label="Close">&#215;</a>
</div>

