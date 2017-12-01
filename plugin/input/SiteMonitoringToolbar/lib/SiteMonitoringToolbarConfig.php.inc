<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version	: 1.0
 * Object Type      : Plugin / Input Config
 * Creation Date	: Nov 2017
 * Last Modif Date	: Nov 2017
 *
 * SiteMonitoringToolbar configuration file
 */

final class SiteMonitoringToolbarConfig extends PluginConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  public function SiteMonitoringToolbarConfig($name, &$parent) {
    parent::__construct($name, $parent);
    
    $this->add_newItem('accessRestriction', 'integer', 1);
    $this->add_newItem('buttonLocation', 'string', 'top:right');
    $this->add_newItem('appliedTheme', 'string', 'dark');

    /* generic initialisation */
    parent::init_config();
  }
  
  /* specific tool methods */
  
  /*
   * return access restriction value list
   * @return array
   * @access public
   */
  public function get_accessRestrictionList() {
    return array(
      0 => $this->get_translation('accessrestriction_webmasteronly'),
      1 => $this->get_translation('accessrestriction_adminonly'),
      2 => $this->get_translation('accessrestriction_all'),
    );
  }
  
  /*
   * return button location value list
   * @return array
   * @access public
   */
  public function get_buttonLocationList() {
    return array(
      'top:left'        => $this->get_translation('buttonlocation_topleft'),
      'top:right'       => $this->get_translation('buttonlocation_topright'),
      'bottom:left'     => $this->get_translation('buttonlocation_bottomleft'),
      'bottom:right'    => $this->get_translation('buttonlocation_bottomright'),
    );
  }
  
  /*
   * return button location value list
   * @return array
   * @access public
   */
  public function get_availableThemeList() {
    return array(
      'dark' => $this->get_translation('availabletheme_dark'),
    );
  }
}
?>