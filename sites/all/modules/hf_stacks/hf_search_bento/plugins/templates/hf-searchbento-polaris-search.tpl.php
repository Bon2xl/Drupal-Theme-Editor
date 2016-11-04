<div class="ajaxResult bnt-container">
  <!--  Unique ID for DIV that corresponds to the $delta of the block. Needed for AJAX to append to this DIV -->
  <div id="ajax<?php print str_replace(" ", "-", $delta); ?>" class="bnt-inner">
    <div class="bnt-ttl">
      <!--  The specific heading of the block (e.g., Books, Academic Journals, etc.)    -->
      <h2><?php print $sourceType; ?></h2>
    </div>
    <div class="bnt-item">
      <div class="bnt-content"></div>
      <!--  This seeMore Button will conditionally appear based on logic within the javascript file    -->
      <a class="bnt-see-more" id="seeMoreButton<?php print str_replace(" ", "-", $sourceType);?>" href="<?php print $catalogueUrl; ?>/searchresults.aspx?term=<?php print $query;?>&limit=TOM=<?php print substr($delta, 10);?>">See More...</a>
      <div class="ajax-loader">
        <img src=" <?php echo drupal_get_path('module', 'hf_search_bento') . '/images/ajax-loader.gif'; ?>">
      </div>
    </div>
  </div>
</div>