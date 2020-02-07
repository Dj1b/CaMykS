<?php
/**
 * @brief Content_GenericLegalMentions Module admin main layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2020
 * @date Modification: Jan 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title.' : '. $this->contentItem->vars['name'].' [ ' .$this->contentItem->id . ' ] '); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
    <?= $this->form->display_header(); ?>
    <?= $this->form->display_hiddens(); ?>

    <div id="itemProperties" style="display:<?= $this->tabBuilder->get_tabDisplay('Properties'); ?>;" class="adminContentPanel">
        <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
            <tr>
                <td class="eTableLine0 eContent2" style="width:150px">
                    <?= $camyks->get_translation('formitem_name'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->form->display_textInput('name'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_lastupdate'); ?>
                </td>
                <td class="eTableLine1 eContent1">
                    <?php if ($this->contentItem->id == 0) : ?>
                        --
                    <?php else : ?>
                        <?= date_displayLongDateHour($this->contentItem->vars['updateDate']); ?>
                    <?php endif; ?>
                </td>
            </tr>

            <tr>
                <td colspan="2">
                    &nbsp;
                </td>
            </tr>

            <tr>
                <td colspan="2" class="eTableHeader">
                    <?= $this->get_translation('formtitle_page'); ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine0 eContent2" >
                    &nbsp;
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->form->display_checkboxInput(array('name'=>'defaultPage', 'value'=>1, 'label'=>$this->get_translation('defineaslegalmentionsdefaultpage'), 'labelClass'=>'eContent2', 'disabled'=>($this->contentItem->vars['defaultPage'] == 1))); ?>
                </td>
            </tr>
        </table>
    </div>

    <div id="itemOwner" style="display:<?= $this->tabBuilder->get_tabDisplay('Owner'); ?>;" class="adminContentPanel">
        <?php $this->load_file('html/admin/edit_owner.html.inc'); ?>
    </div>

    <div id="itemCreator" style="display:<?= $this->tabBuilder->get_tabDisplay('Creator'); ?>;" class="adminContentPanel">
        <?php $this->load_file('html/admin/edit_creator.html.inc'); ?>
    </div>

    <div id="itemWebmasterDPO" style="display:<?= $this->tabBuilder->get_tabDisplay('WebmasterDPO'); ?>;" class="adminContentPanel">
        <?php $this->load_file('html/admin/edit_webmasterdpo.html.inc'); ?>
    </div>

    <div id="itemHost" style="display:<?= $this->tabBuilder->get_tabDisplay('Host'); ?>;" class="adminContentPanel">
        <?php $this->load_file('html/admin/edit_host.html.inc'); ?>
    </div>

    <?php foreach ($camyks->get_confValue('editing_languages') as $l) : ?>
        <div id="item<?= $l?>" style="display:<?= $this->tabBuilder->get_tabDisplay($l); ?>;" class="adminContentPanel">
            <?php $this->editor->set_contentInfos('text', $this->contentItem->vars['additional_content_'.$l]); ?>
            <?php $this->editor->set_textareaInfos('additional_content_'.$l, '100%', '400px'); ?>
            <?php $this->editor->display(); ?>
        </div>
    <?php endforeach; ?>

    <?= $this->form->display_footer(); ?>

    <?php if ($this->help != null) : ?>
        <div id="itemhelp" class="adminContentPanel" style="display:none;">
            <?php $this->display_help() ?>
        </div>
    <?php endif; ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
