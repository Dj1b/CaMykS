<?php
/**
 * @brief Admin_GenericDownloadManager Module admin edit document layout.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2008
 * @date Modification: Dec 2020
 * @copyright 2008 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader('width:600px;margin:0 auto;'); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->editform->display_header(); ?>
<?= $this->editform->display_hiddens(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $camyks->get_translation('formitem_status'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editform->display_selectInput(array('name'=>'active', 'values'=>$this->get_documentStatusList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_language'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->editform->display_selectInput(array('name'=>'lg', 'values'=>$this->get_languageList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_category'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editform->display_selectInput(array('name'=>'category', 'values'=>$this->categoryList)); ?>
            </td>
        </tr>

        <?php $alt = 1; ?>
        <?php foreach ($camyks->get_confValue('editing_languages') as $l) : ?>
            <tr>
                <td class="eTableLine<?= $alt; ?> eContent2">
                    <img src="<?= language_getIcon($l, false); ?>" alt="<?= $l; ?>" style="float:right;" />
                    <?= $camyks->get_translation('formitem_title'); ?>
                </td>
                <td class="eTableLine<?= $alt; ?> eContent1">
                    <?= $this->editform->display_textInput(array('name'=>'title', 'language'=>$l)); ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine<?= $alt; ?> eContent2">
                    <img src="<?= language_getIcon($l, false); ?>" alt="<?= $l; ?>" style="float:right;" />
                    <?= $camyks->get_translation('formitem_description'); ?>
                </td>
                <td class="eTableLine<?= $alt; ?> eContent1">
                    <?= $this->editform->display_textInput(array('name'=>'subtitle', 'language'=>$l)); ?>
                </td>
            </tr>
            <?php $alt = abs($alt-1); ?>
        <?php endforeach; ?>

        <tr>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $camyks->get_translation('formitem_date'); ?>
            </td>
            <td class="eTableLine<?= $alt; ?> eContent1">
                <?= $this->editform->display_dateInput(array('name'=>'releasedate', 'objects'=>array('day', 'month', 'year'))); ?>
            </td>
        </tr>

        <?php $alt = abs($alt-1); ?>

        <tr>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $this->get_translation('formitem_filetitle'); ?>
            </td>
            <td class="eTableLine<?= $alt; ?> eContent1">
                <?= $this->editform->display_textInput(array('name'=>'filetitle')); ?>
            </td>
        </tr>

        <?php $alt = abs($alt-1); ?>

        <tr>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $this->get_translation('document_file'); ?> (<?= $this->get_translation('maxfilesize', file_getFileSize($this->config->vars['file_size']*1024*1024)); ?>)
            </td>
            <td class="eTableLine<?= $alt; ?> eContent1">
                <?= $this->editform->display_fileInput('file'); ?>
            </td>
        </tr>

        <?php if ($this->documentItem->id > 0) : ?>
            <?php $alt = abs($alt-1); ?>
            <tr>
                <td class="eTableLine<?= $alt; ?> eContent2">
                    <?= $this->get_translation('document_url'); ?>
                </td>
                <td class="eTableLine<?= $alt; ?> eContent1">
                    <?= $this->documentItem->get_link(); ?>
                </td>
            </tr>
        <?php endif; ?>
    </table>
</div>
<?= $this->editform->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
