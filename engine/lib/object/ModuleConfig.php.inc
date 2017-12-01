<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: Oct 2007
 * Last Modif Date  : Dec 2014
 * History :
 * * 07-10-xx : Initial file
 * * 08-04-16 : Add 'get_translation' method
 * * 14-12-05 : Add 'get_value' method
 *
 * Module Config Generic Object
 */

class ModuleConfig extends PluginConfig {
  
  /*
   * constructor
   * @param string $name
   * @param Module $module
   */
  function ModuleConfig ($name, &$module) {
    parent::__construct($name, $module);
  }
}
?>