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
 * Content_GenericHTMLNews Module Site Layout : site list custom
*/		
?>
<?=$this->theme->get_boxHeader();?>
<?=$this->theme->get_boxTitleBar($this->get_translation('site_title'));?>
<?=$this->theme->get_boxContent1Header();?>

  <?php foreach ( $this->newsitems as $n ) : ?>
  
  <h2 class="eTitle2">
    <?=$n->vars['title']?>
  </h2>
  
  <h3 class="eTitle3">
    <?=$this->get_translation('infos', array($n->vars['author'], date_displayLongDayDateHour($n->vars['ndate'])))?>
  </h3>
  
  <div style="padding:0 16px;">
    <?php if ( $n->vars['source_title'] != '' ) : ?>
    <h4 class="eTitle4">
      <?= $this->get_translation('sourcelnk')?>
      <?php if ($n->vars['source_url'] != '') : ?>
      <a href="<?=$n->vars['source_url']?>" class="eLink1" target="_blank">
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

    <p class="eContent1">
    <?=$this->get_translation('shareon');?>
    <a name="fb_share" type="icon" share_url="<?=$this->get_singlenewslink($n->id);?>"></a>
    </p>

  </div>
  <?php endforeach; ?>

<?=$this->theme->get_boxContent1Footer(); ?>
<?php if ( isset( $this->buttons ) ) : ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?php endif; ?>
<?=$this->theme->get_boxFooter(); ?>