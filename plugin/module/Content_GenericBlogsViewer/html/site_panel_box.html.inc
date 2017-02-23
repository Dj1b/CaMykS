<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Apr 2008
 * Last Modif Date	: Jul 2008
 * 
 * Content_GenericBlogsViewer Module Site Layout : site list_box layout
 */
global $camyks;
?>
<div style="width:150px;">
  <?=$this->theme->get_boxHeader('width:100%');?>
  <?=$this->theme->get_boxContent1Header('padding:4px 8px');?>
  <?php if ( count( $this->configItem->vars['authors_'] ) != 1 ) : ?> 
  <div class="eContent2">
    <?=$this->get_translation('panel_authors');?>
  </div>
  <div class="eContent1">
    <?php foreach ( $this->panel_authors as $author => $count ) : ?>
    <?=$this->get_blogNewsAuthorDisplay( $author, 'eLink1');?> (<?=$count?>) <br />
    <?php endforeach; ?>
    <?php endif; ?>
  </div>
  
  <?php if ( count( $this->panel_tags ) > 0 ) : ?>
  <div class="eContent2" style="padding-top:16px;">
    <?=$this->get_translation('panel_tags');?>
  </div>
  <div class="eContent1">
    <div class="eContent1">
      <?php foreach ( $this->panel_tags as $value ) : ?>
      <?php if ( $count > 0 ) : ?>
      <?=$this->get_blogNewsTagsDisplay( array($value['tag']), 'eLink1');?> (<?=$value['count']?>) <br />
      <?php endif; ?>
      <?php endforeach; ?>
    </div>
    <?php endif; ?>
    
    <?php if ( count($this->panel_links) > 0 ) : ?>
    <div class="eContent2" style="padding-top:16px;">
      <?=$this->get_translation('panel_links');?>
    </div>
    <div class="eContent1">
      <?php foreach( $this->panel_links as $link ) : ?>
      <a href="<?=$link->vars['link']?>" class="eLink1" target="_blank">
	<?=$link->vars['title']?>
      </a><br />
      <?php endforeach; ?>
      <?php endif; ?>
    </div>
    <?php if($this->configItem->vars['panel_insert'] != '') : ?>
    <div class="eContent1">
      &nbsp;
    </div>
    <div class="eContent1">
      <?=$this->configItem->vars['panel_insert'];?>
    </div>
    <?php endif; ?>
  </div>
  <?=$this->theme->get_boxContent1Footer(); ?>
  <?=$this->theme->get_boxFooter(); ?>
</div>