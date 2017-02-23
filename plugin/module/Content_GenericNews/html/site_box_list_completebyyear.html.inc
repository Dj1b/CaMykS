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
 * Content_GenericNews Module Site Layout : site list complete with month display separator
 */		
global $camyks;
/* last date */
$lastdate = 0;
?>
<?=$this->theme->get_boxHeader();?>
<?=$this->theme->get_boxTitleBar( $this->get_translation('site_title'));?>
<?=$this->theme->get_boxContent1Header('padding:8px;');?>
<table cellspacing="0" cellpadding="0" border="0" width="100%">
<?php foreach ( $this->newsitems as $n ) : ?>
<?php if ( $lastdate == 0 or  
	  mktime( 0,0,0, 1, 1, date('Y', $lastdate)) > 
	  mktime( 0,0,0, 1, 1, date('Y', $n->vars['ndate']))) : ?>  

<tr>
  <td class="title2">
    <?= strftime('%Y', $n->vars['ndate']) ?>
  </td>
</tr>
<?php endif; ?>
<?php $lastdate = $n->vars['ndate']; ?>

<tr>
  <td class="title3" style="text-align:left;">
    <?=$n->vars['title']?>
  </td>
</tr>
<tr>
  <td class="title4" style="text-align:left">
<?= $this->get_translation('infos', array($n->vars['author'], date_displayLongDayDateHour($n->vars['ndate']) ) );?> 
  </td>
</tr>
<tr>
  <td class="content1" style="padding-left:16px;">
<?=nl2br($n->vars['content'])?>
   </td>
</tr>
  <?php if ( $n->vars['source_title'] != '' and $n->vars['source_url'] != '' ) : ?>
  <tr>
    <td class="title4" style="padding:4px 16px;">
      <?= $this->get_translation('sourcelnk')?>
      <a href="<?=$n->vars['source_url']?>" class="title4"><?=$n->vars['source_title']?></a>
    </td>
  </tr>
  <?php elseif ( $n->vars['source_title'] != '' ) : ?>
  <tr>
    <td class="title4" style="padding:4px 16px;">
      <?= $this->get_translation('sourcelnk')?><?=$n->vars['source_title']?>
    </td>
  </tr>
  <?php endif; ?>
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