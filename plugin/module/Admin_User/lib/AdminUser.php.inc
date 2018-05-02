<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version 	: 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date	: Sep 2005
 * Last Modif Date	: Mar 2007
 *
 * AdminUser module library for Admin_User module
 *
 * Rights is define as an int construct like : 
 *
 * -  0 : no right
 * - +1 : read
 * - +2 : write (default, or module right 2)
 * - +4 : module adding right 1
 * - +8 : module adding right 2
 * - ...
 *
*/

define('ADMINUSER_LOGIN_MAX_LENGTH',     32);
define('ADMINUSER_LOGIN_MIN_LENGTH',     5);
define('ADMINUSER_LASTNAME_LENGTH',      32);
define('ADMINUSER_FIRSTNAME_LENGTH',     32);
define('ADMINUSER_EMAIL_LENGTH',         255);
define('ADMINUSER_ALLOW_EMPTY_PWD',      false);

class AdminUser {
  /* variables */
  var $login;
  var $pwd;
  var $email;
  var $active;
  var $webmaster;
  var $firstname;
  var $lastname;
  var $address;
  var $rights;
  
  /* other vars */
  var $rights_;
  var $is_new;
  var $change_pwd;
  var $pwd_conf;
  var $full_update;
  
  /* generic library vars */
  var $_libError;
  var $_libDesc;
  
  /*
   * constructor
   * @param string $login
   */
  function AdminUser($login = '') {
    global $camyks;
    $this->login = preg_replace('/["\']/', '', $login);
    $this->is_new = ($this->login == '' ? 1 : 0);
    /* update generic library vars */
    $this->_libParent = &$camyks->modules['Admin_User'];
    $this->_libError = '';
    $this->_libDesc = 'Module: Admin_User Lib: AdminUser';
  }

  /* basic management methods */

  /*
   * get adminuser object
   * @return boolean success
   * @access private
   */
  function get () {
    if ($this->login == '')
      return $this->initialise();
    else 
      return $this->get_fromDatabase(); 
  }

  /*
   * initialise new empty adminuser object
   * @return boolean result
   * @access private
   */
  function initialise () {
    $this->email = '';
    $this->webmaster = 0;
    $this->active = 1;
    $this->firstname = '';
    $this->lastname = '';
    $this->address = '';
    $this->rights = $this->initialise_rights();
    $this->is_new = 1;
    return true;
  }

  /*
   * save adminuser object
   * @return boolean result
   * @access private
   */
  function save () {
    if ($this->check_data()) {
      if ($this->is_new == 1)
	    return $this->create_toDatabase();
      else 
	    return $this->update_toDatabase();
    }
    return false;
  }
  
  /* data I/O methods */
  
  /*
   * get object from database
   * @return boolean success
   * @access private
   */
  function get_fromDatabase() {
    global $camyks;
    
    /* check login */
    if ($this->login=='')
      return false;
    
    /* build sql query */
    $sql = "select *";
    $sql .= " from admin_user";
    $sql .= " where login='".$this->login."'";
    
    /* execute sql query */
    if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
    
      /* get data from database */
      if ($data = $camyks->db_conn->get_queryDataLine()) {
	    $this->get_fromArray($data);
	    return true;
      } else {
	    $this->initialise();
	    return false;
      }
    }
    return false;
  }
  
  /*
   * create new adminser object to database
   * @return boolean success
   * @acces private
   */
  function create_toDatabase () {
    global $camyks;
    $this->is_new = 0;
    /* build sql query */
    $sql = 'INSERT INTO `admin_user` (';
    $sql .= '`login`';
    $sql .= ', `pwd`';
    $sql .= ', `firstname`';
    $sql .= ', `lastname`';
    $sql .= ', `email`';
    $sql .= ', `active`';
    $sql .= ', `webmaster`';
    $sql .= ', `address`';
    $sql .= ', `rights`';
    $sql .= ') VALUES (';
    $sql .= '"'.$this->login.'"';
    $sql .= ', "'.password_encode($this->pwd).'"';
    $sql .= ', "'.addslashes($this->firstname).'"';
    $sql .= ', "'.addslashes($this->lastname).'"';
    $sql .= ', "'.addslashes($this->email).'"';
    $sql .= ', '.$this->active;
    $sql .= ', '.$this->webmaster;
    $sql .= ', "'.$this->address.'"';
    $sql .= ', "'.$this->rights_.'"';
    $sql .= ')';
    
    /* return result of sql query execution */
    return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
  }
  
  /*
   * update adminuser object to database
   * @return boolean success
   * @access private
   */
  function update_toDatabase () {
    global $camyks;
    
    /* build sql query */
    $sql = "UPDATE `admin_user`";
    $sql .= " SET `email`='".$this->email. "'";
    if ($this->change_pwd == 1) {
      $sql .= ", `pwd`='".password_encode($this->pwd). "'";
    }
    $sql .= ", `firstname`='".addslashes($this->firstname). "'";
    $sql .= ", `lastname`='".addslashes($this->lastname). "'";
    $sql .= ", `address`='".addslashes($this->address). "'";
    if ($this->full_update == 1) {
      $sql .= ", `active`=".$this->active;
      $sql .= ", `rights`='".$this->rights_."'";
    }
    $sql .= " WHERE login='".$this->login."'";

    /* return result of sql query execution */
    return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
  }

  /*
   * delete adminuser object from database
   * @return boolean success
   * @access private
   */
  function delete_fromDatabase() {
    /* to do */
  }
  
  /*
   * install adminuser table and first adminuser object in database
   * @return boolean success
   * @access private
   */
  function install() {
    global $camyks;
    
    /* initialise params */
    $params = array('login' => 'admin', 'password' => 'admin', 'email' => 'admin@example.com');
    
    /* check session params */
    $sData = $camyks->get_sessionValue('InstallerConfig', array());
    if (isset($sData['webmaster_login']) and trim($sData['webmaster_login']) != '')
      $params['login'] = preg_replace('/["\']/', '', $sData['webmaster_login']);
    if (isset($sData['webmaster_password']) and trim($sData['webmaster_password']) != '')
      $params['password'] = $sData['webmaster_password'];
    if (isset($sData['webmaster_email']) and trim($sData['webmaster_email']) != '')
      $params['email'] = $sData['webmaster_email'];
    
    /* create table */
    $fields = array(
        array('name'=>'login', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>ADMINUSER_LOGIN_MAX_LENGTH, 'default'=>''),
        array('name'=>'pwd', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>32, 'default'=>''),
        array('name'=>'firstname', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>ADMINUSER_FIRSTNAME_LENGTH, 'default'=>''),
        array('name'=>'lastname', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>ADMINUSER_LASTNAME_LENGTH, 'default'=>''),
        array('name'=>'email', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>ADMINUSER_EMAIL_LENGTH, 'default'=>''),
        array('name'=>'active', 'type'=>'int', 'desc1'=>'tinyint unsigned', 'desc2'=>'', 'default'=>0),
        array('name'=>'webmaster', 'type'=>'int', 'desc1'=>'tinyint unsigned', 'desc2'=>'', 'default'=>0),
        array('name'=>'address', 'type'=>'text', 'desc1'=>'text', 'desc2'=>'', 'default'=>''),
        array('name'=>'rights', 'type'=>'text', 'desc1'=>'text', 'desc2'=>'', 'default'=>''),
   );
    
    if ($camyks->db_conn->create_table('admin_user', $fields, $camyks->get_mysqlencodingvalue(), false, array('login'))) {    
      /* add first user */
      $this->initialise();
      $this->login = $params['login'];
      $this->pwd = $params['password'];
      $this->pwd_conf = $params['password'];
      $this->webmaster = 1;
      $this->active = 1;
      $this->email = $params['email'];
      /* other vars */
      $this->change_pwd = 1;
      $this->is_new = 1;
      $this->rights_ = '';
      /* save user */
      return $this->save();
    }
    return false; 
  }
  
  /*
   * check is object is installed
   * @return boolean success
   * @access private
   */
  function is_installed () {
    global $camyks;
    if (!isset($this->_libIsInstalled)) {
    
      /* check with plugin manager */
      if (isset($camyks->modules['Admin_PluginManager'])) {
        $this->_libIsInstalled = $camyks->modules['Admin_PluginManager']->check_tableExists('admin_user');
      } else {
    
        /* build sql query */
        $sql = 'show tables like "admin_user"';
      
        /* execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) { 
	      /* get data from database */
	      $this->_libIsInstalled = ($camyks->db_conn->get_queryDataLine()!==false);
	    }
      }
    }
    return $this->_libIsInstalled;

  }

  /*
   * get adminuser object from header
   * @param string $prefix
   * @access private
   */
  function get_fromHeader($prefix = '') {
    global $camyks;
    $this->login = $_REQUEST[$prefix.'login'];
    $this->firstname = $_REQUEST[$prefix.'firstname'];
    $this->lastname = $_REQUEST[$prefix.'lastname'];
    $this->email =  $_REQUEST[$prefix.'email'];
    $this->address = $_REQUEST[$prefix.'address'];
    /* get is_new value */
    $this->is_new = (isset ($_REQUEST[$prefix.'is_new']) ? $_REQUEST[$prefix.'is_new'] : 1);
    
    
    /* check for password modification */
    $this->change_pwd = (isset ($_REQUEST[$prefix.'change_pwd']) ? $_REQUEST[$prefix.'change_pwd'] : 0);
    if ($this->change_pwd == 1) {
      $this->pwd = $_REQUEST[$prefix.'pwd'];
      $this->pwd_conf = $_REQUEST[$prefix.'pwd_conf'];
    }
    
    /* get full information */
    $this->full_update = (isset ($_REQUEST[$prefix.'full_update']) ? $_REQUEST[$prefix.'full_update'] : 0);
    if ($this->full_update == 1) {
      $this->active = isset ($_REQUEST[$prefix.'active']) ? $_REQUEST[$prefix.'active'] : 0;
      $this->webmaster = isset ($_REQUEST[$prefix.'webmaster']) ? $_REQUEST[$prefix.'webmaster'] : 0;
      /* get all rights */
      $this->rights = array();
      foreach ($camyks->modules as $m) {
	    if ($m->type == 'admin') {
	      $m->get_rights();
	      $this->rights[ $m->name ] = array();
	      foreach ($m->rights as $ridx => $right) {
	        $this->rights[ $m->name ][$ridx] = isset ($_REQUEST[$prefix.$m->name.'_'.$ridx]) ? $_REQUEST[$prefix.$m->name.'_'.$ridx] : 0;
	      }
	    }
      }
    }
  }
  
  /*
   * get adminuser object from array
   * @return void
   * @access private
   */
  function get_fromArray($data) {
    $this->active = isset($data['active'])?$data['active']:0;
    $this->webmaster = isset($data['webmaster'])?$data['webmaster']:0;
    $this->email = isset($data['email'])?$data['email']:'';
    $this->firstname = isset($data['firstname'])?stripslashes($data['firstname']):'';
    $this->lastname = isset($data['lastname'])?stripslashes($data['lastname']):'';
    $this->address = isset($data['address'])?stripslashes($data['address']):'';
    $this->rights_ = isset($data['rights'])?$data['rights']:'';
    $this->rights = data_decode_properties($this->rights_, ':');
    $this->is_new = 0;
  }

  /* tool methods */

  /*
   * parse and check all data
   * @return boolean success
   * @access private
   */
  function check_data() {
    global $camyks;

    if ($this->is_new == 1) {
      /* check empty login */
      if ($this->login == '') {
	    $this->_libError = $this->get_translation('erroremptylogin');
	    return false;
      }
      /* check login first and last char validity */
      if ($this->login != trim ($this->login)) {
	    $this->_libError = $this->get_translation('errorbadlogin');
	    $this->login = trim ($this->login);
	    return false;
      }
      /* check login length */
      if (strlen($this->login) < 3) {
	    $this->_libError = $this->get_translation('errorshortlogin');
	    return false;
      }
      
      /* check login chars validity */
      $l = string_parseSpecialChars($this->login, array('pattern'=>'/[^_a-zA-Z0-9]/'));
      if ($this->login != $l) {
	    $this->_libError = $this->get_translation('errorbadlogin');
	    $this->login = $l;
	    return false;
      }
      /* check existing login */
      if ($this->exists_login($this->login)) {
	    $this->_libError = $this->get_translation('errorexistinglogin');
	    return false;
      }
    }
    
    $this->email = trim ($this->email);
    /* check empty mail */
    if ($this->email == '') {
      $this->_libError = $this->get_translation('erroremptymail');
      return false;
    }    

    /* check email validity */
    if (email_isValidEmail($this->email) == false){
      $this->_libError = $this->get_translation('errorbadmail');
      return false;      
    }

    if ($this->change_pwd == 1) {
      /* check empty password */
      if ($this->pwd == '') {
	    $this->_libError = $this->get_translation('erroremptypwd');
	    return false;
      }
      /* check password length */
      if (strlen($this->pwd) < 3) {
	    $this->_libError = $this->get_translation('errorshortpwd');
	    return false;
      }
      /* check password & confirmation */
      if ($this->pwd != $this->pwd_conf) {
	    $this->_libError = $this->get_translation('errorconfpwd');
	    return false;
      }
    }

    if ($this->full_update == 1) {
      /* get rights */
      foreach ($this->rights as $m => $r){
	    $this->encode_rights($m, $r);
      }
      $this->rights_ = data_encode_properties($this->rights, ':');
    }
    return true;
  }

  /* tests methods */

  /*
   * check if $login login already exists
   * @param string $param
   * @return boolean result
   * @access private
   */
  function exists_login($login) {
    global $camyks;
    
    /* check database connexion and by pass it for check while installing website */
    if (!$camyks->db_conn->is_active())
      return false;

    /* build sql query */
    $sql = 'select login';
    $sql .= ' from admin_user';
    $sql .= ' where login="'.$login.'"';
    /* execute sql query */
    if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
      /* get value from database */
      if ($camyks->db_conn->get_queryDataLine()) {
	    return true;
      }
    }
    return false;
  }

  /* 
   * try login
   * @param string $pwd
   * @return boolean result
   * @access private
   */
  function can_login($pwd) {
    global $camyks;

    /* build sql query */
    $sql = 'select login from admin_user';
    $sql .= ' where pwd="'.password_encode($pwd).'"';
    $sql .= ' and login="'.$this->login .'"';
    $sql .= ' and active="1"';
    
    /* execute sql query */
    if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__))
      return $camyks->db_conn->get_queryDataLine();
    return false;
  }
  
  /* rights tool methods */

  /*
   * initialise new rights combining modules defaults rights and current admin user ones
   * @return array
   * @access private
   */
  function initialise_rights() {
    global $camyks;
    $r = array();
    foreach($camyks->modules as $module) {
      if ($module->type == 'admin') {
	$r[$module->name] = array();
	$module->get_rights();
	foreach ($module->rights as $idx => $right) {
	  $r[$module->name][$idx] = $right['default']*$module->check_right($idx);
	}
      }
    }
    return $r;
  }
  
  /*
   * decode rights for given module
   * @return void
   * @access private
   */
  function decode_rights ($module) {
    global $camyks;

    if (isset ($this->rights[$module]) and is_array($this->rights[$module])) {
      return;
    } else if (! isset ($this->rights[$module])) {
      return;
    }
    
    $r = array(false, false);
    if (isset($camyks->modules[$module])) {
      $camyks->modules[$module]->get_rights();
      for($i=0; $i< count($camyks->modules[$module]->rights); $i++)
	$r[$i] = false;
    }
    
    $t = $this->rights[$module];    
    $cnt = 0;
    while ($t > 0) {
      $r[$cnt] = ($t != intVal($t/2)*2);
      $t = intVal($t/2);
      $cnt ++;
    }
    $this->rights[$module] = $r;
  }
  
  /*
   * encode rights for given module
   * @param string $module
   * @param array $rights
   * @return void
   * @access private
   */
  function encode_rights ($module, $rights) {
    if (!is_array($rights)) {
      return;
    }
    $total = 0;
    foreach ($rights as $idx=>$r) {
      $total += ($r ? pow(2, $idx) : 0); 
    }
    $this->rights[$module] = $total;
  }
  
  /*
   * get right for a module
   * @param string $module
   * @param integer $idx
   * @return boolean result
   * @access private
   */
  function get_right ($module, $idx) {
    global $camyks;

    /* always return true for the webmaster */
    if ($this->webmaster == 1) {
      return true;
    }
    
    /* decode rights if needed */
    $this->decode_rights($module);
    
    /* return value */
    if (isset ($this->rights[$module][$idx])) {
      return $this->rights[$module][$idx];
    }

    /* return default module value */
    if (isset ($camyks->modules[$module])) {
      $camyks->modules[$module]->get_rights();
      if (isset ($camyks->modules[$module]->rights[$idx]['default'])) {
	    return $camyks->modules[$module]->rights[$idx]['default'];
      }
    }
    return false;
  }

  /* data gathering methods */

  /*
   * return the user list corresponding to the where sql statement
   * @param string $where
   * @param boolean $objMode
   * @return array
   * @access private
   */
  function get_userList($where='', $objMode=false) {
    global $camyks;
    $list = array();
    
    /* build sql query */
    $sql = 'select login, firstname, lastname, email, active, rights';
    $sql .= ' from admin_user';
    if ($where != '') {
      $sql .= ' where '.$where;
    }
    $sql .= ' order by login;';
    
    /* execute sql query */
    if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
      /* get informations from sql query */
      while ($data = $camyks->db_conn->get_queryDataLine()) {
	    if ($objMode) {
	      $o = new AdminUser($data['login']);
	      $o->get_fromArray($data);
	      $list[$data['login']] = $o;
	    } else
	      $list[$data['login']] = $data;
      }
    }
    return $list;
  }

  /*
   * return active user list
   * @param boolean $objMode
   * @return array
   * @access private
   */
  function get_activeUserList($objMode=false) {
    return $this->get_userList('active=1', $objMode);
  }

  /*
   * return user name display
   * @return string
   * @access public
   */
  function get_nameDisplay() {
    if ($this->firstname == '' and $this->lastname == '')
      return $this->login;
    elseif ($this->firstname == '')
      return $this->lastname;
    elseif ($this->lastname == '')
      return $this->firstname;
    return $this->firstname.' '.$this->lastname;
  }
  
  /*
   * return users status list
   * @param array $params
   * @return array
   * @access public
   */
  function get_usersStatusList($params=array()) {
    $defaultParams = array('addAll'=>false);
    $params = array_merge($defaultParams, $params);
    
    $list = array();
    if ($params['addAll'] == true)
      $list['-1'] = $this->get_translation('users_all');
    $list[0] = $this->get_translation('users_disabled');
    $list[1] = $this->get_translation('users_enabled');
    
    return $list;
  }


  /*
   * return the user login list
   * @return array
   * @access private
   */
  function static_getList() {
    global $camyks;
    $list = array();
    
    /* build sql query */
    $sql = 'select login ';
    $sql .= ' from admin_user';
    $sql .= ' order by login';
    /* execute sql query */
    if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
      /* get informations from sql query */
      while ($data = $camyks->db_conn->get_queryDataLine()) {
	    $list[] = new AdminUser($data['login']);
      }
    }
    return $list;
  }
  
  /* tool methods */
  
  /*
   * return translation
   * @param string $translation
   * @param array $params
   * @return string
   * @access private
   */
  function get_translation($translation, $params=null) {
    return $this->_libParent->get_translation($translation, $params);
  }
}
?>