<?php
/**
 * @brief Admin_GenericSearchEngineManager module, admin edit configuration layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2026
 * @date Modification: Sep 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
$flags = array();
if (count($camyks->get_confValue('editing_languages')) > 1 )
    foreach ($camyks->get_confValue('editing_languages') as $l)
        $flags[$l] = '<img src="'.language_getIcon($l, false).'" alt="" style="float:right;" />';
else
    foreach ($camyks->get_confValue('editing_languages') as $l)
        $flags[$l] = '';


?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="4">
                <?= $this->get_translation('formtitle_indexing'); ?>
            </td>
        </tr>

        <?php foreach ($camyks->get_confValue('editing_languages') as $l) : ?>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $flags[$l]; ?>
                <?= $this->get_translation('formitem_excludedwords'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="3">
                <?= $this->editForm->display_textAreaInput(array('name'=>'Indexing_ExcludedWords', 'class'=>'vlinputs', 'language'=>$l)); ?>
            </td>
        </tr>
        <?php endforeach; ?>
        <tr>
            <td class="eTableLine1 eContent2" style="width:170px;">
                <?= $this->get_translation('formitem_minwordlength'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->editForm->display_numberInput(array('name'=>'Indexing_WordMinLength', 'min'=>1, 'step'=>1, 'class'=>'sinputs')); ?>
            </td>
            <td class="eTableLine1 eContent2" style="width:165px;">
                <?= $this->get_translation('formitem_wordkeptchars'); ?>
            </td>
            <td class="eTableLine1 eContent1" >
                <?= $this->editForm->display_textInput(array('name'=>'Indexing_WordKeptChars', 'class'=>'sinputs')); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="4">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableSubHeader" colspan="4">
                <?= $this->get_translation('formtitle_maxwords'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_n1'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_numberInput(array('name'=>'Indexing_N1MaxWords', 'min'=>0, 'step'=>1, 'class'=>'sinputs')); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_n2'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_numberInput(array('name'=>'Indexing_N2MaxWords', 'min'=>0, 'step'=>1, 'class'=>'sinputs')); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="4">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableSubHeader" colspan="4">
                <?= $this->get_translation('formtitle_weights'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_n1'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_numberInput(array('name'=>'Indexing_N1Weight', 'min'=>0, 'step'=>1, 'class'=>'sinputs')); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_n2'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_numberInput(array('name'=>'Indexing_N2Weight', 'min'=>0, 'step'=>1, 'class'=>'sinputs')); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_n3'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_numberInput(array('name'=>'Indexing_N3Weight', 'min'=>0, 'step'=>1, 'class'=>'sinputs')); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="4">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="4">
                <?= $this->get_translation('formtitle_results'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_maximumcount'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_numberInput(array('name'=>'Results_MaximumCount', 'min'=>1, 'step'=>1, 'class'=>'sinputs')); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_countperpage'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_numberInput(array('name'=>'Results_CountPerPage', 'min'=>1, 'step'=>1, 'class'=>'sinputs')); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="4">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="4">
                <?= $this->get_translation('formtitle_logging'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_logqueries'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_selectInput(array('name'=>'Logging_LogQueries', 'values'=>$this->config->get_statusList(), 'class'=>'sinputs')); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_statqueries'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_selectInput(array('name'=>'Logging_StatQueries', 'values'=>$this->config->get_statusList(), 'class'=>'sinputs')); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="4">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="4">
                <?= $this->get_translation('formtitle_opensearchxml'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_status'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_selectInput(array('name'=>'OpenSearchXML_Status', 'values'=>$this->config->get_statusList(), 'class'=>'sinputs')); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_name'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_textInput(array('name'=>'OpenSearchXML_Name', 'class'=>'vlinputs', 'maxlength'=>16)); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_description'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->editForm->display_textInput(array('name'=>'OpenSearchXML_Description', 'class'=>'vlinputs', 'maxlength'=>128)); ?>
            </td>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_tags'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->editForm->display_textInput(array('name'=>'OpenSearchXML_Tags', 'class'=>'vlinputs', 'maxlength'=>128)); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_page'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_textInput(array('name'=>'OpenSearchXML_URLPage', 'class'=>'inputs', 'maxlength'=>32)); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_param'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_textInput(array('name'=>'OpenSearchXML_URLParam', 'class'=>'inputs', 'maxlength'=>32)); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_example'); ?>
            </td>
            <td class="eTableLine1 eContent1" colspan="3">
                <?= $this->editForm->display_textInput(array('name'=>'OpenSearchXML_Example', 'class'=>'inputs', 'maxlength'=>64)); ?>
            </td>
        </tr>
    </table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
