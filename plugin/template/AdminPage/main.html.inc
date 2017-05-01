<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Template Layout
 * Creation Date	: Sep 2005
 * Last Modif Date	: Apr 2017
 *      
 * AdminPage Template Main HTML
*/
global $camyks;
?>
<div id="adminengine_main">
  <div id="pageHeader">
      <?php if ($this->get_fileURL('img/banner.jpg') == '') : ?>
      <div id="pageHeaderTitle" class="eTitle1">
        <?=$camyks->get_translation('site_admin', $camyks->site_conf['site_title']);?>
      </div>
      <?php else :  ?>
      <div id="pageHeaderBanner">
         <img src="<?=$this->get_fileURL('img/banner.jpg');?>" alt="<?=$camyks->get_translation('site_admin', $camyks->site_conf['site_title']);?>" style="margin:0 auto; border:none;" />
      </div>
      <?php endif; ?>
    <div id="pageHeaderBar">
      <?=$this->display_module(1);?>
    </div>
  </div>
  <div id="pageContent">
    <?=$this->display_module(0);?>
  </div>
  <div id="pageFooter">
    <div id="pageFooterEngine">
      <a href="<?=$camyks->website?>" class="img" target="_blank">
        <img src="<?=$this->get_signPicture()?>" alt="Powered By CaMykS" border="0" />
      </a>
    </div>
  </div>
</div>
<div id="adminengine_modalPopupBackground" style="z-index:9000">
  &nbsp;
</div>