<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date   	: Jan 2018
 * Last Modif Date	: Jan 2018
 *
 * Admin_Site Module Admin Layout : view plugin configuration mode
 */
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule', 'style'=>'width:800px; margin:0 auto;'));?>
<?=$this->theme->get_boxTitleBar($this->get_translation('formtitle_pluginconfig', $this->plugin->title));?>

<?=$this->plugin->display_configDisplay(); ?>

<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter();?>