<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Mar 2007
 * Last Modif Date	: Mar 2007
 *
 * Content_GenericNews Module Site Layout : site list title only
*/		
global $camyks;
?>
<?=$this->theme->get_boxHeader();?>
<?=$this->theme->get_boxTitleBar( $this->get_translation('site_title'));?>
<?=$this->theme->get_boxContent1Header('padding:8px;');?>
<table cellspacing="0" cellpadding="0" border="0" width="100%">
<?php foreach ( $this->newsitems as $n ) : ?>
<tr>
  <td class="title3" style="text-align:left;">
    <a href="<?= $this->get_singlenewslink($n->id)?>" class="title3">
    <?=$n->vars['title']?>
    <span class="title4">
    -
    <?=$n->vars['author']?>
    -
    <?=date_displayShortDateHour( $n->vars['ndate']);?>
    </span>
    </a>
  </td>
</tr>
<tr>
  <td>
&nbsp;
  </td>
</tr>
<?php endforeach; ?>
</table>
<?=$this->theme->get_boxContent1Footer(); ?>
<?php if ( $this->prevnews != '' or $this->nextnews != '' ) : ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?php endif; ?>
<?=$this->theme->get_boxFooter(); ?>