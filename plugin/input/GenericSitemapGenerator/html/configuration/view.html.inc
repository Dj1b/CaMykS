<?php
/**
 * @brief GenericSitemapGenerator Input configuration view layout.
 * @details Plugin / Input layout
 * @file plugin/input/GenericSitemapGenerator/html/configuration/view.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2019
 * @date Modification: Feb 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_update'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $this->get_translation('formitem_method'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_updateMethodTitle(); ?>
            </td>
        </tr>
        <?php if ($this->config->get_value('update_method') == 0) : ?>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_mode'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->get_updateModeTitle(); ?>
            </td>
        </tr>
        <?php if ($this->config->get_value('update_mode') == 0) : ?>
        <tr>
            <td class="eTableLine0" colspan="2">
                <?= $camyks->theme->get_button(array('title'=>$this->get_translation('update_now'), 'url'=>'javascript:ConfigViewer.initiate_writeSitemap();', 'id'=>'UpdateButton')); ?>
            </td>
        </tr>
        <?php else : ?>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_delay'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_updateDelayTitle(); ?>
            </td>
        </tr>

        <?php endif; ?>
        <?php endif; ?>

        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_lastupdate'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_date'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if ($this->config->get_value('lastUpdate_date') < 3600) : ?>
                    --
                <?php else : ?>
                    <?= date_displayLongDayDateHour($this->config->get_value('lastUpdate_date')); ?>
                <?php endif; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_pages'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?php if ($this->config->get_value('lastUpdate_date') < 3600) : ?>
                    --
                <?php else : ?>
                    <?= $this->config->get_value('lastUpdate_pages'); ?>
                <?php endif; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_duration'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if ($this->config->get_value('lastUpdate_date') < 3600) : ?>
                    --
                <?php else : ?>
                    <?= $this->config->vars['lastUpdate_duration']; ?> ms
                <?php endif; ?>
            </td>
        </tr>
    </table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
