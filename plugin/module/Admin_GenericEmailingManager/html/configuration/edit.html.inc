<?php
/**
 * @brief Admin_GenericEmailingManager Module edit configuration sub layout
 * @details Plugin, Module Layout
 * @file plugin/module/Admin_GenericEmailingManager/html/configuration/edit.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2012
 * @date Modification: Dec 2018
 * @copyright 2012 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$file = $this->theme->get_pictURL('file', 12, 'std');
$file_ = $this->theme->get_pictURL('file', 12, 'ovr');
?>

<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

<tr>
    <td class="eTableHeader" colspan="4">
        <?= $this->get_translation('formtitle_unsubscribe'); ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
        <?= $this->get_translation('formitem_backpage'); ?>
    </td>
    <td class="eTableLine0 eContent1" colspan="3">
        <?= $this->editform->display_textInput(array('name'=>'unsubscribe_backpage')); ?>
        <?php if ($this->pc) : ?>
            <a href="javascript:open_pageChooser('unsubscribe_backpage');">
                <img src="<?= $file?>" border="0"
                    alt="<?= $this->get_translation('select_sitepage'); ?>"
                    title="<?= $this->get_translation('select_sitepage'); ?>"
                    onmouseover="this.src='<?= $file_?>';"
                    onmouseout="this.src='<?= $file?>';" />
            </a>
        <?php endif; ?>
    </td>
</tr>

</table>
