<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Library
 * Creation Date	: Oct 2008
 * Last Modif Date	: Nov 2017
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
    
    /* create table */
    $fields = array(
        array('name'=>'plugin', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>255, 'default'=>''),
        array('name'=>'type', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>16, 'default'=>''),
        array('name'=>'location', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>8, 'default'=>''),
        array('name'=>'active', 'type'=>'int', 'desc1'=>'tinyint unsigned', 'desc2'=>'', 'default'=>0),
        array('name'=>'version', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>16, 'default'=>'1.0'),
    );
    
    if ($camyks->db_conn->create_table('admin_pluginmanager', $fields, $camyks->get_mysqlencodingvalue(), false, array('plugin', 'type'))) {
      /* add first element, plugin itself */
      $this->pluginvalue = $this->_libParent->name;
      $this->typevalue = 'module';
      $this->locationvalue = 'camyks';
      $this->activevalue = 1;
      $this->versionvalue = $this->_libParent->version;
      return $this->create_toDatabase();
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
    
      /* check database presence in plugin manager module */
      if (isset($camyks->modules['Admin_PluginManager']))
        $this->_libIsInstalled = $camyks->modules['Admin_PluginManager']->check_tableExists('admin_pluginmanager');
    
      /* load table list */
      $tl = $camyks->db_conn->get_tableList();
    
      /* check if main table is in installed table list */
      $this->_libIsInstalled = in_array('admin_pluginmanager', $tl);
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
    $sql .= '","'.addslashes($this->locationvalue).'",'.(int)$this->activevalue.',';
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
  
  /* generic methods for multi object data manipulation  */

  /*
   * get plugin list
   * @param array $params
   * @return array
   * @access public
   */
  public function get_objectList($params=array()) {
    global $camyks;

    /* check params */
    $params = array_merge($this->get_defaultParams(), $params);

    /* initialise plugin list */
    $plugins = array();
    
    /* build where statement */
    $where = $this->build_whereStatement($params);

    /* build sql query */
    $sql = 'select *';
    $sql .= ' from admin_pluginmanager';
    
    /* add where statement */
    if ($where != '')
      $sql .= ' where '.$where;

    /* execute sql query */
    if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__))
    
      /* get data from database */
      while ($data = $camyks->db_conn->get_queryDataLine())
	    $plugins[] = $data;
	
	/* return result */
	return $plugins;
  }
  
  /*                                                                                 
   * build where statement from params                                               
   * @param array $params                                                            
   * @return string                                                                  
   * @access private                                                                 
   */
  function build_whereStatement($params=array()) {
    $w = array();
    
    /* check status */
    if ($params['status'] != -1)
      $w[] = 'active = '.(int)$params['status'];
      
    /* check type */
    if ($params['type'] != -1)
      $w[] = 'type = "'.$params['type'].'"';
    
	/* return result */
    return implode(' and ', $w);
  }
  
  /*
   * return default params
   * @return array
   * @access private
   */
  function get_defaultParams() {
    return array(
      'status'      => -1, 
      'type'        => -1,
    );
  }
}
?>