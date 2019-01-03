<?php
/**
 * @brief Admin_GenericEmailingManager Module import contacts - prepare step layout
 * @details Plugin, Module Layout
 * @file plugin/module/Admin_GenericEmailingManager/html/admin_import_contactsPrepare.html.inc
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
<?= $this->importform->display_header(); ?>
<?= $this->importform->display_hiddens(); ?>
<div id="itemproperties" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
    <td class="eTableLine0 eContent2" colspan="2">
        &nbsp;
    </td>
</tr>
<tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
        <?= $this->get_translation('formitem_yourfile'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= $this->importform->display_fileInput(array('name'=>'file')); ?>
    </td>
</tr>
<tr>
    <td class="eTableLine0 eContent2" colspan="2">
        &nbsp;
    </td>
</tr>

</table>
</div>

<?php if ($this->help != null) : ?>
<div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
    <?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?= $this->importform->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
