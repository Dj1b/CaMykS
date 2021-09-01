<?php
/**
 * @brief Content_GenericSiteMap module, admin layout.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title.' : '.$this->smItem->vars['name'].' [ '.$this->smItem->id.' ] '); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine1" style="width:150px">
                 <?= $this->get_translation('itemname'); ?>
            </td>
            <td class="eTableLine1">
                <input type="text" name="name" value="<?= $this->smItem->vars['name']; ?>" maxlength="32" class="inputs" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" style="width:150px;">
                <?= $this->get_translation('itemlayout'); ?>
            </td>
            <td class="eTableLine0">
                <select name="layout" class="inputs">
                    <?php foreach ($this->layouts as $name => $title) : ?>
                        <option value="<?= $name; ?>"<?= $name == $this->smItem->vars['layout'] ? ' selected="selected"' : ''; ?>>
                            <?= $title; ?>
                        </option>
                    <?php endforeach; ?>
                </select>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1" style="width:150px;">
                <?= $this->get_translation('itemcolumns'); ?>
            </td>
            <td class="eTableLine1">
                <input type="text" name="columns" value="<?= $this->smItem->vars['columns']; ?>" maxlength="1" class="inputs" />
            </td>
        </tr>
    </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
