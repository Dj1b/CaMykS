<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jul 2007
 * Last Modif Date	: Jul 2007
 * 
 * Content_GenericMenu Module site layout : horizontal menu with layer
*/
global $camyks;
?>
<table cellspacing="0" class="cgmMainHTable">
<tr>
<?php foreach ( $this->root->children as $p ) : ?>
<?php $page = $this->pages[$p]; ?>
<?php if ( (!isset($page->metas['menu']) or $page->metas['menu']['content'] != 'hidden') and $page->active==1 ) : ?>
<td  class="cgmHItem"
<?php if ( count($page->children)>0 ) : ?>
 id="cgm<?=$this->mindex?>_<?=$page->name?>Button"
 onmouseover="this.className='cgmHItemOver';globalCMenu.select('cgm<?=$this->mindex?>_<?=$page->name?>Menu');"
 onmouseout="this.className='cgmHItem';globalCMenu.unselect('cgm<?=$this->mindex?>_<?=$page->name?>Menu');">
<?php else : ?>
 onmouseover="this.className='cgmHItemOver';" onmouseout="this.className='cgmHItem';">
<?php endif; ?>
<a class="cgmHItem" href="<?=$page->get_siteLink()?>">
<?=$page->shorttitle!=''?$page->shorttitle:($page->title != ''?$page->title:$page->name)?>
</a>
</td>
<?php endif; ?>
<?php endforeach; ?>
</tr>
</table>

<?php foreach ( $this->layeredMenu as $n => $m ) : ?>

<?=$this->theme->get_layeredMenu($n, 'globalCMenu', $m); ?>

<?php endforeach; ?>