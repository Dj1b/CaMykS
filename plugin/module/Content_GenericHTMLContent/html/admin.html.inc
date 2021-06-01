<?php
/**
 * @brief Content_GenericHTMLContent module, admin layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2008
 * @date Modification: May 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title.' : '. $this->content->vars['name'].' [ '.$this->content->id.' ] '); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div id="itemProperties" style="display:<?= $this->tabBuilder->get_tabDisplay('Properties'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:100px">
                <?= $this->get_translation('itemname'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_textInput('name'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('itemlayout'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->layouts)); ?>
            </td>
        </tr>
    </table>
</div>
<?php foreach ($camyks->get_confValue('editing_languages') as $l) : ?>
    <div id="item<?= $l?>" style="display:<?= $this->tabBuilder->get_tabDisplay($l); ?>" class="adminContentPanel">
        <?php $this->input->set_contentInfos('file', $this->content->vars['content_'.$l]); ?>
        <?php $this->input->set_textareaInfos('content_'.$l, '100%', '400px'); ?>
        <?php $this->input->display(); ?>
    </div>
<?php endforeach; ?>

<?php if ($this->help != null) : ?>
<div id="itemhelp" style="display:none;">
    <?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
