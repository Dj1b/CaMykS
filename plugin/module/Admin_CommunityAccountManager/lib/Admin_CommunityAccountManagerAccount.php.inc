<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Oct 2010
 * Last Modif Date  : Oct 2010
 *
 * Admin_CommunityAccountManagerAccount library for Admin_CommunityAccountUsersManager module
 */

class Admin_CommunityAccountManagerAccount extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_CommunityAccountManagerAccount ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );

    /* admin data */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('email', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('login', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('password', 'db', 'password', 'varchar', 32, ''); 
    $this->add_newItem('securecode', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('registrationdate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('connectiondate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('ipaddresses', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('group_id', 'db', 'int', 'bigint unsigned', '', 0);

    /* account data */
    $this->add_newItem('gender', 'db', 'int', 'tinyint', 64, '');
    $this->add_newItem('firstname', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('lastname', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('company', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('phone', 'db', 'text', 'varchar', 24, '');
    $this->add_newItem('address1', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('address2', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('address3', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('city', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('zipcode', 'db', 'text', 'varchar', 12, '');
    $this->add_newItem('country', 'db', 'text', 'varchar', 3, 'fr');

    /* temporary items */
    $this->add_newItem('change_password', 'temp', 'int', 'tinyint unisigned', '', 0);
    $this->add_newItem('confirm_password', 'temp', 'text', 'varchar', 32, '');
    $this->add_newItem('old_password', 'temp', 'text', 'varchar', 32, '');
    $this->add_newItem('account_autologin', 'temp', 'int', '', '', 0);
    $this->add_newItem('account_secretcode', 'temp', 'text', '', '', '');
    
    $this->personal_items = array('gender', 'firstname', 'lastname', 'company', 'phone', 'country');
    $this->password_items = array('password', 'old_password', 'confirm_password');

    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */
  
  /*
   * build sql condition for lists
   * @param array $params
   * @return string
   * @access public
   */
  function build_SQLCondition($params) {
    $search = array();
    if ( isset( $params['status']) and $params['status']!='' and $params['status'] > -1 )
      $search[] = 'status='.$params['status'];
    return implode(' and ', $search);
  }
  
  /*
   * check data
   * @return boolean result
   * @access public
   */
  function check_data() {
    global $camyks;

    if ( $this->id == 0 ) {
      /* create new account */

      /* check email */
      if (($error=$this->check_accountMainData()) !== true ) {
	      $this->_libError = $this->get_translation('saveaccount_error_'.$error);
	      return false;
     }

      /* check password */
      if (($error=$this->check_accountPassword(true)) !== true ) {
	      $this->_libError = $this->get_translation('saveaccount_error_'.$error);
	      return false;
      }

      /* set date values */
      $this->_libItems['registrationdate']->initialise();
      $this->_libItems['connectiondate']->initialise();

      /* set secure code value */
      $this->set_secureCodeValue();

    } else {
      /* update account */
      $this->account = $this->get_newObject();
      $this->account->id = $this->id;
      if ( $this->account->get() === false ) {
	      $this->id = 0;
	      return $this->check_data();
      }
      $this->account->get_fromItems();
      
      /* get old values */
      $this->get_previousValue('email');
      $this->get_previousValue('registrationdate');
      $this->get_previousValue('connectiondate');
      $this->get_previousValue('ipaddresses');
      $this->get_previousValue('securecode');

      /* check for new password */
      $change = ($this->_libItems['change_password']->value==1);
      if (($error=$this->check_accountPassword($change)) !== true ) {
	      $this->_libError = $this->get_translation('saveaccount_error_'.$error);
	      return false;
      }
    }
    /* generic account check */
    return true;
  }

  /* specific methods */
  
  /*
   * return objects status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_multiStatusList($full=false) {
    $list = array();
    if ($full)
      $list['-1'] = $this->get_translation('accountsstatus_all');
    $list['0'] = $this->get_translation('accountsstatus_disabled');
    $list['1'] = $this->get_translation('accountsstatus_enabled');
    $list['2'] = $this->get_translation('accountsstatus_unconfirmed');
    $list['3'] = $this->get_translation('accountsstatus_confirmed');
    $list['4'] = $this->get_translation('accountsstatus_banned');
    return $list;
  }
  
  /*
   * return status list
   * @return array
   * @access private
   */
  function get_statusList() {
    return array(0=>$this->get_translation('accountstatus_inactive'),
      1=>$this->get_translation('accountstatus_active'),
      2=>$this->get_translation('accountstatus_banned'));
  }
    
  /*
   * check accounts main infos
   * @return mixed
   * @access private
   */
  function check_accountMainData() {
    global $camyks;

    /* get values */
    $email = $this->_libItems['email']->value;
    
    /* check email value */
    $new_email = trim($email);
    if ($email != $new_email) {
      $this->_libItems['email']->value = $new_email;
      return 'email_isinvalid';
    }

    if ($email == '')
      return  'email_isempty';

    if (mail_isValidEmail($email) != true)
      return 'email_isinvalid';

    /* build sql query */
    $sql = 'select email';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where email="'.$email.'"';

    /* execute sql query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      /* get data from database */
      if ( $data = mysql_fetch_assoc( $req )) {
	      if( $data['email'] == $email )
	        return 'email_exists';
      }  
    }
    return true;
  }

  /*
   * check password values
   * @param boolean $check
   * @return mixed
   * @access private
   */
  function check_accountPassword($check=true) {
    /* no new password check */
    if ($check===false and $this->account->id > 0) {
      $this->get_previousValue('password');
      return true;
    }

    /* check new password */
    $password = trim($this->_libItems['password']->value);
    $confirm = $this->_libItems['confirm_password']->value;

    /* check if password is empty */
    if ($password == '')
      return 'password_isempty';
    
    /* password configuration check */
    $this->minlength = 4;
    $this->maxlength = 16;

    if (strlen($password) < $this->minlength)
      return 'password_istooshort';

    if (strlen($password) > $this->maxlength)
      return 'password_istoolong';

    /* check password confirmation */
    if ($password != $confirm )
      return 'password_notconfirmed';

    /* set password value */
    $this->_libItems['password']->value = password_encode($password);
    return true;
  }

  /*
   * get previous value
   * @param string $item
   * @return boolean success
   * @access private
   */
  function get_previousValue($item) {
    if (!isset($this->account->vars))
      return false;
    $this->_libItems[$item]->value = $this->account->vars[$item];
    return true;
  }

  /*
   * build and set secure code
   * @return boolean success
   * @access private
   */
  function set_secureCodeValue() {
    $code = $this->_libItems['email']->value.
            $this->_libItems['company']->value.
            $this->_libItems['firstname']->value.
            mktime();
    $this->_libItems['securecode']->value = password_encode($code);
    return true;
  }

  /*
   * get account object from email and password
   * @return boolean success
   * @access private
   */
  function get_fromLoginForm() {
    global $camyks;

    /* get email */
    $this->_libItems['email']->get_fromHeader();
    $email = $this->_libItems['email']->value;
    if ($email == '')
      return false;

    /* get password */
    $this->_libItems['password']->get_fromHeader();
    $password = $this->_libItems['password']->value;

    /* get auto-login checkbox */
    $this->_libItems['autologin']->get_fromHeader();
    $autologin = $this->_libItems['autologin']->value;

    /* check login */
    if($email != string_parseSpecialChars( $email, array('pattern'=>'/[^a-zA-Z0-9_\-]/')))
      return false;

    /* build sql query */
    $sql = 'select * from '.$this->_libSQLTable.'';
    $sql .= ' where email="'.$email.'" and password="'.password_encode($password).'"';
    $sql .= ' and status=1';

    /* execute sql query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* get data from database */
      if ( $data = mysql_fetch_assoc( $req )) {
	      $this->id = $data['id'];
	      $this->get_fromArray($data, $this->_libItemTypes['db']);
	      $this->get_fromItems();
	      if ( $autologin == 1 )
	        $this->set_loginCookie();
	      return $this->update_connectionValues();
      }
    return false;
  }

  /*
   * get account object from id and secure code
   * @return boolean success
   * @access private
   */
  function get_fromLoginCookie() {
    global $camyks;

    /* check existing session */
    if ($camyks->get_sessionValue('accountlogin', null) != null )
      return false;

    /* get cookie login */
    if( ($login = cookie_get('accountlogin')) == null or $this->get_fromSession() ==-1 )
      return false;

    /* check login */
    $login = explode(':', $login);
    if (count($login) != 2)
      return false;
    if (!((int)$login[0]>0))
      return false;
    
    /* build sql query */
    $sql = 'select * from '.$this->_libSQLTable.'';
    $sql .= ' where id='.$login[0].' and securecode="'.$login[1].'"';
    $sql .= ' and status=1';
    
    /* execute sql query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* get data from database */
      if ( $data = mysql_fetch_assoc( $req )) {
	      $this->id = $data['id'];
	      $this->get_fromArray($data, $this->_libItemTypes['db']);
	      $this->get_fromItems();
	      return $this->update_connectionValues();
      }
    return false;
  }

  /*
   * update current account connection values
   * @return boolean success
   * @access private
   */
  function update_connectionValues() {
    global $camyks;
    
    /* build sql update query */
    $sql = 'update '.$this->_libSQLTable.' set';
    $sql .= ' connectiondate='.mktime();
    
    /* check ipadresses */
    $ips = explode(';', $this->vars['ipaddresses']);
    $ip = client_getIp();
    if (!in_array($ip, $ips)){
      if (count($ips)==1 and $ips[0]=='')
	      $ips = $ip;
      else {
	      $ips[] = $ip;
	      if (count($ips)>10)
	        array_shift($ips);
	      $ips = implode(';', $ips);
      }
      $sql .= ', ipaddresses="'.$ips.'"';
    }    
    
    /* continue building query */
    $sql .= ' where id='.$this->id;
    
    /* execute sql query */
    return ($req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ));
  }

  /*
   * set login cookie value
   * @return boolean result
   * @access private
   */
  function set_loginCookie($extend=false) {
    if ($extend)
      cookie_extendTTL('accountlogin', 90);
    else
      cookie_save('accountlogin', $this->id.':'.$this->vars['securecode'], 90);
    return true;
  }

  /*
   * save account in visit mode 
   * @return boolean success
   * @access private
   */
  function save_fromSite() {
    if ($this->id == 0 ) {
	      return $this->save_newAccount();
    } else {
	    /* get data from header */
	    $this->get_personalDataFromHeader();
	    /* try to save */
	    return $this->save_personalData();
    }  
  }
   
  function update_password() {
    if($this->id == 0)
	    return false;
    /* get data from header */
    $this->get_newPasswordFromHeader();
    /* try to save */
    return $this->save_newPassword();
  }

  /*
   * reset account security code
   * @return boolean result
   * @access private
   */
  function reset_securityCode() {
    if($this->id == 0)
	    return false;
    /* try to reset code */
    $this->set_secureCodeValue();
    return $this->update_databaseSpecificItems(array('securecode'));
  }

  /*
   * save new account 
   * @return boolean result
   * @access private
   */
  function save_newAccount() {
    global $camyks;
    /* get all data from header */
    $this->get_fromHeader();
    
    /* set first client IP */
    $this->_libItems['ipaddresses']->value = client_getIp();
    
    /* backup data */
    $this->get_fromItems();
    /* try to save */
    if ($this->save()) {
      $this->get_fromItems();
      $camyks->update_statistic('account_registration', $this->_libParent->name, 'dated');
	    return true;
    }
    return false;
  }
  
  /*
   * save account item id to session
   * @return boolean result
   * @access private
   */
  function save_idToSession() {
    global $camyks;
    $camyks->set_sessionValue('accountid', $this->id);
    return true;
  }

  /*
   * get account item id from session
   * @return integer
   * @access private
   */
  function get_idFromSession() {
    global $camyks;
    $this->id = $camyks->get_sessionValue('accountid', 0);
    return $this->id;
  }

  /*
   * check account item id from session
   * @return boolean result
   * @access private
   */
  function check_fromSession() {
    global $camyks;
    if ($this->id == 0 and $camyks->get_sessionValue('accountid', 0) == -1)
      return true;
    return ($this->id == $camyks->get_sessionValue('accountid', 0));
  }

  /*
   * get personal data from header 
   * @return void
   * @access private
   */
  function get_personalDataFromHeader() {
    foreach ($this->personal_items as $item)
      $this->_libItems[$item]->get_fromHeader();
  }

  /*
   * save personal data
   * @return boolean success
   * @access private
   */
  function save_personalData() {
    return ($this->update_databaseSpecificItems($this->personal_items));
  }

  /*
   * get passwords from header 
   * @return void
   * @access private
   */
  function get_newPasswordFromHeader() {
    foreach ($this->password_items as $item)
      $this->_libItems[$item]->get_fromHeader();
  }

  /*
   * save new account password
   * @return boolean success
   * @access private
   */
  function save_newPassword() {
    /* check old password */
    if ( $this->vars['password'] != password_encode($this->_libItems['old_password']->value) ) {
      $this->_libError = $this->get_translation('saveaccount_error_password_oldisnotcorrect');
      return false;
    }
    /* check new password */
    if (($error = $this->check_accountPassword(true)) !== true ) {
      $this->_libError = $this->get_translation('saveaccount_error_'.$error);
      return false;
    }
    /* save password */
    return $this->update_databaseSpecificItems(array('password'));
  }
  
  /*
   * confirm registration
   * @param integer $id
   * @param string $sec
   * @return boolean result
   * @access private
   */
  function confirm_registration($id, $sec) {
    global $camyks;
    
    /* build sql query */
    $sql = 'update '.$this->_libSQLTable;
    $sql .= ' set status = 1';
    $sql .= ' where id = '.$id;
    $sql .= ' and securecode = "'.$sec.'"';
    $sql .= ' and status = 0';
     
    /* execute sql query */
    if ($req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__));
      return (mysql_affected_rows() == 1);
    return false;
  }
  
  /*
   * return name display
   * @param boolean $mode
   * @return string
   * @access public
   */
  function get_nameDisplay($mode=true) {
    if ( $this->vars['firstname'] == '' and $this->vars['lastname'] == '' ) {
      if ($mode)
        return $this->vars['email'];
      else
        return $this->get_translation('visitor');
    }
    if ( $this->vars['firstname'] != '' and $this->vars['lastname'] != '' )
      return $this->vars['firstname'] . ' ' .$this->vars['lastname'];
    if ( $this->vars['firstname'] != '')
      return $this->vars['firstname'];
    return $this->vars['lastname'];
  }
  
  /*
   * try to connect member
   * @param string $email
   * @param string $pwd
   * @return array
   * @access private
   */
  function connect_member($email, $pwd) {
    global $camyks;
    
    /* check email validity */
    if ( mail_isValidEmail($email) == false ) {
      $result['login'] = 0;
      $result['error'] = $this->get_translation('login_error_loginfailed');
      return $result;
    }
   
    /* initialise result */
    $result = array();

    /* build sql query */
    $sql = 'select id, status, securecode';
    $sql .= ' from '.$this->_libSQLTable;
    $sql .= ' where email="'.$email.'"';
    $sql .= ' and password="'.password_encode($pwd).'"';
    
    /* execute sql query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)){
      if ($data = mysql_fetch_assoc($req)){
        if ($data['status'] == 1) {
          $result['login']=1;
          $result['targetURL'] = $camyks->get_siteLink($this->get_configValue('site_membernavrootpage'));
          $this->id = $data['id'];
          $this->vars = $data;
          $this->save_idToSession();
          if ( isset($_REQUEST['autologin']) and $_REQUEST['autologin']=='true')
            $this->set_loginCookie();
          return $result;
        } else if ($data['status']==0) {
          $result['login'] = 0;
          $result['error'] = $this->get_translation('login_error_membernotconfirmed');
          return $result;
        } else {
          $result['login'] = 0;
          $result['error'] = $this->get_translation('login_error_memberdisabled');
          return $result;
        }
      } else {
        $result['login'] = 0;
        $result['error'] = $this->get_translation('login_error_loginfailed');
        return $result;
      }
    }
    
    $result['login'] = 0;
    $result['error'] = $this->get_translation('login_error_loginerror');
    return $result;
  }
  
  /*
   * try to connect member
   * @return array
   * @access private
   */
  function disconnect_member() {
    global $camyks;
    $this->id = -1;
    $this->save_idToSession();
    return array('targetURL' => $camyks->get_siteHomePageLink());
  }
  
  /*
   * get parent config value
   * @param string $param 
   * @return mixed
   * @access private
   */
  function get_configValue($param) {
    return $this->_libParent->get_configValue($param);
  }
}
?>