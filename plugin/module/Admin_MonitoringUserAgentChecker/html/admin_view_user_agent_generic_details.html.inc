<?php
/**
 * @brief Admin_MonitoringUserAgentChecker Module admin view user agent, browser details, layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_MonitoringUserAgentChecker/html/admin_view_user_agent_generic_details.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Dec 2014
 * @date Modification: Jun 2019
 * @copyright 2014 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_platform_company')?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('platform_company', $this->uaInfos) ? $this->uaInfos['platform_company'] : ''; ?>
        <?php if (array_key_exists('platform_country', $this->uaInfos) and $this->uaInfos['platform_country'] != '') : ?>
            <img src="<?= language_getIcon($this->uaInfos['platform_country'], false); ?>" alt="<?= countries_getTranslation($this->uaInfos['platform_country']); ?>" title="<?= countries_getTranslation($this->uaInfos['platform_country']); ?>" style="vertical-align:-2px; margin-left:4px;" />
        <?php endif; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_platform_model')?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= array_key_exists('platform_model', $this->uaInfos) ? $this->uaInfos['platform_model'] : ''; ?>
        <?php if (array_key_exists('platform_year', $this->uaInfos) and $this->uaInfos['platform_year'] != '') : ?>
            (<?= $this->uaInfos['platform_year']; ?>)
        <?php endif; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_platform_format')?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= (array_key_exists('platform_format', $this->uaInfos) and isset($this->recordPlatformFormats[$this->uaInfos['platform_format']])) ? $this->recordPlatformFormats[$this->uaInfos['platform_format']] : ''; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_system_title')?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= array_key_exists('system_title', $this->uaInfos) ? $this->uaInfos['system_title'] : ''; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_system_version')?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('system_version', $this->uaInfos) ? $this->uaInfos['system_version'] : ''; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_browser_title')?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= array_key_exists('browser_title', $this->uaInfos) ? $this->uaInfos['browser_title'] : ''; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_browser_version')?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('browser_version', $this->uaInfos) ? $this->uaInfos['browser_version'] : ''; ?>
    </td>
</tr>

<?php
/**
 * @endcond Exclude
 */
?>
