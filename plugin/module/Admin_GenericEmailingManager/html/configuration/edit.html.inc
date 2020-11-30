<?php
/**
 * @brief Admin_GenericEmailingManager Module edit configuration sub layout
 * @details Plugin, Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.1
 * @date Creation: Dec 2012
 * @date Modification: Nov 2020
 * @copyright 2012 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$file = $camyks->theme->get_pictURL('file', 12, 'std');
$file_ = $camyks->theme->get_pictURL('file', 12, 'ovr');
?>

<?php if (isset($this->isConfig) and $this->isConfig) :?>

<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">

<?php endif; ?>

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

<?php if (isset($this->isConfig) and $this->isConfig) :?>

</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>

<?php endif; ?>
