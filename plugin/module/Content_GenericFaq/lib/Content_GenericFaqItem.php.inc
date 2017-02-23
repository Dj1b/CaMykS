<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Apr 2007
 * Last Modif Date	: Apr 2007
 *
 * Content_GenericFaqItem object for Content_GenericFaq module
 */
class Content_GenericFaqItem extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_GenericFaqItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('listid', 'db', 'int', 'bigint unsigned', '', 0 );
    $this->add_newItem('position', 'db', 'int', 'int unsigned', '', 0);
    $this->add_newItem('language', 'db', 'text', 'varchar', 3, '');
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('title', 'db', 'etext', 'varchar', 255, '');
    $this->add_newItem('content', 'db', 'etext', 'text', '', '');
    /* generic init */
    $this->init_library();
  }
  
  /* overwrite ModuleLibrary methods */

  /*
   * check object data values
   * @return boolean result
   * @access private
   */
  function check_data( ) {
    if ( $this->id == 0 ) {
      $this->_libItems['position']->value = $this->get_itemNewIndex();
    }
    return true;
  }
  
  
  /* specific tool methods */

  /*
   * get faq item new index
   * @return int
   * @access private
   */
  function get_itemNewIndex( ) {
    global $camyks;
    /* build sql query */
    $sql = 'select count(id) as p';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where listid='.$this->_libItems['listid']->value;
    /* execute sql query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ )){
      if ( $data = mysql_fetch_assoc( $req ) ) {
	return ((int)$data['p'])+1;
      }
    }
    return 1;
  }


  /*
   * set position of object to position - 1
   * @return void
   * @access private
   */
  function move_up ( ) {
    global $camyks;
    /* get the other object id to move */
    $sql = 'select id';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where listid='.$this->_libItems['listid']->value;
    $sql .= ' and position<'.$this->_libItems['position']->value;
    $sql .= ' order by position desc';
    $sql .= ' limit 1';
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ )) {
      if ( $data = mysql_fetch_assoc( $req ) ) {
	$objid = $data['id'];
      } else {
	/* item is the first one, no need to move it up */
	return;
      }
    } else {
      return;
    }

    /* update item */
    $sql = 'update '.$this->_libSQLTable.' set position=position-1 where id='.$this->id;
    if ( !( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ )))
      return;

    /* update other item */
    $sql = 'update '.$this->_libSQLTable.' set position='.( $this->_libItems['position']->value ).' where id='.$objid;
    if ( !( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ )))
      return;

  }


  /*
   * set position of object to position + 1
   * @return void
   * @access private
   */
  function move_down ( ) {
    global $camyks;
    /* get the other object id to move */
    $sql = 'select id';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where listid='.$this->_libItems['listid']->value;
    $sql .= ' and position>'.$this->_libItems['position']->value;
    $sql .= ' order by position';
    $sql .= ' limit 1';
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ )) {
      if ( $data = mysql_fetch_assoc( $req ) ) {
	$objid = $data['id'];
      } else {
	/* item is the last one, no need to move it down */
	return;
      }
    } else {
      return;
    }

    /* update item */
    $sql = 'update '.$this->_libSQLTable.' set position=position+1 where id='.$this->id;
    if ( !( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ )))
      return;

    /* update other item */
    $sql = 'update '.$this->_libSQLTable.' set position='.( $this->_libItems['position']->value ).' where id='.$objid;
    if ( !( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ )))
      return;

  }


  /*
   * return object list for admin usage
   * @param integer $listid
   * @return array
   * @access private
   */
  function get_adminlist ( $listid  ) {
    return $this->get_objectList(true, 'listid='.$listid, -1, -1, 'position');
  }

  /*
   * return object list for site usage
   * @param integer $listid
   * @param integer $page
   * @param integer $bypage
   * @return array
   * @access private
   */ 
  function get_sitelist ( $listid, $page=-1, $bypage=-1  ) {
    global $camyks;
    if ( $page>-1 and $bypage>-1 )
      return $this->get_objectList(true,
				   'listid='.$listid.' and status=1 and language=\''.$camyks->current_language.'\'', 
				   $page*$bypage, 
				   $bypage, 
				   'position', 
				   '');
    return $this->get_objectList(true,
				 'listid='.$listid.' and status=1 and language=\''.$camyks->current_language.'\'', 
				 -1,
				 -1,
				 'position', 
				 '');
   }
  
  /*
   * return object count value
   * @param integer $listid
   * @param integer $status
   * @param string $language
   * @return integer
   * @access private
   */
  function get_listcount( $listid, $status=-1, $lg='' ) {
    global $camyks;
    $where = 'listid='.$listid;
    if ( $status > -1 ) {
      $where .= ' and status='.$status;
    }
    if ( $lg != '' ) {
      $where .= ' and language="'.$lg.'"';
    }
    return $this->get_objectCount( $where );
  }
}
?>