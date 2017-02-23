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
 * Content_SimpleText Module site layout : without box
*/
?>
<?php if ( $this->textitem->vars['title'] != "" ) : ?> 
<h1 class="title1">
<?= $this->textitem->vars['title']  ?>
</h1>
<?php endif; ?>
<div class="content1">
<?=$this->textitem->vars['content']?>
</div>