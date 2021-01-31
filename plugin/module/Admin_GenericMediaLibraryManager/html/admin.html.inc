<?php
/**
 * @brief Admin_GenericMediaLibraryManager Module admin main layout.
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
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>

<div id="itemPictureGalleries" style="display:<?= $this->tabBuilder->get_tabDisplay('PictureGalleries');?>;" class="adminContentPanel">
    <?= $this->pictureGalleryList->display('head');?>
    <?= $this->pictureGalleryList->display('list');?>
</div>

<?php if ($this->check_right(1) === true) : ?>
<div id="itemConfiguration" style="display:<?= $this->tabBuilder->get_tabDisplay('Configuration');?>;" class="adminContentPanel">
    <?php $this->load_file('html/configuration/admin_view.html.inc');?>
</div>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
