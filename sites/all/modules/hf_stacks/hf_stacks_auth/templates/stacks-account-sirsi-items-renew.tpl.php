
<div class="row">
    <div class="patron-info small-12 medium-12 large-12 large-centered columns">
        <div class="panel">
            <ul>
                <li>
                    <strong class="label info"><?php print $vars['notice']; ?></strong>
                </li>
                <?php if (!empty($value['errors'])): ?>
                    <li>
                        <strong class="label alert">Error</strong>: <?php print $vars['errors']; ?>
                    </li>
                <?php endif ?>
                <?php if (!empty($value['duedate'])): ?>
                    <li>
                        <strong class="label warning">Due Date</strong>: <?php print $vars['duedate']; ?>
                    </li>
                <?php endif ?>
            </ul>
        </div>
    </div>
</div>