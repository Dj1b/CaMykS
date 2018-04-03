<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date    : Dec 2014
 * Last Modif Date  : Mar 2018
 *
 * Admin_MonitoringUserAgentChecker Module Admin Layout : view bot details
*/
?>
<tr>
    <td class="eTableLine1 eContent2">
        <?=$this->get_translation('formitem_platform_format')?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('platform_format', $this->uaInfos) ? $this->recordPlatformFormats[$this->uaInfos['platform_format']] : '';?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?=$this->get_translation('formitem_bot_title')?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= array_key_exists('bot_title', $this->uaInfos) ? $this->uaInfos['bot_title'] : '';?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?=$this->get_translation('formitem_bot_url')?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('bot_url', $this->uaInfos) ? $this->uaInfos['bot_url'] : '';?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?=$this->get_translation('formitem_engine_title')?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= array_key_exists('engine_title', $this->uaInfos) ? $this->uaInfos['engine_title'] : '';?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?=$this->get_translation('formitem_engine_url')?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('engine_url', $this->uaInfos) ? $this->uaInfos['engine_url'] : '';?>
    </td>
</tr>
