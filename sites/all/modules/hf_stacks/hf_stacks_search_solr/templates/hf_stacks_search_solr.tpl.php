<div class="basic-search row">
  <?php if($results === null) : ?>
    <div class="main-content large-12 columns">
      <ul class="search-results">
        <li class="search-result">
          <p class="alert-box info radius">Search (Solr) is unreachable at the moment.</p>
        </li>
      </ul>
    </div>
  <?php else: ?>
    <?php if($results === 0) : ?>
      <div class="main-content large-12 columns">
        <ul class="search-results">
          <li class="search-result">
            <p class="alert-box info radius">No results found for <?php print $query; ?>.</p>
          </li>
        </ul>
      </div>
    <?php else: ?>
      <?php if($facetBlock != null): ?>
        <!--
        <div class="large-3 columns sidebar">
          <?php //print render($facetBlock); ?>
        </div>
        <div class="main-content large-9 columns">
        -->
        <div class="main-content large-12 columns">
      <?php else: ?>
        <div class="main-content large-12 columns">
      <?php endif; ?>
          <div class="content">
            <ul class="search-results">
              <p>Found <?php print $count;?> results for <?php print $query; ?></p>
              <?php foreach($results as $result): ?>
                <li class="search-result">
                  <h3 class="title">
                    <?php print ($result['url']) ? l($result['title'], $result['url']['path'], $result['url']['options']) : check_plain($result['title']); ?>
                  </h3>
                  <div class="search-snippet-info">
                    <p class="search-snippet"><?php print $result['snippet']; ?></p>
                  </div>
                </li>
              <?php endforeach; ?>
            </ul>
          </div>
        </div>
    <?php endif; ?>
  <?php endif; ?>
</div>