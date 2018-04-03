<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date    : Mar 2017
 * Last Modif Date  : Mar 2018
 *
 * Admin_MonitoringUserAgentChecker Module Admin Layout : view hack record
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
