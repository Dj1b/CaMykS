<?php
/**
 * @brief MoneticoPaiement Input configuration view layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2020
 * @date Modification: Sep 2020
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
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_operation'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2" style="width:160px;">
            <?= $this->get_translation('formitem_mode'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->config->get_modeTitle(); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_companycode'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->config->get_value('company_code'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_countrycode'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->config->get_value('country_code'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_testkeys'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_tpeid'); ?>
        </td>
        <td class="eTableLine0 eContent1">
        	<?= $this->config->get_value('tpeId_test'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_key'); ?>
        </td>
        <td class="eTableLine1 eContent1">
        	<?= $this->config->get_value('bankKey_test'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_livekeys'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_tpeid'); ?>
        </td>
        <td class="eTableLine0 eContent1">
        	<?= $this->config->get_value('tpeId_live'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_key'); ?>
        </td>
        <td class="eTableLine1 eContent1">
        	<?= $this->config->get_value('bankKey_live'); ?>
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
