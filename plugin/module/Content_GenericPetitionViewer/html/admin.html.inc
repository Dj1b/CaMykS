<?php
/**
 * @brief Content_GenericPetitionViewer module, admin layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2010
 * @date Modification: May 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title.' : '.$this->configItem->vars['name'].' ['.$this->configItem->id.']'); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $camyks->get_translation('formitem_name'); ?>
            </td>
            <td class="eTableLine0" colspan="2">
                <?= $this->form->display_textInput('name'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_layout'); ?>
            </td>
            <td class="eTableLine1" colspan="2">
                <?= $this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->get_layoutList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_petition'); ?>
            </td>
            <td class="eTableLine0" colspan="2">
                <?= $this->form->display_selectInput(array('name'=>'petition', 'values'=>$this->petitionList)); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_signbypage'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textInput('signcount'); ?>
            </td>
        </tr>
    </table>
</div>

<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
