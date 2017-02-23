<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 * 
 * Admin_GenericPetitionManager Module Admin Layout : edit_signature
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:610px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxContent2Header( )?>
<?=$this->editform->display_header(); ?>
<?=$this->editform->display_hiddens(); ?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="eTableLine0 eContent2" style="width:150px;">
<?=$camyks->get_translation('formitem_status')?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->editform->display_selectInput(array('name'=>'status', 'values'=>$this->get_signatureStatusList()));?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2" style="width:150px;">
<?=$camyks->get_translation('formitem_civility')?>
</td>
<td class="eTableLine1 eContent1">
<?=$this->editform->display_civilitySelectInput('title');?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$camyks->get_translation('formitem_lastname')?>
</td>
<td class="eTableLine0 eContent1">
  <?=$this->editform->display_textInput('lastname');?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$camyks->get_translation('formitem_firstname')?>
</td>
<td class="eTableLine1 eContent1">
  <?=$this->editform->display_textInput('firstname');?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$camyks->get_translation('formitem_email')?>
</td>
<td class="eTableLine0 eContent1">
  <?=$this->editform->display_textInput('email');?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$camyks->get_translation('formitem_zipcode')?>
</td>
<td class="eTableLine1 eContent1">
  <?=$this->editform->display_textInput('zipcode');?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$camyks->get_translation('formitem_city')?>
</td>
<td class="eTableLine0 eContent1">
  <?=$this->editform->display_textInput('city');?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$camyks->get_translation('formitem_country')?>
</td>
<td class="eTableLine1 eContent1">
  <?=$this->editform->display_countrySelectInput();?>
</td>
</tr>

</table>
</div>

<?=$this->editform->display_footer(); ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>