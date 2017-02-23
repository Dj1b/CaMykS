<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Lib
 * Creation Date    : Jul 2010
 * Last Modif Date  : Jul 2010
 *
 * Content_TwitterStatusesViewerItem object for Content_TwitterStatusesViewer module
*/

class Content_TwitterStatusesViewerItem extends ModuleLibrary {
  /*
   * Constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_TwitterStatusesViewerItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('account', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('tweetcount', 'db', 'int', 'tinyint unsigned', '', 4);
    $this->add_newItem('style', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('datedisplay', 'db', 'int', 'tinyint unsigned', '', 0);

    /* generic init */
    $this->init_library();
  }
 
  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean result
   * @access private
   */
  function check_data( ) {
    global $camyks;
    /* check name */
    $this->_libItems['name']->check_value('symbolic', 'twitter_statuses');

    /* return result */
    return true;
  }

  /* specific methods */

  /* 
   * return account last statuses
   * @return array
   * @access private
   */
  function load_statuses() {
    return file_get_contents('http://twitter.com/statuses/user_timeline/'.$this->vars['account'].'.xml?count='.$this->vars['tweetcount']);
    //return file_get_contents('http://devel.skymac.org/xml.xml');
  }
}
?>