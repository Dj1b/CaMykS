<?php
/**
 * @brief GoogleAnalytics Input, edit configuration layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2018
 * @date Modification: Feb 2023
 * @copyright 2018 - 2023 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_googleparams'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_trackingcode'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'trackingId', 'class'=>'linputs', 'maxlength'=>24)); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_trackingmode'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'trackingMode', 'class'=>'inputs', 'values'=>$this->config->get_trackingModeList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_trackingparams'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'trackingParams', 'class'=>'vlinputs', 'maxlength'=>255)); ?>
            </td>
        </tr>

        <tr>
            <td colspan="2">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_internalparams'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_enableforadmin'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_booleanSelectInput(array('name'=>'enableAdminStats')); ?>
            </td>
        </tr>

    </table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
