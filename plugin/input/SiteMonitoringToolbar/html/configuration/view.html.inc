<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Plugin / Input Layout
 * Creation Date    : Jan 2018
 * Last Modif Date	: Jan 2018
 * 
 * SiteMonitoringToolbar special layout : view configuration
*/
global $camyks;
?>
<?=$camyks->theme->get_boxContent2Header();?>
<div class="adminContentPanel">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td class="eTableLine0 eContent2" style="width:160px;">
      <?=$this->get_translation('formitem_accessrestriction');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->config->get_accessRestrictionValue(); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_buttonlocation');?>
    </td>
    <td class="eTableLine1 eContent1">
      <?=$this->config->get_buttonLocationValue(); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_appliedtheme');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->config->get_availableThemeValue(); ?>
    </td>
  </tr>
</table>
</div>
<?=$camyks->theme->get_boxContent2Footer();?>