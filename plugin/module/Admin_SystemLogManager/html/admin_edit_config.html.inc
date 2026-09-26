<?php
/**
 * @brief Admin_SystemLogManager module, edit configuration admin layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jun 2018
 * @date Modification: Sep 2026
 * @copyright 2018 - 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>

<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>

<div id="itemConfiguration" style="display:<?=$this->tabBuilder->get_tabDisplay('Configuration'); ?>" class="adminContentPanel">
    <?php $this->load_file('html/Configuration/Edit.html.inc'); ?>
</div>
<?php if (!is_null($this->help)) : ?>
    <div id="itemhelp" style="display:<?=$this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
        <?php $this->display_help(); ?>
    </div>
<?php endif; ?>

<?= $this->form->display_footer(); ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>

<?php
/**
 * @endcond Exclude
 */
?>
