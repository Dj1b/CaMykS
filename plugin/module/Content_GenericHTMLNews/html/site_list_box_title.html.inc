<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Creation Date	: Dec 2007
 * Last Modif Date	: Jan 2009
 *
 * Content_GenericHTMLNews Module Site Layout : site list title only
*/		
?>
<?=$this->theme->get_boxHeader();?>
<?=$this->theme->get_boxTitleBar( $this->get_translation('site_title'));?>
<?=$this->theme->get_boxContent1Header();?>

  <?php foreach ( $this->newsitems as $n ) : ?>
  <div class="eTitle2">
    <a href="<?=$this->get_singlenewslink($n->id)?>" class="eLink2">
      <?=$n->vars['title']?>
      <span class="eTitle3">
	-
	<?=$n->vars['author']?>
	-
	<?=date_displayShortDateHour( $n->vars['ndate']);?>
      </span>
    </a>
  </div>
  <?php endforeach; ?>

<?=$this->theme->get_boxContent1Footer(); ?>
<?php if ( isset( $this->buttons ) ) : ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?php endif; ?>
<?=$this->theme->get_boxFooter(); ?>