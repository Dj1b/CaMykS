<?php
/**
 * @brief Admin_GenericEmailingManager Module main layout
 * @details Plugin, Module Layout
 * @file plugin/module/Admin_GenericEmailingManager/html/admin.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2012
 * @date Modification: Dec 2018
 * @copyright 2012 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('style'=>'width:800px;margin:0 auto;', 'class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title) ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs,$this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itemcontacts" style="display:<?= $this->tabBuilder->get_tabDisplay('contacts'); ?>;" class="adminContentPanel">
    <?= $this->contactList->display('head'); ?>
    <?= $this->contactList->display('list'); ?>
</div>

<?php if ($this->check_right(2)) : ?>
<div id="itememailings" style="display:<?= $this->tabBuilder->get_tabDisplay('emailings'); ?>;" class="adminContentPanel">
    <?= $this->emailingList->display('head'); ?>
    <?= $this->emailingList->display('list'); ?>
</div>
<?php endif; ?>

<?php if ($this->check_right(5)) : ?>
<div id="itemconfig" style="display:<?= $this->tabBuilder->get_tabDisplay('config'); ?>;" class="adminContentPanel">
    <?php $this->load_file('html/configuration/view.html.inc'); ?>
</div>
<?php endif; ?>

<?php if ($this->help != null) : ?>
<div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
    <?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
