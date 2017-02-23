<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: May 2010
 * Last Modif Date	: May 2010
 * 
 * Content_GenericGlossaryViewer Module Site Layout : site nobox layout
 */
global $camyks;
$l = '';
?>
<?php if( $this->configItem->vars['pagemode'] == 0 ) : ?>
<?=$this->pageController->display();?>
<?php else : ?>
<div class="eTableLine1" style="text-align:center;">
<?php $first = true; ?>
<?php foreach($this->pages as $title => $link) : ?>
<?php if ($first) : ?>
<?php $first = false; ?>
<?php else : ?>
 - 
<?php endif; ?>
<a href="<?=$link?>" class="eLink1"><?=$title?></a>
<?php endforeach; ?>
</div>
<?php endif; ?>

<?=$this->configItem->vars['content'];?>

<?php foreach($this->wordList as $word) : ?>
<?php if (substr($word->vars['word'], 0, 1) != $l) : ?>
<?php $l = substr($word->vars['word'], 0, 1); ?>
<h1 class="eTitle1" style="font-size:40px">
<?=strtoupper($l); ?>
</h1>
<?php endif; ?>

<div style="padding-top:12px;">
<?php $w = $word->vars['word']; ?>
<a class="eTitle2" name="<?=$w;?>" href="<?=$this->get_pageLink(null, $w)?>">
<?=$w?>
</a>

<?php if( count($this->configItem->vars['categories_']) != 1 ) : ?>
<h3 class="eTitle3">
<?=$camyks->get_translation('formitem_category');?>
<?=$this->categoryList[$word->vars['category']];?>
</h3>
<?php endif; ?>

<div class="">
<?=$word->vars['description'];?>
</div>
</div>
<?php endforeach; ?>