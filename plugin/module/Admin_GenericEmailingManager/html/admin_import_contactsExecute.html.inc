<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Jan 2013
 * Last Modif Date	: Jan 2013
 * 
 * Admin_GenericEmailingManager Module Admin Layout : import_contactsExecute
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxContent2Header();?>
<div id="itemproperties" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<div class="adminContentPanel">

<div id="updatebox" style="height:450px; overflow:auto;">
<div id="updatecontentbox">


</div>
</div>

</div>
</table>
</div>

<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:<?=$this->tabBuilder->get_tabDisplay('help')?>;" class="adminContentPanel">
<?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>