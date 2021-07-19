<?php
/**
 * @brief Content_GenericRandomText module, admin edit item layout.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2007
 * @date Modification: Jul 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $this->get_translation('formitem_name'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                <input type="text" name="name" value="<?= $this->gitem->vars['name']; ?>" class="inputs" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_weight'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <input type="text" name="weight" value="<?= $this->gitem->vars['weight']; ?>" class="inputs" />
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->get_translation('itemweightalt'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_content'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                <textarea name="content" cols="40" rows="8" class="vlinputs"><?= $this->gitem->vars['content']; ?></textarea>
            </td>
        </tr>
    </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
