<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Oct 2007
 * Last Modif Date	: Oct 2007
 * 
 * Admin_SecurityTools module admin layout
*/
global $camyks;

$view = $this->theme->get_pictURL('view', 12, 'std' );
$view_ = $this->theme->get_pictURL('view', 12, 'ovr' );

$edit = $this->theme->get_pictURL('edit', 12, 'std' );
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr' );

$del = $this->theme->get_pictURL('cross', 12, 'std' );
$del_ = $this->theme->get_pictURL('cross', 12, 'ovr' );

$add = $this->theme->get_pictURL('plus', 12, 'std' );
$add_ = $this->theme->get_pictURL('plus', 12, 'ovr' );

$file = $this->theme->get_pictURL('file', 12, 'std' );
$file_ = $this->theme->get_pictURL('file', 12, 'ovr' );

?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title);?>
<?=$this->theme->get_boxTabsBar($this->tabs,
				$this->tabObject.'.mouseclick',
				$this->tabObject.'.mouseover',
				$this->tabObject.'.mouseout',
				'main');?>
<?=$camyks->theme->get_boxContent2Header( )?>
<div id="itemmain" style="display:block;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0">

<tr>
<td class="eTitle3" colspan="4">
<?=$this->get_translation('availabletools');?>
</td>
</tr>

<?php foreach ( $this->tools as $tool ) : ?>
<tr>
<td class="eTableLine0 eContent1" style="width:12px;">
&nbsp;
</td>
<td class="eTableLine0 eContent1">
<img src="<?=$this->get_fileURL('img/'.($this->config->vars[$tool]?'enabled':'disabled').'.gif');?>" alt="" border="0" />
</td>
<td class="eTableLine0 eContent1" style="padding:0 8px;">
<?=$this->get_translation('tool_'.$tool);?>
</td>
<td class="eTableLine0 eContent1">
<?php if ( $this->check_right(1) ) : ?>
<?php $action = $this->config->vars[$tool]?'disable':'enable'; ?>
<?=$this->theme->get_button(array('title'=>$this->get_translation($action), 'url'=>$camyks->get_adminLink($this->name, array('mode'=>'update_config','action'=>$action, 'item'=>$tool))));?>
<?php endif; ?>
</td>
</tr>
<?php endforeach; ?>

</table>
</div>

<?php if ( $this->config->vars['ipfilter'] ) : ?>
<div id="itemipfilter" style="display:none;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="eTitle3" colspan="4">
<?=$this->get_translation('ipfilter_therules');?>
</td>
</tr>
<?php if ( $this->check_right(2) ) : ?>
<tr>
<td class="eTableLine1">
&nbsp;
</td>
<td class="eTableLine1" colspan="4">
<a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'edit_ipfilter', 'ruleid'=>0))?>">
<?=$this->get_translation('ipfilter_addrule');?>
</a>
</td>
<td class="eTableLine1 eContent1" style="width:12px;">
<a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'edit_ipfilter', 'ruleid'=>0))?>">
<img src="<?=$add?>" border="0"
 alt="<?=$this->get_translation('ipfilter_addrule');?>"
 title="<?=$this->get_translation('ipfilter_addrule');?>"
 onmouseover="this.src='<?=$add_?>';" onmouseout="this.src='<?=$add?>';" />
</a>
</td>
<td class="eTableLine1 eContent1" style="width:12px;">
&nbsp;
</td>
</tr>
<?php endif; ?>

<tr>
<td class="eTableHeader">
&nbsp;
</td>
<td class="eTableHeader" colspan="6">
<?=$this->get_translation('ipfilter_unauthorizedip');?>
</td>
</tr>

<?php $cnt = 0; ?>
<?php $alt = 0; ?>
<?php foreach ( $this->ipfilterrules as $rule ) : ?>
<?php if ( $rule->vars['permission'] == 1 ) : ?>
<tr>
<td class="eTableLine<?=$alt?> eContent1">
&nbsp;
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$rule->vars['ipaddress'];?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$this->get_translation('ipfilter_active'.$rule->vars['active']);?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$this->get_translation('ipfilter_mode'.$rule->vars['permission']);?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$rule->vars['comment'];?>
</td>
<?php if ( $this->check_right(2) ) : ?>
<td class="eTableLine<?=$alt?> eContent1">
<a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'edit_ipfilter', 'ruleid'=>$rule->id))?>">
<img src="<?=$edit?>" border="0"
alt="<?=$this->get_translation('ipfilter_editrule');?>"
title="<?=$this->get_translation('ipfilter_editrule');?>"
onmouseover="this.src='<?=$edit_?>';" onmouseout="this.src='<?=$edit?>';" />
</a>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<a href="javascript:admin_securitytools_deleteIPFilterRule(<?=$rule->id?>);">
<img src="<?=$del?>" border="0"
alt="<?=$this->get_translation('ipfilter_deleterule');?>" 
title="<?=$this->get_translation('ipfilter_deleterule');?>"
onmouseover="this.src='<?=$del_?>';" onmouseout="this.src='<?=$del?>';" />
</a>
</td>
<?php endif; ?>
</tr>
<?php $cnt++; ?>
<?php $alt=abs( $alt-1 ); ?>
<?php endif; ?>
<?php endforeach ?>
<?php if ( $cnt == 0 ) : ?>
<tr>
<td class="eTableLine0 eContent1">
&nbsp;
</td>
<td class="eTableLine0 eContent1">
<?=$this->get_translation('ipfilter_norule')?>
</td>
</tr>
<?php endif ?>

<tr>
<td class="eTableHeader">
&nbsp;
</td>
<td class="eTableHeader" colspan="6">
<?=$this->get_translation('ipfilter_authorizedip');?>
</td>
</tr>

<?php $cnt = 0; ?>
<?php $alt = 0; ?>
<?php foreach ( $this->ipfilterrules as $rule ) : ?>
<?php if ( $rule->vars['permission'] == 0 ) : ?>
<tr>
<td class="eTableLine<?=$alt?> eContent1">
&nbsp;
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$rule->vars['ipaddress'];?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$this->get_translation('ipfilter_active'.$rule->vars['active']);?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$this->get_translation('ipfilter_mode'.$rule->vars['permission']);?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$rule->vars['comment'];?>
</td>
<?php if ( $this->check_right(2) ) : ?>
<td class="eTableLine<?=$alt?>">
<a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'edit_ipfilter', 'ruleid'=>$rule->id))?>">
<img src="<?=$edit?>" border="0"
alt="<?=$this->get_translation('ipfilter_editrule');?>" 
title="<?=$this->get_translation('ipfilter_editrule');?>"
 onmouseover="this.src='<?=$edit_?>';" onmouseout="this.src='<?=$edit?>';" />
</a>
</td>
<td class="eTableLine<?=$alt?>">
<a href="javascript:admin_securitytools_deleteIPFilterRule(<?=$rule->id?>);">
<img src="<?=$del?>" border="0"
alt="<?=$this->get_translation('ipfilter_deleterule');?>" 
title="<?=$this->get_translation('ipfilter_deleterule');?>"
onmouseover="this.src='<?=$del_?>';" onmouseout="this.src='<?=$del?>';" />
</a>
</td>
<?php endif; ?>
</tr>
<?php $cnt++; ?>
<?php $alt=abs( $alt-1 ); ?>
<?php endif; ?>
<?php endforeach ?>
<?php if ( $cnt == 0 ) : ?>
<tr>
<td class="eTableLine0">
&nbsp;
</td>
<td class="eTableLine0">
<?=$this->get_translation('ipfilter_norule')?>
</td>
</tr>
<?php endif ?>

</table>
</div>
<?php endif; ?>

<?php if ( $this->config->vars['backup'] ) : ?>
<div id="itembackup" style="display:none;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="eTitle3" colspan="3">
<?=$this->get_translation('backup_configuration');?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('backup_method'); ?>
</td>
<td class="eTableLine1 eContent1">
<?=$this->get_translation('backup_method_'.$this->config->vars['backup_method']);?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('backup_compression'); ?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->get_translation('backup_compression_'.$this->config->vars['backup_compression']);?>
</td>
</tr>
<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('backup_type'); ?>
</td>
<td class="eTableLine1 eContent1">
<?=$this->get_translation('backup_type_'.$this->config->vars['backup_type']); ?>
</td>
</tr>
<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('backup_temp'); ?>
</td>
<td class="eTableLine0 eContent1">
<?= $this->config->vars['backup_temp'] == '' ? $this->get_translation('backup_systempfolder') : $this->config->vars['backup_temp'] ?>
</td>
</tr>
<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('backup_nextdate'); ?>
</td>
<td class="eTableLine1 eContent1">
<?php if ( $this->config->vars['backup_nextdate'] == 0 ) : ?>
--
<?php else : ?>
<?=date_displayShortDayDate($this->config->vars['backup_nextdate']);?>
<?php endif; ?>
</td>
</tr>

<tr>
  <td class="" colspan="3">
&nbsp;
</td>
</tr>

<tr>
<td class="" colspan="2">
<table cellspacing="0">
<tr><td style="padding:2px 8px;">
<?=$this->theme->get_button($this->get_translation('backup_modify'), $camyks->get_adminLink($this->name, array('mode'=>'edit_backupconfig')));?>
</td><td style="padding:2px 8px;">
<?=$this->theme->get_button($this->get_translation('backup_newbackup'), $camyks->get_adminLink($this->name, array('mode'=>'edit_newbackupfile')));?>
</td>
</tr>
</table>
</td>
</tr>
</table>

<div style="clear:both">
&nbsp;
</div>

<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
<tr>
<td class="eTitle3" colspan="6">
<?=$this->get_translation('backup_files');?>
</td>
</tr>

<?php if ( count ( $this->backupfiles ) > 0 ) : ?>
<tr>
<td class="eTableHeader">
&nbsp;
</td>
<td class="eTableHeader">
<?=$camyks->get_translation('date'); ?>
</td>
<td class="eTableHeader">
<?=$camyks->get_translation('type'); ?>
</td>
<td class="eTableHeader">
<?=$this->get_translation('backup_size'); ?>
</td>
<td class="eTableHeader" style="width:12px;">
&nbsp;
</td>
<td class="eTableHeader" style="width:12px;">
&nbsp;
</td>
</tr>
<?php $alt=0; ?>
<?php foreach ( $this->backupfiles as $backupfile ) : ?>
<tr>
<td class="eTableLine<?=$alt?> eContent1">
&nbsp;
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=date_displayShortDayDateHour($backupfile->vars['ndate']);?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$this->get_translation('backup_type_'.$backupfile->vars['type'])?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$backupfile->get_fileSize()?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<a href="<?=$this->get_varFileUrl('backups/'.$backupfile->vars['name'])?>">
<img src="<?=$file?>" border="0"
alt="<?=$this->get_translation('backup_download');?>" 
title="<?=$this->get_translation('backup_download');?>"
onmouseover="this.src='<?=$file_?>';" onmouseout="this.src='<?=$file?>';" />
</a>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<a href="javascript:admin_securitytools_deleteBackUp(<?=$backupfile->id;?>);">
<img src="<?=$del?>" border="0"
alt="<?=$this->get_translation('backup_delete');?>" 
title="<?=$this->get_translation('backup_delete');?>"
onmouseover="this.src='<?=$del_?>';" onmouseout="this.src='<?=$del?>';" />
</a>
</tr>
<?php $alt=abs($alt-1); ?>
<?php endforeach; ?>
<?php else : ?>
<tr>
<td class="eTableline0 eContent1" colspan="2">
<?=$this->get_translation('backup_nofile');?>
</td>
</tr>
<?php endif; ?>
</table>
</div>
<?php endif; ?>


<?php if ( $this->help ) : ?>
<div id="itemhelp" style="display:none;" class="adminContentPanel">
<?=$this->display_help();?>
</div>
<?php endif; ?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>
