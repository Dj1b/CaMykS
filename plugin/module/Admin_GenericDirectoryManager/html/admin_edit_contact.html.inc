<?php
/**
 * @brief Admin_GenericGlossaryManager Module admin edition contact layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$file = $this->theme->get_pictURL('file', 12, 'std');
$file_ = $this->theme->get_pictURL('file', 12, 'ovr');
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->editform->display_header(); ?>
<?= $this->editform->display_hiddens(); ?>
<div id="itemproperties" style="display:<?= $this->tabBuilder->get_tabDisplay('properties'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $camyks->get_translation('formitem_status'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editform->display_selectInput(array('name'=>'status', 'values'=>$this->get_definitionStatusList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_category'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->editform->display_selectInput(array('name'=>'category', 'values'=>$this->categoryList)); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_link'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editform->display_textInput('link'); ?>
                &nbsp;
                <a href="javascript:glossarymanager_selectButtonLink(<?= $i?>);" class="img">
                    <img src="<?= $file?>" alt="<?= $this->get_translation('select_sitepage'); ?>" title="<?= $this->get_translation('select_sitepage'); ?>" onmouseover="this.src='<?= $file_?>';" onmouseout="this.src='<?= $file?>';" />
                </a>
            </td>
        </tr>
    </table>
</div>

<?php foreach ($this->lgs as $l) : ?>
    <div id="item<?= $l; ?>" style="display:<?= $this->tabBuilder->get_tabDisplay($l); ?>;" class="adminContentPanel">
        <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
            <tr>
                <td class="eTableLine0 eContent2" style="width:150px;">
                    <?= $this->get_translation('formitem_word'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->editform->display_textInput(array('name'=>'word', 'language'=>$l)); ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine1 eContent2" colspan="2">
                    <?= $camyks->get_translation('formitem_description'); ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine1 eContent1" colspan="2">
                    <?php $this->editor->set_contentInfos('text', $this->definitionItem->vars['description_'.$l]); ?>
                    <?php $this->editor->set_textareaInfos('description_'.$l, '100%', '300px'); ?>
                    <?php $this->editor->display(); ?>
                </td>
            </tr>
        </table>
    </div>
<?php endforeach; ?>

<?= $this->editform->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
