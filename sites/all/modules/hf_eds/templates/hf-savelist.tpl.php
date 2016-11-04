<div class="page-library-search row">
  <div class="large-12 columns">
    <h1 class="page-title">Saved List</h1>
   
    <?php
    $url_args = drupal_get_query_parameters();
    $locationArray = array();

    $user_patron = false;
    $user_role = $GLOBALS['user']->roles;
    if (!empty($user_role)) {
      foreach ($user_role as $role) {
        if (strpos($role,'patron') !== false) {
          $user_patron = true;
        }
      }
    }

    $user = $GLOBALS['user'];
    $uid = $user->uid;
    ?>
  
  <div id="stacks-request" class="alert-box success radius">
    Item request has been placed!
    <a href="#" class="close close-reveal-modal">&times;</a>
  </div>
  <?php if (empty($vars)){ ?>
    <!-- If result is empty, a error massage will show up -->
    <div class="result table-row">
      <div class="table-cell">
        <h2 class="panel">No results were found.</h2>
      </div>
    </div>
  <?php } else { ?>
    <div class="views-module search-views">
      <?php
      /* Fetch out results */
      foreach ($vars as $result) {?>
        <?php //dpm($result); ?>
        <div class="views-row">
          <div class="book-jacket">
            <!-- Pub Type -->
            <?php if (!empty($result['pubType'])) { ?>

              <?php
              $params = array(
                'db'=>$result['DbId'],
                'an'=>$result['An']
              );
              $params = http_build_query($params);
              ?>
              <?php if (!empty($result['ImageInfo'])) { ?>
                <a href="<?php echo base_path(); ?>eds/detail?<?php echo $params ?>">
                  <img src="<?php echo $result['ImageInfo']['thumb']; ?>" />
                </a>
              <?php } else {
                $pubTypeId =  $result['PubTypeId'];

                $bookCover = "<a href=\"".base_path()."eds/detail?".$params."\">";
                switch ($pubTypeId) {
                  case 'academicJournal':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-academic-journals.png\" />";
                    break;
                  case 'audio':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-audio.png\" />";
                    break;
                  case 'biography':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-biographies.png\" />";
                    break;
                  case 'book':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-books.png\" />";
                    break;
                  case 'conference':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-conference-materials.png\" />";
                    break;
                  case 'dissertation':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-dissertations.png\" />";
                    break;
                  case 'dissertation/ thesis':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-dissertations.png\" />";
                    break;
                  case 'ebook':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-ebooks.png\" />";
                    break;
                  case 'electronicResource':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-electronic-resources.png\" />";
                    break;
                  case 'newspaperArticle':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-news.png\" />";
                    break;
                  case 'news':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-news.png\" />";
                    break;
                  case 'periodical':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                    break;
                  case 'primarySource':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                    break;
                  case 'serialPeriodical':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                    break;
                  case 'unknown':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                    break;
                  case 'videoRecording':
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-videos.png\" />";
                    break;
                  default:
                    $bookCover = "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                }
                $bookCover .= "</a>";

                echo $bookCover;
                ?>
              <?php } ?>
              <div class="file-format book">
                <?php echo $result['pubType'] ?>
              </div>
            <?php } ?>
          </div> <!-- ./book-jacket -->
          <div class="item-details">

            <!-- ISBN  -->
            <?php
            $isbnString = "";
            $isbnCount = 0;
            $isbnNum = '';
            //echo "<div class=\"isbn\">";
            if (isset($result['RecordInfo'])) {
              foreach ($result['RecordInfo'] as $ISBN) {
                if (strpos($ISBN['Type'],'isbn') !== false) {
                  if ($isbnCount == 0) {
                    $isbnNum = $ISBN['Value'];
                  }
                  //echo $ISBN['Type'] . ": " . $ISBN['Value'] . "<br />";
                  $isbnCount++;
                }
              }
            }
            //echo "</div>";
            ?>

            <?php
            if ($isbnNum != '') {
              $params = array(
                'db'=>$result['DbId'],
                'an'=>$result['An'],
                'isbn'=>$isbnNum
              );
            } else {
              $params = array(
                'db'=>$result['DbId'],
                'an'=>$result['An']
              );
            }

            $params = http_build_query($params);
            ?>

            <?php
            // get the bibid for this library asset
            if ($isbnNum != '') {
              global $base_url;
              $url = $base_url."/my-account/bib/".$isbnNum;
              $bibid = '';
              $bibinfo = array();
              $locationCount = 0;

              $request = chr_curl_http_request($url);
              if (!empty($request)) {
                if ($request->status_message == 'OK') {
                  $json_response = drupal_json_decode($request->data);
                  if (!empty($json_response)) {
                    foreach ($json_response as $response_data) {
                      $bibid =  $response_data;
                    }
                  }
                }
              }

              // get the bib info for this library asset
              if ($bibid != '') {
                $url = $base_url."/my-account/items/info/".$bibid;
                $request = chr_curl_http_request($url);

                if (!empty($request)) {
                  if ($request->status_message == 'OK') {
                    $json_response = drupal_json_decode($request->data);
                    if (!empty($json_response)) {
                      foreach ($json_response as $response_data) {
                        $bibinfo =  $response_data;
                      }
                    }
                  }
                }

                if (!empty($bibinfo)) {
                  $locationCount = 0;
                  $locationArray[] = $bibinfo;
                  $locationLast = '';

                  foreach ($locationArray[0] as $location) {
                    if ($location['LocationName'] != $locationLast) {
                      $locationCount++;
                    }
                    $locationLast = $location['LocationName'];
                  }
                }
              }
            }
            ?>

            <!-- Title -->
            <h3 class="title">
              <?php
              if (!empty($result['Items'])) {
                foreach ($result['Items'] as $Ti) {
                  if ($Ti['Group'] == 'Ti') {
                    echo "<a href=\"".base_path()."eds/detail?".$params."\">".$Ti['Data']."</a>";
                  }
                }
              } else {
                echo "<a href=\"/".current_path()."?".$params."\">Title is not Available</a>";
              }
              ?>
            </h3>

            <!-- Authors -->
            <ul class="js-search-listing-details authors-list">
              <?php if (!empty($result['Items'])) { ?>
                <li class="item">
                  <span class="lbl">Authors : </span>
                  <?php
                  $authorCount = 0;
                  foreach($result['Items'] as $Author) {
                    if ($Author['Group'] == 'Au') {
                      if ($authorCount <= 2 ) {
                        echo '<span class="lbl-author">'.$Author['Data'].';</span>';
                      }
                      elseif ($authorCount == 3) {
                        echo '<span class="lbl-author">...</span>';
                      }
                      $authorCount++;
                    }
                  }
                  ?>
                </li>
              <?php } ?>
            </ul>

            <!-- Availability -->
            <?php
            $pubTypeId =  $result['PubTypeId'];
            $locationLast = '';

            switch ($pubTypeId) {
              case 'academicJournal':
                if ($locationCount > 0) {
                  echo "<span class=\"avail icon-location\">Available at: <i></i><a href=\"#\" data-reveal-id=\"locationModal\">".$locationCount." Location</a></span>";

                  echo "<div id=\"locationModal\" class=\"reveal-modal\" data-reveal aria-labelledby=\"modalTitle\" aria-hidden=\"true\" role=\"dialog\">";
                  echo "<h2 id=\"modalTitle\">Locations</h2>";
                  echo "<p>This title is available at the following locations:</p>";

                  echo "<div class='eds-location'>";
                  echo "<div class='eds-location_column'>Branch</div>";
                  echo "<div class='eds-location_column'>Call Number</div>";
                  echo "<div class='eds-location_column'>Status</div>";
                  //echo "<div class='eds-location_column'>Count</div>";
                  echo "</div>";

                  foreach ($locationArray[0] as $location) {
                    //if ($location['LocationName'] != $locationLast) {
                    echo "<div class='eds-location'>";
                    echo "<div class='eds-location_column'>" . $location['LocationName'] . "</div>";
                    echo "<div class='eds-location_column'>" . $location['CallNumber'] . "</div>";
                    echo "<div class='eds-location_column'>" . $location['CircStatus'] . "</div>";
                    //echo "<div class='eds-location_column'>" . $location['ItemsTotal'] . "</div>";
                    echo "</div>";
                    //}
                    //$locationLast = $location['LocationName'];
                  }
                  echo "<a class=\"close-reveal-modal\" aria-label=\"Close\">&#215;</a>";
                  echo "</div>";
                }
                break;
              case 'ebook':
                echo "<span class=\"avail icon-online\">Available at: <i></i><span>Online</span></span>";
                break;
              case 'book':
                if ($locationCount > 0) {
                  echo "<span class=\"avail icon-location\">Available at: <i></i><a href=\"#\" data-reveal-id=\"locationModal\">".$locationCount." Location</a></span>";

                  echo "<div id=\"locationModal\" class=\"reveal-modal\" data-reveal aria-labelledby=\"modalTitle\" aria-hidden=\"true\" role=\"dialog\">";
                  echo "<h2 id=\"modalTitle\">Locations</h2>";
                  echo "<p>This title is available at the following locations:</p>";

                  echo "<div class='eds-location'>";
                  echo "<div class='eds-location_column'><strong>Branch</strong></div>";
                  echo "<div class='eds-location_column'><strong>Call Number</strong></div>";
                  echo "<div class='eds-location_column'><strong>Status</strong></div>";
                  //echo "<div class='eds-location_column'>Count</div>";
                  echo "</div>";

                  foreach ($locationArray[0] as $location) {
                    //if ($location['LocationName'] != $locationLast) {
                    echo "<div class='eds-location'>";
                    echo "<div class='eds-location_column'>" . $location['LocationName'] . "</div>";
                    echo "<div class='eds-location_column'>" . $location['CallNumber'] . "</div>";
                    echo "<div class='eds-location_column'>" . $location['CircStatus'] . "</div>";
                    //echo "<div class='eds-location_column'>" . $location['ItemsTotal'] . "</div>";
                    echo "</div>";
                    //}
                    //$locationLast = $location['LocationName'];
                  }
                  echo "<a class=\"close-reveal-modal\" aria-label=\"Close\">&#215;</a>";
                  echo "</div>";
                }
                break;
              case 'electronicResource':
                echo "<span class=\"avail icon-online\">Available at: <i></i><span>Online</span></span>";
                break;
              case 'periodical':
                if ($locationCount > 0) {
                  echo "<span class=\"avail icon-location\">Available at: <i></i><a href=\"#\" data-reveal-id=\"locationModal\">".$locationCount." Location</a></span>";

                  echo "<div id=\"locationModal\" class=\"reveal-modal\" data-reveal aria-labelledby=\"modalTitle\" aria-hidden=\"true\" role=\"dialog\">";
                  echo "<h2 id=\"modalTitle\">Locations</h2>";
                  echo "<p>This title is available at the following locations:</p>";

                  echo "<div class='eds-location'>";
                  echo "<div class='eds-location_column'><strong>Branch</strong></div>";
                  echo "<div class='eds-location_column'><strong>Call Number</strong></div>";
                  echo "<div class='eds-location_column'><strong>Status</strong></div>";
                  //echo "<div class='eds-location_column'>Count</div>";
                  echo "</div>";

                  foreach ($locationArray[0] as $location) {
                    //if ($location['LocationName'] != $locationLast) {
                    echo "<div class='eds-location'>";
                    echo "<div class='eds-location_column'>" . $location['LocationName'] . "</div>";
                    echo "<div class='eds-location_column'>" . $location['CallNumber'] . "</div>";
                    echo "<div class='eds-location_column'>" . $location['CircStatus'] . "</div>";
                    //echo "<div class='eds-location_column'>" . $location['ItemsTotal'] . "</div>";
                    echo "</div>";
                    //}
                    //$locationLast = $location['LocationName'];
                  }
                  echo "<a class=\"close-reveal-modal\" aria-label=\"Close\">&#215;</a>";
                  echo "</div>";
                }
                break;
              default:
                if ($locationCount > 0) {
                  echo "<span class=\"avail icon-location\">Available at: <i></i><a href=\"#\" data-reveal-id=\"locationModal\">".$locationCount." Location</a></span>";

                  echo "<div id=\"locationModal\" class=\"reveal-modal\" data-reveal aria-labelledby=\"modalTitle\" aria-hidden=\"true\" role=\"dialog\">";
                  echo "<h2 id=\"modalTitle\">Locations</h2>";
                  echo "<p>This title is available at the following locations:</p>";

                  echo "<div class='eds-location'>";
                  echo "<div class='eds-location_column'><strong>Branch</strong></div>";
                  echo "<div class='eds-location_column'><strong>Call Number</strong></div>";
                  echo "<div class='eds-location_column'><strong>Status</strong></div>";
                  //echo "<div class='eds-location_column'>Count</div>";
                  echo "</div>";

                  foreach ($locationArray[0] as $location) {
                    //if ($location['LocationName'] != $locationLast) {
                    echo "<div class='eds-location'>";
                    echo "<div class='eds-location_column'>" . $location['LocationName'] . "</div>";
                    echo "<div class='eds-location_column'>" . $location['CallNumber'] . "</div>";
                    echo "<div class='eds-location_column'>" . $location['CircStatus'] . "</div>";
                    //echo "<div class='eds-location_column'>" . $location['ItemsTotal'] . "</div>";
                    echo "</div>";
                    //}
                    //$locationLast = $location['LocationName'];
                  }
                  echo "<a class=\"close-reveal-modal\" aria-label=\"Close\">&#215;</a>";
                  echo "</div>";
                }
            }
            ?>

            <?php if (!empty($result['CustomLinks'])){ ?>
              <!-- Custom Links -->
              <div class="custom-links">
                <?php if (count($result['CustomLinks'])<=3){?>
                  <?php foreach ($result['CustomLinks'] as $customLink) { ?>
                    <p>
                      <a href="<?php echo base_path().$customLink['Url']; ?>" title="<?php echo $customLink['MouseOverText']; ?>">
                        <img src="<?php echo base_path().$customLink['Icon'] ?>"/>
                        <?php echo base_path().$customLink['Name']; ?>
                      </a>
                    </p>
                  <?php } ?>
                <?php } else {?>
                  <?php for($i=0; $i<3 ; $i++){
                    $customLink = $result['CustomLinks'][$i];
                    ?>
                    <p>
                      <a href="<?php echo base_path().$customLink['Url']; ?>" title="<?php echo $customLink['MouseOverText']; ?>"><?php echo $customLink['Name']; ?></a>
                    </p>
                  <?php } }?>
              </div>
            <?php } ?>
            <?php if (!empty($result['FullTextCustomLinks'])){ ?>
              <div class="custom-links">
                <?php if (count($result['FullTextCustomLinks'])<=3){?>
                  <?php foreach ($result['FullTextCustomLinks'] as $customLink) { ?>
                    <p>
                      <a href="<?php echo base_path().$customLink['Url']; ?>" title="<?php echo $customLink['MouseOverText']; ?>"><img src="<?php echo $customLink['Icon']?>" /> <?php echo $customLink['Name']; ?></a>
                    </p>
                  <?php } ?>
                <?php } else {?>
                  <?php for($i=0; $i<3 ; $i++) {
                    $customLink = $result['FullTextCustomLinks'][$i];
                    ?>
                    <p>
                      <a href="<?php echo base_path().$customLink['Url']; ?>" title="<?php echo $customLink['MouseOverText']; ?>"><?php echo $customLink['Name']; ?></a>
                    </p>
                  <?php } ?>
                <?php } ?>
              </div>
            <?php } ?>
          </div> <!-- ./item-details medium-9 -->
          <div class="save-item-hold">
            <div class="form-wrapper">
              <!-- Save Item Checkbox -->
              <form id="saved-items-form">
                <!--
								<span class="lbl">Add To savelist</span>
								<input id="<?php echo $result['An']; ?>-<?php echo $result['DbId']; ?>" class="select_item_checkbox hidden-field" type="checkbox" onclick="saveItemToggle(this, '<?php echo $result['An']; ?>', '<?php echo $result['DbId']; ?>')" name="monitor">
								<span class="custom checkbox"></span>
                -->
                <?php
                if (!empty($uid)) {
                  $itemCounter = 0;

                  $wquery = db_select('stacks_savelist', 'w');
                  $wquery->fields('w', array('uid', 'an'));
                  $wquery->condition('w.uid',$uid,'=');
                  $wquery->condition('w.an',$result['An'],'=');
                  $wresult = $wquery->execute();
                  while($wrecord = $wresult->fetchAssoc()) {
                    $itemCounter++;
                  }

                  if ($itemCounter == 0) {
                    echo "<a class=\"btn-wishlist\" title=\"Add To Saved List\" onclick=\"saveItemToggle(this, '".$result['An']."', '".$result['DbId']."')\">Add To Saved List</a>";
                  } else {
                    echo "<a class=\"btn-wishlist added\" title=\"Added To Saved List\" onclick=\"deleteItemToggle(this, '".$result['An']."', '".$result['DbId']."')\">Remove From Saved List</a>";
                  }
                }
                ?>
              </form>

              <!-- Place Hold Button -->
              <?php if (!empty($result['Items']['URL'][0]['Data'])) { ?>
                <?php if(strpos($result['Items']['URL'][0]['Data'], '</a>')) { ?>
                  <?php if($bibid != '') { ?>
                    <?php if($user_patron == true) { ?>
                      <a id="btn-request-<?php echo $bibid; ?>" class="btn-request js-holdbutton" data-bib-id="<?php echo $bibid; ?>">Request&nbsp;Item</a>
                    <?php } else { ?>
                      <a title="" href="/user/login?destination=login" class="btn-request" data-reveal-id="patron-login-modal">Request&nbsp;Item</a>
                    <?php } ?>
                  <?php } ?>
                <?php } else { ?>
                  <?php
                  $html_string = $result['Items']['URL'][0]['Data'];
                  $counter = 1;
                  preg_match_all("'<externallink(.*?)>([^<]*)</externallink>'si", $html_string, $match);
                  foreach($match[1] as $val)
                  {
                    $val = trim($val);
                    $val = str_replace("term", "href", $val);
                    if (strpos($val, 'worldcat.org') === false) {
                      echo "<a ".$val." class='btn-request'>Read&nbsp;Now</a>";
                    }
                    $counter++;
                  }
                  ?>
                <?php } ?>
              <?php } else { ?>
                <?php if($bibid != '') { ?>
                  <?php if($user_patron == true) { ?>
                    <a id="btn-request-<?php echo $bibid; ?>" class="btn-request js-holdbutton" data-bib-id="<?php echo $bibid; ?>">Request&nbsp;Item</a>
                  <?php } else { ?>
                    <a title="" href="/user/login?destination=login" class="btn-request" data-reveal-id="patron-login-modal">Request&nbsp;Item</a>
                  <?php } ?>
                <?php } ?>
              <?php } ?>

            </div> <!-- ./form-wrapper -->
          </div> <!-- ./medium-3 .save-item-hold -->
          <div id="hold-confirmation" class="reveal-modal small">
            <div class="js-form-message"></div>
            <div class="js-hold-form"> </div>
            <a class="close-reveal-modal">×</a>
          </div> <!-- ./hold confirmation -->
        </div> <!-- ./views modules -->
      <?php } ?>
    </div>
  <?php } ?>
  </div>
</div> <!-- ./page-library-search .row -->