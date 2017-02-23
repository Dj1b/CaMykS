<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Create Date		: May 2007
 * Last Modif Date	: Mar 2009
 *
 * Admin_MyShortcuts module admin engine layout
 */
global $camyks;
?>
<div id="admin_myshortcuts_addpopup" class="adminPopupFrame" style="display:none;width:300px;position:absolute;z-index:10001">
  <?=$this->addform->display_header();?>
  <?=$this->addform->display_hiddens();?>
  <?=$camyks->theme->get_boxHeader()?>
  <?=$camyks->theme->get_boxTitleBar($this->get_translation('addpopuptitle'))?>
  <?=$camyks->theme->get_boxContent1Header()?>
  <div class="eContent2">
    <?=$this->get_translation('addpopupname')?>
  </div>
  <div class="eContent1">
    <input type="text" name="name" value="" maxlength="32" style="width:275px;" />
  </div>
  <?=$camyks->theme->get_boxContent1Footer()?>
  <?=$camyks->theme->get_boxButtonsBar($this->popupbuttons)?>
  <?=$camyks->theme->get_boxFooter()?>
  <?=$this->addform->display_footer();?>
</div>