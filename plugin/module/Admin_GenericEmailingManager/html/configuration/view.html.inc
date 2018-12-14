<?php
/**
 * @brief Admin_GenericEmailingManager Module view configuration sub layout
 * @details Plugin, Module Layout
 * @file plugin/module/Admin_GenericEmailingManager/html/configuration/view.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2012
 * @date Modification: Dec 2018
 * @copyright 2012 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
<tr>
    <td class="eTableHeader" colspan="2">
        <?= $this->get_translation('formtitle_unsubscribe'); ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2" style="width:150px">
        <?= $this->get_translation('formitem_backpage'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= $this->config->vars['unsubscribe_backpage']; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2" coslpan="2">
        <?= $this->theme->get_button(array('url'=>$this->get_adminLink(array('mode'=>'edit_config')), 'title'=>$camyks->get_translation('modify'))); ?>
    </td>
</tr>
</table>
