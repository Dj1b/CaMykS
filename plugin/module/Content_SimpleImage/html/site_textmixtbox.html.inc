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
 * Content_SimpleImage Module site layout : with mixt box
 */
global $camyks;
?>
<?=$this->theme->get_boxHeader();?>
<?php if ( $this->imageitem->vars['title'] != "" ) : ?> 
<?=$this->theme->get_boxTitleBar ( $this->imageitem->vars['title'] ) ?>
<?php endif; ?>
<?=$this->theme->get_boxContent2Header(); ?>
<?php if ( $this->imageitem->vars['image'] != "" ) : ?> 
<img src="<?= $this->imageitem->vars['image'] ?>" alt="" border="0" />
<?php endif; ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxContent1Header(); ?>
<?=nl2br($this->imageitem->vars['description'])?>
<?=$this->theme->get_boxContent1Footer(); ?>
<?=$this->theme->get_boxFooter(); ?>