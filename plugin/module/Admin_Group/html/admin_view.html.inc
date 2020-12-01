<?php
/**
 * @brief Admin_Group Module admin view group layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Mar 2007
 * @date Modification: Dec 2020
 * @copyright 2007 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->get_translation('group').' : '.$this->group->name); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $this->get_translation('formitem_description'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->group->description; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_users'); ?>
            </td>
            <?php $first = true; ?>
            <?php $alt = 1; ?>
            <?php foreach ($this->group->users as $u) : ?>
                <?php if ($first) : ?>
                    <?php $first = false; ?>
                <?php else : ?>
                    <tr>
                        <td class="eTableLine0 eContent1">
                            &nbsp;
                        </td>
                <?php endif; ?>
                <td class="eTableLine<?= $alt; ?> eContent1">
                    <?= $u; ?>
                </td>
            </tr>
            <?php $alt = abs($alt-1); ?>
        <?php endforeach; ?>
    </table>
</div>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
