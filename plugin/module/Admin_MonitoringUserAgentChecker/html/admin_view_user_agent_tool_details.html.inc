<?php
/**
 * @brief Admin_MonitoringUserAgentChecker Module admin view user agent, tool details, layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_MonitoringUserAgentChecker/html/admin_view_user_agent_tool_details.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2014
 * @date Modification: Nov 2018
 * @copyright 2014 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_platform_format'); ?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('platform_format', $this->uaInfos) ? $this->recordPlatformFormats[$this->uaInfos['platform_format']] : ''; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_tool_title'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= array_key_exists('tool_title', $this->uaInfos) ? $this->uaInfos['tool_title'] : ''; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_bot_url'); ?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('tool_url', $this->uaInfos) ? $this->uaInfos['tool_url'] : ''; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_engine_title'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= array_key_exists('engine_title', $this->uaInfos) ? $this->uaInfos['engine_title'] : ''; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_engine_url'); ?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('engine_url', $this->uaInfos) ? $this->uaInfos['engine_url'] : ''; ?>
    </td>
</tr>
<?php
/**
 * @endcond Exclude
 */
?>
