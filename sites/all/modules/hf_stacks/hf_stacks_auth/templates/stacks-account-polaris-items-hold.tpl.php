
<div class="row">
    <div class="panel">
        <div class="personal-info small-12 medium-12 large-4 large-centered">
            <div class="drop-down-wrapper">
                <a href="#" class="data-link"><i class="fi-torso"></i></a>
                <div class="data-dropdown">
                    <h4>Personal Information</h4>
                    <span class="address"><i class="fi-address-book"></i> <?php print $vars['address'] ?></span>
                    <span class="phone-number"><i class="fi-telephone"></i> <?php print $vars['phone'] ?></span>
                    <span class="barcode"><i class="fi-results"></i> <?php print $vars['barcode'] ?></span>
                </div>
            </div>
        </div>
        <div class="patron-info small-12 medium-12 large-8 large-centered columns">
            <h4>Patron Information</h4>
            <ul>
                <li>
                    <span class="lbl">Name</span>
                    <span class="val"><?php print $vars['name_first'].' '.$vars['name_last']; ?></span>
                </li>
                <li>
                    <span class="lbl">Email</span>
                    <span class="val"><?php print $vars['email_address']; ?></span>
                </li>
                <li>
                    <span class="lbl">Current Fees</span>
                    <span class="val"><?php print $vars['current_fees']; ?></span>
                </li>
                <li>
                    <span class="lbl">Items (<a href="/my-account/items">View</a>)</span>
                    <span class="val"><?php print $vars['items_out']; ?></span>
                </li>
                <li>
                    <span class="lbl tabbed">Items Overdue</span>
                    <span class="val"><?php print $vars['items_overdue']; ?></span>
                </li>
                <li>
                    <span class="lbl tabbed">Items Lost</span>
                    <span class="val"><?php print $vars['items_lost']; ?></span>
                </li>
                <li>
                    <span class="lbl">Holds (<a href="/my-account/holds">View</a>)</span>
                    <span class="val"><?php print $vars['holds_total']; ?></span>
                </li>
                <li>
                    <span class="lbl tabbed">Holds - Current</span>
                    <span class="val"><?php print $vars['holds_current']; ?></span>
                </li>
                <li>
                    <span class="lbl tabbed">Holds - Shipped</span>
                    <span class="val"><?php print $vars['holds_shipped']; ?></span>
                </li>
                <li>
                    <span class="lbl tabbed">Holds - Held</span>
                    <span class="val"><?php print $vars['holds_held']; ?></span>
                </li>
                <li>
                    <span class="lbl tabbed">Holds - Unclaimed</span>
                    <span class="val"><?php print $vars['holds_unclaimed']; ?></span>
                </li>
            </ul>
        </div>
    </div>
</div>