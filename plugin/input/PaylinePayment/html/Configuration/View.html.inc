<?php
/**
 * @brief PaylinePayment input, view configuration layout.
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Apr 2026
 * @date Modification: Apr 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_operation'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2" style="width:200px;">
            <?= $this->get_translation('formitem_runningmode'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->config->get_modeTitle(); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_authentication'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_merchant_id'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->config->vars['merchantId']; ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_contract_number'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->config->vars['contractNumber']; ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableSubHeader" colspan="2">
            <?= $this->get_translation('runningmode_homologation'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_access_key'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->config->vars['homologation_accessKey']; ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableSubHeader" colspan="2">
            <?= $this->get_translation('runningmode_production'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_access_key'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->config->vars['production_accessKey']; ?>
        </td>
    </tr>

</table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
