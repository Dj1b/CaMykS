<?php
/**
 * @brief Admin_SystemReport Module admin main layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_SystemReport/html/admin.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2007
 * @date Modification: Apr 2019
 * @copyright 2007 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->itemform->display_header(); ?>
<?= $this->itemform->display_hiddens(); ?>
<?= $this->itemform->display_footer(); ?>

<?= $this->theme->get_boxHeader(array('style'=>'width:700px;margin:0 auto;', 'class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxContent1Header(); ?>
    <div class="adminContentPanel">
        <?= $this->reportList->display('head'); ?>
        <?= $this->reportList->display('list'); ?>
    </div>
<?= $this->theme->get_boxContent1Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
