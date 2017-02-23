<?php
/*
 * CaMyks Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : May 2010
 * Last Modif Date  : May 2010
 * 
 * Content_TwitterStatusesVIewer Module Site Layout : site nobox layout
 */
$uData = $this->userData;
$tData = $this->tweets;
?>
<div class="twitterBox<?=$uData['id']?>">
  <div>
  <a href="http://www.twitter.com/" target="_blank">
  <img src="<?=$this->get_fileURL('img/icon_twitter.png');?>" style="float:left; margin-right:4px;" alt="Twitter" border="0" />
    </a>
  <a href="http://www.twitter.com/<?=$uData['screen_name']?>" class="eTitle2" target="_blank">
  @<?=$uData['name'];?>
    </a>
  </div>
  <?php foreach ($tData['status'] as $status) : ?>
  <p class="eContent<?=$status['favorited']=='true'?2:1?>">
    <?=$this->update_tweetText($status['text']);?>
  </p>
  <div class="eTitle4">
    <?=$this->display_tweetDate($status['created_at']);?>
  </div>
  <div style="border-top:solid 1px #<?=$this->get_borderColor('888888');?>; margin:8px 20px 0;">
    &nbsp;
  </div>
  <?php endforeach; ?>
</div>