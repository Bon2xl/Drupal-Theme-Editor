<div class="page-library-search">
    <div class="large-9 push-3 main columns">
        <div class="row">
            <div class="large-12 columns">
                <div class="panel-content">
                    <h1 id="page-title" class="title">Search</h1>
                    <?php
                        $url_args = drupal_get_query_parameters();
                        $filters = _hf_eds_search_url_to_filters($url_args);
                        print _hf_eds_build_search_stats($vars,$filters);
                    ?>

                    <?php if (empty($vars->search_results)){ ?>
                        <!-- If result is empty, a error massage will show up -->
                        <div class="result table-row">
                            <div class="table-cell">
                                <h2 class="panel">No results were found.</h2>
                            </div>
                        </div>
                    <?php } else { ?>
                        <div class="views-module saved-views">
                        <?php /* Fetch out results */
                        foreach ($vars->search_results as $result) { ?>
                            <?php //var_dump($result['Identifier']); ?>
                            <div class="views-row">
                                <div class="large-9 columns">
                                    <!-- Pub Type -->
                                    <?php if (!empty($result['pubType'])) { ?>
                                        <div class="book-jacket">
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

                                                $bookCover = "<a href=\"/eds/detail?".$params."\">";
                                                switch ($pubTypeId) {
                                                    case 'academicJournal':
                                                        $bookCover .= "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/article.png\" />";
                                                        break;
                                                    case 'ebook':
                                                        $bookCover .= "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/book.png\" />";
                                                        break;
                                                    case 'book':
                                                        $bookCover .= "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/book.png\" />";
                                                        break;
                                                    case 'electronicResource':
                                                        $bookCover .= "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/book.png\" />";
                                                        break;
                                                    case 'periodical':
                                                        $bookCover .= "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/article.png\" />";
                                                        break;
                                                    default:
                                                        $bookCover .= "<img src=\"".base_path()."sites/all/themes/hfstacks/assets/img/book.png\" />";
                                                }
                                                $bookCover .= "</a>";

                                                echo $bookCover;
                                            ?>
                                            <?php } ?>
                                            <div class="file-format book">
                                                <?php echo $result['pubType'] ?>
                                            </div>
                                        </div>
                                    <?php } ?>
                                    <div class="item-details">
                                        <div style="margin-left: 10px">
                                            <div class="title">
                                                <?php
                                                $params = array(
                                                    'db'=>$result['DbId'],
                                                    'an'=>$result['An']
                                                );
                                                $params = http_build_query($params);
                                                ?>
                                                <!-- Title -->
                                                <h3>
                                                    <?php if (!empty($result['Items']['Ti'])) { ?>
                                                        <?php foreach ($result['Items']['Ti'] as $Ti) { ?>
                                                            <a href="<?php echo base_path(); ?>eds/detail?<?php echo $params ?>"><?php echo $Ti['Data']; ?></a>
                                                        <?php }
                                                    } else { ?>
                                                        <a href="/<?php echo current_path() ?>?<?php echo $params ?>"><?php echo "Title is not Aavailable"; ?></a>
                                                    <?php } ?>
                                                </h3>
                                            </div>

                                            <?php if(!empty($result['Items']['TiAtl'])){ ?>
                                                <?php foreach($result['Items']['TiAtl'] as $TiAtl){ ?>
                                                    <?php //echo $TiAtl['Data']; ?>
                                                <?php } ?>
                                            <?php } ?>

                                            <ul class="js-search-listing-details">
                                                <!-- Authors -->
                                                <?php if (!empty($result['Items']['Au'])) { ?>
                                                    <li class="author">
                                                        Authors :
                                                       <?php foreach($result['Items']['Au'] as $Author){ ?>
                                                           <?php echo $Author['Data']; ?>;
                                                       <?php } ?>
                                                    </li>
                                                <?php } ?>

                                                <?php if (isset($result['Items']['Src'])||isset($result['Items']['SrcInfo'])) { ?>
                                                    <!-- Source  -->
                                                    <?php if(isset($result['Items']['Src'])){ ?>
                                                        <li class="source">
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
                                                                    echo $src['Data'];
                                                                }?>
                                                            </span>
                                                        </li>
                                                    <?php } ?>
                                                    <br/>
                                                <?php } ?>
                                            </ul>

                                            <?php if (!empty($result['Items']['Ab'])) { ?>
                                                <!-- Abstract  -->
                                                <?php foreach($result['Items']['Ab'] as $Abstract){ ?>
                                                    <?php //echo $Abstract['Data']; ?>
                                                <?php } ?>
                                            <?php } ?>

                                            <?php if (!empty($result['Items']['Su'])) { ?>
                                                <!-- Subject  -->
                                                <?php foreach($result['Items']['Su'] as $Subject){ ?>
                                                    <?php //echo $Subject['Data']; ?>
                                                <?php } ?>
                                            <?php } ?>

                                            <!-- ISBN  -->
                                            <?php
                                            $isbnString = "";
                                            echo "<div class=\"isbn\">";
                                                if (isset($result['Identifier'])) {
                                                    foreach ($result['Identifier'] as $ISBN) {
                                                        //echo "<strong>" . $ISBN['Type'] . "</strong>: " . $ISBN['Value'] . "<br />";
                                                    }
                                                }
                                            echo "</div>";
                                            ?>

                                            <!-- HTML Fulltext  -->
                                            <?php if($result['HTML']==1){ ?>
                                                <!--
                                                <a target="_blank"  class="icon html fulltext" href="/<?php echo current_path() ?>?record=y&an=<?php echo $result['An']; ?>&db=<?php echo $result['DbId']; ?>&query=<?php echo $query ?>&type=<?php echo $_REQUEST['type']?>#html">Full Text</a>
                                                -->
                                            <?php } ?>
                                            <!-- PDF Fulltext  -->
                                            <?php if(isset($result['Items']['URL'][0]['Data'])){ ?>
                                                <div class="extLink">
                                                    <strong>External Download</strong>
                                                    <br />
                                                    <?php echo autolink($result['Items']['URL'][0]['Data']); ?>
                                                </div>
                                            <?php } ?>

                                            <?php if (!empty($result['CustomLinks'])){ ?>
                                                <!-- Custom Links --> <div class="custom-links">
                                                    <?php if (count($result['CustomLinks'])<=3){?>

                                                        <?php foreach ($result['CustomLinks'] as $customLink) { ?>
                                                            <p>
                                                                <a href="<?php echo base_path().$customLink['Url']; ?>" title="<?php echo $customLink['MouseOverText']; ?>">
                                                                    <img src="<?php echo base_path().$customLink['Icon'] ?>"/>
                                                                    <?php echo $customLink['Name']; ?>
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
                                                        <?php for($i=0; $i<3 ; $i++){
                                                            $customLink = $result['FullTextCustomLinks'][$i];
                                                            ?>
                                                            <p>
                                                                <a href="<?php echo base_path().$customLink['Url']; ?>" title="<?php echo $customLink['MouseOverText']; ?>"><?php echo $customLink['Name']; ?></a>
                                                            </p>
                                                        <?php } ?>

                                                    <?php } ?>
                                                </div>
                                            <?php } ?>
                                        </div>
                                    </div>
                                </div>
                                <div class="large-3 columns">
                                    <div class="form-wrapper">
                                        <form id="saved-items-form">
                                            Select Item
                                            <input id="<?php echo $result['An']; ?>-<?php echo $result['DbId']; ?>" class="select_item_checkbox hidden-field" type="checkbox" onclick="saveItemToggle(this, '<?php echo $result['An']; ?>', '<?php echo $result['DbId']; ?>')" name="monitor">
                                            <span class="custom checkbox"></span>
                                        </form>
                                    </div>
                                </div>
                            </div>
                            <div id="hold-confirmation" class="reveal-modal small">
                                <div class="js-form-message"></div>
                                <div class="js-hold-form"> </div>
                                <a class="close-reveal-modal">×</a>
                            </div>
                        <?php } ?>
                        </div>
                    <?php } ?>

                    <?php //print _hf_eds_build_pagination_bar($vars); ?>
                </div>
            </div>
        </div>
    </div>
    <aside class="large-3 pull-9 sidebar-first columns sidebar hide-for-small" role="complementary">
        <?php //print _hf_eds_filter_block(); ?>
        <?php print hf_eds_search_filter_block(); ?>
    </aside>
</div>