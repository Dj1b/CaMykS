<?php
/**
 * @brief Content_GenericGuestBookViewer module, admin layout.
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
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div id="itemproperties" style="display:<?= $this->tabBuilder->get_tabDisplay('properties'); ?>;" class="adminContentPanel">
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
                <?= $this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->get_configLayoutList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_formlayout'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'formlayout', 'values'=>$this->get_configFormLayoutList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_msgbypage'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textInput('msgcount'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_gpcstyle'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'gpcstyle', 'values'=>$this->get_configGPCStyleList())); ?>
            </td>
        </tr>
    </table>
</div>

<?php foreach ($this->lgs as $l) : ?>
    <div id="item<?= $l; ?>" style="display:<?= $this->tabBuilder->get_tabDisplay($l); ?>;" class="adminContentPanel">
        <?php $this->editor->set_contentInfos('text', $this->configItem->vars['description_'.$l]); ?>
        <?php $this->editor->set_textareaInfos('description_'.$l, '100%', '400px'); ?>
        <?php $this->editor->display(); ?>
    </div>
<?php endforeach; ?>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
