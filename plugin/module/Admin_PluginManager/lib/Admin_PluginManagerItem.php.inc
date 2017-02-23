<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Library
 * Creation Date	: Oct 2008
 * Last Modif Date	: Oct 2008
 *
 * Admin_PluginManagerItem library
 */

class Admin_PluginManagerItem {

  /*
   * constructor
   * @param integer $id;
   * @param module $parent
   */
  function Admin_PluginManagerItem($id=0, $parent=null) {
    $this->id = $id;
    $this->_libParent = $parent;
    $this->_libIsInstalled = null;
  }

  /* generic module library object definition methods */
  
  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install( ) {
    global $camyks;
    
    /* build sql query */
    $sql ='create table if not exists admin_pluginmanager';
    $sql .= '( plugin varchar (255) not null,';
    $sql .= ' type varchar (16) not null,';
    $sql .= ' location varchar (8) not null,';
    $sql .= ' active tinyint default 0,';
    $sql .= ' version varchar(16) default "1.0",';
    $sql .= ' primary key(plugin, type));';
        
    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      /* add plugin_manager installation value */
      $sql = 'insert ignore into admin_pluginmanager';
      $sql .= ' ( plugin, type, location, active, version ) VALUES';
      $sql .= ' ( "'.$this->_libParent->name.'", "module", "camyks", 1, "'.$this->_libParent->version.'");';
      /* execute sql query */
      return ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );
    }
    return false;
  }
 
  /*
   * check installation
   * @return boolean result
   * @access private
   */
  function is_installed ( ) {
    global $camyks;
    if ( $this->_libIsInstalled == null ) {
    
      /* check with plugin manager */
      if (isset($camyks->modules['Admin_PluginManager'])) {
        $this->_libIsInstalled = $camyks->modules['Admin_PluginManager']->check_tableExists('admin_pluginmanager');
      } else {
        /* build sql query */
        $sql = "show tables like 'admin_pluginmanager'";
      
        /* execute sql query */
        if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) { 
	      /* get data from database */
	      $this->_libIsInstalled = ($camyks->db_conn->get_queryDataLine()!==false);
        }
      }
    }
    return $this->_libIsInstalled;
  }

  /* generic module library single object data manipulation */

  /*
   * get plugin data from header
   * @return void
   * @access private
   */
  function get_fromHeader() {
    $this->pluginvalue = $_REQUEST['plugin'];
    $this->typevalue = $_REQUEST['type'];
    $this->locationvalue = $_REQUEST['location'];
  }

  /*
   * save plugin info in database
   * @return boolean success
   * @access private
   */
  function save_toDatabase( ) {
    global $camyks;

    /* build sql query */
    $sql = 'select * from admin_pluginmanager';
    $sql .= ' where plugin="'.$this->pluginvalue.'"';
    $sql .= ' and type="'.$this->typevalue.'"';

    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) { 

      /* check query result */
      if ($camyks->db_conn->get_queryDataLine()) {
	    return $this->update_toDatabase();
      } else {
	    return $this->create_toDatabase();
      }
    }
    return false;
  }

  /*
   * create new entry in database
   * @return boolean success
   * @access private
   */
  function create_toDatabase() {
    global $camyks;
    
    /* build sql query */
    $sql = 'insert into admin_pluginmanager';
    $sql .= ' ( plugin, type, location, active, version ) VALUES';
    $sql .= ' ( "'.$this->pluginvalue.'","'.$this->typevalue;
    $sql .= '","'.$this->locationvalue.'",'.$this->activevalue.',';
    $sql .= '"'.$this->versionvalue.'");';
    
    /* execute sql query */
    return ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );
  }

  /*
   * delete item from database
   * @param $p array
   * @return boolean success
   * @access private
   */
  function delete_fromDatabase( $p ) {
    global $camyks;
    
    /* build sql query */
    $sql = 'delete from admin_pluginmanager';
    $sql .= ' where plugin="'.$p['plugin'].'"';
    $sql .= ' and type="'.$p['type'].'"';
    $sql .= ' and location="'.$p['location'].'"';
    
    /* execute sql query */
    return ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );
  }
  
  /*
   * update existing entry in database
   * @return boolean success
   * @access private
   */
  function update_toDatabase() {
    global $camyks;
    
    /* build sql query */
    $sql = 'update admin_pluginmanager';
    $sql .= ' set active='.$this->activevalue;
    $sql .= ' where plugin="'.$this->pluginvalue.'"';
    $sql .= ' and type="'.$this->typevalue.'"';
    
    /* execute sql query */
    return ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );
  }

  /*
   * plugin activation method
   * @param string $plugin
   * @param string $type
   * @param string $location
   * @param string $active
   * @return boolean success
   * @access private
   */
  function active_plugin( $plugin=null, $type=null, $location=null, $active=null ) {
    if ( isset( $plugin ) )
      $this->pluginvalue = $plugin;
    if ( isset( $type ) )
      $this->typevalue = $type;
    if ( isset( $location ) )
      $this->locationvalue = $location;
    if ( isset( $active) )
      $this->activevalue = $active;

    /* install module if needed */
    switch ( $this->typevalue ) {
    case 'module':
      $plugin = module_get ($this->pluginvalue, $this->locationvalue);
      if ( $plugin->is_installed()===false and $plugin->install()===false ) {
	return false;
      }
      break;
    case 'template':
      $plugin = template_get ($this->pluginvalue, $this->locationvalue);
      break;
    case 'theme':
      $plugin = theme_get ($this->pluginvalue, $this->locationvalue);
      break;
    case 'input':
      $plugin = input_get ($this->pluginvalue, $this->locationvalue);
      break;
    }
    $this->versionvalue = $plugin->version;
    /* active plugin in database */
    return $this->save_toDatabase( );
  }

  /*
   * update plugin version
   * @param string $plugin
   * @param string $type
   * @param string $version
   * @return boolean success
   * @access private
   */
  function update_pluginVersion($plugin, $type, $version) {
    global $camyks;
    
    /* build sql query */
    $sql = 'update admin_pluginmanager';
    $sql .= ' set version="'.$version.'"';
    $sql .= ' where plugin="'.$plugin.'"';
    $sql .= ' and type="'.$type.'"';
    
    /* execute sql query */
    return ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) );    
  }

  /* generic module library multi object data manipulation */

  /*
   * get plugin list
   * @return array
   * @access private
   */
  function get_objectList() {
    global $camyks;

    $plugins = array();

    /* build sql query */
    $sql = 'select *';
    $sql .= ' from admin_pluginmanager';

    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
    
      /* get data from database */
      while ($data = $camyks->db_conn->get_queryDataLine())
	    $plugins[] = $data;
    return $plugins;
  }
}
?>