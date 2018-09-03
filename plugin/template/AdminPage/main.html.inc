<?php
/**
 * @brief AdminPage Template main layout
 * @details Plugin / Template layout
 * @file plugin/template/AdminPage/main.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Oct 2005
 * @date Modification: Aug 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<div id="adminengine_main">
  <div id="pageHeader">
      <?php if ($this->get_fileURL('img/banner.jpg') == '') : ?>
      <div id="pageHeaderTitle" class="eTitle1">
        <?= $camyks->get_translation('site_admin', $camyks->get_confValue('site_title')); ?>
      </div>
      <?php else : ?>
      <div id="pageHeaderBanner">
         <img src="<?= $this->get_fileURL('img/banner.jpg'); ?>" alt="<?= $camyks->get_translation('site_admin', $camyks->get_confValue('site_title')); ?>" style="margin:0 auto; border:none;" />
      </div>
      <?php endif; ?>
    <div id="pageHeaderBar">
      <?= $this->display_module(1); ?>
    </div>
  </div>
  <div id="pageContent">
    <?= $this->display_module(0); ?>
  </div>
  <div id="pageFooter">
    <div id="pageFooterVersion">
      CaMykS - version <?= $camyks->version; ?>
    </div>
    <div id="pageFooterEngine">
      <a href="<?= $camyks->website; ?>" class="img" target="_blank">
        <img src="<?= $this->get_signPicture(); ?>" alt="Powered By CaMykS" border="0" />
      </a>
    </div>
  </div>
</div>
<div id="adminengine_modalPopupBackground" style="z-index:9000">
  &nbsp;
</div>
<?php
/**
 * @endcond Exclude
 */
?>
