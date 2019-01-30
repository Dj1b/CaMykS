<?php
/**
 * @brief Admin_MyAccount Module edit account information layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_MyAccount/html/admin_edit.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2005
 * @date Modification: Jan 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('style'=>'width:500px; margin:0 auto;', 'class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <?php if ($this->myAccount->_libError != '') : ?>
        <tr>
            <td class="error" colspan="2">
                <?= $this->get_translation($this->myAccount->_libError); ?>
            </td>
        </tr>
        <?php endif; ?>
        <tr>
            <td class="eTableLine0 eContent2" style="width:175px;">
                <?= $camyks->get_translation('formitem_login'); ?>
            </td>
            <td class="eTableLine0 eContent4">
                <?= $this->myAccount->login?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_changepwd'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_booleanSelectInput(array('name'=>'myaccount_change_pwd', 'onchange'=>'myaccount_pwdObject.selectChange(this);')); ?>
            </td>
        </tr>
        <tr>
            <td colspan="2" style="font-size:0px;height:1px;">
                <div id="changepwd_page0" style="display:none;">
                </div>
                <div id="changepwd_page1" style="display:none;">
                    <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
                        <tr>
                            <td class="eTableLine0 eContent2" style="width:175px;">
                                <?= $camyks->get_translation('formitem_pwd'); ?>
                            </td>
                            <td class="eTableLine0 eContent1">
                                <input type="password" name="myaccount_pwd" value="" maxlength="16" class="inputs" />
                            </td>
                        </tr>
                        <tr>
                            <td class="eTableLine1 eContent2">
                                <?= $camyks->get_translation('formitem_confirm'); ?>
                            </td>
                            <td class="eTableLine1 eContent1">
                                <input type="password" name="myaccount_pwd_conf" value="" maxlength="16" class="inputs" />
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_firstname'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <input type="text" name="myaccount_firstname" value="<?= $this->myAccount->firstname?>" maxlength="32" class="inputs" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $camyks->get_translation('formitem_lastname'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <input type="text" name="myaccount_lastname" value="<?= $this->myAccount->lastname?>" maxlength="32" class="inputs" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_email'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <input type="text" name="myaccount_email" value="<?= $this->myAccount->email?>" maxlength="254" class="inputs" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2" valign="top">
                <?= $camyks->get_translation('formitem_address'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <textarea cols="40" rows="6" name="myaccount_address" class="inputs"><?= $this->myAccount->address?></textarea>
            </td>
        </tr>
    </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
