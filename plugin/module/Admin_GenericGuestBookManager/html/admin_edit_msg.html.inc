<?php
/*
 * CaMykS Engine
 * Developed by		: skymac.org
 * Author		: sky <skymac.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jan 2010
 * Last Modif Date	: Jan 2010
 * 
 * Admin_p2cracingGuestBookManager Module admin layout : edit event
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxContent2Header()?>

<?=$this->editform->display_header();?>
<?=$this->editform->display_hiddens();?>

<div id="itemproperties" class="adminContentPanel">

<table cellspacing="0" cellpadding="0" border="0" style="width:100%">

<tr>
<td class="eTableLine1 eContent2" style="width:150px;">
<?=$camyks->get_translation('formitem_status');?>
</td>
<td class="eTableLine1">
<div style="float:right;" class="eContent2">
<?=$this->msgItem->vars['ipaddress'];?>
</div>
<?=$this->editform->display_selectInput(array('name'=>'status', 'values'=>$this->get_messageStatusList()));?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$camyks->get_translation('formitem_date');?>
</td>
<td class="eTableLine0">
<?=$this->editform->display_dateInput(array('name'=>'edate'));?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_author');?>
</td>
<td class="eTableLine1">
<?=$this->editform->display_textInput('author');?>
</td>
</tr> 

<tr>
<td class="eTableLine0 eContent2">
<?=$camyks->get_translation('formitem_email');?>
</td>
<td class="eTableLine0">
<?=$this->editform->display_textInput('email');?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$camyks->get_translation('formitem_website');?>
</td>
<td class="eTableLine1">
<?=$this->editform->display_textInput('website');?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_message');?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->editform->display_textAreaInput('message');?>
</td>
</tr>

</table>
</div>

<?=$this->editform->display_footer();?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>
