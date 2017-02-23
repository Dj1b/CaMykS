<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: May 2008
 * Last Modif Date	: Apr 2009
 * 
 * Admin_GenericDownloadManager Module Admin Layout : edit_config
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
  <td class="eTableLine0 eContent2" style="width:200px;">
<?=$this->get_translation('config_enablestats');?>
  </td>
<td class="eTableLine0 eContent1">
  <?php if (isset($camyks->modules['Admin_Statistics'])) : ?>
  <?=$this->configform->display_booleanSelectInput('main_stats');?>
  <?php else : ?>
  <input type="hidden" name="main_stats" value="0" />
  <?=$this->configform->display_booleanSelectInput(array('name'=>'main_stats', 'disabled'=>'disabled', 'default'=>0));?>
  <?php endif; ?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('config_maxfilesize');?>
  </td>
  <td class="eTableLine1 eContent1">
  <?=$this->configform->display_textInput(array('name'=>'file_size', 'maxlength'=>6, 'class'=>'vsinputs'));?> M<?=language_getFileUnit()?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('config_linkmode');?>
  </td>
  <td class="eTableLine0 eContent1">
  <?=$this->configform->display_selectInput(array('name'=>'link_mode', 'values'=>$this->get_configLinkModeList()));?>
  </td>
</tr>

</table>
</div>
<?=$this->configform->display_footer(); ?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>