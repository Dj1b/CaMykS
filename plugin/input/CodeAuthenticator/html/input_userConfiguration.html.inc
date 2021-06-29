<?php
/**
 * @brief CodeAuthenticator Input, user configuration layout.
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
    <div class="eContent2" style="width:600px; margin:0 auto; max-width:100%;">
        <br />
        <?= $this->get_translation('instructions1'); ?>
        <br /> <br />
    </div>
    <div>
        <img src="<?= $this->get_QRCodeURL(); ?>" alt="" style="width:250px;" />
    </div>
    <div class="eContent2" style="width:600px; margin:0 auto; max-width:100%;">
        <br />
        <?= $this->get_translation('instructions2'); ?>
        <br /> <br />
    </div>
    <div>
        <?= $this->form->display_textInput(array('name'=>'code', 'maxlength'=>$this->get_configValue('code_length'), 'placeholder'=>'123456', 'autocomplete'=>'off', 'oninput'=>'checkCodeInputValue(this);', 'style'=>'font-size:32px; letter-spacing:12px; padding:12px; font-weight:300;')); ?>
    </div>
</div>
