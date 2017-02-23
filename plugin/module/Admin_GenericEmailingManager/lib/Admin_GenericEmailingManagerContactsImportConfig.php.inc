<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Config
 * Creation Date	: Jan 2013
 * Last Modif Date	: Jan 2013
 *
 * Admin_GenericEmailingManager configuration file
 */

class Admin_GenericEmailingManagerContactsImportConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_GenericEmailingManagerContactsImportConfig ($name, &$parent) {
    parent::ModuleConfig( $name, $parent );

    /* config items */
    $this->add_newItem('import_file', 'string', '');
    $this->add_newItem('cols_params', 'array', array());
    $this->add_newItem('import_current', 'integer', 0);
    $this->add_newItem('first_line', 'integer', 1);
    $this->add_newItem('row_count', 'integer', 0);

    /* generic initialisation */
    parent::init_config();
  }
}

?>