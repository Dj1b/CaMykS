<?php
/**
 * @brief Admin_GenericEmailingManager Module import contacts - execute step layout
 * @details Plugin, Module Layout
 * @file plugin/module/Admin_GenericEmailingManager/html/admin_import_contactsExecute.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2013
 * @date Modification: Dec 2018
 * @copyright 2013 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader('width:600px; margin:0 auto;'); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <div id="updatebox" style="height:450px; overflow:auto;">
        <div id="updatecontentbox">

        </div>
    </div>
</div>

<?php if ($this->help != null) : ?>
<div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
    <?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
