<?php
/**
 * @brief Admin_GenericMediaLibraryManager Module admin edit picture gallery layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.1
 * @date Creation: Jun 2015
 * @date Modification: Jan 2021
 * @copyright 2015 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$flags = array();
if (count($lgs = $camyks->get_confValue('editing_languages')) > 1 )
    foreach ($lgs as $l)
        $flags[$l] = '<img src="'.language_getIcon($l, false).'" alt="" border="0" style="float:right;" />';
else
    foreach ($lgs as $l)
        $flags[$l] = '';
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header( ); ?>
<?= $this->editform->display_header(); ?>
<?= $this->editform->display_hiddens(); ?>

<div id="itemProperties" style="display:<?= $this->tabBuilder->get_tabDisplay('Properties'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $camyks->get_translation('formitem_status'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->editform->display_selectInput(array('name'=>'status', 'values'=>$this->get_pictureGalleryStatusList())); ?>
            </td>
        </tr>

        <?php foreach ($lgs as $l) : ?>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $flags[$l]; ?>
                    <?= $camyks->get_translation('formitem_title'); ?>
                </td>
                <td class="eTableLine1 eContent1">
                    <?= $this->editform->display_textInput(array('name'=>'title', 'language'=>$l)); ?>
                </td>
            </tr>
        <?php endforeach; ?>

        <?php foreach ($lgs as $l) : ?>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $flags[$l]; ?>
                    <?= $this->get_translation('formitem_summary'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->editform->display_textAreaInput(array('name'=>'summary', 'language'=>$l, 'class'=>'linputs mceNoEditor')); ?>
                </td>
            </tr>
        <?php endforeach; ?>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $camyks->get_translation('formitem_date'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->editform->display_dateInput(array('name'=>'cdate', 'objects'=>array('year', 'month', 'day'))); ?>
            </td>
        </tr>

    </table>
</div>

<div id="itemPictures" style="display:<?= $this->tabBuilder->get_tabDisplay('Pictures'); ?>;" class="adminContentPanel">
    <div style="float:right; width:<?= $this->previewWidth + 2; ?>px; margin:27px 0 0 8px;" class="hiddenOnMobile">
          <div id="picturePreview" style="border:solid 1px #6a798b; font-size:0;">
            <img src="<?= $this->get_fileURL('img/preview.jpg'); ?>" alt="" style="max-width:<?= $this->previewWidth; ?>px;" />
          </div>
          <div class="eTableHeader">
            <?= $this->get_translation('photo_preview'); ?>
          </div>
    </div>
    <div class="fullWidthOnMobile" style="margin-right:<?= $this->previewWidth+10; ?>px;">
          <?= $this->pictureList->display('head'); ?>
          <?= $this->pictureList->display('list'); ?>
    </div>
</div>

<?php foreach($lgs as $l ) : ?>
    <div id="item<?= $l?>" style="display:<?= $this->tabBuilder->get_tabDisplay($l); ?>" class="adminContentPanel">
        <?php $this->input->set_contentInfos('text', $this->pictureGalleryItem->vars['content_'.$l] ); ?>
        <?php $this->input->set_textareaInfos('content_'.$l, '100%', '400px'); ?>
        <?php $this->input->display(); ?>
    </div>
<?php endforeach; ?>

<?= $this->editform->display_footer(); ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
