<?php
/**
 * @brief Admin_Group Module admin edit group layout.
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
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div id="itemgeneral" style="display:block;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <?php if ( $this->group->_libError != '' ) : ?>
        <tr>
            <td class="error" colspan="2">
                <?= $this->get_translation($this->group->_libError); ?>
            </td>
        </tr>
        <?php endif; ?>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_name'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if ($this->group->is_new == 1) : ?>
                    <input type="text" name="name" value="<?= addslashes($this->group->name); ?>" maxlength="16" class="inputs"/>
                <?php else : ?>
                    <?= $this->group->name; ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_description'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <input type="text" name="description" value="<?= addslashes($this->group->description); ?>" maxlength="64" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="vertical-align:top;">
                <?= $this->get_translation('formitem_users'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->input->display(); ?>
            </td>
        </tr>

    </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>

