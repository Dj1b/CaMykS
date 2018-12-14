<?php
/**
 * @brief Admin_GenericEmailingManager Module view emailing layout
 * @details Plugin, Module Layout
 * @file plugin/module/Admin_GenericEmailingManager/html/admin_view_emailing.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2012
 * @date Modification: Dec 2018
 * @copyright 2012 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');
?>
<?= $this->theme->get_boxHeader(array('style'=>'width:600px;margin:0 auto;', 'class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itemproperties" style="display:<?= $this->tabBuilder->get_tabDisplay('properties'); ?>" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
        <?= $camyks->get_translation('formitem_status'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= $this->emailingStatusList[$this->emailingItem->vars['status']]; ?>
        <?php if ($this->check_right(4) and $this->emailingItem->vars['status'] > 0) : ?>
            [<a href="<?= $this->get_adminLink(array('mode'=>'reset_emailing', 'emailing_id'=>$this->emailingItem->id)); ?>">
            <?= $this->get_translation('reset_emailing'); ?>
            </a>]
        <?php endif; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_cdate'); ?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= date_displayLongDayDateHour($this->emailingItem->vars['cdate']); ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_contactstatus'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= $this->contactSourceList[$this->emailingItem->vars['contact_source']]; ?>
        <?php if ($this->emailingItem->vars['contact_source'] == 'internal:1') :?>
        / <?= $this->emailingItem->get_groupTitle(); ?>
        <?php endif; ?>
    </td>
</tr>

<tr>
  <td class="eTableHeader" colspan="2">
      <?= $this->get_translation('formtitle_emailcontent'); ?>
  </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $camyks->get_translation('formitem_title'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= $this->emailingItem->vars['email_title']; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_content'); ?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= $this->emailingItem->get_contentFileDescription(); ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_sender'); ?>
    </td>
    <td class="eTableLine0 eContent1" colspan="2">
      <?= $this->emailingItem->vars['sender_name']; ?>
      &lt;<?= $this->emailingItem->vars['sender_email']; ?>&gt;
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_replyto'); ?>
    </td>
    <td class="eTableLine1 eContent1" colspan="2">
      <?= $this->emailingItem->vars['replyto_name']; ?>
      &lt;<?= $this->emailingItem->vars['replyto_email']; ?>&gt;
    </td>
</tr>

<tr>
  <td class="eTableHeader" colspan="3">
      <?= $this->get_translation('formtitle_attachedimages'); ?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
      <?= $this->get_translation('formitem_images'); ?>
  </td>
  <td class="eTableLine0 eContent1">
      <?= $this->emailingItem->vars['valid_images']?> / <?= count($this->emailingItem->config->vars['content_images']); ?>
  </td>
</tr>

<?php $alt = 1; ?>
<?php foreach ($this->emailingItem->config->vars['content_images'] as $index => $file) : ?>
<tr>
    <td class="eTableLine<?= $alt?> eContent2">
        &nbsp;
    </td>
    <td class="eTableLine<?= $alt?> eContent1">
        <?= $file ?> &nbsp;
        <a href="<?= $this->emailingItem->get_imageFolderPath().'/'.$file?>" target="_blank" class="img">
            <img src="<?= $view?>" alt="" border="0"
                onmouseover="this.src='<?= $view_?>';"
                onmouseout="this.src='<?= $view?>';" />
            </a>
    </td>
</tr>
<?php $alt = abs($alt-1); ?>
<?php endforeach; ?>

</table>
</div>

<div id="itemsending" style="display:<?= $this->tabBuilder->get_tabDisplay('sending'); ?>" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<?php if ($this->emailingItem->vars['status'] == 0) : ?>
<tr>
  <td class="eTableLine0 eContent2" style="width:250px;">
      <?= $this->get_translation('formitem_approxemailtosend'); ?>
  </td>
  <td class="eTableLine0">
      <?= $this->contactCount; ?>
  </td>
</tr>

<?php if ($this->check_right(4) == true) : ?>
<tr>
    <td colspan="2">
        &nbsp;
    </td>
</tr>
<tr>
  <td colspan="2">
      <?= $this->theme->get_button(array('url'=>$this->get_adminLink(array('mode'=>'send_emailing', 'emailing_id'=>$this->emailingItem->id)), 'title'=>$this->get_translation('action_startsending'))); ?>
  </td>
</tr>

<?php endif; ?>
</table>

<?php elseif ($this->emailingItem->vars['status'] == 1 and $this->check_right(4) == true) : ?>

<tr>
  <td class="eTableLine0 eContent2" style="width:250px;">
      <?= $this->get_translation('formitem_approxemailtosend'); ?>
  </td>
  <td class="eTableLine0">
      <?= $this->contactCount; ?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
      <?= $this->get_translation('formitem_alreadysent'); ?>
  </td>
  <td class="eTableLine0">
      <?= $this->emailingItem->config->get_value('emailing_current', 0); ?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
      <?= $this->get_translation('formitem_remainingtosend'); ?>
  </td>
  <td class="eTableLine0">
      <?= $this->contactCount - $this->emailingItem->config->get_value('emailing_current', 0); ?>
  </td>
</tr>


<tr>
    <td colspan="2">
        &nbsp;
    </td>
</tr>
<tr>
  <td colspan="2">
      <?= $this->theme->get_button(array('url'=>$this->get_adminLink(array('mode'=>'send_emailing', 'emailing_id'=>$this->emailingItem->id)), 'title'=>$this->get_translation('action_continuesending'))); ?>
  </td>
</tr>

<?php elseif ($this->emailingItem->vars['status'] == 2) : ?>

<tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
        <?= $this->get_translation('formitem_sdate'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?php if ($this->emailingItem->vars['sdate'] > 3600) : ?>
            <?=date_displayLongDayDateHour($this->emailingItem->vars['sdate']); ?>
        <?php else : ?>
        --
        <?php endif; ?>

    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_edate'); ?>
    </td>
    <td class="eTableLine1 eContent1">
        <?php if ($this->emailingItem->vars['edate'] > 3600) : ?>
            <?= date_displayLongDayDateHour($this->emailingItem->vars['edate']); ?>
        <?php else : ?>
            --
        <?php endif; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_totalsent'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= $this->emailingStatisticsSummary['total_built']; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_totalsucceededsent'); ?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= $this->emailingStatisticsSummary['total_sent']; ?>
        <?php if ($this->emailingStatisticsSummary['total_built'] > 0) : ?>
            (<?= ((int)($this->emailingStatisticsSummary['total_sent']*10000.00 / $this->emailingStatisticsSummary['total_built']))/100; ?>%)
        <?php endif; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_totalopened'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= $this->emailingStatisticsSummary['total_opened']; ?>
        <?php if ($this->emailingStatisticsSummary['total_built'] > 0) : ?>
            (<?= ((int)($this->emailingStatisticsSummary['total_opened']*10000.00 / $this->emailingStatisticsSummary['total_built']))/100; ?>%)
        <?php endif; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_totalclicks'); ?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= $this->emailingStatisticsSummary['total_clicks']; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_unsubscribed'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= $this->emailingStatisticsSummary['total_unsubscribed']; ?>
        <?php if ($this->emailingStatisticsSummary['total_built'] > 0) : ?>
            (<?= ((int)($this->emailingStatisticsSummary['total_unsubscribed']*10000.00 / $this->emailingStatisticsSummary['total_built']))/100; ?>%)
        <?php endif; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_invalid'); ?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= $this->emailingStatisticsSummary['total_invalid']; ?>
        <?php if ($this->emailingStatisticsSummary['total_built'] > 0) : ?>
            (<?= ((int)($this->emailingStatisticsSummary['total_invalid']*10000.00 / $this->emailingStatisticsSummary['total_built']))/100; ?>%)
        <?php endif; ?>
    </td>
</tr>


<?php endif; ?>
</table>
</div>

<?php if ($this->emailingItem->vars['status'] == 2) : ?>
<div id="itememails" style="display:<?= $this->tabBuilder->get_tabDisplay('emails'); ?>;" class="adminContentPanel">
    <?= $this->emailList->display('head'); ?>
    <?= $this->emailList->display('list'); ?>
</div>
<?php endif; ?>

<?php if ($this->help != null) : ?>
<div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
    <?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
