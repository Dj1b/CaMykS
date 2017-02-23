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
 * Admin_GenericBlogTagItem object for Admin_GenericBlogsManager module
*/
class Admin_GenericBlogTagItem extends ModuleLibrary {
  /*
   * Constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericBlogTagItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('newsid', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('title', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('author', 'db', 'text', 'varchar', 32, '' );
    /* generic initialisation */
    $this->init_library();
  }
  
  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean result
   * @access public
   */
  function check_data() {
    /* update name value */
    $this->_libItems['name']->value = string_parseSpecialChars(strtolower($this->_libItems['title']->value), array('pattern'=>'/[^\w]/'));
    return true;
  }
  
  /* value methods */

  /*
   * return tag list
   * @param boolean $tagMode, the tag counter mode, true=global, false=current admin only
   * @return array
   * @access public
   */
  function get_countTagList($tagMode=false) {
    global $camyks;
    /* build the list */
    $tagList = array();

    /* build sql query */
    $sql = 'select title, count(id) as counter';
    $sql .= ' from '.$this->_libSQLTable;
    if ( $tagMode !== true )
      $sql .= ' where author="'.$camyks->adminUser->login.'"';
    $sql .= ' group by title';
    /* execute query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* gather results */
      while ( $data = mysql_fetch_assoc( $req ))
	$tagList[stripslashes($data['title'])] = $data['counter'];
    
    return $tagList;
  }

  /*
   * update tag objects
   * @param string $tag the old tag value
   * @param string $tagvalue the new tag value
   * @return boolean success
   * @access private
   */
  function update_tagTitle($tag, $tagValue, $tagMode=false) {
    global $camyks;

    /* get name */
    $nameValue = string_parseSpecialChars(strtolower($tagValue), array('pattern'=>'/[^\w]/'));

    if ( $tagValue == '' or $nameValue == '' )
      return false;
    
    if ( $tag == '' ) {
      /* update object data */
      $this->_libItems['newsid']->value = 0;
      $this->_libItems['author']->value = $camyks->adminUser->login;
      $this->_libItems['title']->value = $tagValue;
      $this->_libItems['name']->value = $nameValue;
      return $this->save();
    } else {
      /* build update tags sql query */
      $sql = 'update '.$this->_libSQLTable;
      $sql .= ' set title="'.$tagValue.'"';
      $sql .= ', name="'.$nameValue.'"';
      $sql .= ' where title="'.$tag.'"';
      if ( $tagMode !== true )
	$sql .= ' and author="'.$camyks->adminUser->login.'"';
      /* execute query */
      return ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );
    }
  }
  
  /*
   * delete tag objects from title
   * @param string $tag the tag to delete
   * @return boolean succes
   * @access private
   */
  function delete_tagTitle($tag, $tagMode=false) {
    global $camyks;
    /* build sql query */
    $sql = 'delete from '.$this->_libSQLTable.' where title="'.$tag.'"';
    if ( $tagMode !== true )
      $sql .= ' and author="'.$camyks->adminUser->login.'"';

    /* execute query */
    return ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );    
  }

  /* 
   * delete tag objects from ids
   * @param array $tags the tags ids to delete
   * @return boolean success
   * @access private
   */
  function delete_tagIDs($tags=array()) {
    global $camyks;
    
    /* check array */
    if ( count($tags) == 0 )
      return true;

    /* build sql query */
    $sql = 'delete from '.$this->_libSQLTable.' where id IN('.implode(',',$tags).')';

    /* execute query */
    return ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );    
  }

  /*
   * delete tags object from given news
   * @param integer $newsid the targeted news
   * @return boolean success
   * @access private
   */
  function delete_newsTags($newsid=null) {
    global $camyks;

    /* check newsid */
    if ( !isset($newsid) )
      return false;

    /* build sql query */
    $sql = 'delete from '.$this->_libSQLTable.' where newsid='.$newsid;

    /* execute query */
    return ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );    
  }

  /*
   * prune old tags from given news
   * @param integer $newsid the targeted news
   * @param array $tagids the tags to keep
   * @return boolean success
   * @access private
   */
  function prune_oldNewsTags($newsid=null, $tags=array()) {
    global $camyks;

    /* check newsid */
    if ( !isset($newsid) )
      return false;

    /* check tags */
    if ( count($tags) == 0 )
      return $this->delete_newsTags( $newsid );

    /* build sql query */
    $sql = 'delete from '.$this->_libSQLTable.' where newsid='.$newsid.' and id NOT IN ('.implode(',', $tags).')';

    /* execute query */
    return ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );    
  }

  /*
   * return tag unique titles list
   * @return array
   * @access private
   */
  function get_titleList($tagMode=false) {
    global $camyks;

    /* build the list */
    $tagList = array();

    /* build sql query */
    $sql = 'select title';
    $sql .= ' from '.$this->_libSQLTable;
    if ( $tagMode !== true )
      $sql .= ' where author="'.$camyks->adminUser->login.'"';
    $sql .= ' group by title';

    /* execute query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )

      /* gather results */
      while ( $data = mysql_fetch_assoc( $req ))
	$tagList[] = stripslashes($data['title']);

    /* return result */
    return $tagList;
  }
}
?>