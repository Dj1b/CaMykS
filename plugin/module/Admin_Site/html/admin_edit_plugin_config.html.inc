<?php
/**
 * @brief Admin_Site Module admin edit plugin configuration layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_Site/html/admin_edit_plugin_config.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2018
 * @date Modification: Nov 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule', 'style'=>'width:800px; margin:0 auto;')); ?>
<?= $this->theme->get_boxTitleBar($this->get_translation('formtitle_pluginconfig', $this->plugin->title)); ?>

<?= $this->plugin->display_configEdition(); ?>

<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
<?= $this->form->display_footer(); ?>
