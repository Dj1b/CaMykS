<?php
/**
 * @brief PayBoxPayment Input configuration edit layout
 * @details Plugin / Input layout
 * @file plugin/input/PayBoxPayment/html/configuration/edit.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2018
 * @date Modification: May 2020
 * @copyright 2018 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?=$camyks->theme->get_boxContent2Header();?>
<div class="adminContentPanel">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_operation'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2" style="width:160px;">
            <?=$this->get_translation('formitem_mode');?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->form->display_selectInput(array('name'=>'bankMode', 'values'=>$this->config->get_modeList())); ?>
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
            <?=$this->get_translation('formitem_test');?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->form->display_textInput(array('name'=>'bankKey_Test', 'class'=>'linputs', 'maxlength'=>255));?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?=$this->get_translation('formitem_live');?>
        </td>
        <td class="eTableLine1 eContent1">
            <?=$this->form->display_textInput(array('name'=>'bankKey_Live', 'class'=>'linputs', 'maxlength'=>255));?>
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
            <?=$this->get_translation('formitem_site');?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->form->display_textInput(array('name'=>'site'));?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?=$this->get_translation('formitem_rang');?>
        </td>
        <td class="eTableLine1 eContent1">
            <?=$this->form->display_textInput(array('name'=>'rang'));?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?=$this->get_translation('formitem_identifiant');?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->form->display_textInput(array('name'=>'identifiant'));?>
        </td>
    </tr>
</table>
</div>
<?=$camyks->theme->get_boxContent2Footer();?>
<?php
/**
 * @endcond Exclude
 */
?>
