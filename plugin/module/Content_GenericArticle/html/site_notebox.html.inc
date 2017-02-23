<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Sep 2007
 * Last Modif Date	: Sep 2007
 *
 * Content_GenericArticle Module site layout : notebox
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader()?>
<?php if ( $this->articleitem->vars['title'] != '' ) : ?>
<?=$this->theme->get_boxTitleBar($this->articleitem->vars['title']) ?>
<?php endif; ?>
<?=$this->theme->get_boxContent1Header()?>

<?php if ( $this->articleitem->vars['subtitle'] != '' ) : ?>
<h1 class="title2">
<?=$this->articleitem->vars['subtitle'] ?>
</h1>
<?php endif; ?>

<?php if ( $this->articleitem->vars['author'] != '' ) : ?>
<h2 class="title3">
<?=$this->get_translation('siteauthor', $this->articleAuthor['display']);?>
</h2>
<?php endif; ?>

<?php if ( $this->articleitem->vars['date_'] != '' ) : ?>
<p class="title3">
<?=date_displayDate($this->articleitem->vars['date_']) ?>
</p>
<?php endif; ?>

<?php if ( $this->articleitem->vars['header'] != '' ) : ?>
<p class="content2">
<?=nl2br($this->articleitem->vars['header']) ?>
</p>
<?php endif; ?>

<?php if ( file_exists( $this->articleitem->vars['content'] ) ) : ?>
<?php include $this->articleitem->vars['content']; ?>
<?php endif; ?>

<?=$this->theme->get_boxContent1Footer()?>

<?php if ( $this->articleitem->vars['note'] != '' ) : ?>
<?=$this->theme->get_boxContent2Header()?>
<p class="content3">
<?=nl2br($this->articleitem->vars['note']) ?>
</p>
<?=$this->theme->get_boxContent2Footer()?>
<?php endif; ?>

<?=$this->theme->get_boxFooter()?>