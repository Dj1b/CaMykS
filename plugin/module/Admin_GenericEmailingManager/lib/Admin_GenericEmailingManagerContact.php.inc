<?php
/**
 * @brief Admin_GenericEmailingManager Module, contact library.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.1
 * @date Creation: Dec 2012
 * @date Modification: Oct 2021
 * @copyright 2012 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericEmailingManagerContact class.
 */
final class Admin_GenericEmailingManagerContact extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('lastname', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('firstname', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('email', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('group', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('denomination', 'db', 'text', 'varchar', 64, '');

        $this->add_newItem('old_email', 'temp', 'text', '', '', '');
        $this->add_newItem('extra', 'temp', 'array', '', '', array());
        $this->add_newItem('cc', 'temp', 'array', '', '', array());

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Build sql condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $search = array();

        if (isset($params['status']) and $params['status']!='' and $params['status'] > -1)
            $search[] = 'status='.$params['status'];
        if (isset($params['group']) and $params['group']!='_all_')
            $search[] = '`group`="'.$params['group'].'"';
        if (isset($params['search']) and $params['search'] != '')
            $search[] = '(firstname like "%'.$params['search'].'%" or lastname like "%'.$params['search'].'%"'. ' or email like "%'.$params['search'].'%")';
        return implode(' and ', $search);
    }

    /**
     * Check object data.
     * @return boolean success
     */
    public function check_data() {

        /* Trim values */
        $this->_libItems['email']->value = trim($this->_libItems['email']->value);
        $this->_libItems['lastname']->value = trim($this->_libItems['lastname']->value);
        $this->_libItems['firstname']->value = trim($this->_libItems['firstname']->value);

        /* Check email value */
        $this->_libItems['email']->value = preg_replace('/"\'/', '', $this->_libItems['email']->value);

        /* Check if email already exists */
        if ($this->_libItems['email']->value != $this->_libItems['old_email']->value
            and $this->_check_existingEmail($this->_libItems['email']->value)) {
            $this->_libError = $this->get_translation('contact_saveerror_alreadyexists');
            return false;
        }

        /* Return default result */
        return true;
    }

    /* Specific tool methods */

    /**
     * Return object status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0  => $this->get_translation('contactstatus_disabled'),
            1  => $this->get_translation('contactstatus_subscribed'),
            2  => $this->get_translation('contactstatus_unsubscribed'),
            3  => $this->get_translation('contactstatus_invalid'),
            99 => $this->get_translation('contactstatus_test'),
        );
    }

    /**
     * Return objects status list.
     * @param boolean $more
     * @return array
     */
    public function get_multiStatusList($more=false) {
        $l = array();
        if ($more)
            $l['-1'] = $this->get_translation('contacts_all');
        return $l + array(
            0  => $this->get_translation('contactsstatus_disabled'),
            1  => $this->get_translation('contactsstatus_subscribed'),
            2  => $this->get_translation('contactsstatus_unsubscribed'),
            3  => $this->get_translation('contactsstatus_invalid'),
            99 => $this->get_translation('contactsstatus_test'),
        );
    }

    /**
     * Return object status list.
     * @return array
     */
    public function get_statusIconList() {
        return array(
            0  => '<img src="'.$this->_libParent->theme->get_pictURL('empty', 12, 'std').'" alt="" border="0" />',
            1  => '<img src="'.$this->_libParent->theme->get_pictURL('valid', 12, 'std').'" alt="" border="0" />',
            2  => '<img src="'.$this->_libParent->theme->get_pictURL('cross', 12, 'std').'" alt="" border="0" />',
            3  => '<img src="'.$this->_libParent->theme->get_pictURL('minus', 12, 'std').'" alt="" border="0" />',
            99 => '<img src="'.$this->_libParent->theme->get_pictURL('target', 12, 'std').'" alt="" border="0" />',
        );
    }

    /**
     * Return object group list.
     * @param boolean $all
     * @param boolean $other
     * @return array
     */
    public function get_groupList($all=false, $other=false) {
        $list = array();

        if ($all)
            $list['_all_'] = $this->get_translation('contactgroup_all');

        $list[''] = $this->get_translation('contactgroup_none');

        /* Build sql query */
        $sql = 'select `group`';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' group by `group`';
        $sql .= ' order by `group` asc';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* Get result of sql query */
            while ($data = $this->get_DBQueryDataLine()) {
                if ($data['group'] != '')
                    $list[$data['group']] = $data['group'];
            }
        }
        if ($other)
            $list['_other_'] = $this->get_translation('contactgroup_other');
        return $list;
    }

    /**
     * Return object category title.
     * @param integer $group
     * @return string
     */
    public function get_groupTitle($group) {
        $list = $this->get_groupList(true);
        return $list[$group];
    }

    /**
     * Return object items as mail params.
     * @return array
     */
    public function get_itemsAsMailParams() {
        return array_merge(
            array(
                'recipient_id'=>$this->id,
                'recipient_fullname'=>$this->get_fullName(),
                'recipient_firstname'=>utf8_decode($this->vars['firstname']),
                'recipient_lastname'=>utf8_decode($this->vars['lastname']),
                'recipient_email'=>$this->vars['email'],
            ),
            $this->vars['extra']
        );
    }

    /**
     * Return object list.
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        /* Default params list */
        $dParams = array('status'=>-1, 'group'=>'_all_', 'ids'=>-1, 'search'=>'', 'startwith'=>'', 'limit'=>-1, 'count'=>-1, 'order'=>'rdate', 'orderway'=>'desc');

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Build where statement */
        $w = $this->build_whereStatement($params);

        /* Return list */
        return $this->get_objectList($params['language'], $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
    }

    /**
     * Return message count with given parameters.
     * @param array $params
     * @return array
     */
    public function count($params=array()) {
        /* Default params list */
        $dParams = array('status'=>-1, 'group'=>'_all_', 'ids'=>-1, 'search'=>'', 'emailstartwith'=>'');

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Build where statement */
        $where = $this->build_whereStatement($params);

        /* Return results */
        return $this->get_objectCount($where);
    }

    /**
     * Return object id list.
     * @param array $params
     * @return array
     */
    public function get_idList($params=array()) {
        /* Default params list */
        $dParams = array('status'=>-1, 'group'=>'_all_', 'ids'=>-1, 'search'=>'', 'emailstartwith'=>'');

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Build where statement */
        $w = $this->build_whereStatement($params);

        /* Build sql query */
        $sql = 'select id ';
        $sql .= ' from '.$this->_libSQLTable;
        if ($w != '')
            $sql .= ' where '.$w;

        /* Execute sql query */
        $list = array();
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* Get result of sql query */
            while ($data = $this->get_DBQueryDataLine())
                $list[] = $data['id'];
        }
        return $list;
    }

    /**
     * Return object email list.
     * @param array $params
     * @return array
     */
    public function get_emailList($params=array()) {
        /* Default params list */
        $dParams = array('status'=>-1, 'group'=>'_all_', 'ids'=>-1, 'search'=>'', 'emailstartwith'=>'');

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Build where statement */
        $w = $this->build_whereStatement($params);

        /* Build sql query */
        $sql = 'select email ';
        $sql .= ' from '.$this->_libSQLTable;
        if ($w != '')
            $sql .= ' where '.$w;

        /* Execute sql query */
        $list = array();
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* Get result of sql query */
            while ($data = $this->get_DBQueryDataLine())
                $list[] = $data['id'];
        }
        return $list;
    }

    /**
     * Return contact full name list.
     * @param array $params
     * @return array
     */
    public function get_fullNameList($params=array()) {
        /* Default params list */
        $dParams = array('status'=>-1, 'group'=>'_all_', 'ids'=>-1, 'search'=>'', 'emailstartwith'=>'');

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Build where statement */
        $w = $this->build_whereStatement($params);

        /* Build sql query */
        $sql = 'select id, firstname, lastname, email ';
        $sql .= ' from '.$this->_libSQLTable;
        if ($w != '')
            $sql .= ' where '.$w;

        /* Execute sql query */
        $list = array();
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* Get result of sql query */
            while ($data = $this->get_DBQueryDataLine()) {
                if ($data['firstname'] != '' and $data['lastname'] != '')
                    $list[$data['id']] = $data['firstname'].' '.$data['lastname'];
                elseif ($data['firstname'] != '')
                    $list[$data['id']] = $data['firstname'];
                elseif ($data['lastname'] !=    '')
                    $list[$data['id']] = $data['lastname'];
                else
                    $list[$data['id']] = $data['email'];
            }
        }
        return $list;
    }

    /**
     * Build where statement from params.
     * @param array $params
     * @return string
     */
    private function build_whereStatement($params=array()) {
        $w = array();

        /* Check status */
        if ($params['status'] != -1)
            $w[] = 'status = '.$params['status'];

        /* Check group id */
        if ($params['group'] != '_all_')
            $w[] = '`group` = "'.$params['group'].'"';

        /* Check ids */
        if ($params['ids'] != -1 and count($params['ids'])>0)
                $w[] = 'id in ('.implode(',', array_unique($params['ids'])).')';

        /* Check search */
        if ($params['search'] != '') {
            $w[] = '(firstname like "%'.$params['search'].'%"'
                . 'or lastname like "%'.$params['search'].'%"'
                . 'or email like "%'.$params['search'].'%")';
        }

        /* Check start with */
        if ($params['emailstartwith'] != '') {
            $w[] = 'email like "'.$params['emailstartwith'].'%"';
        }

        /* Return result */
        return implode(' and ', $w);
    }

    /**
     * Load object from email.
     * @param string $email
     * @param integer $id
     * @return boolean success
     */
    public function get_fromEmail($email, $id=false) {
        /* Build sql query */
        $sql = 'select *';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where email = "'.$email.'"';
        if ($id !== false)
            $sql .= ' and id = '.$id;

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* Get result of sql query */
            if ($data = $this->get_DBQueryDataLine()) {
                $this->id = $data['id'];
                $this->get_fromArray($data, $this->_libItemTypes['db']);
                return true;
            }
        }

        /* Return default result */
        return false;
    }

    /**
     * Load object from fullname.
     * @param string $firstname
     * @param string $lastname
     * @return boolean success
     */
    public function get_fromFullName($firstname, $lastname) {

        /* Build sql query */
        $sql = 'select *';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where firstname = "'.$firstname.'"';
        $sql .= ' and lastname = "'.$lastname.'"';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            /* Get result of sql query */
            if ($data = $this->get_DBQueryDataLine()) {
                $this->id = $data['id'];
                $this->get_fromArray($data, $this->_libItemTypes['db']);
                return true;
            }
        }
        return false;
    }

    /**
     * Set status as unsubsribed.
     * @param string $email
     * @return boolean success
     */
    public function update_asUnsubscribed($email) {
        if (!$this->get())
            return false;
        $this->get_fromItems();
        if (!$this->vars['email'] == $email)
            return false;
        $this->_libItems['status']->value = 2;
        return $this->update_databaseSpecificItems(array('status'));
    }

    /**
     * Update status to invalid.
     * @return boolean result
     */
    public function mark_asInvalid() {
        $this->_libItems['status']->value = 3;
        return $this->update_databaseSpecificItems(array('status'));
    }

    /**
     * Return full contact name.
     * @return string
     */
    public function get_fullName($default='') {
        if ($this->vars['firstname'] != '' and $this->vars['lastname'] != '')
            return $this->vars['firstname'].' '.$this->vars['lastname'];
        elseif ($this->vars['firstname'] != '')
            return $this->vars['firstname'];
        elseif ($this->vars['lastname'] !=    '')
            return $this->vars['lastname'];
        return $default;
    }

    /**
     * Add new object or update existing one.
     * @param array $params
     * @return boolean result
     */
    public function add_object($params=array()) {

        $dParams = array('status'=>1, 'email'=>'', 'firstname'=>'', 'lastname'=>'', 'group'=>'', 'denomination'=>'');
        $params = array_merge($dParams, $params);

        /* Check email */
        if ($params['email'] == '' or mail_isValidEmail($params['email']) == false) {
            $this->_libError = $this->get_translation('contact_saveerror_emailinvalid');
            return false;
        }

        /* Load existing email */
        if ($this->get_fromEmail($params['email'])) {
            $this->_libItems['old_email']->value = $params['email'];
            if ($params['status'] > -1) $this->_libItems['status']->value = $params['status'];
            if ($params['firstname'] != '') $this->_libItems['firstname']->value = $params['firstname'];
            if ($params['lastname'] != '') $this->_libItems['lastname']->value = $params['lastname'];
            if ($params['group'] != '') $this->_libItems['group']->value = $params['group'];
            if ($params['denomination'] != '') $this->_libItems['denomination']->value = $params['denomination'];
            return $this->save();
        } else {
            $this->initialise();
            $this->get_fromArray($params);
            $this->get_fromItems();
            return $this->save();
        }
        return true;
    }

    /**
     * Check is email already exists
     * @return boolean result
     */
    private function _check_existingEmail($email=null) {
        /* Build sql query */
        $sql = 'select id';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where email = "'.$email.'"';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__))
            if ($this->get_DBQueryDataLine())
                return true;

        /* Return default result */
        return false;
    }
}
?>
