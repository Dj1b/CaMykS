<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jul 2008
 * Last Modif Date	: Jul 2008
 * 
 * Content_GoogleMapsViewer Module Site Layout : map display
 */
if ( $this->mapItem->vars['link_class'] == 0 ) {
  $l = 'style="';
  $l .= 'color:#'.$this->mapItem->vars['link_color'].';';
  $l .= 'font-size:'.$this->mapItem->vars['link_size'].'px;';
  $l .= 'font-weight:'.($this->mapItem->vars['link_bold']==1?'bold':'normal').';';
  $l .= 'font-style:'.($this->mapItem->vars['link_italic']==1?'italic':'normal').';';
  $l .= 'text-decoration:'.($this->mapItem->vars['link_underline']==1?'underline':'none').';';
  $l .= '"';
} else {
  $l = 'class="link'.$this->mapItem->vars['link_class'].'"';
}
?>
<div>
<iframe width="<?=$this->mapItem->vars['map_width']?>" height="<?=$this->mapItem->vars['map_height']?>" 
  frameborder="0" scrolling="no" marginheight="0" marginwidth="0" 
  src="<?=$this->mapItem->vars['map_baseurl']?>&amp;z=<?=$this->mapItem->vars['map_zoom']?>&amp;s=<?=$this->mapItem->vars['map_code']?>&amp;output=embed">
</iframe>
</div>
<?php if ( $this->mapItem->vars['link_enabled'] == 1 ) : ?>
<a href="<?=$this->mapItem->vars['map_baseurl']?>&amp;z=<?=$this->mapItem->vars['map_zoom']?>&amp;source=embed" <?=$l?>>
  <?=$this->get_translation('site_viewlargermap');?>
</a>
<?php endif; ?>

