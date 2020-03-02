<?php
/**
 * @brief Content_GenericLegalMentions Module admin, edit owner sub layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2020
 * @date Modification: Feb 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td class="eTableLine0 eContent2" style="width:150px">
            <?= $camyks->get_translation('formitem_name'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('owner_name'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $camyks->get_translation('formitem_type'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_selectInput(array('name'=>'owner_type', 'values'=>$this->contentItem->get_ownerTypeList())); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_manager'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2">
            <?= $camyks->get_translation('formitem_name'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('owner_managername'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $camyks->get_translation('formitem_email'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput(array('name'=>'owner_manageremail', 'class'=>'linputs')); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_contacts'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2">
            <?= $camyks->get_translation('formitem_address'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput(array('name'=>'owner_address', 'class'=>'vlinputs')); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $camyks->get_translation('formitem_phone'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput('owner_phone'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2">
            <?= $camyks->get_translation('formitem_fax'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('owner_fax'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $camyks->get_translation('formitem_email'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput(array('name'=>'owner_email', 'class'=>'linputs')); ?>
        </td>
    </tr>
</table>

<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_details'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2" style="width:150px;">
            <?= $this->get_translation('formitem_legalform'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('owner_company_legalform'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_capital'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput('owner_company_capital'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_vat'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('owner_company_vat'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_siret'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput('owner_company_siret'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2">
            <?= $this->get_translation('formitem_registerednumber'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('owner_company_rcsnum'); ?>
            <?= $this->get_translation('formitem_at'); ?>
            <?= $this->form->display_textInput('owner_company_rcsloc'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_naf'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->form->display_textInput('owner_company_naf'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_legal'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2" style="width:150px;">
            <?= $this->get_translation('formitem_tribunal'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->form->display_textInput('law_tribunal'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>
</table>

<?= $this->theme->get_boxTabsBar($this->ownerTabs->tabs, $this->ownerTabs->jsParams); ?>

<?php foreach ($camyks->get_confValue('editing_languages') as $l) : ?>
    <div id="itemOwner<?= $l?>" style="display:<?= $this->ownerTabs->get_tabDisplay('Owner'.$l); ?>;" class="adminContentPanel">
        <?php $this->editor->set_contentInfos('text', $this->contentItem->vars['owner_additional_'.$l]); ?>
        <?php $this->editor->set_textareaInfos('owner_additional_'.$l, '100%', '400px'); ?>
        <?php $this->editor->display(); ?>
    </div>
<?php endforeach; ?>

