<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Library
 * Creation Date	: Oct 2008
 * Last Modif Date	: Oct 2017
 *
 * Admin_PluginManagerItem library
 */

final class Admin_PluginManagerItem {
  
  private $_libIsInstalled;

  /*
   * constructor
   * @param integer $id;
   * @param module $parent
   */
  public function __construct($id=0, $parent=null) {
    $this->id = $id;
    $this->_libParent = $parent;
    $this->_libIsInstalled = null;
  }

  /* generic module library object definition methods */
  
  /*
   * install module
   * @return boolean success
   * @access public
   */
  public function install() {
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
   * @access public
   */
  public function is_installed ( ) {
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
   * @access public
   */
  public function get_fromHeader() {
    $this->pluginvalue = isset($_REQUEST['plugin'])?$_REQUEST['plugin']:'';
    $this->typevalue = isset($_REQUEST['type'])?$_REQUEST['type']:'';
    $this->locationvalue = isset($_REQUEST['location'])?$_REQUEST['location']:'';
  }

  /*
   * save plugin info in database
   * @return boolean success
   * @access public
   */
  public function save_toDatabase( ) {
    global $camyks;

    /* build sql query */
    $sql = 'select * from admin_pluginmanager';
    $sql .= ' where plugin="'.addslashes($this->pluginvalue).'"';
    $sql .= ' and type="'.addslashes($this->typevalue).'"';

    /* execute sql query */
    if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) { 
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
   * @access public
   */
  public function create_toDatabase() {
    global $camyks;
    
    /* build sql query */
    $sql = 'insert into admin_pluginmanager';
    $sql .= ' ( plugin, type, location, active, version ) VALUES';
    $sql .= ' ( "'.addslashes($this->pluginvalue).'","'.addslashes($this->typevalue);
    $sql .= '","'.addslashes($this->locationvalue).'",'.addslashes($this->activevalue).',';
    $sql .= '"'.addslashes($this->versionvalue).'");';
    
    /* execute sql query */
    return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
  }

  /*
   * delete item from database
   * @param $p array
   * @return boolean success
   * @access public
   */
  public function delete_fromDatabase( $p ) {
    global $camyks;
    
    /* build sql query */
    $sql = 'delete from admin_pluginmanager';
    $sql .= ' where plugin="'.addslashes($p['plugin']).'"';
    $sql .= ' and type="'.addslashes($p['type']).'"';
    $sql .= ' and location="'.addslashes($p['location']).'"';
    
    /* execute sql query */
    return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
  }
  
  /*
   * update existing entry in database
   * @return boolean success
   * @access public
   */
  public function update_toDatabase() {
    global $camyks;
    
    /* build sql query */
    $sql = 'update admin_pluginmanager';
    $sql .= ' set active='.addslashes($this->activevalue);
    $sql .= ' where plugin="'.addslashes($this->pluginvalue).'"';
    $sql .= ' and type="'.addslashes($this->typevalue).'"';
    
    /* execute sql query */
    return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
  }

  /*
   * plugin activation method
   * @param string $plugin
   * @param string $type
   * @param string $location
   * @param string $active
   * @return boolean success
   * @access public
   */
  public function active_plugin( $plugin=null, $type=null, $location=null, $active=null ) {
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
    return $this->save_toDatabase();
  }

  /*
   * update plugin version
   * @param string $plugin
   * @param string $type
   * @param string $version
   * @return boolean success
   * @access public
   */
  public function update_pluginVersion($plugin, $type, $version) {
    global $camyks;
    
    /* build sql query */
    $sql = 'update admin_pluginmanager';
    $sql .= ' set version="'.addslashes($version).'"';
    $sql .= ' where plugin="'.addslashes($plugin).'"';
    $sql .= ' and type="'.addslashes($type).'"';
    
    /* execute sql query */
    return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));    
  }
  
  /*
   * set plugin as default plugin in CaMykS Configuration
   * @param string $cMode
   * @return boolean success
   * @access public
   */
  public function set_asDefault($cMode='site') {
    global $camyks;
    
    /* check values */
    if ($this->typevalue == 'theme' and in_array($cMode, array('admin', 'site'))
       or ($this->typevalue == 'template' and $cMode == 'site'))
      return $camyks->update_siteConfFile(array($cMode.'_default_'.$this->typevalue => $this->pluginvalue));
        
    /* by default, return false */
    return false;
  }
  
  /* generic module library multi object data manipulation */

  /*
   * get plugin list
   * @return array
   * @access public
   */
  public function get_objectList() {
    global $camyks;

    $plugins = array();

    /* build sql query */
    $sql = 'select *';
    $sql .= ' from admin_pluginmanager';

    /* execute sql query */
    if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__))
    
      /* get data from database */
      while ($data = $camyks->db_conn->get_queryDataLine())
	    $plugins[] = $data;
	
	/* return result */
	return $plugins;
  }
}
?>