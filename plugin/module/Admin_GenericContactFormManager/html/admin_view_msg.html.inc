<?php
/**
 * @brief Admin_GenericContactFormManager Module view message layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxContent2Header()?>

<div id="itemproperties" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
        <tr>
            <td class="eTableLine1 eContent2" style="width:150px;">
                <?= $camyks->get_translation('formitem_status'); ?>
            </td>
            <td class="eTableLine1">
                <div style="float:right;" class="eContent2">
                    <?= $this->msgItem->vars['ipaddress']; ?>
                </div>
                <?= $this->msgItem->get_statusValue(); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_date'); ?>
            </td>
            <td class="eTableLine0">
                <?= date_displayLongDateHour($this->msgItem->vars['edate']); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_author'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->msgItem->vars['author']; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_email'); ?>
            </td>
            <td class="eTableLine0">
                <a class="eLink2" href="mailto:<?= $this->msgItem->vars['email']; ?>"><?= $this->msgItem->vars['email']; ?></a>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $camyks->get_translation('formitem_website'); ?>
            </td>
            <td class="eTableLine1">
                <?php if ($this->msgItem->vars['website'] != '') : ?>
                    <a class="eLink2" href="<?= $this->msgItem->vars['website']; ?>" target="_blank"><?= $this->msgItem->vars['website']; ?></a>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_message'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->msgItem->vars['message']; ?>
            </td>
        </tr>
    </table>
</div>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
