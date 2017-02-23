<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jul 2007
 * Last Modif Date	: Jul 2007
 *
 * Content_GenericGallery Module site layout : with box 2
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader();?>
<?=$this->theme->get_boxContent2Header(); ?>

<?php $this->gallery->display(); ?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxFooter(); ?>