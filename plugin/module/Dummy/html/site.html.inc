<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Dec 2006
 * Last Modif Date	: Dec 2006
 *
 * Dummy Module site layout
 * A simple dummy text is display in a current theme box
 */
global $camyks;

?>
<div style="width:300px; padding-top:30px;">
<?=$this->theme->get_boxHeader('width:300;height:200px;');?>
<?=$this->theme->get_boxTitleBar ( $this->get_translation('site_title') );?>
<?=$this->theme->get_boxContent2Header(); ?>

<?=$this->get_translation('site_text')?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxFooter(); ?>

</div>