<?php
/**
 * @brief Admin_GenericGlossaryManager Module admin main layout.
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
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itemcontacts" style="display:<?= $this->tabBuilder->get_tabDisplay('contacts'); ?>;" class="adminContentPanel">
    <?= $this->listContact->display('head'); ?>
    <?= $this->listContact->display('list'); ?>
</div>

<?php if ($this->check_right(1)) : ?>
<div id="itemcategories" style="display:<?= $this->tabBuilder->get_tabDisplay('categories'); ?>;" class="adminContentPanel">
    <?= $this->listCategory->display('head'); ?>
    <?= $this->listCategory->display('list'); ?>
</div>
<?php endif; ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
