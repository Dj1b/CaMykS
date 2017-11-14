<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0
 * Object Version 	: 1.0
 * Object Type      : Plugin / Module Lib 
 * Creation Date	: Mar 2007
 * Last Modif Date	: Nov 2017
 *
 * Administrator Group object
 * Contains 2 default groups : all / none
*/

class AdminGroup {
  /* variables */
  var $name;
  var $title;
  var $description;

  /* other variables */
  var $is_new;
  var $users; /* users as list */
  var $users_; /* users as string */
  
  /* generic library vars */
  var $_libError;
  var $_libDesc;
  var $_libIsInstalled;
  
  /*
   * constructor
   * @param string $name
   */
  function AdminGroup ( $name = '', $parent = null) {
    $this->name = $name;
    $this->is_new = ( $name == '' ? 1 : 0 );
    /* update generic library vars */
    $this->_libError = '';
    $this->_libDesc = 'Module: Admin_Group Lib: AdminGroup';
    $this->_libIsInstalled = null;
    $this->_libParent = &$parent;
  }

  /* object i/o methods */

  /*
   * get admingroup object
   * @return boolean success
   * @access private
   */
  function get ( ) {
    if ( $this->name == '' )
      return $this->initialise();
    else 
      return $this->get_fromDatabase(); 
  }

  /*
   * initialise new object
   * @return boolean success
   * @access private
   */
  function initialise ( ) {
    $this->description = '';
    $this->users = array();
    $this->is_new = 1;
    return true;
  }

  /*
   * save object
   * @return boolean success
   * @access private
   */
  function save ( ) {
    if ( $this->check_data() ) {
      if ( $this->is_new == 1 and  $this->create_toDatabase()
	   or $this->update_toDatabase() )
	return $this->update_usersToDatabase();
    }
    return false;
  }
    
  /*
   * get object from database
   * @return boolean success
   * @access private
   */
  function get_fromDatabase( ) {
    global $camyks;
    /* build sql query */
    $sql = "SELECT *";
    $sql .= " FROM admin_group";
    $sql .= " WHERE name='".$this->name."'";
    
    /* execute sql query */
    if ( $req = $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      /* get data from database */
      if ( $data = $camyks->db_conn->get_queryDataLine()) {
	$this->get_fromArray( $data );
	$this->is_new = 0;
	return $this->get_usersFromDatabase();
      } else {
	$this->initialise();
	return false;
      }
    }
    return false;
  }
    
  /*
   * create new admingroup object to database
   * @return boolean success
   * @access private
   */
  function create_toDatabase ( ) {
    global $camyks;
    /* build sql query */
    $sql = 'INSERT INTO `admin_group` (';
    $sql .= '`name`';
    $sql .= ', `description`';
    $sql .= ' ) VALUES ( ';
    $sql .= '"'.$this->name.'"';
    $sql .= ',"'.addslashes($this->description).'"';
    $sql .= ')';
    /* return result of sql query execution */
    return ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );
  }
  
  /*
   * update admingroup object to database
   * @return boolean success
   * @access private
   */
  function update_toDatabase ( ) {
    global $camyks;
    /* build sql query */
    $sql = 'UPDATE `admin_group` ';
    $sql .= ' SET description="'.addslashes($this->description).'"';
    $sql .= ' WHERE name="'.$this->name.'"';
    /* return result of sql query execution */
    return ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );    
  }

  /*
   * delete admingroup object from database
   * @return boolean success
   * @access private
   */
  function delete_fromDatabase( ) {
    global $camyks;
    /* build sql query */
    $sql = 'delete from admin_group where name="'.$this->name.'";';
    /* return result of sql query execution */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {   
      /* build sql query */
      $sql = 'delete from admin_user_group where group="'.$this->name.'";';
      /* return result of sql query execution */
      return ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );    
    }
    return false;
  }

  /*
   * get user list from database
   * @return boolean success
   * @access private
   */
  function get_usersFromDatabase() {
    global $camyks;
    /* build sql query */
    $sql = 'select user';
    $sql .= ' from admin_user_group';
    $sql .= ' where `group`="'.$this->name.'"';
    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      /* get data from database */
      while ( $data = $camyks->db_conn->get_queryDataLine()) {
	    $this->users[] = $data['user'];
      }
      /* encode user list as string */
      $this->users_ = implode( $this->users, ':' );
      return true;
    }
    return false;
  }

  /*
   * update user list to database
   * @return boolean success
   * @access private
   */
  function update_usersToDatabase() {
    global $camyks;

    /* delete previous items */

    /* build sql query */
    $sql = 'delete from admin_user_group where `group`="'.$this->name.'";';
    /* add new items */
    if ( count($this->users) > 0 and ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ))) {
      $isFirst = true;
      $sql = 'insert into admin_user_group ( `group`, `user` ) values';
      foreach ( $this->users as $u ) {
	if ( $isFirst ) {
	  $isFirst = false;
	} else {
	  $sql .= ',';
	}
	$sql .= ' ("'.$this->name.'", "'.$u.'")';
      }
    }
    /* return result of sql query execution */
    return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
  }
  
  /*
   * install admingroup table in database
   * @return boolean success
   * @access private
   */
  function install() {
    global $camyks;
    
    /* create group table */
    $fields = array(
        array('name'=>'name', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>32, 'default'=>''),
        array('name'=>'description', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>64, 'default'=>''),
    );
    
    if ($camyks->db_conn->create_table('admin_group', $fields, $camyks->get_mysqlencodingvalue(), false, array('name'))) { 
      /* create user/group links table */
      $fields = array(
        array('name'=>'user', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>32, 'default'=>''),
        array('name'=>'group', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>32, 'default'=>''),
      );
    
      return ($camyks->db_conn->create_table('admin_user_group', $fields, $camyks->get_mysqlencodingvalue(), false, array('user', 'group')));
    }
    
    /* build sql query *
    $sql = 'CREATE TABLE IF NOT EXISTS `admin_group` (';
    $sql .= ' `name` VARCHAR ( 32 ) NOT NULL ,';
    $sql .= ' `description` VARCHAR ( 64 ) NOT NULL ,';
    $sql .= ' PRIMARY  KEY ( `name` ) ';
    $sql .= ')';
    $sql .= ' CHARACTER SET '.$camyks->get_mysqlencodingvalue( ).'';
    /* execute sql query *
    if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      $sql = 'CREATE TABLE IF NOT EXISTS `admin_user_group` (';
      $sql .= ' `user` VARCHAR ( 32 ) NOT NULL ,';
      $sql .= ' `group` VARCHAR ( 32 ) NOT NULL ,';
      $sql .= ' PRIMARY  KEY ( `user`,`group` ) ';
      $sql .= ')';
      $sql .= ' CHARACTER SET '.$camyks->get_mysqlencodingvalue( ).'';
      /* execute sql query *
      return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );
    }
    */
    return false;
  }
  
  /*
   * check is object is installed
   * @return boolean success
   * @access private
   */
  function is_installed ( ) {
    global $camyks;
    
    if (!isset($this->_libIsInstalled)) {
      /* check database presence in plugin manager module */
      if (isset($camyks->modules['Admin_PluginManager']))
        $this->_libIsInstalled = $camyks->modules['Admin_PluginManager']->check_tableExists('admin_user_group');
      else {
        /* load table list */
        $tl = $camyks->db_conn->get_tableList();
    
        /* check if main table is in installed table list */
        $this->_libIsInstalled = in_array('admin_user_group', $tl);
      }
    }
    return $this->_libIsInstalled;
  }

  /*
   * get object data from header
   * @param string $prefix
   * @return void
   * @access private
   */
  function get_fromHeader( $prefix = '' ) {
    global $camyks;
    $this->name = $_REQUEST['name'];
    $this->description = $_REQUEST['description'];
    /* get is_new value */
    $this->is_new = ( isset ( $_REQUEST['is_new'] ) ? $_REQUEST['is_new'] : 1 );
    /* get user list as string */
    $this->users_ = $_REQUEST['users'];
    $this->users = explode( ':', $this->users_ );
  }
  
  /*
   * get object data from array
   * @param array $data
   * @access private
   */
  function get_fromArray( $data ) {
    $this->title = $data['name'];
    $this->description = stripslashes( $data['description'] );
  }

  /* object check methods */

  /*
   * parse and check all data
   * @return boolean result
   * @access private
   */
  function check_data( ) {
    global $camyks;

    if ( $this->is_new == 1 ) {
      /* check empty name */
      if ( $this->name == '' ) {
	    $this->_libError = 'erroremptyname';
	    return false;
      }
      /* check name first and last char validity */
      if ( $this->name != trim ( $this->name ) ) {
	    $this->_libError = 'errorbadname';
	    $this->name = trim ( $this->name );
	    return false;
      }
      /* check name length */
      if ( strlen($this->name) < 3 ) {
	    $this->_libError = 'errorshortname';
	    return false;
      }
      
      /* check name chars validity */
      $n = string_parseSpecialChars($this->name, array('pattern'=>'/[^_a-zA-Z0-9]/'));
      if ( $this->name != $n ) {
	    $this->_libError = 'errorbadname';
	    $this->name = $n;
	    return false;
      }
      /* check existing name */
      if ( $this->exists_group($this->name)) {
	    $this->_libError = 'errorexistingname';
	    return false;
      }
    }
    return true;
  }


  /*
   * check if object name already exists
   * @param string $name
   * @return boolean result
   * @access private
   */
  function exists_group( $name ) {
    global $camyks;
    
    /* build sql query */
    $sql = 'select name';
    $sql .= ' from admin_group';
    $sql .= ' where name="'.$name.'"';
    
    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__ ) ) {
      /* get value from database */
      if ( $camyks->db_conn->get_queryDataLine()) {
	    return true;
      }
    }
    return false;
  }

  /*
   * check if user is in object
   * @param string $user
   * @return boolean result
   * @access public
   */
  function is_userInGroup( $user ) {
    if ( $this->name == 'all' ) {
      return true;
    } else if ( $this->name == 'none' ) {
      return false;
    } else if ( in_array( $user, $this->users )){
      return true;
    }
    return false;
  }

  /* list methods */

  /*
   * return object list
   * @return array
   * @access public
   */
  function get_objectList() {
    global $camyks;
    $list = array();
    
    $g = new AdminGroup ( 'all' );
    $g->title = $camyks->get_translation('mod_admin_group_allgroupname');
    $g->users = array();
    $list['all'] = $g;
    $g = new AdminGroup ( 'none' );
    $g->title = $camyks->get_translation('mod_admin_group_nonegroupname');
    $g->users = array();
    $list['none'] = $g;

    /* get groups */

    /* build sql query */
    $sql = 'SELECT * ';
    $sql .= ' FROM admin_group';
    $sql .= ' ORDER BY name';
    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      /* get informations from sql query */
      while ( $data = $camyks->db_conn->get_queryDataLine()) {
	    $g = new AdminGroup( $data['name'] );
	    $g->get_fromArray( $data );
	    $g->users = array();
	    $list[$data['name']] = $g;
      }
    }

    /* get users in groups */

    /* build sql query */
    $sql = 'SELECT * ';
    $sql .= ' FROM admin_user_group';
    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      /* get informations from sql query */
      while ( $data = $camyks->db_conn->get_queryDataLine()) {
	    if (isset ( $list[$data['group']] )) 
	      $list[$data['group']]->users[] = $data['user'];
      }
    }
    return $list;
  }

  /* static methods */

  /*
   * return object name list
   * @return $array
   * @access private
   */
  function static_getNameList() {
    global $camyks;
    $list = array();
    
    $list[] = $this->get_translation('allgroupname');
    $list[] = $this->get_translation('nonegroupname');

    /* build sql query */
    $sql = 'SELECT name ';
    $sql .= ' FROM admin_group';
    $sql .= ' ORDER BY name';
    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      /* get informations from sql query */
      while ( $data = $camyks->db_conn->get_queryDataLine()) {
	    $list[] = $data['name'];
      }
    }
    return $list;
  }

  /*
   * return object list in admin mode
   * @return $array
   * @access private
   */
  function static_getAdminList() {
    global $camyks;
    $list = array();
    
    /* add default groups */
    $list[] = array( 'name' => $this->_libParent->get_translation('allgroupname'),
		     'description' => $this->_libParent->get_translation('allgroupdesc'),
		     'editable' => false );
    $list[] = array( 'name' => $this->_libParent->get_translation('nonegroupname'),
		     'description' => $this->_libParent->get_translation('nonegroupdesc'),
		     'editable' => false );

    /* build sql query */
    $sql = 'SELECT name, description ';
    $sql .= ' FROM admin_group';
    $sql .= ' ORDER BY name';
    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__) ) {
      /* get informations from sql query */
      while ( $data = $camyks->db_conn->get_queryDataLine()) {
	    $data['editable'] = true;
	    $list[] = $data;
      }
    }
    return $list;
  }
}
?>