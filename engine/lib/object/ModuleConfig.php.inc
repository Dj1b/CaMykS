<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: Oct 2007
 * Last Modif Date  : Feb 2018
 *
 * Module Config Generic Object, alias to PluginConfig, kept for retro-compatibility
 */

abstract class ModuleConfig extends PluginConfig {
  
  /*
   * constructor
   * @param string $name
   * @param Module $module
   */
  public function ModuleConfig ($name, &$module) {
    parent::__construct($name, $module);
  }
}
?>