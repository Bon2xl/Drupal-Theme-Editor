<?php
$user_patron = false;
$user_role = $GLOBALS['user']->roles;
if (!empty($user_role)) {
  foreach ($user_role as $role) {
    if (strpos($role,'patron') !== false) {
      $user_patron = true;
    }
  }
}

$issnNum = '';
$isbnNum = '';
$title = '';
$requestLink = FALSE;
?>

<div class="page-library-search row">
  <div class="large-12 columns">
    <div id="stacks-request" class="alert-box success radius" style="display:none;">
      Item request has been placed!
      <a href="#" class="close">&times;</a>
    </div>
    <div class="node-detail">
      <h1 class="title"><?php if(isset($vars['Items'])){ echo $vars['Items'][0]['Data']; } ?></h1>
      <div class="book-jacket">
        <div class="book-jacket-image">
        <?php if (!empty($vars['ImageInfo']['medium'])) { ?>
          <img src="<?php echo $vars['ImageInfo']['medium']; ?>" />
        <?php } elseif (!empty($vars['ImageInfo']['thumb'])) { ?>
          <img src="<?php echo $vars['ImageInfo']['thumb']; ?>" />
        <?php } else {
          if (isset($vars['PubTypeId'])) {
            $pubTypeId =  $vars['PubTypeId'];

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
          } else {
            $bookCover = "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/stacks-reports.png\" />";
          }

          echo $bookCover;
        } ?>
        </div>
        <?php
          if (isset($vars['pubType'])) {
            echo "<div class=\"file-type\">".$vars['pubType']."</div>";
          } else {
            echo "<div class=\"file-type\"></div>";
          }
        ?>
        <div class="action-wrapper">

          <?php
            // get the bibid for this library asset
            global $base_url;
            $isbnNum = $_GET['isbn'];
            $url = $base_url."/my-account/bib/".$isbnNum;

            $request = drupal_http_request($url);
            $json_response = drupal_json_decode($request->data);

            $bibid = "";
            if (isset($json_response)) {
              foreach ($json_response as $response_data) {
                $bibid =  $response_data;
              }
            }
          ?>

          <?php if(!empty($read_url)) { ?>
          <?php } ?>
          <?php if(!empty($vars['An'])) { ?>
            <?php if($bibid != '') { ?>
              <?php if($user_patron == true) { ?>
                <a id="btn-request-<?php echo $bibid; ?>" class="btn-request js-holdbutton" data-bib-id="<?php echo $bibid; ?>"><i></i> Request Item</a>
                <?php $requestLink = TRUE; ?>
              <?php } else { ?>
                <a href="/user/login?destination=login" class="btn-request js-loginbutton" data-bib-id="<?php echo $bibid; ?>" data-reveal-id="patron-login-modal"><i></i>  Request Item</a>
                <?php $requestLink = TRUE; ?>
              <?php } ?>
            <?php } ?>
          <?php } ?>

          <?php
          if (!empty($vars['Items'])) {
            $online_access = '';
            foreach ($vars['Items'] as $item) {
              // get Title
              if ($item['Label'] == "Title") {
                $title = $item['Data'];
              }
              // get ISBN
              if ($item['Label'] == "ISBN") {
                $isbnNum = $item['Data'];
              }
              // get ISSN
              if ($item['Label'] == "ISSN") {
                $issnNum = $item['Data'];
              }
              // Get online access link and store it in a variable to show at the bottom
              if (($item['Label'] == "Online Access") || ($item['Label'] == "URL")) {
                $online_access = $item['Data'];
              }
              else {
                if ($item['Label'] == 'URL') {
                  $buttonHTML .= $item['Data'];
                  $read_url = $item['Data'];
                }
              }
            }

            // CUSTOM LINKS
            if (isset($vars['CustomLinks'])) {
              foreach ($vars['CustomLinks'] as $custom_links) {
                if ( strpos($custom_links['Name'], 'ILLiad') !== false ) {
                  echo "<a href=\"" . $custom_links['Url'] . "\" target=\"_blank\" class=\"btn-read-online\">Docuserve Request</a>";
                }
                if ( strpos($custom_links['Name'], 'Reprints') !== false ) {
                  echo "<a href=\"" . $custom_links['Url'] . "\" target=\"_blank\" class=\"btn-read-online\">Rush Request</a>";
                }
                if ( strpos($custom_links['Url'], 'tind.io') !== false ) {
                  echo "<a href=\"" . $custom_links['Url'] . "\" target=\"_blank\" class=\"btn-read-online\">Place Request</a>";
                  $requestLink = TRUE;
                }
              }
            }

            // Read Online
            $readonline = FALSE;
            if ($requestLink == FALSE) {
              if ($online_access != "") {
                preg_match('/^<a.*?href=(["\'])(.*?)\1.*$/', $online_access, $m);
                echo "<a href=\"" . $m[2] . "\" target=\"_blank\" class=\"btn-read-online\">Read Online</a>";
                $readonline = TRUE;
              }
              else {
                if (isset($vars['ReadOnline'])) {
                  if (!empty($vars['ReadOnline'])) {
                    echo "<a href=\"" . $vars['ReadOnline'] . "\" target=\"_blank\" class=\"btn-read-online\">Read Online</a>";
                    $readonline = TRUE;
                  }
                }
              }
            }

            if ($readonline == FALSE) {
              echo "<a href=\"" . $vars['PLink'] . "\" target=\"_blank\" class=\"btn-read-online\">Read More</a>";
            }

            /*
            if (($online_access == "") && ($requestLink == FALSE)) {
              if (variable_get('stacks_search_eds_docuserve_checkbox') != "") {
                $docuserve = '';
                $docuserve .= "issn=" . $issnNum;
                $docuserve .= "&isbn=" . $isbnNum;
                $docuserve .= "&volume=&issue=&date=&spage=&pages=&title=";
                $docuserve .= "&atitle=" . $title;
                $docuserve .= "&aulast=";
                echo "<a href=\"" . variable_get('stacks_search_eds_docuserve_url') . "?" . $docuserve . "\" target=\"_blank\" class=\"btn-read-online\">Docuserve Request</a>";
              }
              if (variable_get('stacks_search_eds_rush_checkbox') != "") {
                $rushill = '';
                $rushill .= "issn=" . $issnNum;
                $rushill .= "&title=&aulast=&doi=&pmid=&aufirst=";
                $rushill .= "&atitle=" . $title;
                $rushill .= "&volume=&issue=&spage=&pages=&date=";
                echo "<a href=\"" . variable_get('stacks_search_eds_rush_url') . "?" . $rushill . "\" target=\"_blank\" class=\"btn-read-online\">Rush Request</a>";
              }
            }
            */
          }
          ?>

          <!-- goodreads icon -->
          <span class="soc-med">
            <span class='st_email_large' displayText='Email'></span>
            <span class='st_sharethis_large' displayText='ShareThis'></span>
            <a class="goodreads" href="http://www.goodreads.com/update_status?isbn=<?php echo $isbnNum; ?>&url=http%3A%2F%2Fwww.goodreads.com%2Fbook%2Fshow%2F19501" target="_blank"><img alt="Share on Goodreads" border="0" src="/sites/all/themes/hfstacks/assets/img/icon_goodreads.png" /></a>
          </span>
          <script src="https://www.goodreads.com/javascripts/widgets/update_status.js"></script>
          <script type="text/javascript">var switchTo5x=true;</script>
          <script type="text/javascript" src="http://w.sharethis.com/button/buttons.js"></script>
          <script type="text/javascript">stLight.options({publisher: "dr-4ec3227e-a7-6aef-da34-bdd47a918bfe", doNotHash: false, doNotCopy: false, hashAddressBar: false});</script>
          <!-- ./goodreads -->

        </div>

        <?php
        $block = block_load('hf_rating', 'hf_rating');
        $render_array = _block_get_renderable_array(_block_render_blocks(array($block)));
        $output = render($render_array);
        print($output);
        ?>

      </div> <!-- ./book-jacket -->
      <div class="item-details">
        <?php if (!empty($vars['Items'])) { ?>
          <ul>
          <?php
            $online_access = '';
            for ($i=1;$i<count($vars['Items']);$i++) {
              // get Title
              if ($vars['Items'][$i]['Label'] == "Title") {
                $title =  $vars['Items'][$i]['Data'];
              }
              // get ISBN
              if ($vars['Items'][$i]['Label'] == "ISBN") {
                $isbnNum =  $vars['Items'][$i]['Data'];
              }
              // get ISSN
              if ($vars['Items'][$i]['Label'] == "ISSN") {
                $issnNum =  $vars['Items'][$i]['Data'];
              }
              // Get online access link and store it in a variable to show at the bottom
              if (($vars['Items'][$i]['Label'] == "Online Access") || ($vars['Items'][$i]['Label'] == "URL")) {
                $online_access = $vars['Items'][$i]['Data'];
              } else {
                if ($vars['Items'][$i]['Label'] == "Description" || $vars['Items'][$i]['Label'] == "Notes" || $vars['Items'][$i]['Label'] == "Content Notes") {
                  echo "<li class=\"item long-text\">";
                } else {
                  echo "<li class=\"item\">";
                }
                echo "<span class=\"lbl\">".$vars['Items'][$i]['Label'].": </span>";
                echo "<span class=\"lbl-info\">";
                if($vars['Items'][$i]['Label']=='URL') {
                  echo $vars['Items'][$i]['Data'];
                  $read_url = $vars['Items'][$i]['Data'];
                } elseif ($vars['Items'][$i]['Label'] == "Subject Terms") {
                  $sterms = $vars['Items'][$i]['Data'];
                  //echo $vars['Items'][$i]['Data'];
                  if (strpos($sterms, '</a>;') === FALSE) {
                    echo $vars['Items'][$i]['Data'];
                  } else {
                    $subjects = explode(";", $sterms);
                    foreach($subjects as $subject)
                    {
                      echo $subject;
                    }
                  }
                } else {
                  echo $vars['Items'][$i]['Data'];
                }
                echo "</span>";
                echo "</li>";
              }
            }
            ?>

            <!-- PubType -->
            <?php if(!empty($vars['pubType'])){ ?>
              <li class='item'>
                <span class="lbl">PubType: </span>
                <span class="lbl-info"><?php echo $vars['pubType']; ?></span>
              </li>
            <?php } ?>

            <!-- Database long name -->
            <?php if (!empty($vars['DbLabel'])) { ?>
              <li class='item'>
                <span class="lbl">Database: </span>
                <span class="lbl-info"><?php echo $vars['DbLabel']; ?></span>
              </li>
            <?php } ?>

            <!-- LANGUAGE  -->
            <?php
            if (isset($vars['Language'])) {
              foreach ($vars['Language'] as $ISBN) {
                echo "<li class='item'><span class='lbl'>Language: </span><span class='lbl-info'> " . $ISBN['Text'] . "</span></li>";
              }
            }
            ?>

            <!-- PAGINATION  -->
            <?php
            if (isset($vars['Pagination'])) {
              foreach ($vars['Pagination'] as $ISBN) {
                echo "<li class='item'><span class='lbl'>Page Count: </span><span class='lbl-info'> " . $ISBN['PageCount'] . "</span></li>";
              }
            }
            ?>

            <!-- ISBN  -->
            <?php
            $isbnCount = 0;
            $isbnNum = '';
            if (isset($vars['RecordInfo'])) {
              foreach ($vars['RecordInfo'] as $ISBN) {
                if ($isbnCount == 0) {
                  $isbnNum = $ISBN['Value'];
                }
                echo "<li class='item'><span class='lbl'>" . $ISBN['Type'] . ": </span><span class='lbl-info'> " . $ISBN['Value'] . "</span></li>";
                $isbnCount++;
              }
            }
            ?>

            <!-- IDENTIFIER  -->
            <?php
            if (isset($vars['Identifier'])) {
              foreach ($vars['Identifier'] as $identifier) {
                echo "<li class='item'><span class='lbl'>" . $identifier['Type'] . ": </span><span class='lbl-info'>ITE " . $identifier['Value'] . "</span></li>";
              }
            }
            ?>

          </ul>

          <?php
        } else { ?>
          <p>Sorry, this item is not in our collection.</p>
          <p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p>
        <?php  } ?>

      </div><!-- ./item-details -->

      <?php
        $block = block_load('hf_reviews', 'review');
        $render_array = _block_get_renderable_array(_block_render_blocks(array($block)));
        $output = render($render_array);
        print($output);
      ?>
      <?php
        $block = block_load('hf_similartitles', 'similartitles');
        $render_array = _block_get_renderable_array(_block_render_blocks(array($block)));
        $output = render($render_array);
        print($output);
      ?><!-- ./hf-similarities -->
    </div>
  </div>
</div> <!-- ./row -->
