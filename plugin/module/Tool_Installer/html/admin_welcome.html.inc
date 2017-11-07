<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date	: Oct 2017
 * Last Modif Date  : Oct 2017
 * 
 * Installer Module Layout : welcome layout
 */
global $camyks;

?>
<div style="margin:100px auto; width:600px; text-align:center;">
  
  <div class="eTitle1">
    <?= $this->get_translation('welcome_title'); ?>
  </div>
  
  <div class="">
    <img src="<?=$this->welcomePicture->get_base64Data();?>" alt="<?=CAMYKS_NAME;?>" />
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