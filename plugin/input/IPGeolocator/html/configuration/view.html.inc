<?php
/**
 * @brief IPGeolocator Input view configuration layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Dec 2020
 * @date Modification: Dec 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

/* Load service list */
$services = $this->config->get_serviceList();
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
                <?= $this->get_translation('formitem_service'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_serviceTitle(); ?>
            </td>
        </tr>

        <tr>
            <td colspan="2" class="eTableLine0">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_apikeysforservices'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $services['IPGeolocation']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if (($v = $this->config->get_value('APIKey_IPGeolocation')) == '') : ?>
                    <span class="eContent3"><?= $this->get_translation('noapikey'); ?></span>
                <?php else : ?>
                    <?= $v; ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2" style="width:160px;">
                <?= $services['IPStack']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?php if (($v = $this->config->get_value('APIKey_IPStack')) == '') : ?>
                    <span class="eContent3"><?= $this->get_translation('noapikey'); ?></span>
                <?php else : ?>
                    <?= $v; ?>
                    <?php if ($this->config->get_value('APIKey_IPStackPremium') == 1) : ?>
                    &nbsp;(<?= $this->get_translation('ispremium'); ?>)
                    <?php endif; ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $services['IPAPI']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if (($v = $this->config->get_value('APIKey_IPAPI')) == '') : ?>
                    <span class="eContent3"><?= $this->get_translation('noapikey'); ?></span>
                <?php else : ?>
                    <?= $v; ?>
                    <?php if ($this->config->get_value('APIKey_IPAPIPremium') == 1) : ?>
                    &nbsp;(<?= $this->get_translation('ispremium'); ?>)
                    <?php endif; ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2" style="width:160px;">
                <?= $services['IPData']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?php if (($v = $this->config->get_value('APIKey_IPData')) == '') : ?>
                    <span class="eContent3"><?= $this->get_translation('noapikey'); ?></span>
                <?php else : ?>
                    <?= $v; ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $services['Ipify']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if (($v = $this->config->get_value('APIKey_Ipify')) == '') : ?>
                    <span class="eContent3"><?= $this->get_translation('noapikey'); ?></span>
                <?php else : ?>
                    <?= $v; ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2" style="width:160px;">
                <?= $services['IPWhois']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?php if (($v = $this->config->get_value('APIKey_IPWhois')) == '') : ?>
                    <span class="eContent3"><?= $this->get_translation('limitedservice'); ?></span>
                <?php else : ?>
                    <?= $v; ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $services['IPRegistry']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if (($v = $this->config->get_value('APIKey_IPRegistry')) == '') : ?>
                    <span class="eContent3"><?= $this->get_translation('noapikey'); ?></span>
                <?php else : ?>
                    <?= $v; ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2" style="width:160px;">
                <?= $services['IPInfoDB']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?php if (($v = $this->config->get_value('APIKey_IPInfoDB')) == '') : ?>
                    <span class="eContent3"><?= $this->get_translation('noapikey'); ?></span>
                <?php else : ?>
                    <?= $v; ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $services['DB_IP']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if (($v = $this->config->get_value('APIKey_DB_IP')) == '') : ?>
                    <span class="eContent3"><?= $this->get_translation('noapikey'); ?></span>
                <?php else : ?>
                    <?= $v; ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2" style="width:160px;">
                <?= $services['IP2Location']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?php if (($v = $this->config->get_value('APIKey_IP2Location')) == '') : ?>
                    <span class="eContent3"><?= $this->get_translation('noapikey'); ?></span>
                <?php else : ?>
                    <?= $v; ?>
                <?php endif; ?>
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
