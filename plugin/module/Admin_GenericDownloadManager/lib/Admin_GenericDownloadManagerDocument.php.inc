<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date	: Mar 2008
 * Last Modif Date	: Sep 2014
 *
 * Admin_GenericDownloadManagerDocument object for Admin_GenericDownloadManager Module
 */

class Admin_GenericDownloadManagerDocument extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericDownloadManagerDocument ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* content */
    $this->add_newItem('category', 'db', 'int', 'int unsigned', '', 0);
    $this->add_newItem('active', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('lg', 'db', 'text', 'varchar', 4, '');
    $this->add_newItem('security', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
    $this->add_newItem('subtitle', 'db', 'text', 'varchar', 128, '', true);
    $this->add_newItem('filetitle', 'db', 'text', 'varchar', 128, '');
    $this->add_newItem('releasedate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('file', 'file', 'documents', '', '', '');

    /* temp content */
    $this->add_newItem('update_security', 'temp', 'int', '', '', 0);

    /* file object */
    $this->fsfile = null;

    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary method */

  /*
   * check object data
   * @return boolean result
   * @access public
   */
  function check_data() {

    /* check for security code update */
    if ($this->_libItems['update_security']->value == 1) {
      $v = $this->_libItems['releasedate']->value;
      $v .= $this->_libItems['filetitle']->value;
      $v .= $this->_libItems['category']->value;
      
      $this->_libItems['security']->value = substr(md5($v), 0, 8);
    }
    
    if ($this->_libItems['filetitle']->value == '' 
        and $this->_libItems['file']->upload === true) {
        $this->_libItems['filetitle']->value = $this->_libItems['file']->get_uploadedFileName();
    }
    
    return true;
  }

  /*
   * build sql condition for lists
   * @param array $params
   * @return string
   * @access public
   */
  function build_SQLCondition($params) {
    $search = array();
    if ( isset( $params['active'] ) and $params['active'] > -1 )
      $search[] = 'active='.$params['active'];
    if ( isset( $params['category'] ) and $params['category'] > 0 )
      $search[] = 'category='.$params['category'];
    return implode(',', $search);
  }

  /* specific tool methods */
  
  /*
   * get document link 
   * @return string
   * @access private
   */
  function get_link() {
    global $camyks;
    $link = $camyks->get_confValue('url');
    $link .= '/request.php?module='.$this->_libParent->name.'&did='.$this->id;
    if ($this->_libParent->config->vars['link_mode'] == 1)
      $link .= '&sid='.$this->vars['security'];
    return $link;
  }

  /*
   * get admin titles list
   * @param string $where
   * @return array
   * @access public
   */
  function get_titlesList($where='') {

    $titles = array();
    
    /* get language */
    $lg = $this->_libParent->get_adminEditionLanguage();

    /* build sql query */
    $sql = 'select objectid, title from '.$this->_libSQLLocaleTable;
    $sql .= ' where language="'.$lg.'"';
    if ( $where != '' ) {
      $sql .= ' and '.$where;
    }
    
    /* execute sql query */
    if ( $this->execute_DBQuery($sql, __LINE__ ))
      /* get data from database */
      while ( $data = $this->get_DBQueryDataLine())
	    $titles[$data['objectid']] = $data['title'];
	    
    /* send results */
    return $titles;
  }

  /*
   * get document count by categories
   * @param array $categories
   * @return array
   * @access public
   */
  function get_documentCountByCategories($categories=null) {

    $list = array();
    /* check categories */
    if ( is_array($categories) and count($categories) == 0)
      return $list;

    /* build sql query */
    $sql = 'select category,  count(id) as cnt from '.$this->_libSQLTable;
    if (  is_array($categories) and count($categories)>0 ) {
      $sql .= ' where category in ('.implode(',', $categories).')';
    }
    $sql .= ' group by category';

    /* execute sql query */
    if ( $this->execute_DBQuery($sql, __LINE__ ))
      /* get data from database */
      while ( $data = $this->get_DBQueryDataLine())
	    $list[$data['category']] = $data['cnt'];
	    
    /* send results */
    return $list;
  }

  /*
   * return file info
   * @return string
   * @access public
   */
  function get_fileInfos() {
    if ( $this->fsfile == null)
      $this->fsfile = new FSFile($this->vars['file']);
    return $this->fsfile->hsize.', '.$this->fsfile->typedesc;
  }
}
?>