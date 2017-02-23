<?php
/*
 * Camyks Engine
 * Company		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Mar 2007
 * Last Modif Date	: Oct 2009
 *
 * Content_GenericHTMLNews Module Site Layout : site item complete custom
*/		
?>
<?=$this->theme->get_boxHeader();?>
<?=$this->theme->get_boxTitleBar($this->get_translation('site_title'));?>
<?=$this->theme->get_boxContent1Header();?>

  <h2 class="eTitle2">
    <?=$this->newsitem->vars['title']?>
  </h2>
  
  <h3 class="eTitle3">
    <?= $this->get_translation('infos', array($this->newsitem->vars['author'], date_displayLongDayDateHour($this->newsitem->vars['ndate'])));?> 
  </h3>
  
  <div style="padding:0 16px;">
    <?php if ( $this->newsitem->vars['source_title'] != '' ) : ?>
    <h4 class="eTitle4" style="padding:4px 16px;">
      <?= $this->get_translation('sourcelnk')?>
      <?php if ( $this->newsitem->vars['source_url'] != '' ) : ?>
      <a href="<?=$this->newsitem->vars['source_url']?>" class="eLink1">
	<?=$this->newsitem->vars['source_title']?>
      </a>
      <?php else : ?>
      <?=$this->newsitem->vars['source_title']?>
      <?php endif; ?>
    </h4>
    <?php endif; ?>
    

    <?php if ( file_exists($this->newsitem->vars['content']) ) : ?>
    <?php include($this->newsitem->vars['content']); ?>
    <?php endif; ?>

    <p class="eContent1">
    <?=$this->get_translation('shareon');?>
    <a name="fb_share" type="icon" share_url="<?=$this->get_singlenewslink($this->newsitem->id);?>"></a>
    </p>
  </div>


<?=$this->theme->get_boxContent1Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>