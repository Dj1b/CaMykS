<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Dec 2012
 * Last Modif Date	: Dec 2012
 * 
 * Admin_GenericEmailingManager Module Admin Layout : edit_emailing
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('style'=>'width:600px;margin:0 auto;', 'class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header();?>
<?=$this->editform->display_header(); ?>
<?=$this->editform->display_hiddens(); ?>
<div id="itemproperties" style="display:<?=$this->tabBuilder->get_tabDisplay('properties');?>" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
	<td class="eTableLine0 eContent2" style="width:150px;">
		<?=$camyks->get_translation('formitem_status')?>
	</td>
	<td class="eTableLine0 eContent1" colspan="2">
		<?=$this->emailingStatusList[$this->emailingItem->vars['status']];?>
	</td>
</tr>

<tr>
	<td class="eTableLine1 eContent2">
		<?=$this->get_translation('formitem_cdate')?>
	</td>
	<td class="eTableLine1 eContent1" colspan="2">
		<?=date_displayLongDayDateHour($this->emailingItem->vars['cdate']);?>
	</td>
</tr>


<tr>
	<td class="eTableLine0 eContent2">
		<?=$this->get_translation('formitem_contactstatus')?>
	</td>
	<td class="eTableLine0 eContent1" colspan="2">
		<?=$this->editform->display_selectInput(array('name'=>'contact_source', 'values'=>$this->contactSourceList));?>
	</td>
</tr>

<tr>
	<td class="eTableLine0 eContent2">
		<?=$this->get_translation('formitem_contactgroup')?>
	</td>
	<td class="eTableLine0 eContent1" colspan="2">
		<?=$this->editform->display_selectInput(array('name'=>'contact_group', 'values'=>$this->contactGroupList));?>
	</td>
</tr>

<tr>
  <td class="eTableHeader" colspan="3">
  	<?=$this->get_translation('formtitle_emailcontent')?>
  </td>
</tr>

<tr>
	<td class="eTableLine0 eContent2">
		<?=$camyks->get_translation('formitem_title')?>
	</td>
	<td class="eTableLine0 eContent1" colspan="2">
		<?=$this->editform->display_textInput('email_title');?>
	</td>
</tr>

<tr>
	<td class="eTableLine1 eContent2">
		<?=$this->get_translation('formitem_content')?>
	</td>
	<td class="eTableLine1 eContent1" colspan="2">
		<?=$this->editform->display_fileInput('email_contentfile');?>
	</td>
</tr>


<tr>
	<td class="eTableLine0 eContent2">
		<?=$this->get_translation('formitem_sendername')?>
	</td>
	<td class="eTableLine0 eContent1" colspan="2">
		<?=$this->editform->display_textInput(array('name'=>'sender_name'));?>
	</td>
</tr>

<tr>
	<td class="eTableLine0 eContent2">
		<?=$this->get_translation('formitem_senderemail')?>
	</td>
	<td class="eTableLine0 eContent1" colspan="2">
		<?=$this->editform->display_textInput(array('name'=>'sender_email'));?>
	</td>
</tr>

<tr>
	<td class="eTableLine0 eContent2">
		<?=$this->get_translation('formitem_replytoname')?>
	</td>
	<td class="eTableLine0 eContent1" colspan="2">
		<?=$this->editform->display_textInput(array('name'=>'replyto_name'));?>
	</td>
</tr>

<tr>
	<td class="eTableLine0 eContent2">
		<?=$this->get_translation('formitem_replytoemail')?>
	</td>
	<td class="eTableLine0 eContent1" colspan="2">
		<?=$this->editform->display_textInput(array('name'=>'replyto_email'));?>
	</td>
</tr>

<tr>
  <td class="eTableHeader" colspan="3">
  	<?=$this->get_translation('formtitle_attachedimages')?>
  </td>
</tr>

<?php $alt = 0 ?>
<?php foreach ($this->emailingItem->config->vars['content_images'] as $index => $filename) : ?>
<tr>
	<td class="eTableLine<?=$alt?> eContent2">
		<?=$this->get_translation('formitem_contentimage', $filename)?>
	</td>
	<td class="eTableLine<?=$alt?> eContent1" colspan="2">
		<?=$this->editform->display_fileInput('email_contentimage'.$index);?>
	</td>
</tr>
<?php $alt = abs($alt-1); ?>
<?php endforeach; ?>

</table>
</div>

<div id="itemadvanced" style="display:<?=$this->tabBuilder->get_tabDisplay('advanced');?>" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_headers'); ?>
  </td>
</tr>

<tr>
	<td class="eTableLine0 eContent2" style="width:150px;">
		<?=$this->get_translation('formitem_envelopeemail')?>
	</td>
	<td class="eTableLine0 eContent1" colspan="2">
	  <?=$this->editform->display_textInput('advanced_envelope_email');?>
	</td>
</tr>

<tr>
	<td class="eTableLine1 eContent2">
		<?=$this->get_translation('formitem_includelistunsub')?>
	</td>
	<td class="eTableLine1 eContent1" colspan="2">
	    <?=$this->editform->display_booleanSelectInput('advanced_include_listunsub');?>
	</td>
</tr>

<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_sending'); ?>
  </td>
</tr>

<tr>
	<td class="eTableLine0 eContent2" style="width:150px;">
		<?=$this->get_translation('formitem_sendinginterval')?>
	</td>
	<td class="eTableLine0 eContent1" colspan="2">
	  <?=$this->editform->display_textInput('advanced_sending_interval');?> s.
	</td>
</tr>


</table>
</div>


<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:<?=$this->tabBuilder->get_tabDisplay('help')?>;" class="adminContentPanel">
<?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?=$this->editform->display_footer(); ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>