<?php
/**
 * @brief Admin_Group Module group library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Mar 2007
 * @date Modification: Feb 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @remark Contains 2 default groups : all / none
 */
final class AdminGroup {
    /**
     * var string $name
     * @brief Group symbolic name.
     */
    public $name;

    /**
     * var string $title
     * @brief Group title.
     */
    public $title;

    /**
     * var string $description
     * @brief Group description.
     */
    public $description;

    /**
     * var boolean $is_new
     * @brief Is group new.
     */
    public $is_new;

    /**
     * var array $users
     * @brief Group users as list.
     */
    public $users;

    /**
     * var string $users_
     * @brief Group users as string.
     */
    public $users_;

    /**
     * var string $_libError
     * @brief Object last error.
     */
    public $_libError = '';

    /**
     * var string $_libDesc
     * @brief Object description.
     */
    public $_libDesc = 'Module: Admin_Group Lib: AdminGroup';

    /**
     * var boolean $_libIsInstalled
     * @brief Is group object installed.
     */
    public $_libIsInstalled = null;

    /**
     * var Object $_libParent
     * @brief Link to parent module.
     */
    private $_libParent = null;

    /**
     * Class constructor.
     * @param string $name
     * @param Object $parent
     * @return void
     */
    public function __construct($name = '', $parent = null) {
        $this->name = $name;
        $this->is_new = ($name == '' ? 1 : 0);
        $this->_libParent = &$parent;
    }

    /* Object i/o methods */

    /**
     * Load object.
     * @return boolean success
     */
    public function get() {
        if ($this->name == '')
            return $this->initialise();
        else
            return $this->get_fromDatabase();
    }

    /**
     * Initialise new object.
     * @return boolean success
     */
    public function initialise() {
        $this->description = '';
        $this->users = array();
        $this->users_ = '';
        $this->is_new = 1;
        return true;
    }

    /**
     * Load object from database
     * @return boolean success
     */
    public function get_fromDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = "SELECT *";
        $sql .= " FROM admin_group";
        $sql .= " WHERE name='".addslashes($this->name)."'";

        /* Execute sql query */
        if ($req = $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* get data from database */
            if ($data = $camyks->db_conn->get_queryDataLine()) {
                $this->get_fromArray($data);
                $this->is_new = 0;
                return $this->get_usersFromDatabase();
            } else {
                $this->initialise();
                return false;
            }
        }
        return false;
    }

    /**
     * Save object
     * @return boolean success
     */
    public function save() {
        if ($this->check_data()) {
            if ($this->is_new == 1 and $this->create_toDatabase() or $this->update_toDatabase())
                return $this->update_usersToDatabase();
        }
        return false;
    }

    /**
     * Create new object to database
     * @return boolean success
     */
    private function create_toDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = 'INSERT INTO `admin_group` (';
        $sql .= '`name`';
        $sql .= ', `description`';
        $sql .= ') VALUES (';
        $sql .= '"'.addslashes($this->name).'"';
        $sql .= ',"'.addslashes($this->description).'"';
        $sql .= ')';

        /* Return result of sql query execution */
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /**
     * Update object to database
     * @return boolean success
     */
    private function update_toDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = 'UPDATE `admin_group` ';
        $sql .= ' SET description="'.addslashes($this->description).'"';
        $sql .= ' WHERE name="'.addslashes($this->name).'"';

        /* return result of sql query execution */
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /**
     * Delete object from database
     * @return boolean success
     */
    function delete_fromDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = 'delete from admin_group where name="'.addslashes($this->name).'";';

        /* Return result of sql query execution */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* Build sql query */
            $sql = 'delete from admin_user_group where group="'.addslashes($this->name).'";';
            /* Return result of sql query execution */
            return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
        }
        return false;
    }

    /**
     * Load user list from database.
     * @return boolean success
     */
    public function get_usersFromDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = 'select user';
        $sql .= ' from admin_user_group';
        $sql .= ' where `group`="'.addslashes($this->name).'"';

        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* Load data from database */
            while ($data = $camyks->db_conn->get_queryDataLine())
                $this->users[] = $data['user'];

            /* Encode user list as string */
            $this->users_ = implode($this->users, ':');
            return true;
        }
        return false;
    }

    /**
     * Update user list to database.
     * @return boolean success
     */
    public function update_usersToDatabase() {
        global $camyks;
        /* build sql query */
        $sql = 'delete from admin_user_group where `group`="'.addslashes($this->name).'";';
        /* add new items */
        if (count($this->users) > 0 and ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__))) {
            $isFirst = true;
            $sql = 'insert into admin_user_group (`group`, `user`) values';
            foreach ($this->users as $u) {
                if ($isFirst) {
                    $isFirst = false;
                } else {
                    $sql .= ',';
                }
                    $sql .= ' ("'.addslashes($this->name).'", "'.addslashes($u).'")';
            }
        }

        /* return result of sql query execution */
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /**
     * Install admingroup table in database
     * @return boolean success
     */
    public function install() {
        global $camyks;

        /* Create group table */
        $fields = array(
            array('name'=>'name', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>32, 'default'=>''),
            array('name'=>'description', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>64, 'default'=>''),
        );

        if ($camyks->db_conn->create_table('admin_group', $fields, $camyks->get_mysqlencodingvalue(), false, array('name'))) {
            /* Create user/group links table */
            $fields = array(
                array('name'=>'user', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>32, 'default'=>''),
                array('name'=>'group', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>32, 'default'=>''),
            );
            return ($camyks->db_conn->create_table('admin_user_group', $fields, $camyks->get_mysqlencodingvalue(), false, array('user', 'group')));
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
            /* Check database presence in plugin manager module */
            if (isset($camyks->modules['Admin_PluginManager']))
                $this->_libIsInstalled = $camyks->modules['Admin_PluginManager']->check_tableExists('admin_user_group');
            else {
                /* load table list */
                $tl = $camyks->db_conn->get_tableList();

                /* Check if main table is in installed table list */
                $this->_libIsInstalled = in_array('admin_user_group', $tl);
            }
        }
        return $this->_libIsInstalled;
    }

    /**
     * Load object data from header.
     * @param string $prefix
     * @return void
     */
    public function get_fromHeader($prefix = '') {
        $this->name = $_REQUEST['name'];
        $this->description = $_REQUEST['description'];
        $this->is_new = isset ($_REQUEST['is_new']) ? $_REQUEST['is_new'] : 1;
        $this->users_ = $_REQUEST['users'];
        $this->users = explode(':', $this->users_);
    }

    /**
     * Load object data from array
     * @param array $data
     */
    public function get_fromArray($data) {
        $this->title = stripslashes($data['name']);
        $this->description = stripslashes($data['description']);
    }

    /* Object check methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        global $camyks;

        if ($this->is_new == 1) {
            /* Check empty name */
            if ($this->name == '') {
                $this->_libError = 'erroremptyname';
                return false;
            }
            /* Check name first and last char validity */
            if ($this->name != trim ($this->name)) {
                $this->_libError = 'errorbadname';
                $this->name = trim ($this->name);
                return false;
            }
            /* Check name length */
            if (strlen($this->name) < 3) {
                $this->_libError = 'errorshortname';
                return false;
            }

            /* Check name chars validity */
            $n = string_parseSpecialChars($this->name, array('pattern'=>'/[^_a-zA-Z0-9]/'));
            if ($this->name != $n) {
                $this->_libError = 'errorbadname';
                $this->name = $n;
                return false;
            }
            /* Check existing name */
            if ($this->exists_group($this->name)) {
                $this->_libError = 'errorexistingname';
                return false;
            }
        }
        return true;
    }


    /**
     * Check if object name already exists.
     * @param string $name
     * @return boolean result
     */
    public function exists_group($name) {
        global $camyks;

        /* build sql query */
        $sql = 'select name';
        $sql .= ' from admin_group';
        $sql .= ' where name="'.addslashes($name).'"';

        /* execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* get value from database */
            if ($camyks->db_conn->get_queryDataLine()) {
                return true;
            }
        }
        return false;
    }

    /**
     * Check if user is in object.
     * @param string $user
     * @return boolean result
     */
    public function is_userInGroup($user) {
        if ($this->name == 'all') {
            return true;
        } else if ($this->name == 'none') {
            return false;
        } else if (in_array($user, $this->users)){
            return true;
        }
        return false;
    }

    /* List methods */

    /**
     * Return object list.
     * @return array
     */
    public function get_objectList() {
        global $camyks;
        $list = array();

        $g = new AdminGroup('all');
        $g->title = $camyks->get_translation('mod_admin_group_allgroupname');
        $g->users = array();
        $list['all'] = $g;
        $g = new AdminGroup('none');
        $g->title = $camyks->get_translation('mod_admin_group_nonegroupname');
        $g->users = array();
        $list['none'] = $g;

        /* Build sql query */
        $sql = 'SELECT * ';
        $sql .= ' FROM admin_group';
        $sql .= ' ORDER BY name';

        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* Load informations from sql query */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                $g = new AdminGroup($data['name']);
                $g->get_fromArray($data);
                $g->users = array();
                $list[$data['name']] = $g;
            }
        }

        /* Load users in groups */

        /* Build sql query */
        $sql = 'SELECT * ';
        $sql .= ' FROM admin_user_group';

        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* get informations from sql query */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                if (isset($list[$data['group']]))
                    $list[$data['group']]->users[] = $data['user'];
            }
        }
        return $list;
    }

    /* Static methods */

    /**
     * Return object name list
     * @return $array
     */
    public function static_getNameList() {
        global $camyks;
        $list = array();

        $list[] = $this->get_translation('allgroupname');
        $list[] = $this->get_translation('nonegroupname');

        /* Build sql query */
        $sql = 'SELECT name ';
        $sql .= ' FROM admin_group';
        $sql .= ' ORDER BY name';

        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* Load informations from sql query */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                $list[] = $data['name'];
            }
        }
        return $list;
    }

    /**
     * Return object list in admin mode
     * @return $array
     */
    public function static_getAdminList() {
        global $camyks;
        $list = array();

        /* add default groups */
        $list[] = array(
            'name'          => $this->_libParent->get_translation('allgroupname'),
            'description'   => $this->_libParent->get_translation('allgroupdesc'),
            'editable'      => false,
        );
        $list[] = array(
            'name'          => $this->_libParent->get_translation('nonegroupname'),
            'description'   => $this->_libParent->get_translation('nonegroupdesc'),
            'editable'      => false,
        );

        /* Build sql query */
        $sql = 'SELECT name, description ';
        $sql .= ' FROM admin_group';
        $sql .= ' ORDER BY name';

        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* get informations from sql query */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                $data['editable'] = true;
                $list[] = $data;
            }
        }
        return $list;
    }
}
?>
