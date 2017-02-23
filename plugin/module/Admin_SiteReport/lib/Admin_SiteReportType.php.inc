<?php
/*
 * CaMykS Engine
 * Developed by		   : camyks.net
 * Author		   : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	   : 1.0a
 * Object Version 	   : 1.0
 * Object Type             : Plugin / Module Lib 
 * Creation Date	   : Apr 2007
 * Last Modif Date	   : Apr 2007
 *
 * Admin_SiteReportType object for Admin_SiteReport Module
 */

class Admin_SiteReportType extends ModuleLibrary {
  /*
   * constructor
   * @param $integer $id
   * @param Module $module
   */
  function Admin_SiteReportType ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('title', 'db', 'etext', 'varchar', 64, '', true);
    /* generic initialisation */
    $this->init_library();
  }
}
?>