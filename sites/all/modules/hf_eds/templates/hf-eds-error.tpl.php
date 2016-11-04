<?php
global $user;

$userAccess = false;

if (in_array('super administrator', $user->roles)) { $userAccess = true; }
if (in_array('administrator', $user->roles)) { $userAccess = true; }
?>
<div class="page-library-search">
    <div class="row">
        <div class="large-12 columns">
            <div class="panel-content">
                <h1 id="page-title" class="title">Search Results</h1>
                <!-- If result is empty, a error massage will show up -->
                <div class="result table-row">
                    <div class="table-cell">
                        <p data-alert class="alert-box alert">Your search has not yet been configured.</p>
                        <?php
                            if ($userAccess == true) {
                                echo "<p><a href=\"/admin/config/stacks/eds\" class=\"button\">Click here to enter your search credentials and complete the configuration</a></p>";
                            }
                        ?>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
