<?php
/**
 * @brief Admin_SystemLogManager module, edit configuration layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.2
 * @date Creation: Jun 2018
 * @date Modification: Sep 2026
 * @copyright 2018 - 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

$loggingPeriodList = $this->get_configurationLoggingPeriodList();
?>

<?php if ($this->isConfig) : ?>

<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">

<?php endif; ?>

<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td class="eTableLine0 eContent2" style="width:160px;">
            <?= $this->get_translation('formitem_rotate'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_selectInput(array('name'=>'logging_period', 'values'=>$loggingPeriodList)); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_keeplast'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput(array('name'=>'logging_lastFilesKept', 'class'=>'vsinputs')); ?>
            <?= $this->get_translation('formdesc_keeplast'); ?>
        </td>
    </tr>
</table>

<?php if ($this->isConfig) : ?>

</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>

<?php endif; ?>

<?php
/**
 * @endcond Exclude
 */
?>
