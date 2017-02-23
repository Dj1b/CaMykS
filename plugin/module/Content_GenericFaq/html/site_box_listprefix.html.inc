<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Apr 2007
 * Last Modif Date	: Apr 2007
 *
 * Content_GenericFaq Module Site Layout : indexed list
 */
global $camyks;
?>
<?=$this->theme->get_boxHeader();?>
<?=$this->theme->get_boxTitleBar( $this->get_translation('site_title') );?>
<?=$this->theme->get_boxContent2Header('padding:8px;');?>
<table cellspacing="0" cellpadding="0" border="0" width="100%">
<?php foreach ( $this->faqitems as $n ) : ?>
<tr>
  <td class="title3" style="text-align:left;">
    <?=$this->get_translation('question', '');?><?=$n->vars['title']?>
  </td>
</tr>
<tr>
  <td class="content1" style="padding-left:16px;">
<?=nl2br($n->vars['content'])?>
   </td>
</tr>
<tr>
  <td>
&nbsp;
  </td>
</tr>
<?php endforeach; ?>
</table>
<?=$this->theme->get_boxContent2Footer(); ?>
<?php if ( $this->prevfaqs != '' or $this->nextfaqs != '' ) :?>
<?=$this->theme->get_boxButtonsBar( $this->buttons, false ); ?>
<?php endif; ?>
<?=$this->theme->get_boxFooter(); ?>