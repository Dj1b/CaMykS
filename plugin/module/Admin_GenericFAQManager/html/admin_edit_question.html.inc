<?php
/**
 * @brief Admin_GenericFAQManager Module admin edit question layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Feb 2020
 * @date Modification: Jan 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$flags = array();
if (count($lgs = $camyks->get_confValue('editing_languages')) > 1)
    foreach ($lgs as $l)
        $flags[$l] = '<img src="'.language_getIcon($l, false).'" alt="" border="0" style="float:right;" />';
else
    foreach ($lgs as $l)
        $flags[$l] = '';
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->editform->display_header(); ?>
<?= $this->editform->display_hiddens(); ?>
<div id="itemProperties" style="display:<?= $this->tabBuilder->get_tabDisplay('Properties'); ?>" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $camyks->get_translation('formitem_status'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editform->display_selectInput(array('name'=>'status', 'values'=>$this->questionItem->get_statusList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_family'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->editform->display_selectInput(array('name'=>'family', 'values'=>$this->get_familyTitleList())); ?>
            </td>
        </tr>

        <?php foreach($lgs as $l) : ?>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $flags[$l]; ?>
                    <?= $camyks->get_translation('formitem_title'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->editform->display_textInput(array('name'=>'title', 'language'=>$l, 'class'=>'linputs')); ?>
                </td>
            </tr>
        <?php endforeach; ?>
    </table>
</div>

<?php foreach($lgs as $l) : ?>
    <div id="item<?= $l?>" style="display:<?= $this->tabBuilder->get_tabDisplay($l); ?>" class="adminContentPanel">
        <?php $this->input->set_contentInfos('text', $this->questionItem->vars['answer_'.$l]); ?>
        <?php $this->input->set_textareaInfos('answer_'.$l, '100%', '400px'); ?>
        <?php $this->input->display(); ?>
    </div>
<?php endforeach; ?>

<?= $this->editform->display_footer(); ?>

<?php if ($this->help != null) : ?>
    <div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
        <?php $this->display_help(); ?>
    </div>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
