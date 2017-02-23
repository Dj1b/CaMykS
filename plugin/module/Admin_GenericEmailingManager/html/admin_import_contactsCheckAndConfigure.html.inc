<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Jan 2013
 * Last Modif Date	: Jan 2013
 * 
 * Admin_GenericEmailingManager Module Admin Layout : import_contactsCheckAndConfigure
*/
global $camyks;

$maxLine = 5;
$maxCol = 6;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxContent2Header();?>
<?=$this->importform->display_header(); ?>
<?=$this->importform->display_hiddens(); ?>
<div id="itemproperties" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
  <td class="eTableLine0 eContent2" colspan="2">
    <?= $this->get_translation('xlinesfound', $this->xlsFile->rowcount()); ?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2" colspan="2">
    &nbsp;
  </td>
</tr>
<tr>
  <td class="eTableLine0 eTitle3" colspan="2">
    <?=$this->get_translation('formtitle_listquicklook');?>
  </td>
</tr>
</table>
<?php $alt = 0; ?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%; border:solid 1px #888888;">
<?php for ($i = 1; $i < $maxLine + 1; $i++) : ?>
<tr>
  <td class="eTableHeader">
    <?=$i;?>
  </td>
  <?php for ($j = 1; $j < $maxCol + 1; $j++) : ?>
  <td class="eTableLine<?=$alt?> eContent1">
    <?=$this->xlsFile->value($i, $j); ?>
  </td>
  <?php endfor; ?>
  <?php $alt = abs($alt-1); ?>
</tr>
<?php endfor; ?>
</table>

<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="eTableLine0 eContent2" style="width:150px;">
  <?=$this->get_translation('formitem_loadfromline'); ?>
</td>
<td class="eTableLine0 eContent2">
  <?=$this->importform->display_textInput(array('name'=>'loadfromline', 'class'=>'vsinputs', 'default'=>1, 'maxlength'=>3)); ?>
<tr>
  <td class="eTableLine0 eContent2" colspan="2">
    &nbsp;
  </td>
</tr>
</table>

<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
  <td class="eTableLine0 eTitle3" colspan="4">
    <?=$this->get_translation('formtitle_colmapping');?>
  </td>
</tr>
<tr>
  <td class="eTableHeader" style="width:12px;">
    #
  </td>
  <td class="eTableHeader" style="width:60px;">
    <?=$this->get_translation('value');?>
  </td>
  <td class="eTableHeader" style="width:60px;">
    <?=$this->get_translation('field');?>
  </td>
  <td class="eTableHeader">
    <?=$this->get_translation('parameters');?>
  </td>
</tr>
<?php $alt = 0; ?>
<?php for ($i=1; $i< $this->xlsFile->colcount() + 1; $i ++ ) : ?>
<tr>
  <td class="eTableLine<?=$alt?> eContent2">
    <?=$i;?>
  </td>
  <td class="eTableLine<?=$alt?> eContent3">
    <?=string_getShortenedSentence($this->xlsFile->value(1, $i), 16); ?>
  </td>
  <td class="eTableLine<?=$alt?> eContent1">
    <?=$this->importform->display_selectInput(array('name'=>'col'.$i.'_field', 'class'=>'sinputs', 'values'=>$this->importContactFieldList, 'onchange'=>'icc.show_fieldParameters('.$i.');')); ?>
  </td>
  <td class="eTableLine<?=$alt?> eContent2">
    <div id="col<?=$i?>_statusParams" style="display:none;">
      <?php foreach ($this->contactItem->get_statusList() as $id => $name) : ?>
        <?=$name?>: <?=$this->importform->display_textInput(array('name'=>'col'.$i.'_status'.$id, 'style'=>'width:12px;', 'maxlength'=>3)); ?>
      <?php endforeach; ?>
    </div>
  </td>
</tr>
<?php $alt = abs($alt-1); ?>
<?php endfor; ?>

</table>
</div>

<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:<?=$this->tabBuilder->get_tabDisplay('help')?>;" class="adminContentPanel">
<?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?=$this->importform->display_footer(); ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>