<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Dec 2007
 * Last Modif Date	: Jan 2009
 *
 * Content_GenericHTMLNews Module Site Layout : site list summary
*/		
global $camyks;
?>
<div>

  <h1 class="eTitle1">
    <?=$this->get_translation('site_title');?>
  </h1>
  
  <?php foreach ( $this->newsitems as $n ) : ?>
  <h2 class="eTitle2">
    <a href="<?=$this->get_singlenewslink($n->id)?>">
      <?=$n->vars['title']?>
    </a>
    &nbsp;-&nbsp;
    <span class="eTitle4">
      <?=$this->get_translation('infos', array($n->vars['author'], date_displayLongDayDateHour($n->vars['ndate'])))?>
    </span>
  </h2>
  <div style="padding:0 16px;">
    <div class="eContent1">
      <?=nl2br( $n->vars['summary'] ) ?>
    </div>
    <div class="eContent1">
      <a href="<?=$this->get_singlenewslink($n->id)?>" class="elink1">
	    <?=$this->get_translation('readmore')?>
      </a>
    </div>
  </div>
  <?php endforeach; ?>
  
  <?php $this->load_file('html/site_list_free_buttonsbar.html.inc');?>
  
</div>