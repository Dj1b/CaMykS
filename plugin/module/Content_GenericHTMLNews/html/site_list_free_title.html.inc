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
 * Content_GenericHTMLNews Module Site Layout : site list title only
*/		
?>
<div>
  <h1 class="eTitle1">
    <?=$this->get_translation('site_title');?>
  </h1>
  
  <?php foreach ( $this->newsitems as $n ) : ?>
  <div class="eTitle2">
    <a href="<?=$this->get_singlenewslink($n->id)?>">
      <?=$n->vars['title']?>
      <span class="title4">
	-
	<?=$n->vars['author']?>
	-
	<?=date_displayShortDateHour( $n->vars['ndate']);?>
      </span>
    </a>
  </div>
  <?php endforeach; ?>
  
  <?php $this->load_file('html/site_list_free_buttonsbar.html.inc');?>  

</div>