<?php
/**
 * @brief Admin_SystemNotifications Module admin edit website layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_SystemNotifications/html/admin_edit_website.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2017
 * @date Modification: May 2019
 * @copyright 2017 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>

<?= $this->editForm->display_header(); ?>
<?= $this->editForm->display_hiddens(); ?>

<div id="itemProperties" style="display:<?= $this->tabBuilder->get_tabDisplay('Properties')?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $camyks->get_translation('formitem_status'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_selectInput(array('name'=>'status', 'values'=>$this->get_websiteStatusList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $camyks->get_translation('formitem_name'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->editForm->display_textInput(array('name'=>'name')); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_url'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_textInput(array('name'=>'baseURL')); ?>/<?= $this->editForm->display_textInput(array('name'=>'pageURL')); ?>
            </td>
        </tr>

        <tr>
            <td colspan="2">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_access'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_login'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_textInput(array('name'=>'login')); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_password'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_textInput(array('name'=>'password')); ?>
            </td>
        </tr>

    </table>
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
