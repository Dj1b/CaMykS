<?php
/**
 * @brief Admin_MonitoringUserAgentChecker Module admin view user agent layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_MonitoringUserAgentChecker/html/admin_view_user_agent.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2014
 * @date Modification: Nov 2018
 * @copyright 2014 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>

<div id="itemProperties" style="display:<?= $this->tabBuilder->get_tabDisplay('Properties'); ?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%; table-layout: fixed;">

<tr>
  <td class="eTableLine0 eContent2" style="width:150px">
    <?= $this->get_translation('formitem_user_agent'); ?>
  </td>
  <td class="">
    <div style="overflow:auto; padding:8px; max-width:100%;">
      <?= $this->recordItem->get_adminValue(); ?>
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
    <?= $this->get_translation('formtitle_details'); ?>
  </td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?= $this->get_translation('formitem_platform_type'); ?>
</td>
<td class="eTableLine0 eContent1">
    <?= $this->get_translation('platform_type_' . $this->recordItem->vars['platform_type']); ?>
    <?php if ($this->uaInfos['platform_type'] != '' and $this->recordItem->vars['platform_type'] != $this->uaInfos['platform_type']) : ?>
    (<?= $this->get_translation('platform_type_' . $this->uaInfos['platform_type']); ?> *)
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
    <?= $this->get_translation('formtitle_infos'); ?>
  </td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?= $this->get_translation('formitem_nvisit'); ?>
</td>
<td class="eTableLine0 eContent1">
<?= $this->recordItem->vars['nvisit']; ?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?= $this->get_translation('formitem_fvisit'); ?>
</td>
<td class="eTableLine1 eContent1">
<?= date_displayNumericDateHour($this->recordItem->vars['fvisit']); ?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?= $this->get_translation('formitem_lvisit'); ?>
</td>
<td class="eTableLine0 eContent1">
<?= date_displayNumericDateHour($this->recordItem->vars['lvisit']); ?>
</td>
</tr>

</table>
</div>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
