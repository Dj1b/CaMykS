<?php
/**
 * @brief Admin_MyShortcuts Module admin engine layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_MyShortcuts/html/adminengine.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2007
 * @date Modification: Jan 2019
 * @copyright 2007 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<div id="admin_myshortcuts_addpopup" class="adminPopupFrame" style="display:none; width:300px; position:absolute; z-index:10001;">
    <?= $this->addform->display_header(); ?>
    <?= $this->addform->display_hiddens(); ?>
    <?= $camyks->theme->get_boxHeader(); ?>
    <?= $camyks->theme->get_boxTitleBar($this->get_translation('addpopuptitle')); ?>
    <?= $camyks->theme->get_boxContent1Header(); ?>
    <div class="eContent2">
        <?= $this->get_translation('addpopupname'); ?>
    </div>
    <div class="eContent1">
        <input type="text" name="name" value="" maxlength="32" style="width:275px;" />
    </div>
    <?= $camyks->theme->get_boxContent1Footer(); ?>
    <?= $camyks->theme->get_boxButtonsBar($this->popupbuttons); ?>
    <?= $camyks->theme->get_boxFooter(); ?>
    <?= $this->addform->display_footer(); ?>
</div>
