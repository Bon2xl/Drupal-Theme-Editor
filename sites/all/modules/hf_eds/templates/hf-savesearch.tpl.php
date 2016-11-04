<div class="page-library-search row">
  <div class="large-12 columns">
    <h1 class="page-title">Saved Searches</h1>
   
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
  <?php if (empty($vars)){ ?>
    <!-- If result is empty, a error massage will show up -->
    <div class="result table-row">
      <div class="table-cell">
        <h2><i>No saved searches found.</i></h2>
      </div>
    </div>
  <?php } else { ?>
    <div class="views-module savesearch-view">
      <?php echo $vars; ?>
    </div>
  <?php } ?>
  </div>
</div> <!-- ./page-library-search .row -->