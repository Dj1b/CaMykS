<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Config
 * Creation Date	: Dec 2012
 * Last Modif Date	: Dec 2012
 *
 * Admin_GenericEmailingManager configuration file
 */

class Admin_GenericEmailingManagerEmailingConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_GenericEmailingManagerEmailingConfig ($name, &$parent) {
    parent::ModuleConfig( $name, $parent );

    /* config items */
    $this->add_newItem('emailing_id', 'integer', 0);
    $this->add_newItem('content_images', 'array', array());
    $this->add_newItem('content_links', 'array', array());
    
    $this->add_newItem('emailing_current', 'integer', 0);
    $this->add_newItem('emailing_list', 'array', array());

    /* generic initialisation */
    parent::init_config();
  }
}

?>