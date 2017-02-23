<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Apr 2009
 * Last Modif Date	: Apr 2009
 * 
 * Admin_GenericDownloadManager Module Admin Layout : main
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title) ?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs,
				$this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header( )?>
<div id="itemdocuments" style="display:<?=$this->tabBuilder->get_tabDisplay('documents')?>;" class="adminContentPanel">

<?=$this->listDocument->display('head');?>

<?=$this->listDocument->display('list');?>

</div>

<?php if( $this->check_right(2) === true) : ?>
<div id="itemcategories" style="display:<?=$this->tabBuilder->get_tabDisplay('categories')?>;" class="adminContentPanel">

<?=$this->listCategory->display('head');?>

<?=$this->listCategory->display('list');?>

</div>
<?php endif; ?>



<?php if ( $this->check_right(1) === true ) : ?>
<div id="itemconfiguration" style="display:<?=$this->tabBuilder->get_tabDisplay('configuration')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%";>
<tr>
  <td class="eTableLine0 eContent2" style="width:200px;">
    <?=$this->get_translation('config_enablestats');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$camyks->get_translation($this->config->vars['main_stats']==1?'yes':'no')?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('config_maxfilesize');?>
  </td>
  <td class="eTableLine1 eContent1">
  <?=$this->config->vars['file_size']?> M<?=language_getFileUnit();?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('config_linkmode');?>
  </td>
  <td class="eTableLine0 eContent1">
  <?=$this->configLinkModeList[$this->config->vars['link_mode']];?>
  </td>
</tr>

<tr>
  <td colspan="2">
  &nbsp;
</td>
</tr>
<tr>
<td colspan="2">
<?=$this->theme->get_button($this->get_translation('edit_config'),
			    $this->get_adminLink(array('mode'=>'edit_config')));?>
</td>
</tr>
</table>
</div>
<?php endif; ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>
