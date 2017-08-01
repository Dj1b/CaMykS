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

$width = 160;

?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->title) ?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header( )?>

<?=$this->editForm->display_header(); ?>
<?=$this->editForm->display_hiddens(); ?>

<div id="itemConfiguration" style="display:<?=$this->tabBuilder->get_tabDisplay('Configuration')?>;" class="adminContentPanel">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

  <tr> 
    <td class="eTableHeader" colspan="2">
      <?=$this->get_translation('formtitle_module'); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine0 eContent2" style="width:<?=$width;?>px;">
      <?=$this->get_translation('formitem_mode');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->editForm->display_selectInput(array('name'=>'module_mode', 'values'=>$this->moduleModeList, 'onchange'=>'ce.onModuleModeChange();')); ?>
    </td>
  </tr>
  
  </table>

  <div id="moduleCheckDelay" style="display:<?=$this->config->vars['module_mode'] == 1?'block':'none';?>">
  <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine1 eContent2" style="width:<?=$width;?>px;">
        <?=$this->get_translation('formitem_delay');?>
      </td>
      <td class="eTableLine1 eContent1">
        <?=$this->editForm->display_textInput(array('name'=>'module_checkDelay', 'class'=>'vsinputs')); ?> <?=$this->get_translation('unit_minutes'); ?>
      </td>
    </tr>
  </table>
  </div>
  
  <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
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
    <td class="eTableLine0 eContent2" style="width:<?=$width;?>px;">
      <?=$this->get_translation('formitem_status');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->editForm->display_selectInput(array('name'=>'access_status', 'values'=>$this->accessStatusList)); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_authentication');?>
    </td>
    <td class="eTableLine1 eContent1">
      <?=$this->editForm->display_selectInput(array('name'=>'access_authentication', 'values'=>$this->accessAuthenticationList, 'onchange'=>'ce.onAuthenticationChange();')); ?>
    </td>
  </tr>

  </table>

  <div id="accessCredentials" style="display:<?=$this->config->vars['access_authentication'] == 1?'block':'none';?>">
  <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2" style="width:<?=$width;?>px;">
        <?=$this->get_translation('formitem_login');?>
      </td>
      <td class="eTableLine0 eContent1">
        <?=$this->editForm->display_selectInput(array('name'=>'access_authLogin', 'values'=>$this->adminList)); ?>
      </td>
    </tr>
  </table>
  </div>

  <div id="accessAddressIP" style="display:<?=$this->config->vars['access_authentication'] == 2?'block':'none';?>">
  <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2" style="width:<?=$width;?>px;">
        <?=$this->get_translation('formitem_ipaddress');?>
      </td>
      <td class="eTableLine0 eContent1">
        <?=$this->editForm->display_textInput(array('name'=>'access_authIP', 'placeholder'=>$this->get_translation('addressip_sameserver'))); ?>
      </td>
    </tr>
  </table>
  </div>
</div>

<?=$this->editForm->display_footer(); ?>

<?php if ( $this->help != null ) : ?>
  <div id="itemhelp" style="display:<?=$this->tabBuilder->get_tabDisplay('help')?>;" class="adminContentPanel">
    <?php $this->display_help(); ?>
  </div>
<?php endif; ?>

<?=$this->theme->get_boxContent2Footer( )?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>
