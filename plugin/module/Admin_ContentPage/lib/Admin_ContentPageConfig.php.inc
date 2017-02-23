<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Config
 * Creation Date	: Dec 2014
 * Last Modif Date	: Dec 2014
 *
 * Admin_ContentPage configuration file
 */

class Admin_ContentPageConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_ContentPageConfig ( $name, &$parent ) {
    parent::ModuleConfig($name, $parent);
    
    /* plugin */
    $this->add_newItem('page_404FallBack', 'string', 'home_display');
    $this->add_newItem('page_404ErrorFile', 'string', '');
    $this->add_newItem('page_404ErrorPage', 'string', '');
    $this->add_newItem('page_404SendHeader', 'boolean', 0);
    $this->add_newItem('action_w3cValidator', 'boolean', 0);
    
    $this->add_newItem('site_ogmeta', 'boolean', 0);

    /* generic initialisation */
    parent::init_config();
  }
  
  /*
   * return w3c validation status list
   * @return array
   * @access private
   */
  function get_w3cValidatorList() {
    return array(
        0 => $this->get_translation('config_w3cvalidator_disabled'),
        1 => $this->get_translation('config_w3cvalidator_enabled'),
    );
  }
  
  /*
   * return ogmeta status list
   * @return array
   * @access private
   */
  function get_ogMetaStatusList() {
    return array(
        0 => $this->get_translation('config_ogmeta_disabled'),
        1 => $this->get_translation('config_ogmeta_enabled'),
    );
  }
  
  /*
   * return error 404 fallback values
   * @return array
   * @access private
   */
  function get_404FallbackList() {
    return array('home_display' => $this->get_translation('config_404fallback_homedisplay'),
        'home_redirect' => $this->get_translation('config_404fallback_homeredirect'),
        'page_display' => $this->get_translation('config_404fallback_pagedisplay'),
        'page_redirect' => $this->get_translation('config_404fallback_pageredirect'),
        'error404_display' => $this->get_translation('config_404fallback_error404display'),
        'error404_redirect' => $this->get_translation('config_404fallback_error404redirect'),
    );
  }
 
}
?>