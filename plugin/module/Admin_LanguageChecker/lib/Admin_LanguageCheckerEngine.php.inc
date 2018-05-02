<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Nov 2006
 * Last Modif Date	: Sep 2007
 *      
 * Admin_LanguageCheckerEngine library for Admin_LanguageChecker module
 */

class Admin_LanguageCheckerEngine {
  /* variables */
  var $hasfile;
  var $trads;

  /*
   * constructor
   * @param string $type
   * @param string $item
   * @param string $locale
   */
  function Admin_LanguageCheckerEngine ($folder, $locale) {
    global $camyks;
    
    /* build file full path */
    $file = $folder.'/translation_'.$locale.$camyks->file_extension;

    /* load trad */
    $this->trads = array();
    if (file_exists ($file)) {
      $this->hasfile = true;
      require ($file);
    } else {
      $this->hasfile = false;
    }
  }
}
?>