<?php
/**
 * @brief GenericSitemapGenerator Input configuration view layout.
 * @details Plugin / Input layout
 * @file plugin/input/GenericSitemapGenerator/html/configuration/view.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2019
 * @date Modification: Feb 2019
 * @copyright 2019 CaMykS Team
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
                <?= $this->get_translation('formtitle_update'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $this->get_translation('formitem_method'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'update_method', 'values'=>$this->config->get_updateMethodList())); ?>
            </td>
        </tr>
    </table>
    <div id="updateMethod0" style="display:block;">
        <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
            <tr>
                <td class="eTableLine1 eContent2" style="width:150px;">
                    <?= $this->get_translation('formitem_mode'); ?>
                </td>
                <td class="eTableLine1 eContent1">
                    <?= $this->form->display_selectInput(array('name'=>'update_mode', 'values'=>$this->config->get_updateModeList(), 'onchange'=>'ConfigEditor.check_updateModeStatus();')); ?>
                </td>
            </tr>
        </table>
        <div id="updateMode1" style="display:none;">
            <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
                <tr>
                    <td class="eTableLine0 eContent2" style="width:150px;">
                        <?= $this->get_translation('formitem_delay'); ?>
                    </td>
                    <td class="eTableLine0 eContent1">
                        <?= $this->form->display_textInput(array('name'=>'update_delayValue', 'class'=>'vsinputs')); ?>
                        <?= $this->form->display_selectInput(array('name'=>'update_delayUnit', 'values'=>$this->config->get_updateDelayUnitList(), 'class'=>'sinputs')); ?>
                    </td>
                </tr>
            </table>
        </div>
    </div>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
