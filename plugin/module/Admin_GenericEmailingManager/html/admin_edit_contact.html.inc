<?php
/**
 * @brief Admin_GenericEmailingManager Module edit contact layout
 * @details Plugin, Module Layout
 * @file plugin/module/Admin_GenericEmailingManager/html/admin_edit_contact.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2012
 * @date Modification: Dec 2018
 * @copyright 2012 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$cross = $this->theme->get_pictURL('cross', 12, 'std');
$cross_ = $this->theme->get_pictURL('cross', 12, 'ovr');
?>
<?= $this->theme->get_boxHeader(array('style'=>'width:600px;margin:0 auto;', 'class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->editform->display_header(); ?>
<?= $this->editform->display_hiddens(); ?>
<div id="itemproperties" style="display:<?= $this->tabBuilder->get_tabDisplay('properties'); ?>" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
        <?= $camyks->get_translation('formitem_status'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= $this->editform->display_selectInput(array('name'=>'status', 'values'=>$this->statusList)); ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $camyks->get_translation('formitem_firstname'); ?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= $this->editform->display_textInput('firstname'); ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $camyks->get_translation('formitem_lastname'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= $this->editform->display_textInput('lastname'); ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $camyks->get_translation('formitem_email'); ?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= $this->editform->display_textInput('email'); ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_group'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= $this->editform->display_selectInput(array('name'=>'group', 'id'=>'groupList', 'values'=>$this->contactGroupList, 'onchange'=>'ce.check_groupValue(this)')); ?>
        <div id="groupTextBox" style="display:none;">
        <?= $this->editform->display_textInput(array('name'=>'group', 'id'=>'groupText', 'disabled'=>true)); ?>
        <a href="javascript:ce.display_groupAsList();" class="img">
          <img src="<?= $cross?>" border="0"
            alt="<?= $this->get_translation('backtolist'); ?>"
            title="<?= $this->get_translation('backtolist'); ?>"
            onmouseover="this.src='<?= $cross_?>';"
            onmouseout="this.src='<?= $cross?>';" />
        </a>
        </div>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_denomination'); ?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= $this->editform->display_textInput('denomination'); ?>
    </td>
</tr>


</table>
</div>

<?php if ($this->help != null) : ?>
<div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
    <?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?= $this->editform->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
