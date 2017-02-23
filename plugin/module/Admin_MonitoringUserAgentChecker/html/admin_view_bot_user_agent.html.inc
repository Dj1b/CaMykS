<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date   	: Dec 2014
 * Last Modif Date	: Dec 2014
 * History :
 * * 12-19-14 : Initial files
 * 
 * Admin_MonitoringUserAgentChecker Module Admin Layout : view bot record
*/
global $camyks;

/* check user agent */
if($this->uaInfos == false)
	$this->uaInfos =  array();
?>
<?=$this->theme->get_boxHeader('width:610px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs,
				$this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header( )?>
<?=$this->editform1->display_header(); ?>
<?=$this->editform1->display_hiddens(); ?>
<?=$this->editform1->display_footer(); ?>

<?=$this->editform2->display_header(); ?>
<?=$this->editform2->display_hiddens(); ?>
<?=$this->editform2->display_footer(); ?>
<div id="itemproperties" style="display:<?=$this->tabBuilder->get_tabDisplay('properties')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
<td class="eTableLine0 eContent2" style="width:150px">
<?=$this->get_translation('formitem_user_agent')?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->recordItem->vars['user_agent']; ?>
</td>
</tr>

<tr>
  <td class="eTableLine0" colspan="2">
    &nbsp;
  </td>
</tr>

<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_details'); ?>
  </td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_platform_type')?>
</td>
<td class="eTableLine0 eContent1">
<?php
if(array_key_exists('platform_type', $this->uaInfos)){
	$new_platform_type = $this->uaInfos['platform_type'];
}else 
	$new_platform_type = '';
	
if($new_platform_type != '' && $this->recordItem->vars['platform_type'] != $new_platform_type)
	echo $this->get_translation('platform_type_' . $this->recordItem->vars['platform_type']) . ' (' . 
		$this->get_translation('platform_type_' . $new_platform_type) . '*)';
else
	echo $this->get_translation('platform_type_' . $this->recordItem->vars['platform_type']);

 ?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_platform_format')?>
</td>
<td class="eTableLine1 eContent1">
<?= array_key_exists('platform_format', $this->uaInfos) ? $this->recordPlatformFormats[$this->uaInfos['platform_format']] : '';?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_bot_title')?>
</td>
<td class="eTableLine0 eContent1">
<?= array_key_exists('bot_title', $this->uaInfos) ? $this->uaInfos['bot_title'] : '';?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_bot_url')?>
</td>
<td class="eTableLine1 eContent1">
<?= array_key_exists('bot_url', $this->uaInfos) ? $this->uaInfos['bot_url'] : '';?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_engine_title')?>
</td>
<td class="eTableLine0 eContent1">
<?= array_key_exists('engine_title', $this->uaInfos) ? $this->uaInfos['engine_title'] : '';?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_engine_url')?>
</td>
<td class="eTableLine1 eContent1">
<?= array_key_exists('engine_url', $this->uaInfos) ? $this->uaInfos['engine_url'] : '';?>
</td>
</tr>

<tr>
  <td class="eTableLine0" colspan="2">
    &nbsp;
  </td>
</tr>

<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_infos'); ?>
  </td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_nvisit')?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->recordItem->vars['nvisit']; ?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_fvisit')?>
</td>
<td class="eTableLine1 eContent1">
<?=date_displayNumericDateHour($this->recordItem->vars['fvisit']); ?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_lvisit')?>
</td>
<td class="eTableLine0 eContent1">
<?=date_displayNumericDateHour($this->recordItem->vars['lvisit']); ?>
</td>
</tr>

</table>
</div>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>