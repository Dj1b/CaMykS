<?php
/**
 * @brief Content_GenericHTMLNews Module admin edit news item layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title.' : '.$this->get_translation('editanews')); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div id="itemproperties" style="display:<?= $this->tabBuilder->get_tabDisplay('properties'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $camyks->get_translation('formitem_title'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_textInput('title'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_status'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_selectInput(array('name'=>'status', 'values'=>$this->get_newsStatusList())); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('language'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_selectInput(array('name'=>'language', 'values'=>$this->get_newsLanguageList())); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_date'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_dateInput(array('name'=>'ndate')); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('summary'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_textareaInput(array('name'=>'summary', 'class'=>'mceNoEditor vlinputs')); ?>
             </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('source_title'); ?>
            </td>
            <td class="eTableLine0">
                 <?= $this->form->display_textInput('source_title'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('source_url'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_textInput('source_url'); ?>
            </td>
        </tr>
    </table>
</div>
<div id="itemcontent" style="display:<?= $this->tabBuilder->get_tabDisplay('content'); ?>;" class="adminContentPanel">
    <?php $this->input->display(); ?>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
