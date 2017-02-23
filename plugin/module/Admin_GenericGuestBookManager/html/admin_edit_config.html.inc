<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 * 
 * Admin_GenericGuestBookManager Module Admin Layout : edit_config
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxContent2Header( )?>
<?=$this->configform->display_header(); ?>
<?=$this->configform->display_hiddens(); ?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_messages');?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2" style="width:150px;">
    <?=$this->get_translation('formitem_validation')?>
  </td>
  <td class="eTableLine0 eContent1">
  <?=$this->configform->display_selectInput(array('name'=>'message_validation', 'values'=>$this->config->get_messageValidationList()));?>
  </td>
</tr>

<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_notifications');?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$camyks->get_translation('formitem_status')?>
  </td>
  <td class="eTableLine0 eContent1">
  <?=$this->configform->display_selectInput(array('name'=>'notification_status', 'values'=>$this->config->get_notificationStatusList()));?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('formitem_sender')?>
  </td>
  <td class="eTableLine1 eContent1">
  <?=$this->configform->display_textInput('notification_sender');?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_recipients')?>
  </td>
  <td>
  
  <?php $col = 0; ?>
  <?php $cnt = 0; ?>
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
  <?php foreach ($this->userList as $admin) : ?>
  <?php if ($col == 0) : ?>
  <tr>
  <?php endif; ?>
  <td class="eTableLine0 eContent1">
  <input type="checkbox" id="admin<?=$cnt;?>" name="notification_recipients_<?=$cnt;?>" value="<?=$admin->login?>" <?=in_array($admin->login, $this->config->vars['notification_recipients'])?' checked="checked"':'' ?> />
  <label for="admin<?=$cnt;?>"><?=$admin->get_nameDisplay();?></label>
  </td>
  <?php $cnt++; ?>
  <?php $col++; ?>
  <?php if ($col == 2) : ?>
  </tr>
  <?php $col = 0; ?>
  <?php endif; ?>
  <?php endforeach; ?>
  <?php if ($col == 1) : ?>
  <td class="eTableLine0 eContent1">
  &nbsp;
  </td>
  </tr>
  <?php endif; ?>
  </table>
  </td>
</tr>

<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_statistics');?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$camyks->get_translation('formitem_status')?>
  </td>
  <td class="eTableLine0 eContent1">
  <?=$this->configform->display_selectInput(array('name'=>'statistic_status', 'values'=>$this->config->get_statisticStatusList()));?>
  </td>
</tr>


</table>
</div>

<?=$this->configform->display_footer(); ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>