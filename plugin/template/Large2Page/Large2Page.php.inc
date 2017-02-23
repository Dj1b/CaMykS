<?php
/*
 * Camyks Engine
 * Developed by            : camyks.net
 * Author                  : CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version          : 1.0a
 * Object Version          : 1.0
 * Object Type             : Plugin / Template Description
 * Create Date             : Nov 2007
 * Last Modif Date         : Jan 2008
 * History :
 * * 07-11-28 : Initial file
 * * 08-01-07 : Rebuild template as an object
 *
 * Large2Page Template Informations
 */

class Large2Page extends Template {
  /* constructor */
  function Large2Page( $path_type ) {
    parent::Template('Large2Page', $path_type);
    /* set template title */
    $this->title = '2Large';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package ='Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* initialise template variables */
    $this->modules = 2;
  }
}
?>