<?php
/**
 * @brief LimonetikPayment Input configuration view layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Oct 2020
 * @date Modification: Oct 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

$form = new HTMLForm();

?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_operation'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2" style="width:160px;">
            <?= $this->get_translation('formitem_mode'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->config->get_modeTitle(); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_authenticating'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_apikey'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->config->vars['APIKey']; ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_merchandid'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->config->vars['MerchantId']; ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_payments'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $form->display_checkBoxInput(array('name'=>'EnableCreditCard', 'value'=>1, 'disabled'=>'disabled', 'default'=>$this->config->get_value('EnableCreditCard'), 'label'=>$this->get_translation('payment_creditcard'), 'labelClass'=>'eContent2')); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            &nbsp;
        </td>
        <td class="eTableLine0 eContent1">
            <?= $form->display_checkBoxInput(array('name'=>'EnableConecs', 'value'=>1, 'disabled'=>'disabled', 'default'=>$this->config->get_value('EnableConecs'), 'label'=>$this->get_translation('payment_conecs'), 'labelClass'=>'eContent2')); ?>
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
