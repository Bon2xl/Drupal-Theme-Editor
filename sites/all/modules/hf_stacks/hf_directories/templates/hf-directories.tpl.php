<?php $filter = hf_directories_form_filter(); ?>
<?php if($filter) : ?>
    <aside class="large-3 sidebar-first columns sidebar" role="complementary">
        <div>
            <?php print drupal_render(drupal_get_form('hf_directories_form_filter')); ?>
        </div>
    </aside>
    <div class="large-9 main columns" id="block-views-news-block-1">
<?php else: ?>
    <div class="large-12 main columns" id="block-views-news-block-1">
<?php endif; ?>
    <div class="content">
        <div class="view-directory-listing views-content">
            <?php foreach($directories as $directory) {?>
                <div class="views-row">
                    <!--    Title of the Directory Listing    -->
                    <h3><a href="<?php echo drupal_get_path_alias('node/' . $directory->nid); ?>"><?php echo t($directory->title); ?></a></h3>
                    <!--   Job Title/Location/Information about Listing     -->
                    <?php if(isset($directory->field_job_title_listing_value)) { ?>
                    <p class="vw-item vw-job-listing"><span class='lbl'><?php echo t("Job title/Location/Information"); ?></span>: <?php echo t($directory->field_job_title_listing_value); ?></p>
                    <?php } ?>
                    <!--   Email, if available      -->
                    <?php if(isset($directory->field_email_email)) { ?>
                        <p class="vw-item vw-email"><span class='lbl'>Email:</span> <a href="mailto:<?php echo $directory->field_email_email; ?>"><?php echo $directory->field_email_email; ?></a></p>
                    <?php } ?>
                    <!--   Phone Number, if available      -->
                    <?php if(isset($directory->field_phone_number_listing_number)) { ?>
                        <?php $telNum = hf_format_phone_number($directory->field_phone_number_listing_country_codes, $directory->field_phone_number_listing_number);?>
                        <p class="vw-item vw-phone">
                            <span class='lbl'>Phone Number:</span> 
                            <a href="tel:<?php echo $telNum; ?>"><?php echo $telNum; ?></a>
                        </p>
                    <?php } ?>

                    <!--   Social Media Icons, if available     -->
                    <?php if(isset($directory->field_twitter_link_url) || isset($directory->field_facebook_link_url) || isset($directory->field_linkedin_link_url)) {?>
                        <div class="vw-social">
                            <?php if ($directory->field_facebook_link_url) { ?>
                                <a href="<?php echo $directory->field_facebook_link_url;?>" class="field-facebook-link"></a>
                            <?php } ?>
                            <?php if ($directory->field_twitter_link_url) { ?>
                                <a href="<?php echo $directory->field_twitter_link_url;?>" class="field-linkedin-link"></a>
                            <?php } ?>
                            <?php if ($directory->field_linkedin_link_url) { ?>
                                <a href="<?php echo $directory->field_linkedin_link_url;?>" class="field-twitter-link"></a>
                            <?php } ?>
                        </div>
                    <?php } ?>
                    <!--   Biography   -->
                    <?php if(isset($directory->body_value)) { ?>
                    <p class="vw-field-label-biography"><span class='lbl'><?php echo t("Biography"); ?></span></p>
                    <?php echo truncate_utf8($directory->body_value, 250, TRUE, TRUE); ?>
                    <?php } ?>
                    
                </div>
            <?php } ?>
        </div>
    </div>
</div>