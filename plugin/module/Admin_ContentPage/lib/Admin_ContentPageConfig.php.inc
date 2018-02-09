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

final class Admin_ContentPageConfig extends PluginConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  public function __construct($name, &$parent) {
    parent::__construct($name, $parent);
    
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
  public function get_w3cValidatorList() {
    return array(
        0 => $this->get_translation('config_w3cvalidator_disabled'),
        1 => $this->get_translation('config_w3cvalidator_enabled'),
    );
  }
  
  /*
   * return w3c validation status title
   * @return array
   * @access private
   */
  public function get_w3cValidatorTitle() {
    $l = $this->get_w3cValidatorList();
    if (isset($l[$this->vars['action_w3cValidator']]))
      return $l[$this->vars['action_w3cValidator']];
    return '';
  }
  
  /*
   * return ogmeta status list
   * @return array
   * @access private
   */
  public function get_ogMetaStatusList() {
    return array(
        0 => $this->get_translation('config_ogmeta_disabled'),
        1 => $this->get_translation('config_ogmeta_enabled'),
    );
  }
  
  /*
   * return ogmeta status title
   * @return array
   * @access private
   */
  public function get_ogMetaStatusTitle() {
    $l = $this->get_ogMetaStatusList();
    if (isset($l[$this->vars['site_ogmeta']]))
      return $l[$this->vars['site_ogmeta']];
    return '';
  }
  
  /*
   * return error 404 fallback values
   * @return array
   * @access private
   */
  public function get_404FallbackList() {
    return array(
        'home_display'      => $this->get_translation('config_404fallback_homedisplay'),
        'home_redirect'     => $this->get_translation('config_404fallback_homeredirect'),
        'page_display'      => $this->get_translation('config_404fallback_pagedisplay'),
        'page_redirect'     => $this->get_translation('config_404fallback_pageredirect'),
        'error404_display'  => $this->get_translation('config_404fallback_error404display'),
        'error404_redirect' => $this->get_translation('config_404fallback_error404redirect'),
    );
  }
  
  /*
   * return ogmeta status title
   * @return array
   * @access private
   */
  public function get_404FallbackTitle() {
    $l = $this->get_404FallbackList();
    if (isset($l[$this->vars['page_404FallBack']]))
      return $l[$this->vars['page_404FallBack']];
    return '';
  }
}
?>