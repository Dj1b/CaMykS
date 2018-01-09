<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version	: 1.0
 * Object Type      : Plugin / Input Config
 * Creation Date	: Jan 2018
 * Last Modif Date	: Jan 2018
 *
 * ReCaptcha configuration object
 */

final class ReCaptchaConfig extends PluginConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  public function ReCaptchaConfig($name, &$parent) {
    parent::__construct($name, $parent);
    
    $this->add_newItem('publicKey', 'string', '');
    $this->add_newItem('privateKey', 'string', '');

    /* generic initialisation */
    parent::init_config();
  }
}
?>