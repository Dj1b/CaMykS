<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Oct 2005
 * Last Modif Date	: Mar 2009
 * 
 * Admin_MyAccount Module Layout : read mode
 */
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:500px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title);?>
<?=$this->theme->get_boxContent2Header();?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
      <?=$camyks->get_translation('formitem_login')?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->myAccount->login?>
    </td>
  </tr>
  <tr>
    <td class="eTableLine1 eContent2">
      <?=$camyks->get_translation('formitem_firstname')?>
    </td>
    <td class="eTableLine1 eContent1">
      <?=$this->myAccount->firstname?>
    </td>
  </tr>
  <tr>
    <td class="eTableLine0 eContent2">
      <?=$camyks->get_translation('formitem_lastname')?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->myAccount->lastname?>
    </td>
  </tr>
  <tr>
    <td class="eTableLine1 eContent2">
      <?=$camyks->get_translation('formitem_email')?>
    </td>
    <td class="eTableLine1 eContent1">
      <a href="mailto:<?=$this->myAccount->email?>" class="eLink1">
        <?=$this->myAccount->email?>
      </a>
    </td>
  </tr>
  <tr>
    <td class="eTableLine0 eContent2">
      <?=$camyks->get_translation('formitem_address');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=nl2br($this->myAccount->address)?>
    </td>
  </tr>
</table>
</div>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter();?>