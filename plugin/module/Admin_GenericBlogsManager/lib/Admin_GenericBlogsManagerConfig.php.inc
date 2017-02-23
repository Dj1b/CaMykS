<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Config
 * Create Date		: Apr 2008
 * Last Modif Date	: Apr 2008
 *
 * Admin_GenericBlogsManager configuration object
 *
 * News editor mode :
 * - 0 : Text only
 * - 1 : Limited web editor
 * - 2 : Advanced web editor
 * - 3 : Full web editor
 *
 * Comments validation mode values :
 * - 0 : validated by an admin
 * - 1 : validated on post
 *
 * Document shared mode value :
 * - 0 : shared with site documents
 * - 1 : shared into a specific module folder
 * - 2 : each user has its own folder into a specific module folder
 */

class Admin_GenericBlogsManagerConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_GenericBlogsManagerConfig ( $name, &$parent ) {
    global $camyks;
    parent::ModuleConfig( $name, $parent );
    /* object link configuration */
    $this->add_newItem('links_maxcount', 'int', 5);
    /* object news configuration */
    $this->add_newItem('news_editormode', 'int', 0);
    $this->add_newItem('news_allowvideo', 'boolean', false);
    $this->add_newItem('news_documentmode', 'int', 1);

    /* object comment configuration */
    $this->add_newItem('comments_validationmode', 'int', 1);

    /* generic initialisation */
    parent::init_config();
  }

  /* overwrite ModuleConfig methods */


  /* specific methods */

  /*
   * return available news editor modes
   * @return array
   * @access public
   */
  function get_newsEditorModes() {
    return array(0=>$this->get_translation('config_newseditormode_0'),
		 1=>$this->get_translation('config_newseditormode_1'),
		 2=>$this->get_translation('config_newseditormode_2'),
		 3=>$this->get_translation('config_newseditormode_3'));
  }

  /*
   * return available news document modes
   * @return array
   * @access public
   */
  function get_newsDocumentModes() {
    return array(0=>$this->get_translation('config_newsdocumentmode_0'),
		 1=>$this->get_translation('config_newsdocumentmode_1'),
		 2=>$this->get_translation('config_newsdocumentmode_2'));
  }

  /*
   * return available comment validation modes
   * @return array
   * @access public
   */
  function get_commentsValidationModes() {
    return array(1=>$this->get_translation('config_commentsvalidationmode_1'),
		 0=>$this->get_translation('config_commentsvalidationmode_0'));
  }
}
?>