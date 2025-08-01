<?php
/**
 * @brief Admin_GenericContactFormManager module, form library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.2
 * @date Creation: Nov 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericContactFormManagerForm class.
 */
final class Admin_GenericContactFormManagerForm extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct ($id, $module);

        /* Admin items */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('ipaddress', 'db', 'text', 'varchar', 48, '');
        $this->add_newItem('edate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('locale', 'db', 'text', 'varchar', 3, '');
        $this->add_newItem('hidden', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('account', 'db', 'int', 'bigint unsigned', '', 0);

        /* Request items */
        $this->add_newItem('type', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('company', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('firstname', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('lastname', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('email', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('subject', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('subject_title', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('request', 'db', 'text', 'text', '', '');
        $this->add_newItem('attachment', 'file', 'attachments', '', '', '');

        /* Answer items    */
        $this->add_newItem('answer_date', 'db', 'date', 'bigint', '', 0);
        $this->add_newItem('answer_admin', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('answer_comment', 'db', 'text', 'text', '', '');

        /* Perform generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object data
     * @return boolean success
     */
    public function check_data() {
        global $camyks;

        /* trim author value */
        $this->_libItems['author']->value = trim($this->_libItems['author']->value);

        /* Check author value */
        if ($this->_libItems['author']->value == '') {
            $this->_libError = $this->get_translation('message_saveerror_authorempty');
            return false;
        }

        /* Trim email value */
        $this->_libItems['email']->value = trim($this->_libItems['email']->value);
        /* Check form value */
        if ($this->_libItems['email']->value == '') {
            $this->_libError = $this->get_translation('message_saveerror_emailempty');
            return false;
        }
        if (mail_isValidEmail($this->_libItems['email']->value)==false) {
            $this->_libError = $this->get_translation('message_saveerror_emailinvalid');
            return false;
        }

        /* trim form value */
        $this->_libItems['request']->value = trim(strip_tags($this->_libItems['request']->value));
        /* Check form value */
        if ($this->_libItems['request']->value == '') {
            $this->_libError = $this->get_translation('message_saveerror_formempty');
            return false;
        }

        /* Complete new object data */
        if ($this->id == 0) {
            $this->_libItems['status']->value = 0;
            $this->_libItems['edate']->initialise();
            $this->_libItems['ipaddress']->value = client_getIp();
            $this->_libItems['locale']->value = $camyks->current_language;
        }
        return true;
    }

    /**
     * Build SQL condition.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $query = array();

        /* Check status */
        if (isset($params['status']) and $params['status']!=-1)
            $query[] = 'status = '.$params['status'];

        return implode(' AND ', $query);
    }

    /* Mark: Specific tool methods */

    /**
     * Return objects status list
     * @param boolean $full
     * @return array
     */
    public function get_multiStatusList($full=false) {
        $list = array();
        if ($full)
            $list[-1] = $this->get_translation('formsstatus_all');
        $list[0] = $this->get_translation('formsstatus_disabled');
        $list[1] = $this->get_translation('formsstatus_enabled');
        $list[2] = $this->get_translation('formsstatus_pending');
        return $list;
    }

    /**
     * Return object status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('formstatus_disabled'),
            1 => $this->get_translation('formstatus_enabled'),
            2 => $this->get_translation('formstatus_pending'),
        );
    }

    /**
     * Return object status value.
     * @param mixed $status
     * @return string
     */
    public function get_statusValue($status=false) {
        $list = $this->get_statusList();
        if ($status === false)
            $status = $this->vars['status'];
        return $list[$status];
    }

    /**
     * Return object status icon list.
     * @return array
     */
    public function get_statusIconList() {
        $theme = &$this->_libParent->theme;
        return array(
            0 =>'<img src="'.$theme->get_pictURL('empty', 12, 'std').'" alt="" />',
            1 =>'<img src="'.$theme->get_pictURL('valid', 12, 'std').'" alt="" />',
            2 =>'<img src="'.$theme->get_pictURL('minus', 12, 'std').'" alt="" />',
        );
    }

    /**
     * Return object status icon.
     * @return array
     */
    public function get_statusIcon($status=false) {
        $icons = $this->get_statusIconList();
        if ($status === false)
            return $icons[$this->vars['status']];
        return $icons[$status];
    }

    /**
     * Return form list with given params.
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        global $camyks;
        $p = array('status'=>-1, 'limit'=>-1, 'count'=>-1, 'order'=>'id', 'orderway'=>'');
        $params = array_merge($p, $params);
        $w = $this->build_whereStatement($params);
        return $this->get_objectList($camyks->current_language, $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
    }

    /**
     * Return form count with given params.
     * @param array $params
     * @return array
     */
    public function count($params=array()) {
        global $camyks;
        $p = array('status'=>-1);
        $params = array_merge($p, $params);
        return $this->get_objectCount($this->build_whereStatement($params));
    }

    /**
     * Build where statement from params.
     * @param array $params
     * @return string
     */
    private function build_whereStatement($params=array()) {
        $w = array();

        /* Check status */
        if (is_string($params['status']) and $params['status'] != '')
            $w[] = 'status '.addslashes($params['status']);
        elseif($params['status'] != -1)
            $w[] = 'status = '.$params['status'];

        /* Return result */
        return implode(' and ', $w);
    }
}
?>
