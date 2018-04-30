<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date    : Dec 2014
 * Last Modif Date  : Dec 2014
 *
 * Admin_MonitoringUserAgentChecker Module Admin Layout : view record
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header();?>

<div id="itemProperties" style="display:<?=$this->tabBuilder->get_tabDisplay('Properties')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
  <td class="eTableLine0 eContent2" style="width:150px">
    <?=$this->get_translation('formitem_user_agent')?>
  </td>
  <td class="">
    <div style="width:620px; overflow:auto; padding:8px;">
      <?=$this->recordItem->get_adminValue();?>
    </div>
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
    <?= $this->get_translation('platform_type_' . $this->recordItem->vars['platform_type']); ?>
    <?php if ($this->uaInfos['platform_type'] != '' and $this->recordItem->vars['platform_type'] != $this->uaInfos['platform_type']) : ?>
    (<?=$this->get_translation('platform_type_' . $this->uaInfos['platform_type']);?> *)
    <?php endif; ?>
</td>
</tr>

<?php
switch($this->recordItem->vars['platform_type']) {
    case 'bot': $this->load_file('html/admin_view_user_agent_bot_details.html.inc'); break;
    case 'tool': $this->load_file('html/admin_view_user_agent_tool_details.html.inc'); break;
    case 'fake': $this->load_file('html/admin_view_user_agent_fake_details.html.inc'); break;
    case 'hack': $this->load_file('html/admin_view_user_agent_hack_details.html.inc'); break;
    default: $this->load_file('html/admin_view_user_agent_generic_details.html.inc'); break;
}
?>

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

<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter();?>
