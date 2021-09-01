<?php
/**
 * @brief Content_GenericRandomText module, admin edit list layout.
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
$plus = $this->theme->get_pictURL('plus', 12, 'std');
$plus_ = $this->theme->get_pictURL('plus', 12, 'ovr');
$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');
$delete = $this->theme->get_pictURL('cross', 12, 'std');
$delete_ = $this->theme->get_pictURL('cross', 12, 'ovr');
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title);?>
<?php if ($this->glist->id > 0) : ?>
    <?= $this->theme->get_boxTabsBar($this->tabs, $this->tabObject.'.mouseclick', $this->tabObject.'.mouseover', $this->tabObject.'.mouseout', 'properties');?>
<?php endif; ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div id="itemproperties" class="adminContentPanel" style="display:block;">
    <table cellspacing="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $camyks->get_translation('formitem_name'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <input type="text" name="name" value="<?= $this->glist->vars['name']; ?>" maxlength="16" class="inputs" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $camyks->get_translation('formitem_layout'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->layoutlist, 'default'=>$this->glist->vars['layout']));?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('sitesessionkeep'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <input type="checkbox" name="sessionkeep" value="1"<?=($this->glist->vars['sessionkeep']==1?' checked="checked"':''); ?> />
                <?= $this->get_translation('sitesessionkeepalt'); ?>
            </td>
        </tr>
    </table>
</div>

<?php if ($this->glist->id > 0) : ?>
<div id="itemitems" class="adminContentPanel" style="display:none;">
    <table cellspacing="0" cellpadding="0" border="0" width="100%">
        <tr>
            <td class="eTableLine1" style="width:12px;">
                &nbsp;
            </td>
            <td class="eTableLine1" colspan="2">
                <a href="<?= $this->edittextlink; ?>0">
                    <?= $this->get_translation('newtext'); ?>
                </a>
            </td>
            <td class="eTableLine1">
                <a href="<?= $this->edittextlink; ?>0">
                    <img src="<?= $plus; ?>" alt="<?= $this->get_translation('newtext'); ?>" title="<?= $this->get_translation('newtext');?>" onmouseover="this.src='<?= $plus_; ?>';" onmouseout="this.src='<?= $plus; ?>';" />
                </a>
            </td>
            <td class="eTableLine1">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" style="width:12px;">
                &nbsp;
            </td>
            <td class="eTableHeader">
                <?= $this->get_translation('itemname'); ?>
            </td>
            <td class="eTableHeader">
                <?= $this->get_translation('itemweight'); ?>
            </td>
            <td class="eTableHeader" style="width:12px;">
                &nbsp;
            </td>
            <td class="eTableHeader" style="width:12px;">
                &nbsp;
            </td>
        </tr>
        <?php $alt=0; ?>
        <?php foreach ($this->glist->vars['items'] as $item) : ?>
            <tr>
                <td class="eTableLine<?= $alt; ?>">
                    &nbsp;
            </td>
            <td class="eTableLine<?= $alt; ?>">
                <?= $item->vars['name']; ?>
            </td>
            <td class="eTableLine<?= $alt; ?>">
                <?= $item->vars['weight']; ?>
            </td>
            <td class="eTableLine<?= $alt; ?>">
                <a href="<?= $this->edittextlink; ?><?= $item->id; ?>">
                    <img src="<?= $edit; ?>" alt="<?= $this->get_translation('edittext'); ?>" title="<?= $this->get_translation('edittext'); ?>" onmouseover="this.src='<?= $edit_; ?>';" onmouseout="this.src='<?= $edit; ?>';" />
                </a>
            </td>
            <td class="eTableLine<?= $alt; ?>">
                <a href="<?= vsprintf($this->deleteTextLink, $item->id); ?>">
                    <img src="<?= $delete; ?>" alt="<?= $this->get_translation('deletetext'); ?>" title="<?= $this->get_translation('deletetext'); ?>" onmouseover="this.src='<?= $delete_; ?>';" onmouseout="this.src='<?= $delete; ?>';" />
                </a>
            </td>
        </tr>
        <?php $alt=abs($alt-1); ?>
        <?php endforeach; ?>
    </table>
</div>
<?php endif; ?>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
