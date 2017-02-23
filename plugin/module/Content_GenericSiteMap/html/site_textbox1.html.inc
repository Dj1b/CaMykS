<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jul 2008
 * Last Modif Date	: Jul 2008
 *
 * Content_SimpleText Module site layout : text, title & box 1
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader();?> 
<?=$this->theme->get_boxTitleBar ($this->get_translation('site_title')); ?>
<?=$this->theme->get_boxContent1Header(); ?>
<?=$this->sitemap;?>
<?=$this->theme->get_boxContent1Footer(); ?>
<?=$this->theme->get_boxFooter(); ?>