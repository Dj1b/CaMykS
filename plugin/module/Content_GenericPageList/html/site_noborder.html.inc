<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Nov 2007
 * Last Modif Date	: Nov 2007
 *
 * Content_GenericPageList Module site layout : no border
*/
global $camyks;
?>
<h1 class="title1">
<?=$this->plitem->vars['title']?>
</h1>
<?php foreach ( $this->plitem->vars['pages'] as $p ) : ?>
<?php $page = $this->pages[$p]; ?>
<div style="padding:4px 0px;">
<a class="link1" href="<?=$page->get_siteLink()?>">
<?=$page->title?>
</a>
</div>
<?php endforeach; ?>