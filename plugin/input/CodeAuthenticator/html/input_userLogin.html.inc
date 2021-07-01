<?php
/**
 * @brief CodeAuthenticator Input, user login layout.
 * @details Plugin / Input Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jun 2021
 * @date Modification: Jun 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<div style="text-align:center;">
    <div class="eTitle2">
        <?= $this->get_translation('loginmessage'); ?>
    </div>
    <div>
        <br />
        <?= $this->form->display_textInput(array('name'=>'code', 'maxlength'=>$this->get_configValue('code_length'), 'placeholder'=>'123456', 'autocomplete'=>'off', 'oninput'=>'checkCodeInputValue(this);', 'style'=>'font-size:32px; letter-spacing:12px; padding:12px; font-weight:300;')); ?>
        <br /><br />
    </div>
</div>
