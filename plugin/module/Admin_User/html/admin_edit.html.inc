<?php
/**
 * @brief Admin_User Module admin edit user layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_User/html/admin_edit.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jun 2005
 * @date Modification: Oct 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule', 'style'=>'width:800px;margin:0 auto;')); ?>
<?= $this->theme->get_boxTitleBar($this->get_translation('user').$camyks->get_translation('formitem_separator').$this->user->login); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div id="itemProperties" style="display:<?= $this->tabBuilder->get_tabDisplay('Properties'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <?php if ($this->user->_libError != '') : ?>
        <tr>
            <td class="error" colspan="2">
                <?= $this->user->_libError; ?>
            </td>
        </tr>
        <?php endif; ?>

        <?php $alt=0 ?>
        <?php if ($this->user->is_new == 1) : ?>
        <tr>
            <td class="eTableLine<?= $alt?> eContent2" style="width:175px;">
                <?= $camyks->get_translation('formitem_login'); ?>
            </td>
            <td class="eTableLine<?= $alt?> eContent1">
                <input type="text" name="adminuser_login" value="" maxlength="32" class="inputs" />
                <input type="hidden" name="adminuser_change_pwd" value="1" />
            </td>
        </tr>
        <?php else : ?>
        <tr>
            <td class="eTableLine<?= $alt?> eContent2" style="width:175px;">
                <?= $camyks->get_translation('formitem_login'); ?>
            </td>
            <td class="eTableLine<?= $alt?> eContent1">
                <input type="hidden" name="adminuser_login" value="<?= $this->user->login; ?>" />
                <?= $this->user->login ?>
            </td>
        </tr>
        <tr>
            <?php $alt = abs($alt-1); ?>
            <td class="eTableLine<?= $alt?> eContent2">
                <?= $this->get_translation('pwd_change'); ?>
            </td>
            <td class="eTableLine<?= $alt?> eContent1">
                <?= $this->form->display_booleanSelectInput(array('name'=>'adminuser_change_pwd', 'default'=>0, 'onchange'=>'adminuser_pwdObject.selectChange(this);')); ?>
            </td>
        </tr>
        <tr>
            <td colspan="2" style="font-size:0px;height:1px;">
                <div id="changepwd_page0" style="display:none;">
                </div>
                <div id="changepwd_page1" style="display:none;">
                    <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
        <?php endif; ?>
        <?php $alt = abs($alt-1); ?>
            <tr>
                <td class="eTableLine<?= $alt?> eContent2" style="width:175px;">
                    <?= $camyks->get_translation('formitem_pwd'); ?>
                </td>
                <td class="eTableLine<?= $alt?> eContent1">
                    <input type="password" name="adminuser_pwd" value="" maxlength="16" class="inputs" />
                </td>
            </tr>
            <?php $alt = abs($alt-1); ?>
            <tr>
                <td class="eTableLine<?= $alt?> eContent2">
                    <?= $camyks->get_translation('formitem_confirm'); ?>
                </td>
                <td class="eTableLine<?= $alt?> eContent1">
                    <input type="password" name="adminuser_pwd_conf" value="" maxlength="16" class="inputs"/>
                </td>
            </tr>
        <?php if ($this->user->is_new == 0) : ?>
                    </table>
                </div>
            </td>
        </tr>
        <?php endif; ?>

        <?php $alt = abs($alt-1); ?>

        <tr>
            <td class="eTableLine<?= $alt?> eContent2">
                <?= $camyks->get_translation('formitem_status') ?>
            </td>
            <td class="eTableLine<?= $alt?> eContent1">
                <?= $this->form->display_selectInput(array('name'=>'adminuser_active', 'default'=>$this->user->active?1:0, 'values'=>$this->get_userStatusList())); ?>
            </td>
        </tr>

        <?php $alt = abs($alt-1); ?>
        <tr>
            <td class="eTableLine<?= $alt?> eContent2">
                <?= $camyks->get_translation('formitem_firstname'); ?>
            </td>
            <td class="eTableLine<?= $alt?> eContent1">
                <input type="text" name="adminuser_firstname" value="<?= $this->user->firstname; ?>" maxlength="32" class="inputs" />
            </td>
        </tr>

        <?php $alt = abs($alt-1); ?>
        <tr>
            <td class="eTableLine<?= $alt?> eContent2">
                <?= $camyks->get_translation('formitem_lastname'); ?>
            </td>
            <td class="eTableLine<?= $alt?> eContent1">
                <input type="text" name="adminuser_lastname" value="<?= $this->user->lastname; ?>" maxlength="32" class="inputs" />
            </td>
        </tr>

        <?php $alt = abs($alt-1); ?>
        <tr>
            <td class="eTableLine<?= $alt?> eContent2">
                <?= $camyks->get_translation('formitem_email'); ?>
            </td>
            <td class="eTableLine<?= $alt?> eContent1">
                <input type="text" name="adminuser_email" value="<?= $this->user->email; ?>" maxlength="255" class="inputs" />
            </td>
        </tr>

        <?php $alt = abs($alt-1); ?>
        <tr>
            <td class="eTableLine<?= $alt?> eContent2" style="vertical-align:top;">
                <?= $camyks->get_translation('formitem_address'); ?>
            </td>
            <td class="eTableLine<?= $alt?> eContent1">
                <textarea cols="40" rows="6" name="adminuser_address" class="inputs"><?= $this->user->address; ?></textarea>
            </td>
        </tr>
    </table>
</div>

<div id="itemRights" style="display:<?= $this->tabBuilder->get_tabDisplay('Rights'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <?php $alt=0 ?>
        <?php foreach ($camyks->modules as $m) : ?>
        <?php if ($m->type == 'admin') : ?>
        <?php $m->get_rights() ?>
        <tr>
            <td class="eTableLine<?= $alt?> eContent2" style="width:175px;">
                <?= $m->title; ?>
            </td>
            <?php $rightcount = 0; ?>
            <?php $linecount = 0; ?>
            <?php foreach ($m->rights as $ridx => $right) : ?>
            <td class="eTableLine<?= $alt?> eTableIconCell">
            <?php if ($camyks->adminUser->get_right($m->name, $ridx) == 0 or $camyks->adminUser->login == $this->user->login) : ?>
            <input type="checkbox" name="__" value="1" <?= $this->user->get_right($m->name, $ridx) ? ' checked="checked"':''; ?> disabled="disabled" />
            <input type="hidden" name="adminuser_<?= $m->name?>_<?= $ridx?>" value="<?= $this->user->get_right($m->name, $ridx) ? 1 : 0; ?>"/>
            <?php else : ?>
            <input type="checkbox" name="adminuser_<?= $m->name?>_<?= $ridx?>" value="1" id="adminuser_<?= $m->name?>_<?= $ridx?>" <?= $this->user->get_right($m->name, $ridx) ? ' checked="checked"':''; ?> />
            <?php endif; ?>
            </td>
            <td class="eTableLine<?= $alt?> eContent1" style="width:<?= $this->layout_cellwidth; ?>;">
            <label for="adminuser_<?= $m->name; ?>_<?= $ridx; ?>"><?= $right['title']; ?></label>
            </td>
            <?php $rightcount++; ?>
            <?php if (++$linecount == $this->layout_itemsByLine) : ?>
            </tr>
            <?php $linecount = 0; ?>
            <?php if ($rightcount < count($m->rights)) : ?>
            <tr>
            <td class="eTableLine0">
                &nbsp;
            </td>
        <?php endif; ?>
        <?php endif; ?>
        <?php endforeach; ?>

        <?php if ($linecount != 0) : ?>
            <?php for ($i= $linecount; $i < $this->layout_itemsByLine; $i++) : ?>
            <td class="eTableLine<?= $alt?>" colspan="2">
                &nbsp;
            </td>
            <?php endfor; ?>
            </tr>
        <?php endif; ?>
        <?php $alt = abs ($alt-1); ?>
        <?php endif; ?>
        <?php endforeach; ?>
    </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $camyks->theme->get_boxContent2Footer(); ?>
<?= $camyks->theme->get_boxButtonsBar($this->buttons); ?>
<?= $camyks->theme->get_boxFooter(); ?>
