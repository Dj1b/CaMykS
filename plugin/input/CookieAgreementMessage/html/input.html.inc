<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Layout
 * Create Date		: May 2017
 * Last Modif Date	: May 2017
 * 
 * CookieAgreementMessage input layout
*/
global $camyks;
?>
<div id="cookieAgreementMessage" class="cookieAgreementMessage <?=$this->params['location'];?>">

  <div class="message">
    <?=$this->params['message']; ?>
  </div>

  <div class="buttons">
  
    <?php if ($this->params['styleSource'] == 'plugin') : ?>
    
      <a href="javascript:if(cookieMessage)cookieMessage.accept_cookies();void(0);" class="acceptButton">
        <?=$this->get_translation('accept'); ?>
      </a>
    
      <?php if ($this->params['aboutCookie'] != '') : ?>
    
        <a href="<?=$this->params['aboutCookie'];?>" class="aboutButton" target="_blank">
          <?=$this->get_translation('about'); ?>
        </a>
    
      <?php endif; ?>
    
    <?php else : ?>
  
      <?=$camyks->theme->get_button(array(
          'title'     => $this->get_translation('accept'),
          'link'      => 'javascript:if(cookieMessage)cookieMessage.accept_cookies(); void(0);',
        )); ?>
    
      <?php if ($this->params['aboutCookie'] != '') : ?>
    
        <?=$camyks->theme->get_button(array(
          'title'     => $this->get_translation('about'),
          'link'      => $this->params['aboutCookie'],
          'target'    => '_blank',
         )); ?>
  
      <?php endif; ?>
  
    <?php endif; ?>
  </div>
</div>