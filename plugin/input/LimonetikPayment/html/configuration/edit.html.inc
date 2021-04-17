<?php
/**
 * @brief LimonetikPayment Input configuration edit layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Oct 2020
 * @date Modification: Apr 2021
 * @copyright 2020 - 2021 CaMykS Team
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
        <td class="eTableHeader" colspan="4">
            <?= $this->get_translation('formtitle_operation'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2" style="width:160px;">
            <?= $this->get_translation('formitem_mode'); ?>
        </td>
        <td class="eTableLine0 eContent1" colspan="3">
            <?= $this->form->display_selectInput(array('name'=>'runningMode', 'class'=>'linputs', 'values'=>$this->config->get_modeList())); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="4">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="4">
            <?= $this->get_translation('formtitle_authenticating'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_testapikey'); ?>
        </td>
        <td class="eTableLine0 eContent1" colspan="3">
            <?= $this->form->display_textInput(array('name'=>'APIKey-Test', 'class'=>'linputs', 'maxlength'=>255)); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_apikey'); ?>
        </td>
        <td class="eTableLine1 eContent1" colspan="3">
            <?= $this->form->display_textInput(array('name'=>'APIKey', 'class'=>'linputs', 'maxlength'=>255)); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_merchandid'); ?>
        </td>
        <td class="eTableLine0 eContent1" colspan="3">
            <?= $this->form->display_textInput(array('name'=>'MerchantId', 'class'=>'linputs', 'maxlength'=>255)); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="4">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="4">
            <?= $this->get_translation('formtitle_paymentcards'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent1" colspan="2" style="width:50%;">
            <?= $this->form->display_hiddenInput(array('name'=>'EnableCreditCard', 'default'=>"0")); ?>
            <?= $this->form->display_checkBoxInput(array('name'=>'EnableCreditCard', 'value'=>1, 'label'=>$this->get_translation('payment_creditcard'), 'labelClass'=>'eContent2')); ?>
        </td>
        <td class="eTableLine0 eContent1" colspan="2" style="width:50%;">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="4">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="4">
            <?= $this->get_translation('formtitle_luncheonvouchercards'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent1" colspan="4">
            <?= $this->form->display_hiddenInput(array('name'=>'EnableConecs', 'default'=>"0")); ?>
            <?= $this->form->display_checkBoxInput(array('name'=>'EnableConecs', 'value'=>1, 'label'=>$this->get_translation('payment_conecs'), 'labelClass'=>'eContent2')); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent1" colspan="2">
            <?= $this->form->display_hiddenInput(array('name'=>'EnablePassRestaurant', 'default'=>"0")); ?>
            <?= $this->form->display_checkBoxInput(array('name'=>'EnablePassRestaurant', 'value'=>1, 'label'=>$this->get_translation('payment_passrestaurant'), 'labelClass'=>'eContent2')); ?>
        </td>
        <td class="eTableLine0 eContent1" colspan="2">
            <?= $this->form->display_hiddenInput(array('name'=>'EnableUpChequeDejeuner', 'default'=>"0")); ?>
            <?= $this->form->display_checkBoxInput(array('name'=>'EnableUpChequeDejeuner', 'value'=>1, 'label'=>$this->get_translation('payment_upchequedejeuner'), 'labelClass'=>'eContent2')); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent1" colspan="2">
            <?= $this->form->display_hiddenInput(array('name'=>'EnableApetiz', 'default'=>"0")); ?>
            <?= $this->form->display_checkBoxInput(array('name'=>'EnableApetiz', 'value'=>1, 'label'=>$this->get_translation('payment_apetiz'), 'labelClass'=>'eContent2')); ?>
        </td>
        <td class="eTableLine0 eContent1" colspan="2">
            <?= $this->form->display_hiddenInput(array('name'=>'EnableSwile', 'default'=>"0")); ?>
            <?= $this->form->display_checkBoxInput(array('name'=>'EnableSwile', 'value'=>1, 'label'=>$this->get_translation('payment_swile'), 'labelClass'=>'eContent2')); ?>
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
