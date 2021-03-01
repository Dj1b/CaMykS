<?php
/**
 * @brief Admin_GooglePoIMapManager Module admin edit configuration layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->configform->display_header(); ?>
<?= $this->configform->display_hiddens(); ?>
<div id="itemproperties" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $this->get_translation('formitem_googlemapapikey'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->configform->display_textAreaInput('google_mapapikey'); ?>
            </td>
        </tr>

    </table>
</div>
<?= $this->configform->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
