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
 * Content_GenericMenu Module site layout : vertical, in column
*/
global $camyks;
?>

<div class="cgmMain">
<?php foreach ( $this->root->children as $p ) : ?>
<?php $page = $this->pages[$p]; ?>
<?php if ( (!isset($page->metas['menu']) or $page->metas['menu']['content'] != 'hidden') and $page->active==1 ) : ?>
<a class="cgmItem" href="<?=$page->get_siteLink()?>">
<?=$page->shorttitle!=''?$page->shorttitle:($page->title != ''?$page->title:$page->name)?>
</a>


<?php foreach ( $page->children as $p ) : ?>
<?php $pagel2 = $this->pages[$p]; ?>
<?php if ( !isset($pagel2->metas['menu']) or $pagel2->metas['menu']['content'] != 'hidden' ) : ?>
<a class="cgmItemL2" href="<?=$pagel2->get_siteLink()?>">
<?=$pagel2->shorttitle!=''?$pagel2->shorttitle:($pagel2->title != ''?$pagel2->title:$pagel2->name)?>
</a>

<?php foreach ( $pagel2->children as $p ) : ?>
<?php $pagel3 = $this->pages[$p]; ?>
<?php if ( !isset($pagel2->metas['menu']) or $pagel2->metas['menu']['content'] != 'hidden' ) : ?>
<tr>
<a class="cgmItemL3" href="<?=$pagel3->get_siteLink()?>">
<?=$pagel3->shorttitle!=''?$pagel3->shorttitle:($pagel3->title != ''?$pagel3->title:$pagel3->name)?>
</a>

<?php endif; ?>
<?php endforeach; ?>

<?php endif; ?>
<?php endforeach; ?>

<?php endif; ?>
<?php endforeach; ?>
</div>
