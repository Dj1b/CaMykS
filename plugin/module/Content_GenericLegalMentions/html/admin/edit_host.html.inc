<?php
/**
 * @brief Content_GenericLegalMentions Module admin, edit host sub layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2020
 * @date Modification: Jan 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td class="eTableLine0 eContent2" style="width:150px">
            <?= $camyks->get_translation('formitem_name'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('host_name'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $camyks->get_translation('formitem_address'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput(array('name'=>'host_address', 'class'=>'vlinputs')); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2">
            <?= $camyks->get_translation('formitem_phone'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('host_phone'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $camyks->get_translation('formitem_fax'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput('host_fax'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2">
            <?= $camyks->get_translation('formitem_email'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput(array('name'=>'host_email', 'class'=>'linputs')); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $camyks->get_translation('formitem_website'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput(array('name'=>'host_website', 'class'=>'linputs')); ?>
        </td>
    </tr>
</table>

