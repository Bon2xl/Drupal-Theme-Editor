<?php //print_r($vars); ?>
<?php if(!array_filter($vars)): ?>
  <div class="views-module view-history">
    <div class="alert-box info radius">You don't have any reading history available. Please contact your library.</div>
  </div>
<?php else: ?>
<?php $itemCount = 0; ?>
<div class="views-module view-history">
    <?php foreach ($vars as $key => $value) : ?>
      <?php if ($itemCount <= 5): ?>
        <?php
        $isbnCount = 0;
        $isbnNum = '';
        if (!empty($value['isbn'])) {
          if ($isbnCount == 0) {
            $isbnNum = $value['isbn'];
          }
        }
        ?>
        <?php
        // get the bib info for this library asset
        global $base_url;
        $isbnNum = '';
        $bibid = $value['bib_id'];
        if ($bibid != '') {
          $url = $base_url."/my-account/bibinfo/".$bibid;
          $request = chr_curl_http_request($url);

          if (!empty($request)) {
            if ($request->status_message == 'OK') {
              $json_response = drupal_json_decode($request->data);
              //print_r($json_response);
              if (!empty($json_response)) {
                foreach ($json_response as $response_data) {
                  $bibinfo =  $response_data;
                }
              }
            }
          }
        }

        if (!empty($bibinfo)) {
          foreach ($bibinfo as $info) {
            if ($info[Label] == 'ISBN:') {
              // get ISBN, and remove any added text after the number
              $isbnNum = trim($info[Value]);
              $isbnNumArray = preg_split ('/\s/',$isbnNum);
              $isbnNum = $isbnNumArray[0];
            }
          }
        }
        ?>
        <?php
        if (isset($value['checkout'])) {
          $checkout = new DateTime($value['checkout']);
        } else {
          $checkout = '';
        }
        ?>
        <div class="views-row">
          <div class="book-jacket">
            <?php if ($isbnNum != ''): ?>
              <img src="http://contentcafe2.btol.com/ContentCafe/jacket.aspx?UserID=ebsco-test&Password=ebsco-test&Return=T&Type=S&Value=<?php print $isbnNum; ?>">
            <?php endif ?>
          </div>
          <div class="item-details">
            <h3 class="title">
              <span class="highlight"><?php print $value['title']; ?></span>
            </h3>
            <?php if (!empty($value['author'])): ?>
              <span class="lbl">Author(s) : </span>
              <?php print $value['author']; ?>
              <br />
            <?php endif ?>

            <?php if (!empty($value['bib_id'])): ?>
              <span class="lbl">Bib ID : </span>
              <?php print $value['bib_id']; ?>
              <br />
            <?php endif ?>

            <?php if (!empty($isbnNum)): ?>
              <span class="lbl">ISBN : </span>
              <?php print $isbnNum; ?>
              <br />
            <?php endif ?>
            <?php if (!empty($value['stadus_desc'])): ?>
              <span class="lbl">Checkout Date : </span>
              <?php print $checkout->format('F d, Y'); ?>
              <br />
            <?php endif ?>
          </div>
        </div>
      <?php endif ?>
      <?php $itemCount++; ?>
    <?php endforeach; ?>
</div>
<?php endif ?>