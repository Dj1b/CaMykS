<?php
/**
 * @brief Admin_SystemNotifications Module admin edit configuration layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_SystemNotifications/html/admin_edit_config.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2017
 * @date Modification: May 2019
 * @copyright 2017 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
$width = 160;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>

<?= $this->editForm->display_header(); ?>
<?= $this->editForm->display_hiddens(); ?>
<div id="itemConfiguration" style="display:<?= $this->tabBuilder->get_tabDisplay('Configuration'); ?>;" class="adminContentPanel">
    <?php $this->load_file('html/configuration/edit.html.inc');?>
</div>
<?= $this->editForm->display_footer(); ?>

<?php if ($this->help != null) : ?>
    <div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help')?>;" class="adminContentPanel">
        <?php $this->display_help(); ?>
    </div>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
