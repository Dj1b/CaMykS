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
 * Content_SimpleText Module site layout : text, title & box 2
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader();?>
<?php if ( $this->textitem->vars['title'] != "" ) : ?> 
<?=$this->theme->get_boxTitleBar ( $this->textitem->vars['title'] ) ?>
<?php endif; ?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->textitem->vars['content']?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxFooter(); ?>