<?php
/**
 * @brief YavinPayment input, configuration view layout.
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: May 2026
 * @date Modification: May 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_runningmode'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_runningModeTitle(); ?>
            </td>
        </tr>
        <tr>
            <td colspan="2" class="eTableLine0">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_test'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_apikey'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->vars['testAPIKey']; ?>
            </td>
        </tr>
        <tr>
            <td colspan="2" class="eTableLine0">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_production'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_apikey'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->vars['productionAPIKey']; ?>
            </td>
        </tr>
        <tr>
            <td colspan="2" class="eTableLine0">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_settings'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_allowtitres'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $camyks->get_translation($this->config->vars['settingAllowTitres'] ? 'yes' : 'no'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_adminemail'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->vars['settingAdminEmail']; ?>
            </td>
        </tr>
        <tr>
            <td colspan="2" class="eTableLine0">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_vendor'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_brandname'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->vars['vendorBrandName']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_softwarename'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->vars['vendorSoftwareName']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_softwareversion'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->vars['vendorSoftwareVersion']; ?>
            </td>
        </tr>
    </table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
