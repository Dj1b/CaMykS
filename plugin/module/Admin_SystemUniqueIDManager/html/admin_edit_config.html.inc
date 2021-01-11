<?php
/**
 * @brief Admin_SystemUniqueIDManager Module admin edit configuration layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Apr 2016
 * @date Modification: Jan 2021
 * @copyright 2016 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>

<?= $this->editform->display_header(); ?>
<?= $this->editform->display_hiddens(); ?>

<div id="itemConfiguration" style="display:<?= $this->tabBuilder->get_tabDisplay('Configuration'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_configuration'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableSubHeader" colspan="2">
                <?= $this->get_translation('formtitle_generating'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $this->get_translation('formitem_method'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editform->display_selectInput(array('name'=>'generating_method', 'values'=>$this->generatingMethodList)); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_keylength'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->editform->display_textInput(array('name'=>'generating_length')); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_maxattempts'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editform->display_textInput(array('name'=>'generating_maxAttempts')); ?>
            </td>
        </tr>
    </table>
</div>

<?= $this->editform->display_footer(); ?>

<?php if ($this->help != null) : ?>
    <div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
        <?php $this->display_help(); ?>
    </div>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
