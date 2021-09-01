<?php
/**
 * @brief Admin_MyAccount Module edit account 2FA layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2021
 * @date Modification: Jul 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('style'=>'width:500px; margin:0 auto;', 'class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div class="adminContentPanel">
    <div class="eTableSubHeader">
        <?= $camyks->get_translation('formitem_status'); ?>
        <?= $this->get_translation('2fastatus_'.($this->myAccount->twoFactorData === '' ? 'notconfigured' : 'configured')); ?>
    </div>
    <?= $this->plugin->display_userConfiguration(); ?>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
