<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date	: Jun 2007
 * Last Modif Date	: Jun 2007
 *
 * Admin_DocumentManager module admin layout
*/		
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('style'=>'width:700px; margin:0 auto;'));?>
<?=$this->theme->get_boxTitleBar( $this->title );?>
<?=$this->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">

<?php if ( isset ( $this->fileManager ) ) : ?>
<?php $this->fileManager->display(); ?>
<?php endif; ?>

</div>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>