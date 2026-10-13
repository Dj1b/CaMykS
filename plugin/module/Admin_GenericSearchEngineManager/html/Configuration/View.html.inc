<?php
/**
 * @brief Admin_GenericSearchEngineManager module, admin view configuration layout.
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
                <?= $this->config->vars['Indexing_ExcludedWords_'.$l]; ?>
            </td>
        </tr>
        <?php endforeach; ?>
        <tr>
            <td class="eTableLine1 eContent2" style="width:170px;">
                <?= $this->get_translation('formitem_minwordlength'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->vars['Indexing_WordMinLength']; ?>
            </td>
            <td class="eTableLine1 eContent2" style="width:165px;">
                <?= $this->get_translation('formitem_wordkeptchars'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->vars['Indexing_WordKeptChars']; ?>
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
                <?= $this->config->vars['Indexing_N1MaxWords']; ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_n2'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->vars['Indexing_N2MaxWords']; ?>
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
                <?= $this->config->vars['Indexing_N1Weight']; ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_n2'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->vars['Indexing_N2Weight']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_n3'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->vars['Indexing_N3Weight']; ?>
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
                <?= $this->config->vars['Results_MaximumCount']; ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_countperpage'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->vars['Results_CountPerPage']; ?>
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
                <?= $this->config->get_statusTitle('Logging_LogQueries'); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_statqueries'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_statusTitle('Logging_StatQueries'); ?>
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
                <?= $this->config->get_statusTitle('OpenSearchXML_Status'); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_name'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->vars['OpenSearchXML_Name']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_description'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->vars['OpenSearchXML_Description']; ?>
            </td>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_tags'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->vars['OpenSearchXML_Tags']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_page'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->vars['OpenSearchXML_URLPage']; ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_param'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->vars['OpenSearchXML_URLParam']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_example'); ?>
            </td>
            <td class="eTableLine1 eContent1" colspan="3">
                <?= $this->config->vars['OpenSearchXML_Example']; ?>
            </td>
        </tr>
    </table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
