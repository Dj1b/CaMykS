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
 * Content_GoogleMapsViewer Module Site Layout : site classic layout
 */
?>
<?php if ($this->mapItem->vars['title']!='') : ?>
<div class="title1">
<?=$this->mapItem->vars['title']?>
</div>
<?php endif; ?>
<div>
<?=nl2br($this->mapItem->vars['description'])?>
</div>
<?=$this->load_file('html/_site_map.html.inc');?>