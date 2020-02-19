<?php
/**
 * @brief Admin_GenericFAQManager Module admin edit family layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Feb 2020
 * @date Modification: Feb 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$flags = array();
if (count($camyks->get_confValue('editing_languages')) > 1)
    foreach ($camyks->get_confValue('editing_languages') as $l)
        $flags[$l] = '<img src="'.language_getIcon($l, false).'" alt="" border="0" style="float:right;" />';
else
    foreach ($camyks->get_confValue('editing_languages') as $l)
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
                <?= $this->editform->display_selectInput(array('name'=>'status', 'values'=>$this->familyItem->get_statusList())); ?>
            </td>
        </tr>

        <?php foreach ($camyks->get_confValue('editing_languages') as $l) : ?>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $flags[$l]; ?>
                <?= $camyks->get_translation('formitem_title'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editform->display_textInput(array('name'=>'title', 'language'=>$l)); ?>
            </td>
        </tr>
        <?php endforeach; ?>
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
