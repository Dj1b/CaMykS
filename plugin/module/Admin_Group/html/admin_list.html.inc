<?php
/**
 * @brief Admin_Group Module admin list groups layout.
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

/* Load images urls */
$view = $camyks->theme->get_pictURL('view', 12, 'std');
$view_ = $camyks->theme->get_pictURL('view', 12, 'ovr');
$edit = $camyks->theme->get_pictURL('edit', 12, 'std');
$edit_ = $camyks->theme->get_pictURL('edit', 12, 'ovr');
$del = $camyks->theme->get_pictURL('cross', 12, 'std');
$del_ = $camyks->theme->get_pictURL('cross', 12, 'ovr');
$plus = $camyks->theme->get_pictURL('plus', 12, 'std');
$plus_ = $camyks->theme->get_pictURL('plus', 12, 'ovr');
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <?php if ($this->check_right(1) === true) : ?>
            <tr>
                <td class="eTableLine1">
                    &nbsp;
                </td>
                <td class="eTableLine1" colspan="2">
                    <a href="<?= $camyks->get_adminLink($this->name, array('mode'=>'edit', 'group'=>'')); ?>" class="eLink1">
                        <?= $this->get_translation('addgroup'); ?>
                    </a>
                </td>
                <td class="eTableLine1">
                    &nbsp;
                </td>
                <td class="eTableLine1">
                    <a href="<?= $camyks->get_adminLink($this->name, array('mode'=>'edit', 'group'=>'')); ?>" class="eLink1 img">
                        <img src="<?= $plus; ?>" alt="<?= $this->get_translation('addgroup'); ?>" title="<?= $this->get_translation('addgroup'); ?>" onmouseover="this.src='<?= $plus_; ?>';" onmouseout="this.src='<?= $plus; ?>';" />
                    </a>
                </td>
                <td class="eTableLine1">
                    &nbsp;
                </td>
            </tr>
        <?php endif; ?>
        <tr>
            <td class="eTableHeader eTableIconCell">
                &nbsp;
            <td class="eTableHeader">
                <?= $camyks->get_translation('name'); ?>
            </td>
            <td class="eTableHeader">
                <?= $this->get_translation('description'); ?>
            </td>
            <td class="eTableHeader eTableIconCell">
                &nbsp;
            </td>
            <?php if ($this->check_right(1) === true) : ?>
                <td class="eTableHeader eTableIconCell">
                    &nbsp;
                </td>
            <?php endif; ?>
            <td class="eTableHeader eTableIconCell">
                &nbsp;
            </td>
        </tr>

        <?php $alt = 0; ?>
        <?php foreach ($this->group_list as $g) : ?>
            <tr>
                <td class="eTableLine<?= $alt; ?>">
                    &nbsp;
                </td>
                <td class="eTableLine<?= $alt; ?>">
                    <?= $g['name']; ?>
                </td>
                <td class="eTableLine<?= $alt; ?>">
                    <?= $g['description']; ?>
                </td>
                <?php if ($g['editable']) : ?>
                    <td class="eTableLine<?= $alt; ?>">
                        <a href="<?= $camyks->get_adminLink($this->name, array('mode'=>'view', 'group'=>$g['name'])); ?>" class="img">
                            <img src="<?= $view; ?>" alt="<?= $this->get_translation('viewgroup'); ?>" title="<?= $this->get_translation('viewgroup'); ?>" onmouseover="this.src='<?= $view_; ?>';" onmouseout="this.src='<?= $view; ?>';" />
                        </a>
                    </td>
                    <?php if ($this->check_right(1) === true) : ?>
                        <td class="eTableLine<?= $alt; ?>">
                            <a href="<?= $camyks->get_adminLink($this->name, array('mode'=>'edit', 'group'=>$g['name'])); ?>" class="img">
                                <img src="<?= $edit; ?>" alt="<?= $this->get_translation('editgroup'); ?>" title="<?= $this->get_translation('editgroup'); ?>" onmouseover="this.src='<?= $edit_; ?>';" onmouseout="this.src='<?= $edit; ?>';" />
                            </a>
                        </td>
                    <?php endif; ?>
                <?php else : ?>
                    <td class="eTableLine<?= $alt; ?>" colspan="2">
                        &nbsp;
                    </td>
                <?php endif; ?>
                <td class="eTableLine<?= $alt; ?>">
                    &nbsp;
                </td>
            </tr>
            <?php $alt = abs($alt-1); ?>
        <?php endforeach; ?>
    </table>
</div>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
