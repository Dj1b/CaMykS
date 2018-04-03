<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date    : Sep 2010
 * Last Modif Date  : Mar 2018
 * 
 * Admin_GenericGuestBookManager Module Admin Layout : edit_config
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxContent2Header();?>
<?=$this->configform->display_header();?>
<?=$this->configform->display_hiddens();?>
<div class="adminContentPanel">
    <?php $this->load_file('html/configuration/edit.html.inc'); ?>
</div>
<?=$this->configform->display_footer();?>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter();?>