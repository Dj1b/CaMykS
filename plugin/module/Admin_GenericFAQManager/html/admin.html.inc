<?php
/**
 * @brief Admin_GenericFAQManager Module admin main layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Feb 2020
 * @date Modification: Feb 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title) ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs,$this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent1Header(); ?>

<div id="itemQuestions" style="display:<?= $this->tabBuilder->get_tabDisplay('Questions')?>;" class="adminContentPanel">
    <?= $this->questionList->display('head'); ?>
    <?= $this->questionList->display('list'); ?>
</div>

<div id="itemFamilies" style="display:<?= $this->tabBuilder->get_tabDisplay('Families')?>;" class="adminContentPanel">
    <?= $this->familyList->display('head'); ?>
    <?= $this->familyList->display('list'); ?>
</div>

<?php if ($this->help != null) : ?>
    <div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help')?>;" class="adminContentPanel">
        <?php $this->display_help(); ?>
    </div>
<?php endif; ?>

<?= $this->theme->get_boxContent1Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
