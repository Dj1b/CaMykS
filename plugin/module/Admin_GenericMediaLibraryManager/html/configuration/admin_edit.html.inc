<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0.1
 * Object Type	    : Plugin / Module Layout
 * Creation Date	: Jun 2015
 * Last Modif Date	: Jul 2018
 * 
 * Admin_GenericMediaLibraryManager Module Admin Layout : edit_config
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxContent2Header( )?>

<?=$this->configform->display_header(); ?>
<?=$this->configform->display_hiddens(); ?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
  <td colspan="4" class="eTableHeader">
    <?=$this->get_translation('picturegalleries');?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_maxfilesize');?>
  </td>
  <td class="eTableLine0 eContent1" colspan="3">
    <?=$this->configform->display_textInput(array('name'=>'picture_maxFileSize', 'maxlength'=>6, 'class'=>'vsinputs'));?> M<?=language_getFileUnit()?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2" style="width:200px;">
    <?=$this->get_translation('formitem_resizemode');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->configform->display_selectInput(array('name'=>'picture_resizeMode', 'values'=>$this->get_configResizeModeList()));?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2" style="width:200px;">
    <?=$this->get_translation('formitem_backgroundcolor');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->configform->display_textInput(array('name'=>'picture_backgroundColor', 'maxlength'=>7, 'class'=>'vsinputs'));?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('formitem_filetype');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->configform->display_selectInput(array('name'=>'picture_fileType', 'values'=>$this->get_configFileTypeList()));?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_quality');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->configform->display_textInput(array('name'=>'picture_jpgQuality', 'maxlength'=>3, 'class'=>'vsinputs'));?> %
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('formitem_picturewidth');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->configform->display_textInput(array('name'=>'picture_pictureWidth', 'maxlength'=>6, 'class'=>'vsinputs'));?> px
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_pictureheight');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->configform->display_textInput(array('name'=>'picture_pictureHeight', 'maxlength'=>6, 'class'=>'vsinputs'));?> px
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('formitem_thumbwidth');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->configform->display_textInput(array('name'=>'picture_thumbWidth', 'maxlength'=>6, 'class'=>'vsinputs'));?> px
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_thumbheight');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->configform->display_textInput(array('name'=>'picture_thumbHeight', 'maxlength'=>6, 'class'=>'vsinputs'));?> px
  </td>
</tr>

</table>
</div>
<?=$this->configform->display_footer(); ?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>