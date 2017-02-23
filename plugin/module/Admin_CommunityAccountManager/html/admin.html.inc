<?php
/*
 * CaMykS Engine
 * Developed by     : Ideogram Design
 * Author           : JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version	  : 1.0b
 * Object Version	  : 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date    : Mar 2010
 * Last Modif Date  : Mar 2010
 * 
 * Admin_iqsimAccountManager Module admin layout : main
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title) ?>
<?=$this->theme->get_boxContent1Header('height:20px;')?>
<?=$this->listObject->display('head');?>
<?=$this->theme->get_boxContent1Footer(); ?>
<?=$this->theme->get_boxContent2Header()?>
<div  class="adminContentPanel">
<?=$this->listObject->display('list');?>
</div>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>
