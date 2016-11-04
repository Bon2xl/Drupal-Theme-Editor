<?php $filter = hf_news_form_filter();?>
<?php if($filter) : ?>
    <aside class="large-3 sidebar-first columns sidebar" role="complementary">
        <div>
            <?php print drupal_render(drupal_get_form('hf_news_form_filter')); ?>
        </div>
    </aside>
    <div class="large-9 main columns" id="block-views-news-block-1">
<?php else: ?>
    <div class="large-12 main columns" id="block-views-news-block-1">
<?php endif; ?>
    <div class="content news-items">
        <div class="view-content row">
            <?php foreach($news as $post) { ?>
              <div class="small-12 medium-6 large-3 columns end">
                <div class="views-row news-item">
                    <?php
                        $file = file_load($post->field_news_image_fid);
                        $uri = $file->uri;
                        $url = file_create_url($uri);
                        ?>
                    <?php
                        if (!empty($post->field_news_image_fid)) {
                            echo "<img src='".$url."' />";
                        }
                    ?>

                    <h3><a href="<?php echo drupal_get_path_alias('node/' . $post->nid); ?>"><?php echo $post->title; ?></a></h3>
                    <time datetime="<?php echo substr($post->field_news_date_value, 0, 10); ?>"><?php echo date("F j, Y", strtotime($post->field_news_date_value)); ?></time>
                    <?php if(isset($post->field_news_body_value)) { ?>
                        <?php print check_markup($post->field_news_body_value, 'full_html'); ?>
                        <p><a href="<?php echo drupal_get_path_alias('node/' . $post->nid); ?>">Read more</a></p>
                    <?php } ?>
                    </div>
                </div>
            <?php } ?>
        </div>
    </div>
</div>