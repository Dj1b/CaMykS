<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Create Date	    : Jun 2010
 * Last Modif Date  : Jun 2010
 * 
 * Admin_GooglePoIMapManager Module Admin Layout : edit_icon
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxContent2Header( )?>
<?=$this->editform->display_header(); ?>
<?=$this->editform->display_hiddens(); ?>
<div id="itemproperties" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
  <td class="eTableLine0 eContent2" style="width:150px;">
    <?=$camyks->get_translation('formitem_name');?>
  </td>
  <td class="eTableLine0 eContent1" colspan="3">
    <?=$this->editform->display_textInput('name');?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('formitem_mainimg');?>
  </td>
  <td class="eTableLine1 eContent1" colspan="3">
    <?=$this->editform->display_fileInput('mainImg');?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_rollimg');?>
  </td>
  <td class="eTableLine0 eContent1" colspan="3">
    <?=$this->editform->display_fileInput('rollImg');?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('formitem_slctimg');?>
  </td>
  <td class="eTableLine1 eContent1" colspan="3">
    <?=$this->editform->display_fileInput('slctImg');?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_shdwimg');?>
  </td>
  <td class="eTableLine0 eContent1" colspan="3">
    <?=$this->editform->display_fileInput('shdwImg');?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <div style="float:right;" class="eContent2">
    <?=$this->get_translation('formitem_x');?>
    </div>
    <?=$this->get_translation('formitem_anchorloc');?>
  </td>
  <td class="eTableLine1 eContent1" style="width:110px;">
    <?=$this->editform->display_textInput(array('name'=>'anchorLocX', 'class'=>'sinputs'));?>
  </td>
  <td class="eTableLine1 eContent2" style="width:50px; text-align:right;">
    <?=$this->get_translation('formitem_y');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->editform->display_textInput(array('name'=>'anchorLocY', 'class'=>'sinputs'));?>
  </td>
</tr>

</table>
</div>

<?=$this->editform->display_footer(); ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>