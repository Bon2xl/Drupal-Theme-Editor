<?php
//Check to see if there are results
if(count($collections) > 0) : ?>
  <?php foreach($collections as $key => $value): ?>
    <?php $facet = $value[0]['realType']; //needed for the facetAPI to determine which content type to filter results from solr. ?>
    <div class="bnt-container id-bnt-<?php echo $facet; ?>">
      <div class="bnt-inner">
        <div class="bnt-ttl">
          <h2><?php echo $key; ?></h2>
        </div>
        <div class="bnt-item">
          <div class="bnt-content">
            <div class="bnt-result">
              <?php foreach($value as $result): //Iterate through each of the search items under these heading ?>
                <div class="bnt-result-item bento-solr row">
                  <div class="small-3 medium-2 large-2 columns cover text-center">
                    <?php
                    if ($result['realType'] == 'event') {
                      echo "<span class=\"fa fa-calendar-o\"></span>";
                    }
                    if ($result['realType'] == 'news') {
                      echo "<span class=\"fa fa-newspaper-o\"></span>";
                    }
                    if ($result['realType'] == 'e_resource') {
                    echo "<span class=\"fa fa-database\"></span>";
                    }
                    if ($result['realType'] == 'directory_listing') {
                      echo "<span class=\"fa fa-address-card\"></span>";
                    }
                    ?>
                  </div>
                  <div class="small-9 medium-5 large-10 columns">
                    <h5 class="bnt-item-ttl"><?php print ($result['url']) ? l($result['title'], $result['url']['path'], $result['url']['options']) : check_plain($result['title']); ?></h5>
                    <p class="summary"><?php print strip_tags($result['snippet'], "<strong>"); ?></p>
                  </div>
                </div>
              <?php endforeach; ?>
            </div>
          </div>
          <!--    If resultCount is greater than the result limit, show the seeMore button  -->
          <?php if($resultCount > $limit): ?>
            <a class="bnt-see-more" href="<?php print drupal_get_path() . "/solr?bentoq=" . $query . "&f[0]=type:" . $facet; ?>">See More... (<?php echo $resultCount; ?>)</a>
          <?php endif; ?>
        </div>
      </div>
    </div>
  <?php endforeach; ?>   
 
<?php 
//Display empty result message
else: ?>
  <?php if($collections === null): ?>
    <div class="bnt-container">
      <div class="bnt-inner">
        <div class="bnt-ttl">
          <!--  The specific heading of the block (e.g., Books, Academic Journals, etc.)    -->
          <h2><?php print $sourceType; ?></h2>
        </div>
        <div class="bnt-item">
          <div class="bnt-content bnt-no-result">
            <p>Search error has occurred OR no search query is present.</p>
          </div>
        </div>
      </div>
    </div>
    <? else : ?>
  <div class="bnt-container">
    <div class="bnt-inner">
      <div class="bnt-ttl">
        <!--  The specific heading of the block (e.g., Books, Academic Journals, etc.)    -->
        <h2><?php print $sourceType; ?></h2>
      </div>
      <div class="bnt-item">
        <div class="bnt-content bnt-no-result">
          <p>No results found.</p>
        </div>
      </div>
    </div>
  </div>
    <?php endif; ?>
<?php endif; ?>


