<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CamykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Jun 2007
 * Last Modif Date	: Jun 2007
 *
 * Admin_InternalMessage object for Admin_MyMessages Module
 */

class Admin_InternalMessage extends ModuleLibrary {

  /*
   * constructor
   * @param integer $id
   * @param Module $module 
   */
  function Admin_InternalMessage ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content items */
    $this->add_newItem('senddate', 'db', 'date', 'bigint', '', time() );
    $this->add_newItem('fromuser', 'db', 'text', 'varchar', 16, '' );
    $this->add_newItem('fromstatus', 'db', 'int', 'tinyint', '', 0 );
    $this->add_newItem('touser', 'db', 'text', 'varchar', 16, '' );
    $this->add_newItem('tostatus', 'db', 'int', 'tinyint', '', 2 );
    $this->add_newItem('title', 'db', 'text', 'varchar', 64, '' );
    $this->add_newItem('content', 'db', 'text', 'text', '', '' );
    $this->add_newItem('maxmessages', 'temp', 'int', 'int', '', $this->_libParent->maxmessages );
  }
  
  /* overwrite ModuleLibrary methods */

  /*
   * check object data
   * @return boolean result
   * @access private
   */
  function check_data( ) {
    global $camyks;
    
    /* basic info */
    $this->_libItems['fromuser']->value = $camyks->adminUser->login;
    
    /* check receipt user login / id */
    if (  AdminUser::exists_login ( $this->_libItems['touser']->value ) === false ) {
      $this->_libError = 'touser_doesnt_exists';
      return false;
    }
    
    /* check if receipt user has some free slot on reveived box */
    $messagecount = $this->get_objectCount('touser="'.$this->_libItems['touser']->value.'" and tostatus>0'); 
    
    if ( $messagecount  >= $this->_libItems['maxmessages']->value ) {
      $this->_libError = 'touser_receivedboxfull';
      return false;
    }
    return true;
  }
  
  
  /* specific tool methods */

  /*
   * return messages in receive box
   * @return array
   * @access private
   */
  function get_reveivedBoxMessageList() {
    global $camyks;
    return $this->get_objectList(false,
				 'touser="'.$camyks->adminUser->login.'" and tostatus>0',
				 -1,
				 -1,
				 'senddate',
				 'desc');
  }

  /*
   * return messages in send box
   * @return array
   * @access private
   */
  function get_sentBoxMessageList() {
    global $camyks;
    return $this->get_objectList(false,
				 'fromuser="'.$camyks->adminUser->login.'" and fromstatus>0',
				 -1,
				 -1,
				 'senddate',
				 'desc');
  }
  
  /*
   * delete message list
   * @param array $pms
   * @param string $view
   * @return boolean success
   * @access private
   */
  function delete_messages ( $pms, $view ) {
    global $camyks;
    /* escape if no item exist */
    if ( count( $pms ) == 0 ) {
      return true;
    }
    /* try to delete from database messages marked as deleted as on both side */
    /* build sql query */
    $sql = 'delete from '.$this->_libSQLTable;
    if ( count ( $pms ) == 1 )
      $sql .= ' where id='.$pms[0].'';
    else 
      $sql .= ' where id in ('.implode(',', $pms).')';

    if ( $view == 'from' )
      $sql .= ' and tostatus=0;';
    else
      $sql .= ' and fromstatus=0;';
  
    /* execute sql query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* update all other message */
      return $this->update_messagesStatus ( $pms, $view, 0 );
    return false;
  }
  
  /*
   * update message list status
   * @param array $pms
   * @param string $view
   * @param integer $status
   * @return boolean success
   * @access private
   */
  function update_messagesStatus ( $pms, $view, $status=1 ) {
    global $camyks;
    /* escape if no item exist */
    if ( count( $pms ) == 0 ) {
      return true;
    }
    /* build sql query */
    $sql = 'update '.$this->_libSQLTable;
    $sql .= ' set '.$view.'status='.$status;
    if ( count ( $pms ) == 1 )
      $sql .= ' where id='.$pms[0].';';
    else 
      $sql .= ' where id in ('.implode(',', $pms).');';
    
    /* return result of sql query execution */
    return ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );
  }
}
?>