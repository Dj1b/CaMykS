<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: May 2008
 * Last Modif Date	: May 2008
 * 
 * Admin_GenericDownloadManager Module Admin Layout : edit_category
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
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
<td class="eTableLine0">
<?=$this->editform->display_selectInput(array('name'=>'active', 'values'=>$this->get_categoryStatusList()));?>
</td>
</tr>

<?php  $alt=1; ?>
<?php foreach ( $camyks->_conf['editing_languages'] as $l ) : ?>
<tr>
<td class="eTableLine<?=$alt?> eContent2">
<img src="<?=language_getIcon($l, false);?>" alt="" border="0" style="float:right" />  
<?=$camyks->get_translation('formitem_title')?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$this->editform->display_textInput(array('name'=>'title', 'language'=>$l));?>
</td>
</tr>
<?php $alt=abs($alt-1);?>
<?php endforeach; ?>
</table>
</div>
<?=$this->editform->display_footer(); ?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>