<?php
/**
 * @brief Admin_MyAccount Module read account information layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Oct 2005
 * @date Modification: Jul 2021
 * @copyright 2005 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('style'=>'width:500px; margin:0 auto;', 'class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:175px;">
                <?= $camyks->get_translation('formitem_login'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->myAccount->login?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $camyks->get_translation('formitem_firstname'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->myAccount->firstname?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_lastname'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->myAccount->lastname?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $camyks->get_translation('formitem_email'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <a href="mailto:<?= $this->myAccount->email?>" class="eLink1">
                    <?= $this->myAccount->email?>
                </a>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_address'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= nl2br($this->myAccount->address); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_2faauthentication'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?php if ($camyks->modules['Admin_User']->get_configValue('authentication_2factorInput') === '') : ?>
                    <?= $this->get_translation('2fastatus_unavailable'); ?>
                <?php else : ?>
                    <?= $this->get_translation('2fastatus_'.($this->myAccount->twoFactorData === '' ? 'notconfigured' : 'configured')); ?>
                <?php endif; ?>
            </td>
        </tr>
    </table>
</div>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
