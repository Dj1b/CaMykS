<?php
/**
 * @brief Admin_User Module user library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.2.3
 * @date Creation: Sep 2005
 * @date Modification: Jun 2022
 * @copyright 2005 - 2022 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @remark Permissions are defined as an int constructed like :<br />
 * -  0 : no right<br />
 * - +1 : read<br />
 * - +2 : write (default, or module right 2)<br />
 * - +4 : module adding right 1<br />
 * - +8 : module adding right 2<br />
 * - ...
 */

define('ADMINUSER_LOGIN_MAX_LENGTH',    32);
define('ADMINUSER_LOGIN_MIN_LENGTH',    5);
define('ADMINUSER_LASTNAME_LENGTH',     32);
define('ADMINUSER_FIRSTNAME_LENGTH',    32);
define('ADMINUSER_EMAIL_LENGTH',        255);
define('ADMINUSER_ALLOW_EMPTY_PWD',     false);

/**
 * AdminUser class.
 */
final class AdminUser {
    /* variables */
    public $login;
    public $pwd;
    public $email;
    public $active;
    public $webmaster;
    public $firstname;
    public $lastname;
    public $address;
    public $rights;
    public $twoFactorData;

    /* other vars */
    public $rights_;
    public $is_new;
    public $change_pwd;
    public $pwd_conf;
    public $full_update;

    /* generic library vars */
    public $_libParent;
    public $_libError = '';
    public $_libDesc = 'Module: Admin_User Lib: AdminUser';

    /**
     * Class constructor.
     * @param string $login
     * @return void
     */
    public function __construct($login = '') {
        global $camyks;

        if (!preg_match('/[^_a-zA-Z0-9\-]/', $login))
            $this->login = $login;
        $this->is_new = ($this->login == '' ? 1 : 0);

        /* update generic library vars */
        $this->_libParent = &$camyks->modules['Admin_User'];
    }

    /* Management methods */

    /**
     * Load adminuser object.
     * @return boolean success
     */
    public function get() {
        if ($this->login == '')
            return $this->initialise();
        else
            return $this->get_fromDatabase();
    }

    /**
     * Initialise new empty adminuser object.
     * @return boolean result
     */
    public function initialise() {
        $this->email = '';
        $this->webmaster = 0;
        $this->active = 1;
        $this->firstname = '';
        $this->lastname = '';
        $this->address = '';
        $this->rights = $this->initialise_rights();
        $this->twoFactorData = '';
        $this->is_new = 1;
        return true;
    }

    /**
     * Save adminuser object.
     * @return boolean result
     */
    public function save() {
        if ($this->check_data()) {
            if ($this->is_new == 1)
                return $this->create_toDatabase();
            else
                return $this->update_toDatabase();
        }
        return false;
    }

    /* Data I/O methods */

    /**
     * Load object from database.
     * @return boolean success
     */
    private function get_fromDatabase() {
        global $camyks;

        /* Check login */
        if ($this->login=='')
            return false;

        /* Build sql query */
        $sql = "select *";
        $sql .= " from admin_user";
        $sql .= " where login='".$this->login."'";

        /* Execute sql query */
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

    /**
     * Create new adminser object to database.
     * @return boolean success
     */
    private function create_toDatabase() {
        global $camyks;
        $this->is_new = 0;
        /* Build sql query */
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
        $sql .= ', `twoFactorData`';
        $sql .= ') VALUES (';
        $sql .= '"'.$this->login.'"';
        $sql .= ', "'.password_encode($this->pwd, 'sha512', $this->login).'"';
        $sql .= ', "'.addslashes($this->firstname).'"';
        $sql .= ', "'.addslashes($this->lastname).'"';
        $sql .= ', "'.addslashes($this->email).'"';
        $sql .= ', '.$this->active;
        $sql .= ', '.$this->webmaster;
        $sql .= ', "'.$this->address.'"';
        $sql .= ', "'.$this->rights_.'"';
        $sql .= ', "'.$this->twoFactorData.'"';
        $sql .= ')';

        /* return result of sql query execution */
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /**
     * Update adminuser object to database.
     * @return boolean success
     */
    private function update_toDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = "UPDATE `admin_user`";
        $sql .= " SET `email`='".$this->email. "'";
        if ($this->change_pwd == 1) {
            $sql .= ", `pwd`='".password_encode($this->pwd, 'sha512', $this->login). "'";
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

    /**
     * Delete adminuser object from database.
     * @return boolean success
     */
    private function delete_fromDatabase() {
        /* to do */
    }

    /**
     * Install adminuser table and first adminuser object in database.
     * @return boolean success
     */
    public function install() {
        global $camyks;

        /* initialise params */
        $params = array('login' => 'admin', 'password' => 'admin', 'email' => 'admin@example.com');

        /* Check session params */
        $sData = $camyks->get_sessionValue('InstallerConfig', array());
        if (isset($sData['webmaster_login']) and trim($sData['webmaster_login']) != '')
            $params['login'] = preg_replace('/["\']/', '', $sData['webmaster_login']);
        if (isset($sData['webmaster_password']) and trim($sData['webmaster_password']) != '')
            $params['password'] = $sData['webmaster_password'];
        if (isset($sData['webmaster_email']) and trim($sData['webmaster_email']) != '')
            $params['email'] = $sData['webmaster_email'];

        /* Create table */
        $fields = array(
            array('name'=>'login', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>ADMINUSER_LOGIN_MAX_LENGTH, 'default'=>''),
            array('name'=>'pwd', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>140, 'default'=>''),
            array('name'=>'firstname', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>ADMINUSER_FIRSTNAME_LENGTH, 'default'=>''),
            array('name'=>'lastname', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>ADMINUSER_LASTNAME_LENGTH, 'default'=>''),
            array('name'=>'email', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>ADMINUSER_EMAIL_LENGTH, 'default'=>''),
            array('name'=>'active', 'type'=>'int', 'desc1'=>'tinyint unsigned', 'desc2'=>'', 'default'=>0),
            array('name'=>'webmaster', 'type'=>'int', 'desc1'=>'tinyint unsigned', 'desc2'=>'', 'default'=>0),
            array('name'=>'address', 'type'=>'text', 'desc1'=>'text', 'desc2'=>'', 'default'=>''),
            array('name'=>'rights', 'type'=>'text', 'desc1'=>'text', 'desc2'=>'', 'default'=>''),
            array('name'=>'twoFactorData', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>160, 'default'=>''),
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
            $this->twoFactorData = '';
            /* other vars */
            $this->change_pwd = 1;
            $this->is_new = 1;
            $this->rights_ = '';

            /* save user */
            return $this->save();
        }
        return false;
    }

    /**
     * Check is object is installed.
     * @return boolean success
     */
    public function is_installed() {
        global $camyks;
        if (!isset($this->_libIsInstalled)) {

            /* Check with plugin manager */
            if (isset($camyks->modules['Admin_PluginManager'])) {
                $this->_libIsInstalled = $camyks->modules['Admin_PluginManager']->check_tableExists('admin_user');
            } else {

                /* Build sql query */
                $sql = 'show tables like "admin_user"';

                /* Execute sql query */
                if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
                    /* get data from database */
                    $this->_libIsInstalled = ($camyks->db_conn->get_queryDataLine()!==false);
                }
            }
        }
        return $this->_libIsInstalled;
    }

    /**
     * Update 2FA data.
     * @param string $data.
     * @return boolean success
     */
    public function update_2FAData($data='') {
        global $camyks;

        if (!is_string($data))
            return false;
        if (strlen($data) > 160)
            return false;

        /* Build sql query */
        $sql = "update `admin_user`";
        $sql .= " set `twoFactorData`='".addslashes($data)."'";
        $sql .= " where login='".$this->login."'";

        /* return result of sql query execution */
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /**
     * Reset 2FA data.
     * @return boolean success
     */
    public function reset_2FAData($data='') {
        global $camyks;

        /* Build sql query */
        $sql = "update `admin_user`";
        $sql .= " set `twoFactorData`=''";
        $sql .= " where login='".$this->login."'";

        /* return result of sql query execution */
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /**
     * Load adminuser object from header.
     * @param string $prefix
     */
    public function get_fromHeader($prefix = '') {
        global $camyks;
        $this->login = $_REQUEST[$prefix.'login'];
        $this->firstname = $_REQUEST[$prefix.'firstname'];
        $this->lastname = $_REQUEST[$prefix.'lastname'];
        $this->email = $_REQUEST[$prefix.'email'];
        $this->address = $_REQUEST[$prefix.'address'];

        /* get is_new value */
        $this->is_new = (isset ($_REQUEST[$prefix.'is_new']) ? $_REQUEST[$prefix.'is_new'] : 1);

        /* Check for password modification */
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

    /**
     * Load adminuser object from array.
     * @return void
     */
    public function get_fromArray($data) {
        $this->active = isset($data['active']) ? $data['active'] : 0;
        $this->webmaster = isset($data['webmaster']) ? $data['webmaster'] : 0;
        $this->email = isset($data['email']) ? $data['email'] : '';
        $this->firstname = isset($data['firstname'])?stripslashes($data['firstname']):'';
        $this->lastname = isset($data['lastname'])?stripslashes($data['lastname']):'';
        $this->address = isset($data['address'])?stripslashes($data['address']):'';
        $this->rights_ = isset($data['rights']) ? $data['rights'] : '';
        $this->rights = data_decode_properties($this->rights_, ':');
        $this->twoFactorData = isset($data['twoFactorData']) ? $data['twoFactorData'] : '';
        $this->is_new = 0;
    }

    /* tool methods */

    /**
     * Parse and check all data.
     * @return boolean success
     */
    public function check_data() {
        global $camyks;

        if ($this->is_new == 1) {
            /* Check empty login */
            if ($this->login == '') {
                $this->_libError = $this->get_translation('erroremptylogin');
                return false;
            }

            /* Check login first and last char validity */
            if ($this->login != trim($this->login)) {
                $this->_libError = $this->get_translation('errorbadlogin');
                $this->login = trim($this->login);
                return false;
            }

            /* Check login length */
            if (strlen($this->login) < 3) {
                $this->_libError = $this->get_translation('errorshortlogin');
                return false;
            }

            /* Check login chars validity */
            $l = string_parseSpecialChars($this->login, array('pattern'=>'/[^_a-zA-Z0-9]/'));
            if ($this->login != $l) {
                $this->_libError = $this->get_translation('errorbadlogin');
                $this->login = $l;
                return false;
            }

            /* Check existing login */
            if ($this->exists_login($this->login)) {
                $this->_libError = $this->get_translation('errorexistinglogin');
                return false;
            }
        }

        $this->email = trim($this->email);
        /* Check empty mail */
        if ($this->email == '') {
            $this->_libError = $this->get_translation('erroremptymail');
            return false;
        }

        /* Check email validity */
        if (email_isValidEmail($this->email) == false){
            $this->_libError = $this->get_translation('errorbadmail');
            return false;
        }

        if ($this->change_pwd == 1) {
            /* Check empty password */
            if ($this->pwd == '') {
                $this->_libError = $this->get_translation('erroremptypwd');
                return false;
            }
            /* Check password length */
            if (strlen($this->pwd) < 3) {
                $this->_libError = $this->get_translation('errorshortpwd');
                return false;
            }
            /* Check password & confirmation */
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

    /* Test methods */

    /**
     * Check if $login login already exists.
     * @param string $login
     * @return boolean result
     */
    public function exists_login($login) {
        global $camyks;

        /* Check database connexion and by pass it for check while installing website */
        if (!$camyks->db_conn->is_active())
            return false;

        /* Build sql query */
        $sql = 'select login';
        $sql .= ' from admin_user';
        $sql .= ' where login="'.$login.'"';

        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* Load value from database */
            if ($camyks->db_conn->get_queryDataLine()) {
                return true;
            }
        }
        return false;
    }

    /**
     * Try to log in.
     * @param string $pwd
     * @return boolean result
     */
    public function can_login($pwd) {
        global $camyks;

        /* Build sql query */
        $sql = 'select login, pwd from admin_user';
        $sql .= ' where login="'.$this->login .'"';
        $sql .= ' and active="1"';

        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            if ($data = $camyks->db_conn->get_queryDataLine()) {
                /* Check case sensitive login */
                if ($data['login'] !== $this->login)
                    return false;

                /* Check password */
                if (strlen($data['pwd']) == '32')
                    return password_check($pwd, $data['pwd']);
                return password_check($pwd, $data['pwd'], null, $this->login);
            }
        }
        return false;
    }

    /* Permission tool methods */

    /**
     * Initialise new rights combining modules defaults rights and current admin user ones.
     * @return array
     */
    public function initialise_rights() {
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

    /**
     * Decode rights for given module.
     * @return void
     */
    private function decode_rights($module) {
        global $camyks;

        if (isset ($this->rights[$module]) and is_array($this->rights[$module])) {
            return;
        } elseif (!isset($this->rights[$module])) {
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

    /**
     * Encode rights for given module.
     * @param string $module
     * @param array $rights
     * @return void
     */
    private function encode_rights($module, $rights) {
        if (!is_array($rights))
            return;

        $total = 0;
        foreach ($rights as $idx => $r)
            $total += ($r ? pow(2, $idx) : 0);

        $this->rights[$module] = $total;
    }

    /**
     * Return permission for a module
     * @param string $module
     * @param integer $idx
     * @return boolean result
     */
    public function get_right($module, $idx) {
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

    /* Data gathering methods */

    /**
     * Return the user list corresponding to the where sql statement
     * @param string $where
     * @param boolean $objMode
     * @return array
     */
    public function get_userList($where='', $objMode=false) {
        global $camyks;
        $list = array();

        /* Build sql query */
        $sql = 'select login, firstname, lastname, email, active, rights';
        $sql .= ' from admin_user';
        if ($where != '') {
            $sql .= ' where '.$where;
        }
        $sql .= ' order by login;';

        /* Execute sql query */
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

    /**
     * Return active user list.
     * @param boolean $objMode
     * @return array
     */
    public function get_activeUserList($objMode=false) {
        return $this->get_userList('active=1', $objMode);
    }

    /**
     * Return user name display
     * @return string
     */
    public function get_nameDisplay() {
        if ($this->firstname == '' and $this->lastname == '')
            return $this->login;
        elseif ($this->firstname == '')
            return $this->lastname;
        elseif ($this->lastname == '')
            return $this->firstname;
        return $this->firstname.' '.$this->lastname;
    }

    /**
     * Return users status list.
     * @param array $params
     * @return array
     */
    public function get_usersStatusList($params=array()) {
        $defaultParams = array('addAll'=>false);
        $params = array_merge($defaultParams, $params);

        $list = array();
        if ($params['addAll'] == true)
            $list['-1'] = $this->get_translation('users_all');
        $list[0] = $this->get_translation('users_disabled');
        $list[1] = $this->get_translation('users_enabled');

        return $list;
    }

    /**
     * Return the user login list.
     * @return array
     */
    public function static_getList() {
        global $camyks;
        $list = array();

        /* Build sql query */
        $sql = 'select login ';
        $sql .= ' from admin_user';
        $sql .= ' order by login';
        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* Load informations from sql query */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                $list[] = new AdminUser($data['login']);
            }
        }
        return $list;
    }

    /* Tool methods */

    /**
     * Return translation.
     * @param string $translation
     * @param array $params
     * @return string
     */
    private function get_translation($translation, $params=null) {
        return $this->_libParent->get_translation($translation, $params);
    }

    /* Update methods */

    /**
     * Execute version 1.1 update.
     * @return boolean success
     */
    public function update_toVersion1_1() {
        global $camyks;
        $sql = 'alter table admin_user change pwd pwd varchar(140) default "";';
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /**
     * Execute version 1.2 update.
     * @return boolean success
     */
    public function update_toVersion1_2() {
        global $camyks;
        $sql = 'alter table admin_user add column twoFactorData varchar(160) default "";';
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }
}
?>
