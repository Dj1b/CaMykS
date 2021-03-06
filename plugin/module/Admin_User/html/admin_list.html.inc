<?php
/**
 * @brief Admin_User Module admin list user layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_User/html/admin_list.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Mar 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
/* get img path */
$view = $camyks->theme->get_pictURL('view', 12, 'std');
$view_ = $camyks->theme->get_pictURL('view', 12, 'ovr');
$edit = $camyks->theme->get_pictURL('edit', 12, 'std');
$edit_ = $camyks->theme->get_pictURL('edit', 12, 'ovr');
$del = $camyks->theme->get_pictURL('cross', 12, 'std');
$del_ = $camyks->theme->get_pictURL('cross', 12, 'ovr');
$plus = $camyks->theme->get_pictURL('plus', 12, 'std');
$plus_ = $camyks->theme->get_pictURL('plus', 12, 'ovr');
$valid = $camyks->theme->get_pictURL('valid', 12, 'std');
$empty = $camyks->theme->get_pictURL('empty', 12, 'std');

?>
<?= $camyks->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $camyks->theme->get_boxTitleBar($this->title); ?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">

    <?= $this->listForm->display_header(); ?>
    <?= $this->listForm->display_hiddens(); ?>

    <div class="AdminItemListViewer">
        <div class="selector">
            <div class="label eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_status'); ?>
            </div>
            <div class="input eTableLine0 eContent2">
                <?= $this->listForm->display_selectInput(array('name'=>'status', 'values'=>$this->usersStatusList, 'onchange'=>$this->listForm->get_JSSubmitLink())); ?>
            </div>
        </div>
        <div class="selector">
            <div class="label eTableLine0 eContent2">
                <?= $this->get_translation('formitem_search'); ?>
            </div>
            <div class="input eTableLine0 eContent2">
                <?= $this->listForm->display_textInput(array('name'=>'search', 'onchange'=>$this->listForm->get_JSSubmitLink())); ?>
            </div>
        </div>
    </div>

    <?= $this->listForm->display_footer(); ?>

    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <?php if ($this->check_right (1)) : ?>
        <tr>
            <td class="eTableSubHeader eTableIconCell">
                &nbsp;
            </td>
            <td class="eTableSubHeader" colspan="4">
                <a href="<?= $this->get_adminLink(array('mode'=>'edit', 'user'=>'')); ?>" class="eLink1">
                    <?= $this->get_translation('adduser'); ?>
                </a>
            </td>
            <td class="eTableSubHeader eTableIconCell">
                <a href="<?= $this->get_adminLink(array('mode'=>'edit', 'user'=>'')); ?>">
                    <img src="<?= $plus?>" class="img"
                        alt="<?= $this->get_translation('adduser'); ?>"
                        title="<?= $this->get_translation('adduser'); ?>"
                        onmouseover="this.src='<?= $plus_?>';"
                        onmouseout="this.src='<?= $plus?>';" />
                </a>
            </td>
            <td class="eTableSubHeader">
                &nbsp;
            </td>
        </tr>
        <?php endif; ?>

        <tr>
            <td class="eTableHeader eTableIconCell">
                &nbsp;
            </td>
            <td class="eTableHeader" style="width:120px;">
                <?= $camyks->get_translation('login'); ?>
            </td>
            <td class="eTableHeader" style="width:250px;">
                <?= $camyks->get_translation('name'); ?>
            </td>
            <td class="eTableHeader">
                <?= $camyks->get_translation('email'); ?>
            </td>
            <td class="eTableHeader eTableIconCell">
                &nbsp;
            </td>
            <?php if ($this->check_right(1)) : ?>
            <td class="eTableHeader eTableIconCell">
                &nbsp;
            </td>
            <?php endif; ?>
            <td class="eTableHeader eTableIconCell">
                &nbsp;
            </td>
        </tr>

        <?php $alt = 0; ?>
        <?php foreach ($this->user_list as $u) : ?>
        <tr>
            <td class="eTableLine<?= $alt?> eTableIconCell">
                <img src="<?=($u['active']==1?$valid:$empty); ?>" alt="" />
            </td>
            <td class="eTableLine<?= $alt?>">
                <?= $u['login']; ?>
            </td>
            <td class="eTableLine<?= $alt?>">
                <?= $u['firstname']; ?>&nbsp;<?= $u['lastname']; ?>
            </td>
            <td class="eTableLine<?= $alt?>">
                <a href="mailto:<?= $u['email']; ?>" class="eLink1">
                    <?= $u['email']; ?>
                </a>
            </td>
            <td class="eTableLine<?= $alt?> eTableIconCell">
                <a href="<?= $camyks->get_adminLink($this->name, array('mode'=>'view', 'user'=>$u['login'])); ?>">
                    <img src="<?= $view?>" border="0"
                        alt="<?= $this->get_translation('viewuser'); ?>"
                        title="<?= $this->get_translation('viewuser'); ?>"
                        onmouseover="this.src='<?= $view_?>';"
                        onmouseout="this.src='<?= $view?>';" />
                </a>
            </td>
            <?php if ($this->check_right (1) === true) : ?>
            <td class="eTableLine<?= $alt?> eTableIconCell">
                <a href="<?= $camyks->get_adminLink($this->name, array('mode'=>'edit', 'user'=>$u['login'])); ?>">
                    <img src="<?= $edit?>" border="0"
                        alt="<?= $this->get_translation('edituser'); ?>"
                        title="<?= $this->get_translation('edituser'); ?>"
                        onmouseover="this.src='<?= $edit_?>';"
                        onmouseout="this.src='<?= $edit?>';" />
                </a>
            </td>
            <?php endif; ?>
            <td class="eTableLine<?= $alt?> eTableIconCell">

            </td>
        </tr>
        <?php $alt=abs($alt-1); ?>
        <?php endforeach; ?>
    </table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
<?= $camyks->theme->get_boxButtonsBar($this->buttons); ?>
<?= $camyks->theme->get_boxFooter(); ?>
