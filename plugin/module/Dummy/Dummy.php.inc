<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a2
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Dec 2006
 * Last Modif Date	: Dec 2006
 *
 * Dummy module
 */

class Dummy extends Module {
  /*
   * constructor
   * @param string $path_type
   */
  function Dummy ( $path_type ) {
    /* generic plugin initialisation */
    parent::Module('Dummy', $path_type);
    /* set module type : content | admin | tool */
    $this->type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Dummy';
    /* set author values */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
  }
  
  /* overwrite Module methods */
  
  /* 
   * init module object in admin mode  
   * @return void
   * @access private
   */
  function init_admin () {
    /* nothing to do */
  }
  
  /*
   * display module object in admin mode
   * @return void
   * @access private
   */
  function display_admin () {
    parent::display_admin();
  }

  /*
   * init module object in visit mode
   * @return void
   * @access private
   */
  function init_site ($content=1, $params=array(), $mindex=null) {
    /* nothing to do */
  }

  /*
   * display module object in visit mode
   * @return void
   * @access private
   */
  function display_site ($mindex=null) {
    parent::display_site();
  }
}
?>