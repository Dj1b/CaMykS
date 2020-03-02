<?php
/**
 * @brief Admin_GenericGlossaryManager Module main layout
 * @details Plugin, Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2010
 * @date Modification: Feb 2020
 * @copyright 2010 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>

<div id="itemDefinitions" style="display:<?= $this->tabBuilder->get_tabDisplay('Definitions')?>;" class="adminContentPanel">
    <?= $this->listDefinition->display('head'); ?>
    <?= $this->listDefinition->display('list'); ?>
</div>

<div id="itemCategories" style="display:<?= $this->tabBuilder->get_tabDisplay('Categories')?>;" class="adminContentPanel">
    <?= $this->listCategory->display('head'); ?>
    <?= $this->listCategory->display('list'); ?>
</div>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
