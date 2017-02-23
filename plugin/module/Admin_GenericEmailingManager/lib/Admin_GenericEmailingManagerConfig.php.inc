<?php
/*
 * CaMykS Engine
 * Developed by		: Ideogram Design
 * Author		    : JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Config
 * Creation Date	: Jan 2013
 * Last Modif Date	: Jan 2013
 *
 * Admin_GenericEmailingManagerConfig configuration file
 */

class Admin_GenericEmailingManagerConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_GenericEmailingManagerConfig ( $name, &$parent ) {
    parent::ModuleConfig($name, $parent);

    /* unsubscribing params */
    $this->add_newItem('unsubscribe_backpage', 'string', '');
    
    
   
    

    /* generic initialisation */
    parent::init_config();
  }
}
?>