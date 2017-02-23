<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Config
 * Creation Date	: Jun 2015
 * Last Modif Date	: Jun 2015
 *
 * Admin_GenericMediaLibraryManagerConfig Object 
 */

class Admin_GenericMediaLibraryManagerConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_GenericMediaLibraryManagerConfig ( $name, &$parent ) {
    parent::ModuleConfig( $name, $parent );

    /* config items */
    $this->add_newItem('picture_maxFileSize', 'float', 8 );
    $this->add_newItem('picture_resizeMode', 'integer', 0);
    $this->add_newItem('picture_backgroundColor', 'string', '#FFFFFF');
    $this->add_newItem('picture_fileType', 'integer', 0);
    $this->add_newItem('picture_jpgQuality', 'integer', 70);
    $this->add_newItem('picture_pictureWidth', 'int', 800 );
    $this->add_newItem('picture_pictureHeight', 'int', 600 );
    $this->add_newItem('picture_thumbWidth', 'int', 120 );
    $this->add_newItem('picture_thumbHeight', 'int', 100 );

    /* generic initialisation */
    parent::init_config();
  }
  
  /* specific tool methods */
  
  /*
   * return resize mode list
   * @return array
   * @access parent
   */
  function get_resizeModeList() {
    return array(0 => $this->get_translation('pictureresizemode_fixedsize'),
                 1 => $this->get_translation('pictureresizemode_maxsize'));
  }
  
  /*
   * return image type value list
   * @return array
   * @access private
   */
  function get_fileTypeList() {
    return array(0 => $this->get_translation('imagefiletype_original'),
                 1 => $this->get_translation('imagefiletype_forcedtojpg'),
                 2 => $this->get_translation('imagefiletype_forcedtogif'),
                 3 => $this->get_translation('imagefiletype_forcedtopng'),);
  }
}
?>