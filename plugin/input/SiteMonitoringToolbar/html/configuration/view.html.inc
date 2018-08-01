<?php
/**
 * @brief SiteMonitoringToolbar Input configuration view layout
 * @details Plugin / Input layout
 * @file plugin/input/SiteMonitoringToolbar/html/configuration/view.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jan 2018
 * @date Modification: Jul 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td class="eTableLine0 eContent2" style="width:160px;">
      <?= $this->get_translation('formitem_accessrestriction'); ?>
    </td>
    <td class="eTableLine0 eContent1">
      <?= $this->config->get_accessRestrictionValue(); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?= $this->get_translation('formitem_buttonlocation'); ?>
    </td>
    <td class="eTableLine1 eContent1">
      <?= $this->config->get_buttonLocationValue(); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine0 eContent2">
      <?= $this->get_translation('formitem_appliedtheme'); ?>
    </td>
    <td class="eTableLine0 eContent1">
      <?= $this->config->get_availableThemeValue(); ?>
    </td>
  </tr>
</table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
