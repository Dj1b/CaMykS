<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date    : Oct 2007
 * Last Modif Date	: Mar 2018
 * 
 * Admin_SecurityTools Module Admin Layout : edit new backup file
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->title.' : '.$this->get_translation('backup_newbackup'));?>
<?=$this->theme->get_boxContent2Header();?>
<?=$this->form->display_header();?>
<?=$this->form->display_hiddens();?>
<div class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2">
	    <?=$this->get_translation('backup_compression'); ?>
      </td>
      <td class="eTableLine0 eContent1">
        <?=$this->form->display_selectInput(array('name'=>'backup_compression', 'values'=>$this->backup_compressions, 'default'=>$this->config->vars['backup_compression']));?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	    <?=$this->get_translation('backup_type'); ?>
      </td>
      <td class="eTableLine1 eContent1">
        <?=$this->form->display_selectInput(array('name'=>'backup_type', 'values'=>$this->backup_types, 'default'=>$this->config->vars['backup_type']));?>
      </td>
    </tr>
  </table>
</div>
<?=$this->form->display_footer(); ?>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter();?>