<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Layout
 * Create Date		: Jul 2008
 * Last Modif Date	: Jul 2008
 * 
 * BreadCrumbs input layout
*/
?>
<div class="<?=$this->params['container_class']?>">
  <?php foreach($this->path as $page) : ?>
  <div style="display:inline;">
    <span class="<?=$this->params['text_class']?>">
      <?=$this->params['separator']?>
    </span>
    <?php if ($page['url'] !== false ) : ?>
    <a href="<?=$page['url']?>" class="<?=$this->params['link_class']?>"><?=$page['title'];?></a>
    <?php else : ?>
    <span class="<?=$this->params['text_class']?>">
      <?=$page['title'];?>
    </span>
    <?php endif; ?>
  </div>
  <?php endforeach; ?>
</div>