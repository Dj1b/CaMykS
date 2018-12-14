<?php
/**
 * @brief Admin_GenericEmailingManager Module send emailing layout
 * @details Plugin, Module Layout
 * @file plugin/module/Admin_GenericEmailingManager/html/admin_send_emailing.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2012
 * @date Modification: Dec 2018
 * @copyright 2012 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<?= $this->theme->get_boxHeader(array('style'=>'width:600px;', 'class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <div id="updatebox" style="height:450px; overflow:auto;">
        <div id="updatecontentbox">

        </div>
    </div>
</div>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
