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
 * Admin_GenericPetitionManager Module Admin Layout : list signature
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle) ?>
<?=$this->theme->get_boxContent1Header( )?>
<?=$this->signList->display('head');?>
<?=$this->theme->get_boxContent1Footer( )?>
<?=$this->theme->get_boxContent2Header( )?>
<div class="adminContentPanel">
<?=$this->signList->display('list');?>
</div>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>
