<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Layout
 * Create Date		: Jan 2018
 * Last Modif Date	: Jan 2018
 * 
 * SocialNetworksSharingPanel input layout - follow mode
*/
?>
<div class="SNSP follow<?=($this->params['follow_insertion'] == 1 ? ' '.$this->params['follow_location']:'');?>">
  <?php foreach ($this->networks as $name => $network) : ?>
    <?php if ($network['follow'] == 1 and $this->params['follow_'.$name] != '') : ?>
      <a href="<?=$this->config->vars['follow_'.$name];?>" class="img" target="_blank" rel="noopener">
        <img src="<?=$this->get_fileURL('img/followIcons/'.$name.'.png');?>" alt="<?=$this->get_translation('followuson', $network['title']);?>" title="<?=$this->get_translation('followuson', $network['title']);?>" class="networkIcon" />
      </a>
    <?php endif; ?>
  <?php endforeach; ?>
</div>