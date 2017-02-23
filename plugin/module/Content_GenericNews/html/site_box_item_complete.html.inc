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
 * Content_GenericNews Module Site Layout : site item complete
*/		
global $camyks;
?>
<?=$this->theme->get_boxHeader();?>
<?=$this->theme->get_boxTitleBar($this->get_translation('site_title'));?>
<?=$this->theme->get_boxContent1Header('padding:8px;');?>
<h2 class="eTitle3">
  <?=$this->newsitem->vars['title']?>
</h2>

<h3 class="eTitle4">
<?=$this->get_translation('infos', array($this->newsitem->vars['author'], date_displayLongDayDateHour($this->newsitem->vars['ndate'])));?> 
</h3>

<blockquote>
  <p class="eContent1">
<?=nl2br($this->newsitem->vars['content'])?>
  </p>

  <?php if ( $this->newsitem->vars['source_title'] != '' and $this->newsitem->vars['source_url'] != '' ) : ?>
    <p class="eContent3">
       <?= $this->get_translation('sourcelnk')?>
       <a href="<?=$this->newsitem->vars['source_url']?>" class="title4"><?=$this->newsitem->vars['source_title']?></a>
    </p>
  <?php elseif ( $this->newsitem->vars['source_title'] != '' ) : ?>
    <p class="eContent3">
      <?= $this->get_translation('sourcelnk')?><?=$this->newsitem->vars['source_title']?>
    </p>
  <?php endif; ?>
  <div class="eContent1">
    &nbsp;
  </div>
<?=$this->theme->get_boxContent1Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>