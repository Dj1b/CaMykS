<?php
/*
 * CaMykS Engine
 * Developed by		: Ideogram Design
 * Author			: JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Theme 
 * Creation Date	: Oct 2014
 * Last Modif Date  : Apr 2017
 */

class IndigoFlatStyle extends Theme {
  /* constructor */
  function IndigoFlatStyle( $path_type ) {
    parent::Theme('IndigoFlatStyle', $path_type);
    /* set theme title */
    $this->title = 'Indigo Flat Style';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = '';
    $this->author_mail = 'jb.lebrun@ideogram-design.fr';
    $this->author_group = 'Ideogram Design';
    
    /* update useEnhanceSelectInputs value */
    $this->useEnhancedSelectInputs = false;
    
    /* check for responsive admin mode */
    $this->isAdminResponsive = true;
  }
  
  /* additional parts methods */
  
}
?>