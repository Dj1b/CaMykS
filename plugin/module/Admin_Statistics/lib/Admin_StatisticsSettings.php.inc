<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Config
 * Create Date		: Oct 2007
 * Last Modif Date	: Oct 2009
 *
 * Admin_StatisticsSettings config object for Admin_Statistics
 */

class Admin_StatisticsSettings extends ModuleConfig {
  /*
   * constructor
   * @param sting $name
   * @param &Module $parent
   */
  function Admin_StatisticsSettings ( $name, &$parent ) {
    parent::ModuleConfig( $name, $parent );

    /* object items */
    $this->add_newItem('stat_sitepage', 'int', 0);
    $this->add_newItem('stat_visits', 'int', 0);
    $this->add_newItem('stat_firstpage', 'int', 0);
    $this->add_newItem('stat_referer', 'int', 0);
    $this->add_newItem('stat_webbots', 'int', 0);
    $this->add_newItem('stat_webtools', 'int', 0);

    $this->add_newItem('stat_filteredips', 'array', array());

    /* generic initialisation */
    parent::init_config();
  }

  /* overwrite ModuleConfig methods */
}
?>