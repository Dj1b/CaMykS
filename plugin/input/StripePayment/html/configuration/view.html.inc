<?php
/**
 * @brief StripePayment Input configuration view layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2020
 * @date Modification: Mar 2021
 * @copyright 2020 - 2021 CaMykS Team
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
        <td class="eTableLine0 eContent2" style="width:200px;">
            <?= $this->get_translation('formitem_runningmode'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->config->get_runningModeTitle(); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_authentication_test'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_apikey_public'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->config->vars['testAPIKey_public']; ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_apikey_private'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->config->vars['testAPIKey_private']; ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_displaytestcard'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $camyks->get_translation($this->config->get_value('test_displayTestCard') ? 'yes' : 'no'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_authentication_production'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_apikey_public'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->config->vars['productionAPIKey_public']; ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_apikey_private'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->config->vars['productionAPIKey_private']; ?>
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
