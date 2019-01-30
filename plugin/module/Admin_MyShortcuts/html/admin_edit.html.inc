<?php
/**
 * @brief Admin_MyShortcuts Module edit shortcut layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_MyShortcuts/html/admin_edit.html.inc
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

<?= $this->theme->get_boxHeader(array('style'=>'width:600px; margin:0 auto;', 'class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
    <div class="adminContentPanel">
        <table cellspacing="0" style="width:100%;">
            <tr>
                <td class="eTableHeader" colspan="2">
                    <?= $camyks->get_translation('properties'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2" style="width:150px;">
                    <?= $camyks->get_translation('formitem_title'); ?>
                </td>
                <td class="eTableLine0 eContent2">
                    <?= $this->form->display_textInput(array('name'=>'name')); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_url'); ?>
                </td>
                <td class="eTableLine1 eContent2">
                    <?= $this->form->display_textInput(array('name'=>'url', 'class'=>'vlinputs')); ?>
                </td>
            </tr>
        </table>
    </div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
