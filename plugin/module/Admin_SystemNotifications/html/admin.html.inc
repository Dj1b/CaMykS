<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Jul 2017
 * Last Modif Date  : Jul 2017
 * 
 * Admin_SystemNotifications Module Admin Layout : main
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->title);?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header();?>

<div id="itemFollowUp" style="display:<?=$this->tabBuilder->get_tabDisplay('FollowUp')?>;" class="adminContentPanel">

<?php if ($this->config->vars['module_mode'] == 1) : ?>

<div class="eContent2" style="padding:6px 10px;">
  <?=$this->get_translation('lastcheckdate', date_displayLongDateHour($this->config->vars['running_lastCheck'])); ?>
</div>

<?php endif; ?>


<?php foreach ($this->followUpList as $followUp) : ?>

<?php if ($this->config->vars['module_mode'] == 1) : ?>

<div style="display:inline-block; width:46%; min-width:320px; box-shadow: 0 0 3px 1px rgba(0, 0, 0, 0.25); margin:10px; vertical-align:top;">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%; border: solid 1px white;">

<tr>
  <td colspan="3" class="eTableSubHeader">
    <?=string_getShortenedSentence($followUp['title'], 56); ?>
  </td>
</tr>
<?php else : ?>

<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

<?php endif; ?>

<?php if ($followUp['error'] != '') : ?>

<tr>
  <td colspan="3" class="eTableLine0 error" style="padding-left:<?=(10+$this->config->vars['module_mode']*20);?>px">
    <?=$followUp['error']; ?>
  </td>
</tr>

<?php elseif (count($followUp['modules']) == 0) : ?>

<tr>
  <td colspan="3" class="eTableLine0 eContent2" style="padding-left:<?=(10+$this->config->vars['module_mode']*20);?>px">
    <?=$this->get_translation('nonotifications'); ?>
  </td>
</tr>

<?php else : ?>

<?php foreach ($followUp['modules'] as $module) : ?>

<tr>
  <td colspan="3" class="eTableHeader" style="padding-left:<?=(max(10, $this->config->vars['module_mode']*20));?>px">
    <?=$module['title']; ?>
  </td>
</tr>

<?php $alt = 0; ?>
<?php foreach ($module['items'] as $item) : ?>

<tr>
  <td class="eTableLine<?=$alt;?>" style="padding-left:<?=((1+$this->config->vars['module_mode'])*20);?>px">
    <?=$item['title']; ?>
  </td>
  <td class="eTableLine<?=$alt;?>" style="text-align:right; width:40px;">
    <?=$item['cnt']; ?>
  </td>
  <td class="eTableLine<?=$alt;?>" style="width:20px; font-size:0;">
    <?php if ($item['priority'] == 0) : ?>
      <img src="<?=$this->get_fileURL('img/priority/low.png'); ?>" alt="<?=$this->get_translation('itempriority_low');?>" title="<?=$this->get_translation('itempriority_low');?>" />
    <?php elseif ($item['priority'] == 1) : ?>
      <img src="<?=$this->get_fileURL('img/priority/medium.png'); ?>" alt="<?=$this->get_translation('itempriority_medium');?>" title="<?=$this->get_translation('itempriority_medium');?>" />
    <?php elseif ($item['priority'] == 2) : ?>
      <img src="<?=$this->get_fileURL('img/priority/high.png'); ?>" alt="<?=$this->get_translation('itempriority_high');?>" title="<?=$this->get_translation('itempriority_high');?>" />
    <?php endif; ?>
  </td>
</tr>

<?php $alt = abs($alt-1); ?>
<?php endforeach; ?>

<tr>
  <td colspan="3">
    &nbsp;
  </td>
</tr>

<?php endforeach; ?>
<?php endif; ?>

<?php if ($this->config->vars['module_mode'] == 1) : ?>
  </table>
  </div>
<?php else : ?>
  </table>
<?php endif; ?>




<?php endforeach; ?>


</div>

<div id="itemConfiguration" style="display:<?=$this->tabBuilder->get_tabDisplay('Configuration')?>;" class="adminContentPanel">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_module'); ?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2" style="width:160px;">
    <?=$this->get_translation('formitem_mode');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->moduleModeList[$this->config->vars['module_mode']]; ?>
  </td>
</tr>

<?php if ($this->config->vars['module_mode'] == 1) : ?>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('formitem_status');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->config->vars['module_checkDelay'].$this->get_translation('unit_minutes'); ?>
  </td>
</tr>

<?php endif; ?>

<tr>
  <td  class="eTableLine0" colspan="2">
    &nbsp;
  </td>
</tr>
<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_access'); ?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_status');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->accessStatusList[$this->config->vars['access_status']]; ?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('formitem_authentication');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->accessAuthenticationList[$this->config->vars['access_authentication']]; ?>
  </td>
</tr>


<?php if ($this->config->vars['access_authentication'] == 1) : ?>

  <tr>
    <td class="eTableLine0 eContent2">
        <?=$this->get_translation('formitem_login');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->adminList[$this->config->vars['access_authLogin']]; ?>
    </td>
  </tr>
  
<?php endif; ?>

<?php if ($this->config->vars['access_authentication'] == 2) : ?>

  <tr>
    <td class="eTableLine0 eContent2">
        <?=$this->get_translation('formitem_ipaddress');?>
    </td>
    <td class="eTableLine0 eContent1">
        <?php if ($this->config->vars['access_authIP'] != '') : ?>
          <?=$this->config->vars['access_authIP']; ?>
        <?php else : ?>
          <?=$this->get_translation('addressip_sameserver'); ?>
        <?php endif; ?>
    </td>
  </tr>
  
<?php endif; ?>

<?php if ($this->check_right(1)) : ?>
  <tr>
    <td colspan="2">
      &nbsp;
    </tr>
  </tr>

  <tr>
    <td colspan="2">
      <?=$this->theme->get_button(array(
        'title' => $this->get_translation('edit_configuration'), 
        'url'   => $this->get_adminLink(array('mode'=>'edit_config')),
        )); ?>
    </td>
  </tr>
<?php endif; ?>
</table>
</div>

<?php if ($this->check_right(1) == true and $this->config->vars['module_mode'] == 1) : ?>
<div id="itemWebsites" style="display:<?=$this->tabBuilder->get_tabDisplay('Websites')?>;" class="adminContentPanel">

<?=$this->websiteList->display('head');?>
<?=$this->websiteList->display('list');?>

</div>
<?php endif; ?>

<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:<?=$this->tabBuilder->get_tabDisplay('help')?>;" class="adminContentPanel">
<?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?=$this->theme->get_boxContent2Footer( )?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>
