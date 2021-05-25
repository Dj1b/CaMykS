<?php
/**
 * @brief Content_GenericFaq module, admin edit item layout
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 Ideogram Design
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title.' : '.$this->get_translation('editanitem')); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div id="itemproperties" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" width="100%">
        <tr>
            <td class="eTableLine0">
                <?= $this->get_translation('faqtitle'); ?> :
            </td>
            <td class="eTableLine0">
                <input type="text" name="title" value="<?= $this->faqitem->vars['title']; ?>" maxlength="128" class="inputs" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine1">
                <?= $this->get_translation('status'); ?> :
            </td>
            <td class="eTableLine1">
                <select name="status">
                    <?php foreach ($this->status as $i => $v) : ?>
                        <option value="<?= $i; ?>"<?= ($i == $this->faqitem->vars['status'] ? 'selected="selected"' : ''); ?>><?= $this->get_translation($v); ?></option>
                    <?php endforeach; ?>
                </select>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0">
                <?= $this->get_translation('language'); ?> :
            </td>
            <td class="eTableLine0">
                <select name="language">
                    <?php foreach ($camyks->get_confValue('editing_languages') as $l) : ?>
                        <option value="<?= $l; ?>"<?= ($l==$this->faqitem->vars['language'] ? 'selected="selected"' : ''); ?>><?= $l; ?></option>
                    <?php endforeach; ?>
                </select>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1">
                <?= $this->get_translation('content'); ?> :
            </td>
            <td class="eTableLine1">
                <textarea name="content" cols="40" rows="8"><?= $this->faqitem->vars['content']; ?></textarea>
            </td>
        </tr>
    </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
