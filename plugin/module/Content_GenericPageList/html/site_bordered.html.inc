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
 * Content_GenericPageList Module site layout : bordered
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:100%;');?>
<?php if ( $this->plitem->vars['title'] != '' ) : ?>
<?=$this->theme->get_boxTitleBar( $this->plitem->vars['title'] ); ?>
<?php endif; ?>
<?=$this->theme->get_boxContent1Header('padding:20px;'); ?>
<table cellspacing="0">
<?php foreach ( $this->plitem->vars['pages'] as $p ) : ?>
<?php $page = $this->pages[$p]; ?>
<tr>
<td style="padding:4px 0px;">
<a class="link1" href="<?=$page->get_siteLink()?>">
<?=$page->title?>
</a>
</td>
</tr>
<?php endforeach; ?>
</table>
<?=$this->theme->get_boxContent1Footer();?>
<?=$this->theme->get_boxFooter();?>