<?php
/**
 * @brief Tool_Login Module main layout
 * @details Plugin / Module Layout
 * @file plugin/module/Tool_Login/html/admin.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Sep 2005
 * @date Modification: May 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<div class="adminLoginBox" style="margin:0 auto; width:350px; padding-top:100px;">
    <div class="eTitle1">
        <?=$this->title; ?>
    </div>

    <?=$this->form->display_header()?>
    <?=$this->form->display_hiddens()?>

    <?php if ($this->text != '') : ?>
        <div class="error">
            <?=$this->text?>
        </div>
    <?php endif; ?>
    <div style="text-align:center; padding:8px 0;">
        <?=$this->form->display_textInput(array('name'=>'login', 'default'=>$this->login, 'maxlength'=>32, 'class'=>'inputs', 'placeholder'=>$camyks->get_translation('login'))); ?>
    </div>
    <div style="text-align:center; padding:8px 0;">
        <?=$this->form->display_passwordInput(array('name'=>'pwd', 'maxlength'=>32, 'class'=>'inputs', 'placeholder'=>$camyks->get_translation('pwd'))); ?>
    </div>
    <?php if (count($this->adminLanguages) > 1) : ?>
        <div style="text-align:center; padding:8px 0;">
            <?=$this->form->display_selectInput(array('name'=>'_clg_', 'values'=>$this->adminLanguages, 'default'=>$camyks->current_language, 'onchange'=>'document.location.href=\''.$camyks->get_adminLink().'?_clg_=\'+this.options[this.options.selectedIndex].value;')); ?>
        </div>
    <?php endif; ?>
    <div style="display:none;">
        <input type="submit" />
    </div>

    <?=$this->form->display_footer()?>

    <div class="buttons">
        <?php foreach ($this->buttons as $button) : ?>
            <?=$this->theme->get_button($button); ?>
        <?php endforeach; ?>
    </div>
    <div>
      &nbsp; <br /> &nbsp;
    </div>
    <?php foreach ($this->extensions as $extension) : ?>
        <?php $extension->display_oauthLogin(); ?>
    <?php endforeach; ?>
</div>
<?php 
/**
 * @endcond Exclude
 */
?>