<?php
/**
 * @brief Tool_Login Module main layout
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jun 2021
 * @date Modification: Jun 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<div class="adminLoginBox" style="margin:0 auto; width:350px; padding-top:100px;">
    <?= $this->form->display_header(); ?>
    <?= $this->form->display_hiddens(); ?>

    <?php if (($message = $camyks->get_sessionValue('require2FAMessage', '')) !== '') : ?>
    <div class="error">
        <?= $message; ?>
    </div>
    <?php $camyks->set_sessionValue('require2FAMessage', ''); ?>
    <?php endif; ?>

    <?= $this->plugin->display_userLogin(); ?>

    <div class="buttons">
        <?php foreach ($this->buttons as $button) : ?>
            <?= $this->theme->get_button($button); ?>
        <?php endforeach; ?>
    </div>

    <?= $this->form->display_footer(); ?>
</div>
