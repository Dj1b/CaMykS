<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author               : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Lib
 * Create Date          : Apr 2008
 * Last Modif Date      : Apr 2008
 *
 * Admin_GenericBlogCommentItem object for Admin_GenericBlogsManager module
*/
class Admin_GenericBlogCommentItem extends ModuleLibrary {  
  /*
   * Constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericBlogCommentItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('newsid', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 1);
    $this->add_newItem('title', 'db', 'etext', 'varchar', 64, '');
    $this->add_newItem('content', 'db', 'etext', 'text', '', '');
    $this->add_newItem('author', 'db', 'etext', 'varchar', 32, '' );
    $this->add_newitem('ndate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('email', 'db', 'text', 'varchar', 128, '' );
    $this->add_newItem('website', 'db', 'text', 'varchar', 128, '' );
    $this->add_newItem('ipaddress', 'db', 'text', 'varchar', 48, '' );
    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */
  
  /*
   * check object data before saving
   * @return boolean result
   * @access private
   */
  function check_data() {
    /* check newsid */
    if ( $this->_libItems['newsid']->value == 0 ) {
      $this->_libError = $this->get_translation('savecommentfailed_internal_error');
      return false;
    }

    /* parse content */
    $content = $this->_libItems['content']->value;
    $content = strip_tags($content);
    $content = preg_replace(array('/[\ ]+/', '/(\n\r|\n|\r)+/'), array(' ', "\n"), $content);
    /* allow link */
    $content = preg_replace('/(http:\/\/[^\s]*)/', '<a href="$1" target="_blank">$1</a>', $content);
    $this->_libItems['content']->value = $content;

    /* check content */
    if ( $this->_libItems['content']->value == '' ) {
      $this->_libError = $this->get_translation('savecommentfailed_emptycontent');
      return false;
    }

    /* parse author */
    $author = $this->_libItems['author']->value;
    $author = strip_tags($author);
    $author = preg_replace('/\s\s+/', ' ', $author);
    $this->_libItems['author']->value = $author;
    /* check author */
    if ( $this->_libItems['author']->value == '' ) {
      $this->_libError = $this->get_translation('savecommentfailed_emptyauthor');
      return false;
    }

    /* check email */
    if ( mail_isValidEmail( $this->_libItems['email']->value) === false ){
      $this->_libError = $this->get_translation('savecommentfailed_invalidemail');
      return false;
    } 
    return true;
  }

  /* specific data management methods */
  
  /*
   * delete all comments from given news
   * @param integer $newsid
   * @return boolean success
   * @access private
   */
  function delete_newsComments( $newsid=null ) {
    global $camyks;
    /* check news id value */
    if ( ! ($newsid > 0) )
      return false;

    /* build sql query */
    $sql = 'delete from '.$this->_libSQLTable;
    $sql .= ' where newsid='.$newsid;

    /* return query execution result */
    return (mysql_query( $sql ) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ));
  }

  /* specific data gathering methods */

  /*
   * count comments for given news list by status
   * @param array $newsids
   * @return array
   * @access private
   */
  function count_newsCommentsByStatus($newsids) {
    global $camyks;

    /*  check newsids */
    $coms = array();
    if ( count( $newsids ) == 0 )
      return $coms;

    /* pre-initialise coms values */
    foreach ( $newsids as $id )
      $coms[$id] = array(0, 0, 0);
    
    /* build sql query */
    $sql = 'select newsid, status, count(id) as c';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where newsid IN('.implode(',', $newsids).')';
    $sql .= ' group by newsid, status';
    
    /* execute query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* gather data */
      while ( $data = mysql_fetch_assoc( $req ))
	$coms[$data['newsid']][$data['status']] = $data['c'];
    return $coms;
  }

  /*
   * count comments for given news list
   * @param array $newsids
   * @return array
   * @access private
   */
  function count_newsComments($newsids, $status=null) {
    global $camyks;

    /*  check newsids */
    $coms = array();
    if ( count( $newsids ) == 0 )
      return $coms;
    
    /* build sql query */
    $sql = 'select newsid, count(id) as c';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where newsid IN('.implode(',', $newsids).')';
    if ( isset($status ) )
      $sql .= ' and status='.$status;
    $sql .= ' group by newsid';
    
    /* execute query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* gather data */
      while ( $data = mysql_fetch_assoc( $req ))
	$coms[$data['newsid']] = $data['c'];
    return $coms;
  }

  /*
   * return unread message count for current user news
   * @return integer
   * @access private
   */
  function count_userNewsUnreadComments() {
    global $camyks;

    /* get Newsitem sql table */
    if ( isset($this->_libParent->newsItem->_libSQLTable) )
      $newsTable = $this->_libParent->newsItem->_libSQLTable;
    else
      $newsTable = 'admin_genericblognewsitem';
      

    /* build sql query */
    $sql = 'select count('.$this->_libSQLTable.'.id) as c';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ', '.$newsTable;
    $sql .= ' where '.$newsTable.'.author="'.$camyks->adminUser->login.'"';
    $sql .= ' and '.$this->_libSQLTable.'.newsid='.$newsTable.'.id';
    $sql .= ' and '.$this->_libSQLTable.'.status=0';
    
    /* execute query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* gather data */
      if ( $data = mysql_fetch_assoc( $req ))
	return $data['c'];
    return 0;
  }

  /*
   * return news ids with un read comments
   * @return array
   * @access public
   */
  function get_newsWithUnreadComments() {
    global $camyks;

    $list = array();
    
    /* build sql query */
    $sql = 'select id, newsid';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where status=0';
    
    /* execute query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* gather data */
      while ( $data = mysql_fetch_assoc( $req ))
	$list[]=$data['newsid'];

    /* return list */
    return $list;
  }

  /* specific tool methods */

  /*
   * return available status list for this object type
   * @return array
   * @access public
   */
  function get_statusList() {
    return array(0=>$this->get_translation('comment_statusmode_0'),
		 1=>$this->get_translation('comment_statusmode_1'),
		 2=>$this->get_translation('comment_statusmode_2'));
  }


}
?>