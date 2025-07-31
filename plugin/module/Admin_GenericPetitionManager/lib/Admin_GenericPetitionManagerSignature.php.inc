<?php
/**
 * @brief Admin_GenericPetitionManager module, signature library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Sep 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericPetitionManagerSignature class.
 */
final class Admin_GenericPetitionManagerSignature extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('petition', 'db', 'date', 'bigint unsigned', '', 0);
        $this->add_newItem('signdate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('title', 'db', 'text', 'varchar', 6, '');
        $this->add_newItem('firstname', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('lastname', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('email', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('address', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('zipcode', 'db', 'text', 'varchar', 12, '');
        $this->add_newItem('city', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('country', 'db', 'text', 'varchar', 3, '');
        $this->add_newItem('birthdate', 'db', 'date', 'bigint', '', time());

        /* Temporary attributes */
        $this->add_newItem('confirm', 'temp', 'integer', '', '', 0);

        /* Perform generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean success
     */
    public function check_data() {
        /* Check mandatory values */
        $this->_libItems['firstname']->value = trim($this->_libItems['firstname']->value);
        if ($this->_libItems['firstname']->value == '') {
            $this->_libError = $this->get_translation('error_firstnamemustbeset');
            return false;
        }

        $this->_libItems['lastname']->value = trim($this->_libItems['lastname']->value);
        if ($this->_libItems['lastname']->value == '') {
            $this->_libError = $this->get_translation('error_lastnamemustbeset');
            return false;
        }

        $this->_libItems['city']->value = trim($this->_libItems['city']->value);
        if ($this->_libItems['city']->value == '') {
            $this->_libError = $this->get_translation('error_citymustbeset');
            return false;
        }

        $this->_libItems['zipcode']->value = trim($this->_libItems['zipcode']->value);
        if ($this->_libItems['zipcode']->value == '') {
            $this->_libError = $this->get_translation('error_zipcodemustbeset');
            return false;
        }

        $this->_libItems['email']->value = trim($this->_libItems['email']->value);
        if ($this->_libItems['email']->value == '') {
            $this->_libError = $this->get_translation('error_emailmustbeset');
            return false;
        }

        if (mail_isValidEmail($this->_libItems['email']->value) == false) {
            $this->_libError = $this->get_translation('error_emailmustbevalid');
            return false;
        }
        return true;
    }

    /**
     * Build sql condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $where = array();

        if (isset($_REQUEST['petition_id']) and $_REQUEST['petition_id'] > 0)
            $where[] = 'petition = '.(int)$_REQUEST['petition_id'];

        if (isset($params['status']) and $params['status'] > -1)
            $where[] = 'status='.$params['status'];

        return implode(' and ', $where);
    }

    /* Mark: Specific methods */

    /**
     * Return categories status list.
     * @param boolean $full
     * @return array
     */
    public function get_multiStatusList($full=false) {
        $list = array();
        if($full)
            $list['-1'] = $this->get_translation('signaturesstatus_all');
        $list['0'] = $this->get_translation('signaturesstatus_disabled');
        $list['1'] = $this->get_translation('signaturesstatus_enabled');
        return $list;
    }

    /**
     * Return single signature status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('signaturestatus_disabled'),
            1 => $this->get_translation('signaturestatus_enabled'),
        );
    }

    /**
     * Return signature count by petition.
     * @param array $petitions
     * @return array
     */
    public function count_byPetitions($petitions=null) {
        global $camyks;

        $list = array();

        /* Check petitions */
        if (is_array($petitions) and count($petitions) == 0)
            return $list;

        /* Build SQL query */
        $sql = 'select petition, count(id) as cnt from '.$this->_libSQLTable;
        if (is_array($petitions) and count($petitions)>0)
            $sql .= ' where petition in ('.implode(',', $petitions).')';
        $sql .= ' group by petition';

        /* Execute SQL query */
        if ($this->execute_DBQuery($sql, __LINE__))
            while ($data = $this->get_DBQueryDataLine())
                $list[$data['petition']] = $data['cnt'];

        /* Return results */
        return $list;
    }

    /**
     * Return signature list with given params.
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        global $camyks;
        $p = array('status'=>-1, 'petition'=>-1, 'limit'=>-1, 'count'=>-1, 'order'=>'id', 'orderway'=>'');
        $params = array_merge($p, $params);
        $w = $this->build_whereStatement($params);
        return $this->get_objectList($camyks->current_language, $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
    }

    /**
     * Return petition count with given params
     * @param array $params
     * @return array
     */
    public function count($params=array()) {
        global $camyks;
        $p = array('status'=>-1, 'petition'=>-1);
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
            $w[] = 'status '.$params['status'];
        elseif($params['status'] != -1)
            $w[] = 'status = '.$params['status'];

        /* Check petition */
        if (is_numeric($params['petition']) and $params['petition'] != -1)
            $w[] = 'petition = '.$params['petition'];
        elseif (is_string($params['petition']) and $params['petition'] != '')
            $w[] = 'petition '.$params['petition'];
        elseif(is_array($params['petition'])) {
            if (count($params['petition']) == 0)
        return 'false';
            elseif(count($params['petition']) == 1)
                $w[] = 'petition = '.$params['petition'][0];
            else
                $w[] = 'petition in ('.implode(', ', $params['petition']).')';
        }
        return implode(' and ', $w);
    }

    /**
     * Save object from site.
     * @return success
     */
    public function save_fromSite() {
        $this->id = 0;
        $this->get_fromHeader();
        $this->_libItems['status']->value = 1;
        return $this->save();
    }
}
?>
