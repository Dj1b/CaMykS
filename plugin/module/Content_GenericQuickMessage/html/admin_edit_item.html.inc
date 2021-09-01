<?php
/**
 * @brief Content_GenericQuickMessage module, admin edit item layout.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2007
 * @date Modification: Jul 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title.' : '.$this->qmlist->vars['name'].' [ '.$this->qmlist->id.' ] '); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine1 content2" colspan="2">
                <?= $this->get_translation('itemid', $this->qmitem->id); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0" style="width:150px;">
                <?= $this->get_translation('state'); ?> :
            </td>
            <td class="eTableLine0">
                <select name="status" class="inputs">
                    <?php foreach ($this->qmitem->get_statusValueList() as $value=>$title) : ?>
                        <option value="<?= $value; ?>"<?= $value == $this->qmitem->vars['status'] ? ' selected="selected"' : ''; ?>>
                            <?= $title; ?>
                        </option>
                    <?php endforeach; ?>
                </select>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1">
                <?= $this->get_translation('messageauthor'); ?> :
            </td>
            <td class="eTableLine1">
                <input type="text" name="author" value="<?= $this->qmitem->vars['author']; ?>" maxlength="64" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine0">
                <?= $this->get_translation('messageemail'); ?> :
            </td>
            <td class="eTableLine0">
                <input type="text" name="email" value="<?= $this->qmitem->vars['email']; ?>" maxlength="255" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine1">
                <?= $this->get_translation('date'); ?> :
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_dateInput($this->qmitem->vars['ndate'], 'ndate'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0">
                <?= $this->get_translation('messagetitle'); ?> :
            </td>
            <td class="eTableLine0">
                <input type="text" name="title" value="<?= $this->qmitem->vars['title']; ?>" maxlength="255" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine1">
                <?= $this->get_translation('messagecontent'); ?> :
            </td>
            <td class="eTableLine1">
                <textarea cols="40" rows="6" name="message"><?= $this->qmitem->vars['message']; ?></textarea>
            </td>
        </tr>
    </table>
    <?= $this->form->display_footer(); ?>
</div>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
