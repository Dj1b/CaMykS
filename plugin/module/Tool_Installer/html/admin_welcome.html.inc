<?php
/**
 * @brief Tool_Installer Module welcome layout
 * @details Plugin / Module Layout
 * @file plugin/module/Tool_Installer/html/admin_welcome.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2017
 * @date Modification: May 2019
 * @copyright 2017 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<div style="margin:100px auto; width:600px; text-align:center;">
    <div class="eTitle1">
        <?= $this->get_translation('welcome_title'); ?>
    </div>

    <div class="">
        <img src="<?= $this->welcomePicture->get_base64Data(); ?>" alt="<?= CAMYKS_NAME; ?>" />
    </div>

    <div class="eTitle1">
        &nbsp;
    </div>

    <div class="">
        <?= $camyks->theme->get_button(array(
            'title' => $this->get_translation('start_installation'),
            'url'   => $this->params->vars['url'].'?mode=configuration',
        )); ?>
    </div>
</div>
