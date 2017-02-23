<?php
/*
 * CaMykS Engine
 * Developed by		: skymac.org
 * Author		: sky <skymac.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Sep 2010
 * Last Modif Date	: Sep 2010
 * 
 * Admin_GenericGuestBookManager Module admin layout : view msg
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxContent2Header()?>

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
<?=$this->msgItem->get_statusValue();?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$camyks->get_translation('formitem_date');?>
</td>
<td class="eTableLine0">
<?=date_displayLongDateHour($this->msgItem->vars['edate']);?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_author');?>
</td>
<td class="eTableLine1">
<?=$this->msgItem->vars['author'];?>
</td>
</tr> 

<tr>
<td class="eTableLine0 eContent2">
<?=$camyks->get_translation('formitem_email');?>
</td>
<td class="eTableLine0">
<a class="eLink2" href="mailto:<?=$this->msgItem->vars['email'];?>"><?=$this->msgItem->vars['email'];?></a>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$camyks->get_translation('formitem_website');?>
</td>
<td class="eTableLine1">
<?php if ($this->msgItem->vars['website'] != '') : ?>
<a class="eLink2" href="<?=$this->msgItem->vars['website'];?>" target="_blank"><?=$this->msgItem->vars['website'];?></a>
<?php endif; ?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_message');?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->msgItem->vars['message'];?>
</td>
</tr>

</table>
</div>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>
