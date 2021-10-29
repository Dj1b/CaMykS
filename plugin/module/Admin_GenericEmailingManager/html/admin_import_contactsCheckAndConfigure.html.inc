<?php
/**
 * @brief Admin_GenericEmailingManager Module, import contacts - check and configure step layout.
 * @details Plugin, Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.8.1
 * @date Creation: Jan 2013
 * @date Modification: Oct 2021
 * @copyright 2013 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$maxLine = 5;
$maxCol = count($this->data[0]);
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->importform->display_header(); ?>
<?= $this->importform->display_hiddens(); ?>
<div id="itemproperties" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
    <td class="eTableLine0 eContent2" colspan="2">
        <?= $this->get_translation('xlinesfound', count($this->data)); ?>
    </td>
</tr>
<tr>
    <td class="eTableLine0 eContent2" colspan="2">
        &nbsp;
    </td>
</tr>
<tr>
    <td class="eTableLine0 eTitle3" colspan="2">
        <?= $this->get_translation('formtitle_listquicklook'); ?>
    </td>
</tr>
</table>
<?php $alt = 0; ?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%; border:solid 1px #888888;">
<?php for ($i = 1; $i < $maxLine + 1; $i++) : ?>
<tr>
    <td class="eTableHeader">
        <?= $i; ?>
    </td>
    <?php for ($j = 0; $j < $maxCol; $j++) : ?>
    <td class="eTableLine<?= $alt; ?> eContent1">
        <?= isset($this->data[$i][$j]) ? $this->data[$i][$j] : ''; ?>
    </td>
    <?php endfor; ?>
    <?php $alt = abs($alt-1); ?>
</tr>
<?php endfor; ?>
</table>

<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="eTableLine0 eContent2" style="width:150px;">
    <?= $this->get_translation('formitem_loadfromline'); ?>
</td>
<td class="eTableLine0 eContent2">
    <?= $this->importform->display_textInput(array('name'=>'loadfromline', 'class'=>'vsinputs', 'default'=>1, 'maxlength'=>3)); ?>
<tr>
    <td class="eTableLine0 eContent2" colspan="2">
        &nbsp;
    </td>
</tr>
</table>

<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
    <td class="eTableLine0 eTitle3" colspan="4">
        <?= $this->get_translation('formtitle_colmapping'); ?>
    </td>
</tr>
<tr>
    <td class="eTableHeader" style="width:12px;">
        #
    </td>
    <td class="eTableHeader" style="width:60px;">
        <?= $this->get_translation('value'); ?>
    </td>
    <td class="eTableHeader" style="width:60px;">
        <?= $this->get_translation('field'); ?>
    </td>
    <td class="eTableHeader">
        <?= $this->get_translation('parameters'); ?>
    </td>
</tr>
<?php $alt = 0; ?>
<?php for ($i=0; $i< count($this->data[0]); $i ++) : ?>
<tr>
    <td class="eTableLine<?= $alt?> eContent2">
        <?= $i; ?>
    </td>
    <td class="eTableLine<?= $alt?> eContent3">
        <?= string_getShortenedSentence($this->data[1][$i], 16); ?>
    </td>
    <td class="eTableLine<?= $alt?> eContent1">
        <?= $this->importform->display_selectInput(array('name'=>'col'.$i.'_field', 'class'=>'sinputs', 'values'=>$this->importContactFieldList, 'onchange'=>'icc.show_fieldParameters('.$i.');')); ?>
    </td>
    <td class="eTableLine<?= $alt?> eContent2">
        <div id="col<?= $i?>_statusParams" style="display:none;">
            <?php foreach ($this->contactItem->get_statusList() as $id => $name) : ?>
                <?= $name?>: <?= $this->importform->display_textInput(array('name'=>'col'.$i.'_status'.$id, 'style'=>'width:12px;', 'maxlength'=>3)); ?>
            <?php endforeach; ?>
        </div>
    </td>
</tr>
<?php $alt = abs($alt-1); ?>
<?php endfor; ?>

</table>
</div>

<?php if ($this->help != null) : ?>
<div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
<?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?= $this->importform->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
