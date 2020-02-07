<?php
/**
 * @brief Content_GenericLegalMentions Module admin, edit webmaster & dpo sub layout.
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
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_webmaster'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2" style="width:150px">
            <?= $camyks->get_translation('formitem_name'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('webmaster_name'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $camyks->get_translation('formitem_email'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput('webmaster_email'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2">
            <?= $camyks->get_translation('formitem_company'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('webmaster_company'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_dpo'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2" style="width:150px">
            <?= $camyks->get_translation('formitem_name'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('dpo_name'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $camyks->get_translation('formitem_email'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput('dpo_email'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2">
            <?= $camyks->get_translation('formitem_company'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('dpo_company'); ?>
        </td>
    </tr>
</table>

