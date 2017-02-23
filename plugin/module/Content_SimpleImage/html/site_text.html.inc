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
 * Content_SimpleImage Module site layout : without box
 */
global $camyks;
?>
<?php if ( $this->imageitem->vars['title'] != "" ) : ?> 
<h1 class="title1">
<?= $this->imageitem->vars['title']  ?>
</h1>
<?php endif; ?>
<?php if ( $this->imageitem->vars['image'] != "" ) : ?> 
<div class="content1">
<img src="<?= $this->imageitem->vars['image'] ?>" alt="" border="0" />
</div>
<?php endif; ?>
<div class="content1">
<?=nl2br($this->imageitem->vars['description'])?>
</div>