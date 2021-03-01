<?php
/**
 * @brief Admin_GooglePoIMapManager Module admin edit category layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
$flags = array();
$lgs = $camyks->get_confValue('editing_languages');
if (count($lgs) == 1) {
  $flags[$lgs[0]] = '';
} else {
  foreach ($lgs as $l)
    $flags[$l] = '<img src="'.language_getIcon($l, false).'" alt="" border="0" style="float:right" />';
}
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->editform->display_header(); ?>
<?= $this->editform->display_hiddens(); ?>
<div id="itemproperties" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $camyks->get_translation('formitem_status'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->editform->display_selectInput(array('name'=>'status', 'values'=>$this->get_categoryStatusList())); ?>
            </td>
        </tr>

        <?php  $alt=1; ?>
        <?php foreach ($lgs as $l) : ?>
            <tr>
                <td class="eTableLine<?= $alt; ?> eContent2">
                    <?= $flags[$l];?>
                    <?= $camyks->get_translation('formitem_title'); ?>
                </td>
                <td class="eTableLine<?= $alt; ?> eContent1">
                    <?= $this->editform->display_textInput(array('name'=>'title', 'language'=>$l)); ?>
                </td>
            </tr>
            <?php $alt=abs($alt-1); ?>
        <?php endforeach; ?>

    </table>
</div>
<?= $this->editform->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
