<?php
/**
 * @brief CrispChat Input configuration view layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jul 2020
 * @date Modification: Jul 2020
 * @copyright 2020 CaMykS Team
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
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_params'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_websiteid'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->get_configValue('websiteId'); ?>
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
