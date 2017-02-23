<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Jan 2012
 * Last Modif Date	: Jan 2012
 * 
 * Admin_GenericEmailingManager Module Admin Layout : edit_config
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('style'=>'width:600px;margin:0 auto;', 'class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header( )?>

<?=$this->editform->display_header();?>
<?=$this->editform->display_hiddens();?>

<div id="itemmanager" style="display:<?=$this->tabBuilder->get_tabDisplay('manager');?>" class="adminContentPanel">
<?php $this->load_file('html/configuration/edit.html.inc');?>
</div>

<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:<?=$this->tabBuilder->get_tabDisplay('help')?>;" class="adminContentPanel">
<?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?=$this->editform->display_footer();?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>