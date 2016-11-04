<fieldset id="edit-starrating" class="starrating  form-wrapper">
  <div class="fieldset-wrapper">
    <div class="form-item form-type-radios form-item-superstars">
      <div class="stars">
        <?php print drupal_render($form['starrating']['superstars'][4]); ?>
        <label class="option" for="edit-superstars-4">  </label>
        <?php print drupal_render($form['starrating']['superstars'][3]); ?>
        <label class="option" for="edit-superstars-3">  </label>
        <?php print drupal_render($form['starrating']['superstars'][2]); ?>
        <label class="option" for="edit-superstars-2">  </label>
        <?php print drupal_render($form['starrating']['superstars'][1]); ?>
        <label class="option" for="edit-superstars-1">  </label>
        <?php print drupal_render($form['starrating']['superstars'][0]); ?>
        <label class="option" for="edit-superstars-0">  </label>
      </div>

      <div style="clear:both;"></div>

      <div style="text-align: center; margin-top:15px;">
        <?php print drupal_render($form['submit']); ?>
      </div>
    </div>
  </div>
</fieldset>

<div style="display:none;">
  <?php print drupal_render_children($form); ?>
</div>
