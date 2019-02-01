<?php
/**
 * @brief PayZenPayment Input configuration edit layout
 * @details Plugin / Input layout
 * @file plugin/input/PayZenPayment/html/configuration/edit.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Dec 2018
 * @date Modification: Dec 2018
 * @copyright 2018 CaMykS Team
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
<?php
/**
 * @endcond Exclude
 */
?>
