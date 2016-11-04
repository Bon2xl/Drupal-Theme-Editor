
<?php if(!array_filter($vars)): ?>
<div class="views-module view-hold">
  <div class="alert-box info radius">You have no items on request at this time.</div>
</div>
<?php else: ?>
<div class="views-module view-hold">
  <?php foreach ($vars as $key => $value) : ?>
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
  <div class="views-row">
    <div class="book-jacket">
      <?php if ($isbnNum != ''): ?>
        <img src="http://contentcafe2.btol.com/ContentCafe/jacket.aspx?UserID=ebsco-test&Password=ebsco-test&Return=T&Type=S&Value=<?php print $isbnNum; ?>">
      <?php endif ?>
    </div>
    <div class="item-details">
      <h3 class="title">
        <strong class="highlight"><?php print $value['title']; ?></strong>
      </h3>
      <?php if (!empty($value['author'])): ?>
        <strong class="lbl">Author(s) : </strong>
        <?php print $value['author']; ?>
        <br />
      <?php endif ?>

      <?php if (!empty($value['bib_id'])): ?>
        <strong class="lbl">Bib ID : </strong>
        <?php print $value['bib_id']; ?>
        <br />
      <?php endif ?>

      <?php if (!empty($isbnNum)): ?>
        <strong class="lbl">ISBN : </strong>
        <?php print $isbnNum; ?>
        <br />
      <?php endif ?>
      <?php if (!empty($value['stadus_desc'])): ?>
        <strong class="lbl">Status : </strong>
        <?php print $value['stadus_desc']; ?>
        <br />
      <?php endif ?>
    </div>
    <?php
    if (($value['stadus_desc'] != 'Cancelled') && ($value['stadus_desc'] != 'Shipped')) {
      print "<div class='save-item-hold'><a href=\"".base_path()."my-account/holds/cancel/".$value['request_id']."\" class=\"btn-cancel\">Cancel Request</a></div>";
    } else {
      print "<div class='save-item-hold'><p class='text-center label round warning'><i>Request has been cancelled</i></p></div>";
    }
    ?>
  </div>
  <?php endforeach; ?>
</div>
<?php endif ?>