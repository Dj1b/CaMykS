<?php
/*
 * CaMykS Engine
 * Developed by		: Ideogram Design
 * Author						: JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version		: 1.0b
 * Object Version		: 1.0
 * Object Type	    : Plugin / Module Layout
 * Create Date	    : May 2011
 * Last Modif Date	: May 2011
 * 
 * Admin_amadeusEmailingManager Module Admin Layout : send emailing
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('style'=>'width:600px;', 'class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->adminTitle) ?>
<?=$this->theme->get_boxContent2Header()?>
<div class="adminContentPanel">

<div id="updatebox" style="height:450px; overflow:auto;">
<div id="updatecontentbox">


</div>
</div>

</div>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>
