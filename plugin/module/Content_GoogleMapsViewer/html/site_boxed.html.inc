<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jul 2008
 * Last Modif Date	: Jul 2008
 * 
 * Content_GoogleMapsViewer Module Site Layout : site boxed layout
 */
?>
<?=$this->theme->get_boxHeader()?>
<?php if ( $this->mapItem->vars['title']!='') : ?>
<?=$this->theme->get_boxTitlebar($this->mapItem->vars['title'])?>
<?php endif; ?>
<?=$this->theme->get_boxContent1Header();?>
<div>
<?=nl2br($this->mapItem->vars['description'])?>
</div>
<?=$this->load_file('html/_site_map.html.inc');?>
<?=$this->theme->get_boxContent1Footer();?>
<?=$this->theme->get_boxFooter();?>