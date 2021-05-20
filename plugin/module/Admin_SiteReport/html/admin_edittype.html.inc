<?php
/**
 * @brief Admin_SiteReport Module admin edit type layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2007
 * @date Modification: May 2021
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
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0">
                <?= $camyks->get_translation ('name'); ?> :
            </td>
            <td class="eTableLine0">
                <input type="text" name="name" value="<?= $this->rtype->vars['name']; ?>" maxlength="16" class="inputs" />
            </td>
        </tr>
        <?php $alt=1; ?>
        <?php foreach ($camyks->get_confValue('editing_languages') as $l) : ?>
            <tr>
                <td class="eTableLine<?= $alt; ?>">
                    <?= $this->get_translation('localetitle', $l); ?> :
                </td>
                <td class="eTableLine<?= $alt; ?>">
                    <input type="text" name="title_<?= $l; ?>" value="<?= $this->rtype->vars['title_'.$l]; ?>" maxlength="64" class="inputs" />
                </td>
            </tr>
            <?php $alt = abs($alt-1); ?>
        <?php endforeach; ?>
    </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
