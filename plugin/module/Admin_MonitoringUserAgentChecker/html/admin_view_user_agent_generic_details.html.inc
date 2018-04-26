<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0.1
 * Object Type      : Plugin / Module Layout
 * Creation Date    : Mar 2018
 * Last Modif Date  : Apr 2018
 *
 * Admin_MonitoringUserAgentChecker Module Admin Layout : view record details
*/
?>
<tr>
    <td class="eTableLine1 eContent2">
        <?=$this->get_translation('formitem_platform_company')?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('platform_company', $this->uaInfos) ? $this->uaInfos['platform_company'] : '';?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?=$this->get_translation('formitem_platform_model')?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= array_key_exists('platform_model', $this->uaInfos) ? $this->uaInfos['platform_model'] : '';?>
        <?php if (array_key_exists('platform_year', $this->uaInfos) and $this->uaInfos['platform_year'] != '') : ?>
            (<?=$this->uaInfos['platform_year'];?>)
        <?php endif; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?=$this->get_translation('formitem_platform_format')?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= (array_key_exists('platform_format', $this->uaInfos) and isset($this->recordPlatformFormats[$this->uaInfos['platform_format']])) ? $this->recordPlatformFormats[$this->uaInfos['platform_format']] : '';?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?=$this->get_translation('formitem_system_title')?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= array_key_exists('system_title', $this->uaInfos) ? $this->uaInfos['system_title'] : '';?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?=$this->get_translation('formitem_system_version')?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('system_version', $this->uaInfos) ? $this->uaInfos['system_version'] : '';?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?=$this->get_translation('formitem_browser_title')?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= array_key_exists('browser_title', $this->uaInfos) ? $this->uaInfos['browser_title'] : ''; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?=$this->get_translation('formitem_browser_version')?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('browser_version', $this->uaInfos) ? $this->uaInfos['browser_version'] : '';?>
    </td>
</tr>
