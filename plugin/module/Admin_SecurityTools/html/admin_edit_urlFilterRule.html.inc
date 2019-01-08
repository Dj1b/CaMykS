<?php
/**
 * @brief Admin_SecurityTools Module admin layout to edit filter url rule.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_SecurityTools/html/admin_edit_urlFilterRule.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jan 2019
 * @date Modification: Jan 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
        <?php if (isset($this->ipfilterrule->_libError)) : ?>
        <tr>
            <td class="error" colspan="3">
                <?= $this->ipfilterrule->_libError; ?>
            </td>
        </tr>
        <?php endif; ?>
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $camyks->get_translation('formitem_status'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'status', 'values'=>$this->urlFilterRule->get_statusList())); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_pattern'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textInput(array('name'=>'pattern')); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('ipfilter_comment'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'comment')); ?>
            </td>
        </tr>
    </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>

<?php
/**
 * @endcond Exclude
 */
?>
