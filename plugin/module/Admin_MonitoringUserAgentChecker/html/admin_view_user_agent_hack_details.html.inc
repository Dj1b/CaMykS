<?php
/**
 * @brief Admin_MonitoringUserAgentChecker Module admin view user agent, hack details, layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_MonitoringUserAgentChecker/html/admin_view_user_agent_hack_details.html.inc
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
        <?=$this->get_translation('formitem_info')?>
    </td>
    <td class="eTableLine1 eContent1">
        <?= array_key_exists('hack_info', $this->uaInfos) ? $this->uaInfos['hack_info'] : '';?>
    </td>
</tr>
<?php
/**
 * @endcond Exclude
 */
?>
