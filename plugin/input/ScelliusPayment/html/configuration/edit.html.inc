<?php
/**
 * @brief ScelliusPayment Input, edit configuration layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Aug 2021
 * @date Modification: Aug 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
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
            <?= $this->form->display_selectInput(array('name'=>'ctx_mode', 'values'=>$this->config->get_modeList())); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_bankkeys'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_test'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput(array('name'=>'bankKey_test', 'class'=>'linputs', 'maxlength'=>255)); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_live'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput(array('name'=>'bankKey_live', 'class'=>'linputs', 'maxlength'=>255)); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_bankconfiguration'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_site'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput(array('name'=>'site_id')); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_hashmode'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_selectInput(array('name'=>'hash_mode', 'values'=>$this->config->get_hashModeList())); ?>
        </td>
    </tr>
</table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
