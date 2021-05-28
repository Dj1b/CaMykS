<?php
/**
 * @brief Content_GenericGallery module, admin edit item layout
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title.' : '.$this->imageitem->vars['name'].' [ '.$this->imageitem->id.' ] '); ?>
<?= $this->theme->get_boxTabsBar($this->tabs, $this->tabObject.'.mouseclick', $this->tabObject.'.mouseover', $this->tabObject.'.mouseout', 'general'); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div id="itemgeneral" style="display:block;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px">
                <?= $this->get_translation('itemname'); ?>
            </td>
            <td class="eTableLine0">
                <input type="text" name="name" value="<?= $this->imageitem->vars['name']; ?>" maxlength="32" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('image'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_fileInput('image', $this->imageitem->vars['image'], $this->get_fileInputButtons()); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('maxfilesize', file_getFileSize($this->maxfilesize)); ?>
            </td>
            <td class="eTableLine0">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('thumb'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_fileInput('thumb', $this->imageitem->vars['thumb'], $this->get_fileInputButtons()); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('maxfilesize', file_getFileSize($this->maxfilesize)); ?>
            </td>
            <td class="eTableLine0">
                &nbsp;
            </td>
        </tr>
    </table>
</div>

<?php foreach ($camyks->site_conf['editing_languages'] as $l) : ?>
    <div id="item<?= $l; ?>" style="display:none;" class="adminContentPanel">
        <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
            <tr>
                <td class="eTableLine0 eContent2" style="width:150px">
                    <?= $this->get_translation('itemtitle'); ?>
                </td>
                <td class="eTableLine0">
                    <input type="text" name="title_<?= $l; ?>" value="<?= $this->imageitem->vars['title_'.$l]; ?>" maxlength="128" class="inputs" />
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('description'); ?>
                </td>
                <td class="eTableLine1">
                    <textarea cols="24" rows="8" name="description_<?= $l; ?>" class="inputs"><?= $this->imageitem->vars['description_'.$l] ?></textarea>
                </td>
            </tr>
        </table>
    </div>
<?php endforeach; ?>

 <?php if ($this->help != null) : ?>
    <div id="itemhelp" style="display:none;" class="adminContentPanel">
        <?php $this->display_help(); ?>
    </div>
<?php endif; ?>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
