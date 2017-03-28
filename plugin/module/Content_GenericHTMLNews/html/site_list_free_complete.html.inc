<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Create Date	    : Jan 2008
 * Last Modif Date	: Oct 2009
 *
 * Content_GenericHTMLNews Module Site Layout : site list complete
*/		
?>
<div>
  <h1 class="eTitle1">
    <?=$this->get_translation('site_title');?>
  </h1>

  <?php foreach ( $this->newsitems as $n ) : ?>
  <h2 class="eTitle2">
    <?=$n->vars['title']?>
  </h2>
  
  <h3 class="eTitle3">
    <?=$this->get_translation('infos', array($n->vars['author'], date_displayLongDayDateHour($n->vars['ndate'])))?>
  </h3>
  
  <div style="padding:0 16px 16px;">
    <?php if ( $n->vars['source_title'] != '' ) : ?>
    <h4 class="eTitle4">
      <?= $this->get_translation('sourcelnk')?>
      <?php if ( $n->vars['source_url'] != '' ) : ?>
      <a href="<?=$n->vars['source_url']?>" class="eLink1">
	<?=$n->vars['source_title']?>
      </a>
      <?php else : ?>
      <?=$n->vars['source_title']?>
      <?php endif; ?>
    </h4>
    <?php endif; ?>
    
    <?php if ( file_exists( $n->vars['content'] ) ) : ?>
	<?php include $n->vars['content']; ?>
    <?php endif; ?>
    
    <?php if ($this->networkInput !== false) : ?>
      <?=$this->networkInput->display(array('link'=>$this->get_singlenewslink($n->id)));?>
    <?php endif; ?>

  </div>
  <?php endforeach; ?>
  
  <?php $this->load_file('html/site_list_free_buttonsbar.html.inc');?>

</div>