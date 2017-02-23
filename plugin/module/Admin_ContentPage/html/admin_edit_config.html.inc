<?php
/*
 * CaMykS Engine
 * Developed by		: Ideogram Design
 * Author			: JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Dec 2014
 * Last Modif Date	: Dec 2014
 * 
 * Admin_ContentPage Module Admin Layout : edit_config
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:800px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header( )?>

<?=$this->editform->display_header();?>
<?=$this->editform->display_hiddens();?>

<div id="itemConfiguration" style="display:<?=$this->tabBuilder->get_tabDisplay('Configuration');?>" class="adminContentPanel">
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