<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Sep 2007
 * Last Modif Date	: Sep 2007
 *
 * Content_GenericArticleItem object for Content_GenericArticle module
 */

class Content_GenericArticleItem extends ModuleLibrary {
  
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_GenericArticleItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content description */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('date_', 'db', 'date', 'bigint unsigned', '', 0);
    $this->add_newItem('author', 'db', 'text', 'varchar', 32, '');
    /* database localised content */
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
    $this->add_newItem('subtitle', 'db', 'text', 'varchar', 255, '', true);
    $this->add_newItem('header', 'db', 'text', 'text', '', '', true);
    $this->add_newItem('note', 'db', 'text', 'text', '', '', true);
    /* text file localised content */
    $this->add_newItem('content', 'text', 'content','', '', '',  true);
    
    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean result
   * @access private
   */
  function check_data () {
    /* check symbolic name value */
    $this->_libItems['name']->check_value('symbolic_name', 'article');
    return true;
  }

  /*
   * initialise object
   * @return boolean success
   * @access private
   */
  function initialise () {
    global $camyks;
    /* generic initialise */
    parent::initialise();

    /* update author value with current admin user login */
    $this->_libItems['author']->value = $camyks->adminUser->login;

    return true;
  }
}
?>