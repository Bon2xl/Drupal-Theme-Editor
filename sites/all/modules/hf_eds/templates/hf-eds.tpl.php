<div class="page-library-search pad-top row">
	<div class="large-12 columns">
		<div class="search-head" data-magellan-expedition="fixed">
			<h1 id="page-title" class="title">Search Results</h1>
			<?php
				$url_args = drupal_get_query_parameters();
				$filters = _hf_eds_search_url_to_filters($url_args);
        $bibid = '';
        $locationCount = 0;
				print _hf_eds_build_search_stats($vars,$filters);
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
		</div>
	</div>

	<aside class="large-3 sidebar-first columns sidebar" role="complementary">
	  <?php print hf_eds_search_filter_block($vars); ?>
	</aside>

	<div class="large-9 main columns">
		<div id="stacks-request" class="alert-box success radius">
			Item request has been placed!
			<a href="#" class="close close-reveal-modal">&times;</a>
		</div>
		<?php if (empty($vars->search_results)) { ?>
			<!-- If result is empty, a error massage will show up -->
			<div class="result table-row">
				<div class="table-cell">
					<h2 class="panel">No results were found.</h2>
				</div>
			</div>
		<?php } else { ?>
      <div class="views-module search-views">
        <?php
        /**
         *
         * Get Research Starters
         *
         */
        $research_limit = 1;
        $research_count = 0;
        foreach ($vars->search_starter as $result) {?>
          <?php if ($research_count < $research_limit) { ?>
            <div class="views-row research-starter">
              <div class="book-jacket">
                <!-- Pub Type -->
                <?php if (!empty($result['pubType'])) { ?>
                  <?php
                  $pubTypeId =  $result['PubTypeId'];
                  $locationCount = 0;

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
                    $bookCover = "<a href=\"".base_path()."eds/detail?".$params."\">";
                    $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                    $bookCover .= "</a>";

                    echo $bookCover;
                    ?>
                  <?php } ?>

                <?php } else {
                  $bookCover = "<a href=\"" . base_path() . "eds/detail?" . $params . "\">";
                  $bookCover .= "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                  $bookCover .= "</a>";

                  echo $bookCover;
                  ?>
                <?php } ?>
              </div> <!-- ./book-jacket -->

              <div class="item-details">

                <!-- ISBN  -->
                <?php
                $isbnString = "";
                $isbnCount = 0;
                $isbnNum = '';
                if (isset($result['RecordInfo'])) {
                  foreach ($result['RecordInfo'] as $ISBN) {
                    if (strpos($ISBN['Type'],'isbn') !== false) {
                      if ($isbnCount == 0) {
                        $isbnNum = $ISBN['Value'];
                      }
                      $isbnCount++;
                    }
                  }
                }
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
                if ( (!empty(variable_get('stacks_auth', ''))) && ($isbnNum != '') && (($pubTypeId == 'book') || ($pubTypeId == 'biography')) ) {
                  global $base_url;
                  $url = $base_url."/my-account/bib/".$isbnNum;
                  $bibid = '';
                  $bibinfo = array();
                  $locationCount = 0;

                  $request = drupal_http_request($url);

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
                    $request = drupal_http_request($url);

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

                      if (isset($locationArray[0]["LocationID"])) {
                        $locationCount = 1;
                      } else {
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
                }
                ?>

                <!-- Title -->
                <h3 class="title">
                  <?php if (!empty($result['Items']['Ti'])) { ?>
                    <?php foreach ($result['Items']['Ti'] as $Ti) { ?>
                      <a href="<?php echo base_path(); ?>eds/detail?<?php echo $params ?>"><?php echo $Ti['Data']; ?></a>
                    <?php }
                  } else { ?>
                    <a href="/<?php echo current_path() ?>?<?php echo $params ?>"><?php echo "Title is not available"; ?></a>
                  <?php } ?>
                </h3>

                <ul class="js-search-listing-details authors-list">
                  <!-- Authors -->
                  <?php if (!empty($result['Items']['Au'])) { ?>
                    <li class="item">
                      <span class="lbl">Authors : </span>
                      <?php
                      $authorCount = 0;
                      foreach($result['Items']['Au'] as $Author) {
                        if ($authorCount <= 2 ) {
                          echo '<span class="lbl-author">'.$Author['Data'].'</span>';
                        }
                        elseif ($authorCount == 3) {
                          echo '<span class="lbl-author">...</span>';
                        }
                        $authorCount++;
                      }
                      ?>
                    </li>
                  <?php } ?>

                  <?php if (isset($result['Items']['Src'])||isset($result['Items']['SrcInfo'])) { ?>
                    <!-- Source  -->
                    <?php if(isset($result['Items']['Src'])){ ?>
                      <li class="item">
                        <span>
                          <?php foreach($result['Items']['Src'] as $src){
                            echo $src['Data'];
                          }?>
                        </span>
                      </li>
                    <?php } ?>
                  <?php } ?>
                </ul>

                <!-- IDENTIFIER  -->
                <?php
                $isbnString = "";
                /*
                echo "<div class=\"identifier\">";
                if (isset($result['Identifier'])) {
                  foreach ($result['Identifier'] as $Identifier) {
                    echo $Identifier['Type'] . ": " . $Identifier['Value'] . "<br />";
                  }
                }
                echo "</div>";
                */
                ?>

                <!-- Availability -->
                <?php
                $locationLast = '';

                if ($locationCount > 0) {
                  echo "<span class=\"avail icon-location\">Available at: <i></i><a href=\"#\" data-reveal-id=\"locationModal-".(count($locationArray)-1)."\">".$locationCount." Location</a></span>";

                  echo "<div id=\"locationModal-".(count($locationArray)-1)."\" class=\"reveal-modal\" data-reveal aria-labelledby=\"modalTitle\" aria-hidden=\"true\" role=\"dialog\">";
                  echo "<h2 id=\"modalTitle\">Locations</h2>";
                  echo "<p>This title is available at the following location(s):</p>";

                  echo "<div class='eds-location'>";
                  echo "<div class='eds-location_column'><strong>Branch</strong></div>";
                  echo "<div class='eds-location_column'><strong>Call Number</strong></div>";
                  echo "<div class='eds-location_column'><strong>Status</strong></div>";
                  echo "</div>";

                  if (isset($locationArray[count($locationArray)-1]["LocationID"])) {
                    // only 1 location available
                    echo "<div class='eds-location'>";
                    echo "<div class='eds-location_column'>" . $locationArray[count($locationArray)-1]['LocationName'] . "</div>";
                    echo "<div class='eds-location_column'>" . $locationArray[count($locationArray)-1]['CallNumber'] . "</div>";
                    echo "<div class='eds-location_column'>" . $locationArray[count($locationArray)-1]['CircStatus'] . "</div>";
                    echo "</div>";
                  } else {
                    // multiple locations
                    foreach ($locationArray[count($locationArray)-1] as $location) {
                      // multiple locations
                      echo "<div class='eds-location'>";
                      echo "<div class='eds-location_column'>" . $location['LocationName'] . "</div>";
                      echo "<div class='eds-location_column'>" . $location['CallNumber'] . "</div>";
                      echo "<div class='eds-location_column'>" . $location['CircStatus'] . "</div>";
                      echo "</div>";
                    }
                  }

                  echo "<a class=\"close-reveal-modal\" aria-label=\"Close\">&#215;</a>";
                  echo "</div>";
                }
                ?>

                <?php
                /*
                if (!empty($result['CustomLinks'])) {
                  // Custom Links
                  echo "<div class=\"custom-links\">";
                    if (count($result['CustomLinks'])<=3){
                      foreach ($result['CustomLinks'] as $customLink) {
                        echo "<p>";
                        echo "<a href=\"".$customLink['Url']."\" title=\"".$customLink['MouseOverText']."\">";
                            if(!empty($customLink['Icon'])) {
                              echo "<img src=\"" . base_path() . $customLink['Icon'] . "\"/>";
                            }
                            echo $customLink['Name'];
                          echo "</a>";
                        echo "</p>";
                      }
                    } else {
                      for($i=0; $i<3 ; $i++) {
                        $customLink = $result['CustomLinks'][$i];
                        echo "<p>";
                          echo "<a href=\"".base_path().$customLink['Url']."\" title=\"".$customLink['MouseOverText']."\">".$customLink['Name']."</a>";
                        echo "</p>";
                      }
                    }
                  echo "</div>";
                }
                if (!empty($result['FullTextCustomLinks'])){
                  echo "<div class=\"custom-links\">";
                    if (count($result['FullTextCustomLinks'])<=3){
                      foreach ($result['FullTextCustomLinks'] as $customLink) {
                        echo "<p>";
                          echo "<a href=\"".base_path().$customLink['Url']."\" title=\"".$customLink['MouseOverText']."\"><img src=\"".$customLink['Icon']."\" />".$customLink['Name']."</a>";
                        echo "</p>";
                      }
                    } else {
                      for($i=0; $i<3 ; $i++) {
                        $customLink = $result['FullTextCustomLinks'][$i];
                        echo "<p>";
                          echo "<a href=\"".base_path().$customLink['Url']."\" title=\"".$customLink['MouseOverText']."\">".$customLink['Name']."</a>";
                        echo "</p>";
                      }
                    }
                  echo "</div>";
                }
                */
                ?>
              </div> <!-- ./item-details medium-9 -->
              <div class="save-item-hold">
                <div class="form-wrapper">
                  <!-- Save Item Checkbox -->
                  <form id="saved-items-form">
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
                        <?php if (($isbnNum != '') && (($pubTypeId == 'book') || ($pubTypeId == 'biography'))) { ?>
                          <?php if($user_patron == true) { ?>
                            <a id="btn-request-<?php echo $bibid; ?>" class="btn-request js-holdbutton" data-bib-id="<?php echo $bibid; ?>">Request Item</a>&nbsp;
                          <?php } else { ?>
                            <a title="" href="/user/login?destination=login" class="btn-request js-loginbutton" data-reveal-id="patron-login-modal" data-bib-id="<?php echo $bibid; ?>">Request Item</a>
                          <?php } ?>
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
                          echo "<a ".$val." class='btn-request'>Read&nbsp;Now</a> ";
                        }
                        $counter++;
                      }
                      ?>
                    <?php } ?>
                  <?php } else { ?>
                    <?php if($bibid != '') { ?>
                      <?php if (($isbnNum != '') && (($pubTypeId == 'book') || ($pubTypeId == 'biography'))) { ?>
                        <?php if($user_patron == true) { ?>
                          <a id="btn-request-<?php echo $bibid; ?>" class="btn-request js-holdbutton" data-bib-id="<?php echo $bibid; ?>">Request Item</a>
                        <?php } else { ?>
                          <a title="" href="/user/login?destination=login" class="btn-request js-loginbutton" data-reveal-id="patron-login-modal" data-bib-id="<?php echo $bibid; ?>">Request Item</a>
                        <?php } ?>
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
            <?php $research_count++; ?>
          <?php } ?>
        <?php } ?>

        <?php
        /**
         *
         * Get Primary Records
         *
         */
        foreach ($vars->search_results as $result) {?>
          <div class="views-row">
            <div class="book-jacket">
              <!-- Pub Type -->
              <?php if (!empty($result['pubType'])) { ?>
                <?php
                $pubTypeId =  $result['PubTypeId'];
                $locationCount = 0;

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
                  $bookCover = "<a href=\"".base_path()."eds/detail?".$params."\">";
                  switch ($pubTypeId) {
                    case 'academicJournal':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-academic-journals.png\" />";
                      break;
                    case 'audio':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-audio.png\" />";
                      break;
                    case 'biography':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-biographies.png\" />";
                      break;
                    case 'book':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-books.png\" />";
                      break;
                    case 'conference':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-conference-materials.png\" />";
                      break;
                    case 'dissertation':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-dissertations.png\" />";
                      break;
                    case 'dissertation/ thesis':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-dissertations.png\" />";
                      break;
                    case 'ebook':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-ebooks.png\" />";
                      break;
                    case 'electronicResource':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-electronic-resources.png\" />";
                      break;
                    case 'newspaperArticle':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-news.png\" />";
                      break;
                    case 'news':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-news.png\" />";
                      break;
                    case 'periodical':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                      break;
                    case 'primarySource':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                      break;
                    case 'serialPeriodical':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                      break;
                    case 'unknown':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                      break;
                    case 'videoRecording':
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-videos.png\" />";
                      break;
                    default:
                      $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                  }
                  $bookCover .= "</a>";

                  echo $bookCover;
                  ?>
                <?php } ?>

              <?php } else {
                $bookCover = "<a href=\"" . base_path() . "eds/detail?" . $params . "\">";
                $bookCover .= "<img src=\"" . base_path() . "sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
                $bookCover .= "</a>";

                echo $bookCover;
                ?>
              <?php } ?>

              <div class="file-format book">
                <?php echo $result['pubType'] ?>
              </div>
            </div> <!-- ./book-jacket -->

            <div class="item-details">

              <!-- ISBN  -->
              <?php
              $isbnString = "";
              $isbnCount = 0;
              $isbnNum = '';
              $issnNum = '';
              $title = '';
              $online_access = '';
              $buttonHTML = '';

              if (isset($result['RecordInfo'])) {
                foreach ($result['RecordInfo'] as $record) {
                  // Get ISBN
                  if (strpos($record['Type'],'isbn') !== false) {
                    if ($isbnCount == 0) {
                      $isbnNum = $record['Value'];
                    }
                  }
                  // Get ISSN
                  if (strpos($record['Type'],'issn') !== false) {
                    if ($isbnCount == 0) {
                      $isbnNum = $record['Value'];
                    }
                  }
                }
              }

              if (!empty($result['Items'])) {
                foreach ($result['Items'] as $item) {
                  // get Title
                  if ($item[0]['Label'] == "Title") {
                    $title = $item[0]['Data'];
                  }
                  // get ISBN
                  if ($item[0]['Label'] == "ISBN") {
                    $isbnNum = $item[0]['Data'];
                  }
                  // get ISSN
                  if ($item[0]['Label'] == "ISSN") {
                    $issnNum = $item[0]['Data'];
                  }
                  // Get online access link and store it in a variable to show at the bottom
                  if (($item[0]['Label'] == "Online Access") || ($item[0]['Label'] == "URL")) {
                    $online_access = $item[0]['Data'];
                  }
                  else {
                    if ($item[0]['Label'] == 'URL') {
                      $buttonHTML .= $item[0]['Data'];
                      $read_url = $item[0]['Data'];
                    }
                  }
                }

                // Read Online
                $readonline = FALSE;
                if ($online_access != "") {
                  preg_match('/^<a.*?href=(["\'])(.*?)\1.*$/', $online_access, $m);
                  $buttonHTML .= "<a href=\"" . $m[2] . "\" target=\"_blank\" class=\"btn-read-online\">Read Online</a>";
                  $readonline = TRUE;
                }
                elseif(!empty($read_url)) {
                  preg_match('/^<a.*?href=(["\'])(.*?)\1.*$/', $read_url, $r);
                  $buttonHTML .= "<a href=\"" . $r[2] . "\" target=\"_blank\" class=\"btn-read-online\">Read Online</a>";
                  $readonline = TRUE;
                }
                else {
                  if (isset($result['ReadOnline'])) {
                    if (!empty($result['ReadOnline'])) {
                      $buttonHTML .= "<a href=\"" . $result['ReadOnline'] . "\" target=\"_blank\" class=\"btn-read-online\">Read Online</a>";
                      $readonline = TRUE;
                    }
                  }
                }

                // Place Request
                if ($readonline == FALSE) {
                  $requestLink = FALSE;
                  if (isset($result['CustomLinks'])) {
                    foreach ($result['CustomLinks'] as $custom_links) {
                      if ( (strpos($custom_links['Name'], 'ILLiad') === false) && (strpos($custom_links['Name'], 'Reprints') === false) ) {
                        $buttonHTML .= "<a href=\"" . $custom_links['Url'] . "\" target=\"_blank\" class=\"btn-read-online\">Place Request</a>";
                        $requestLink = TRUE;
                      }
                    }
                  }
                }
              }
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
              if ( (!empty(variable_get('stacks_auth', ''))) && ($isbnNum != '') && (($pubTypeId == 'book') || ($pubTypeId == 'biography')) ) {
                global $base_url;
                $url = $base_url."/my-account/bib/".$isbnNum;
                $bibid = '';
                $bibinfo = array();
                $locationCount = 0;

                //$request = chr_curl_http_request($url);
                $request = drupal_http_request($url);

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

                  //$request = chr_curl_http_request($url);
                  $request = drupal_http_request($url);

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

                    if (isset($locationArray[0]["LocationID"])) {
                      $locationCount = 1;
                    } else {
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
              }
              ?>

              <!-- Title -->
              <h3 class="title">
                <?php if (!empty($result['Items']['Ti'])) { ?>
                  <?php foreach ($result['Items']['Ti'] as $Ti) { ?>
                    <a href="<?php echo base_path(); ?>eds/detail?<?php echo $params ?>"><?php echo $Ti['Data']; ?></a>
                  <?php }
                } else { ?>
                  <a href="/<?php echo current_path() ?>?<?php echo $params ?>"><?php echo "Title is not available"; ?></a>
                <?php } ?>
              </h3>

              <?php
              /*
              if(!empty($result['Items']['TiAtl'])){
                foreach($result['Items']['TiAtl'] as $TiAtl){
                  echo $TiAtl['Data'];
                }
              }
              */
              ?>

              <ul class="js-search-listing-details authors-list">
                <!-- Authors -->
                <?php if (!empty($result['Items']['Au'])) { ?>
                  <li class="item">
                    <span class="lbl">Authors : </span>
                    <?php
                    $authorCount = 0;
                    foreach($result['Items']['Au'] as $Author) {
                      if ($authorCount <= 2 ) {
                        // limit the number of authors to 3
                        $author_string = strip_tags(preg_replace("/<br\W*?\/>/", "; ", $Author['Data']), "<a><sup><sub>");
                        $author_string = explode( ";", $author_string);
                        $author_string = array_slice( $author_string, 0, 3 );
                        $author_string = implode( ";", $author_string );
                        echo '<span class="lbl-author">'.$author_string.'</span>';
                      }
                      elseif ($authorCount == 3) {
                        echo '<span class="lbl-author">...</span>';
                      }
                      $authorCount++;
                    }
                    ?>
                  </li>
                <?php } ?>

                <?php if (isset($result['Items']['Src'])||isset($result['Items']['SrcInfo'])) { ?>
                  <!-- Source  -->
                  <?php if(isset($result['Items']['Src'])){ ?>
                    <li class="item">
                      <span>
                        <?php foreach($result['Items']['Src'] as $src){
                          echo $src['Data'];
                        }?>
                      </span>
                    </li>
                  <?php } ?>
                  <?php if(isset($result['Items']['SrcInfo'])){ ?>
                    <li class="source">
                      <span>
                        <?php foreach($result['Items']['SrcInfo'] as $src){
                          //echo $src['Data'];
                        }?>
                      </span>
                    </li>
                  <?php } ?>
                <?php } ?>
              </ul>

              <?php
              // Abstract
              /*
              if (!empty($result['Items']['Ab'])) {
                foreach($result['Items']['Ab'] as $Abstract){
                  echo $Abstract['Data'];
                }
              }
              */
              ?>

              <?php
              // Subject(s)
              if (!empty($result['Items']['Su'])) {
                echo "<li class=\"item\">";
                  echo "<span class=\"lbl\">Subjects : </span>";
                  $subjectCount = 0;
                  foreach($result['Items']['Su'] as $Subject) {
                    if ($subjectCount <= 2 ) {
                      // limit the number of subjects to 3
                      $subject_string = strip_tags(preg_replace("/<br\W*?\/>/", "; ", $Subject['Data']), "<a><sup><sub>");
                      $subject_string = explode( ";", $subject_string);
                      $subject_string = array_slice( $subject_string, 0, 3 );
                      $subject_string = implode( ";", $subject_string );
                      echo '<span class="lbl-author">'.$subject_string.'</span>';
                    }
                    elseif ($subjectCount == 3) {
                      echo '<span class="lbl-author">...</span>';
                    }
                    $subjectCount++;
                  }
                echo "</li>";
              }
              ?>

              <?php
              // Accesion Number
              /*
              echo "<div class=\"edsAN\">";
                if (!empty($result['An'])) {
                  echo "<strong>an</strong>: ".$result['An'];
                }
              echo "</div>";
              */
              ?>

              <?php
              // identifier
              /*
              $isbnString = "";
              echo "<div class=\"identifier\">";
              if (isset($result['Identifier'])) {
                  foreach ($result['Identifier'] as $Identifier) {
                      echo $Identifier['Type'] . ": " . $Identifier['Value'] . "<br />";
                  }
              }
              echo "</div>";
              */
              ?>

              <!-- HTML Fulltext  -->
              <?php if($result['HTML']==1){ ?>
                  <!--
                  <a target="_blank"  class="icon html fulltext" href="/<?php echo current_path() ?>?record=y&an=<?php echo $result['An']; ?>&db=<?php echo $result['DbId']; ?>&query=<?php echo $query ?>&type=<?php echo $_REQUEST['type']?>#html">Full Text</a>
                  -->
              <?php } ?>

              <!-- External Download  -->
              <?php if(isset($result['Items']['URL'][0]['Data'])){ ?>
                <!--
                  <div class="extLink">
                    <span>External Download</span>
                    <br />
                    <?php //echo autolink($result['Items']['URL'][0]['Data']); ?>
                  </div>
                -->
              <?php } ?>

              <!-- Availability -->
              <?php
                $locationLast = '';

                switch ($pubTypeId) {
                  case 'academicJournal':
                    if ($locationCount > 0) {
                      echo "<span class=\"avail icon-location\">Available at: <i></i><a href=\"#\" data-reveal-id=\"locationModal-".(count($locationArray)-1)."\">".$locationCount." Location</a></span>";

                      echo "<div id=\"locationModal-".(count($locationArray)-1)."\" class=\"reveal-modal\" data-reveal aria-labelledby=\"modalTitle\" aria-hidden=\"true\" role=\"dialog\">";
                      echo "<h2 id=\"modalTitle\">Locations</h2>";
                      echo "<p>This title is available at the following location(s):</p>";

                      echo "<div class='eds-location'>";
                        echo "<div class='eds-location_column'>Branch</div>";
                        echo "<div class='eds-location_column'>Call Number</div>";
                        echo "<div class='eds-location_column'>Status</div>";
                      echo "</div>";

                      if (isset($locationArray[0]["LocationID"])) {
                        // only 1 location available
                        echo "<div class='eds-location'>";
                          echo "<div class='eds-location_column'>" . $locationArray[0]['LocationName'] . "</div>";
                          echo "<div class='eds-location_column'>" . $locationArray[0]['CallNumber'] . "</div>";
                          echo "<div class='eds-location_column'>" . $locationArray[0]['CircStatus'] . "</div>";
                        echo "</div>";
                      } else {
                        // multiple locations
                        foreach ($locationArray[0] as $location) {
                          echo "<div class='eds-location'>";
                            echo "<div class='eds-location_column'>" . $location['LocationName'] . "</div>";
                            echo "<div class='eds-location_column'>" . $location['CallNumber'] . "</div>";
                            echo "<div class='eds-location_column'>" . $location['CircStatus'] . "</div>";
                          echo "</div>";
                        }
                      }
                      echo "<a class=\"close-reveal-modal\" aria-label=\"Close\">&#215;</a>";
                      echo "</div>";
                    }
                    break;
                  /*
                  case 'ebook':
                    echo "<span class=\"avail icon-online\">Available at: <i></i><span>Online</span></span>";
                    break;
                  */
                  case 'book':
                    if ($locationCount > 0) {
                      echo "<span class=\"avail icon-location\">Available at: <i></i><a href=\"#\" data-reveal-id=\"locationModal-".(count($locationArray)-1)."\">".$locationCount." Location</a></span>";

                      echo "<div id=\"locationModal-".(count($locationArray)-1)."\" class=\"reveal-modal\" data-reveal aria-labelledby=\"modalTitle\" aria-hidden=\"true\" role=\"dialog\">";
                      echo "<h2 id=\"modalTitle\">Locations</h2>";
                      echo "<p>This title is available at the following location(s):</p>";

                      echo "<div class='eds-location'>";
                        echo "<div class='eds-location_column'><strong>Branch</strong></div>";
                        echo "<div class='eds-location_column'><strong>Call Number</strong></div>";
                        echo "<div class='eds-location_column'><strong>Status</strong></div>";
                      echo "</div>";

                      if (isset($locationArray[count($locationArray)-1]["LocationID"])) {
                        // only 1 location available
                        echo "<div class='eds-location'>";
                          echo "<div class='eds-location_column'>" . $locationArray[count($locationArray)-1]['LocationName'] . "</div>";
                          echo "<div class='eds-location_column'>" . $locationArray[count($locationArray)-1]['CallNumber'] . "</div>";
                          echo "<div class='eds-location_column'>" . $locationArray[count($locationArray)-1]['CircStatus'] . "</div>";
                        echo "</div>";
                      } else {
                        // multiple locations
                        foreach ($locationArray[count($locationArray)-1] as $location) {
                          echo "<div class='eds-location'>";
                            echo "<div class='eds-location_column'>" . $location['LocationName'] . "</div>";
                            echo "<div class='eds-location_column'>" . $location['CallNumber'] . "</div>";
                            echo "<div class='eds-location_column'>" . $location['CircStatus'] . "</div>";
                          echo "</div>";
                        }
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
                      echo "<span class=\"avail icon-location\">Available at: <i></i><a href=\"#\" data-reveal-id=\"locationModal-".(count($locationArray)-1)."\">".$locationCount." Location</a></span>";

                      echo "<div id=\"locationModal-".(count($locationArray)-1)."\" class=\"reveal-modal\" data-reveal aria-labelledby=\"modalTitle\" aria-hidden=\"true\" role=\"dialog\">";
                      echo "<h2 id=\"modalTitle\">Locations</h2>";
                      echo "<p>This title is available at the following location(s):</p>";

                      echo "<div class='eds-location'>";
                        echo "<div class='eds-location_column'><strong>Branch</strong></div>";
                        echo "<div class='eds-location_column'><strong>Call Number</strong></div>";
                        echo "<div class='eds-location_column'><strong>Status</strong></div>";
                      echo "</div>";

                      if (isset($locationArray[0]["LocationID"])) {
                        // only 1 location available
                        echo "<div class='eds-location'>";
                          echo "<div class='eds-location_column'>" . $locationArray[0]['LocationName'] . "</div>";
                          echo "<div class='eds-location_column'>" . $locationArray[0]['CallNumber'] . "</div>";
                          echo "<div class='eds-location_column'>" . $locationArray[0]['CircStatus'] . "</div>";
                        echo "</div>";
                      } else {
                        // multiple locations
                        foreach ($locationArray[0] as $location) {
                          echo "<div class='eds-location'>";
                            echo "<div class='eds-location_column'>" . $location['LocationName'] . "</div>";
                            echo "<div class='eds-location_column'>" . $location['CallNumber'] . "</div>";
                            echo "<div class='eds-location_column'>" . $location['CircStatus'] . "</div>";
                          echo "</div>";
                        }
                      }

                      echo "<a class=\"close-reveal-modal\" aria-label=\"Close\">&#215;</a>";
                      echo "</div>";
                    }
                    break;
                  default:
                    if ($locationCount > 0) {
                      echo "<span class=\"avail icon-location\">Available at: <i></i><a href=\"#\" data-reveal-id=\"locationModal-".(count($locationArray)-1)."\">".$locationCount." Location</a></span>";

                      echo "<div id=\"locationModal-".(count($locationArray)-1)."\" class=\"reveal-modal\" data-reveal aria-labelledby=\"modalTitle\" aria-hidden=\"true\" role=\"dialog\">";
                      echo "<h2 id=\"modalTitle\">Locations</h2>";
                      echo "<p>This title is available at the following location(s):</p>";

                      echo "<div class='eds-location'>";
                        echo "<div class='eds-location_column'><strong>Branch</strong></div>";
                        echo "<div class='eds-location_column'><strong>Call Number</strong></div>";
                        echo "<div class='eds-location_column'><strong>Status</strong></div>";
                      echo "</div>";

                      if (isset($locationArray[count($locationArray)-1]["LocationID"])) {
                        // only 1 location available
                        echo "<div class='eds-location'>";
                          echo "<div class='eds-location_column'>" . $locationArray[count($locationArray)-1]['LocationName'] . "</div>";
                          echo "<div class='eds-location_column'>" . $locationArray[count($locationArray)-1]['CallNumber'] . "</div>";
                          echo "<div class='eds-location_column'>" . $locationArray[count($locationArray)-1]['CircStatus'] . "</div>";
                        echo "</div>";
                      } else {
                        // multiple locations
                        foreach ($locationArray[count($locationArray)-1] as $location) {
                          // multiple locations
                          echo "<div class='eds-location'>";
                            echo "<div class='eds-location_column'>" . $location['LocationName'] . "</div>";
                            echo "<div class='eds-location_column'>" . $location['CallNumber'] . "</div>";
                            echo "<div class='eds-location_column'>" . $location['CircStatus'] . "</div>";
                          echo "</div>";
                        }
                      }

                      echo "<a class=\"close-reveal-modal\" aria-label=\"Close\">&#215;</a>";
                      echo "</div>";
                    }
                }
              ?>

              <?php
              /*
              if (!empty($result['CustomLinks'])) {
                // Custom Links
                echo "<div class=\"custom-links\">";
                  if (count($result['CustomLinks'])<=3){
                    foreach ($result['CustomLinks'] as $customLink) {
                      echo "<p>";
                      echo "<a href=\"".$customLink['Url']."\" title=\"".$customLink['MouseOverText']."\">";
                          if(!empty($customLink['Icon'])) {
                            echo "<img src=\"" . base_path() . $customLink['Icon'] . "\"/>";
                          }
                          echo $customLink['Name'];
                        echo "</a>";
                      echo "</p>";
                    }
                  } else {
                    for($i=0; $i<3 ; $i++) {
                      $customLink = $result['CustomLinks'][$i];
                      echo "<p>";
                        echo "<a href=\"".base_path().$customLink['Url']."\" title=\"".$customLink['MouseOverText']."\">".$customLink['Name']."</a>";
                      echo "</p>";
                    }
                  }
                echo "</div>";
              }
              if (!empty($result['FullTextCustomLinks'])){
                echo "<div class=\"custom-links\">";
                  if (count($result['FullTextCustomLinks'])<=3){
                    foreach ($result['FullTextCustomLinks'] as $customLink) {
                      echo "<p>";
                        echo "<a href=\"".base_path().$customLink['Url']."\" title=\"".$customLink['MouseOverText']."\"><img src=\"".$customLink['Icon']."\" />".$customLink['Name']."</a>";
                      echo "</p>";
                    }
                  } else {
                    for($i=0; $i<3 ; $i++) {
                      $customLink = $result['FullTextCustomLinks'][$i];
                      echo "<p>";
                        echo "<a href=\"".base_path().$customLink['Url']."\" title=\"".$customLink['MouseOverText']."\">".$customLink['Name']."</a>";
                      echo "</p>";
                    }
                  }
                echo "</div>";
              }
              */
              ?>

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
                    echo $buttonHTML;

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
                      <?php if (($isbnNum != '') && (($pubTypeId == 'book') || ($pubTypeId == 'biography'))) { ?>
                        <?php if($user_patron == true) { ?>
                          <a id="btn-request-<?php echo $bibid; ?>" class="btn-request js-holdbutton" data-bib-id="<?php echo $bibid; ?>">Request Item</a>&nbsp;
                        <?php } else { ?>
                          <a title="" href="/user/login?destination=login" class="btn-request js-loginbutton" data-reveal-id="patron-login-modal" data-bib-id="<?php echo $bibid; ?>">Request Item</a>
                        <?php } ?>
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
                        echo "<a ".$val." class='btn-request'>Read&nbsp;Now</a> ";
                      }
                      $counter++;
                    }
                    ?>
                  <?php } ?>
                <?php } else { ?>
                  <?php if($bibid != '') { ?>
                    <?php if (($isbnNum != '') && (($pubTypeId == 'book') || ($pubTypeId == 'biography'))) { ?>
                      <?php if($user_patron == true) { ?>
                        <a id="btn-request-<?php echo $bibid; ?>" class="btn-request js-holdbutton" data-bib-id="<?php echo $bibid; ?>">Request Item</a>
                      <?php } else { ?>
                        <a title="" href="/user/login?destination=login" class="btn-request js-loginbutton" data-reveal-id="patron-login-modal" data-bib-id="<?php echo $bibid; ?>">Request Item</a>
                      <?php } ?>
                    <?php } ?>
                  <?php } ?>
                <?php } ?>

                <!-- External Download -->
                <?php
                /*
                if(isset($result['Items']['URL'][0]['Data'])) {
                  $downloadString = trim($result['Items']['URL'][0]['Data']);
                  $parts = preg_split('/(<\s*a\s*\/?>)|(<\s*br\s*\/?>)/', $downloadString, -1, PREG_SPLIT_DELIM_CAPTURE | PREG_SPLIT_NO_EMPTY);
                  echo "<a id=\"btn-request-".$result['An']."\" class=\"btn-request js-holdbutton\" data-accession-number=\"".$result['An']."\">View PDF</a>";
                }
                */
                ?>
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
	</div> <!-- ./large-9 .main -->
</div> <!-- ./page-library-search .row -->