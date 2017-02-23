<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date	: Sep 2005
 * Last modif Date	: Mar 2009
 * 
 * Tool_Login Module Layout
 */
global $camyks;
?>
<div class="adminLoginBox" style="margin:0 auto; width:350px; padding-top:100px;">

<div class="eTitle1">
  <?=$this->title; ?>
</div>

<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>

  <?php if ( $this->text != '') : ?>
  <div class="error">
    <?=$this->text?>
  </div>
  <?php endif; ?>
  <div style="text-align:center; padding:8px;">
    <?=$this->form->display_textInput(array('name'=>'login', 'default'=>$this->login, 'maxlength'=>32, 'class'=>'inputs', 'placeholder'=>$camyks->get_translation('login'))); ?>
  </div>
  <div style="text-align:center; padding:8px;">
    <?=$this->form->display_passwordInput(array('name'=>'pwd', 'maxlength'=>32, 'class'=>'inputs', 'placeholder'=>$camyks->get_translation('pwd'))); ?>
  </div>
  <?php if ( count( $camyks->site_conf['admin_languages'] ) > 1 ) : ?>
  <div style="text-align:center; padding:8px;">
     <?=$this->form->display_selectInput(array('name'=>'_clg_', 'values'=>$this->languages, 'default'=>$camyks->current_language, 'onchange'=>'document.location.href=\''.$camyks->get_adminLink().'?_clg_=\'+this.options[this.options.selectedIndex].value;')); ?>
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
</div>