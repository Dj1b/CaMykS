<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Oct 2005
 * Last Modif Date	: Oct 2005
 * 
 *Dummy Module admin layout
 */
?>

<div style="height:200px; width:300px;">
<?=$this->theme->get_boxHeader();?>
<?=$this->theme->get_boxTitleBar ( $this->name ) ?>
<?=$this->theme->get_boxContent1Header(); ?>
<?=$this->get_translation('admin_text')?>
<?=$this->theme->get_boxContent1Header(); ?>
<?=$this->theme->get_boxFooter(); ?>
</div>