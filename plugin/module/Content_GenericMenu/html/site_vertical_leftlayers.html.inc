<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Dec 2007
 * Last Modif Date	: Dec 2007
 *
 * Content_GenericMenu Module site layout : vertical / left layers layout
 */
global $camyks;
?>
<div class="cgmMain">
<?php foreach ( $this->root->children as $p ) : ?>
<?php $page = $this->pages[$p]; ?>
<?php if ( (!isset($page->metas['menu']) or $page->metas['menu']['content'] != 'hidden') and $page->active==1 ) : ?>
<a class="cgmItem" href="<?=$page->get_siteLink()?>"
<?php if ( count($page->children)>0 ) : ?>
 id="cgm<?=$this->mindex?>_<?=$page->name?>Button"
 onmouseover="globalCMenu.select('cgm<?=$this->mindex?>_<?=$page->name?>Menu');"
 onmouseout="globalCMenu.unselect('cgm<?=$this->mindex?>_<?=$page->name?>Menu');"
<?php endif; ?>
><?=$page->shorttitle!=''?$page->shorttitle:($page->title != ''?$page->title:$page->name)?>
</a>
<?php endif; ?>
<?php endforeach; ?>
</div>
<?php foreach ( $this->layeredMenu as $n => $m ) : ?>
<?=$this->theme->get_layeredMenu($n, 'globalCMenu', $m); ?>
<?php endforeach; ?>
