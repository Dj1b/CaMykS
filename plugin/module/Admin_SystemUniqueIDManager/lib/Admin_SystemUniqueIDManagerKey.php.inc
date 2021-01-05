<?php
/**
 * @brief Admin_SystemUniqueIDManager Module key library
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2015
 * @date Modification: Jan 2021
 * @copyright 2015 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SystemUniqueIDManagerKey class.
 */
final class Admin_SystemUniqueIDManagerKey extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);
        
        /* Define attributes */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('cdate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('uniqueID', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('plugin', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('object', 'db', 'text', 'varchar', 16, '');
        
        /* Perform generic initialisation */
        $this->init_library();
    }
    
    /* Override ModuleLibrary method */
    
    /**
     * Check object data
     * @return boolean success
     */
    public function check_data() {
        /* Check object status from data */
        if ($this->_libItems['plugin']->value != '' and $this->_libItems['object']->value != '')
            $this->_libItems['status']->value = 1;
        
        /* Set creating date */
        if ($this->id == 0)
            $this->_libItems['cdate']->value = time();
        
        /* Check for generating a new unique id*/
        if ($this->_libItems['uniqueID']->value == '')
            return ($this->generate_uniqueIdValue());
        return true;
    }
    
    /**
     * Build sql condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $search = array();
        if (isset($params['status']) and $params['status']!='' and $params['status'] > -1)
            $search[] = 'status='.$params['status'];
        return implode(' and ', $search);
    }
    
    /* Specific properties definition method */
    
    /**
     * Return status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('keystatus_free'),
            1 => $this->get_translation('keystatus_used'),
       );
    }
    
    /**
     * Return multi object status list.
     * @param boolean $more
     * @return array
     */
    public function get_multiStatusList($more=false) {
        $list = array();
        if ($more)
            $list['-1'] = $this->get_translation('keys_all');
        $list['0'] = $this->get_translation('keysstatus_free');
        $list['1'] = $this->get_translation('keysstatus_useded');
        return $list;
    }
    
    /**
     * Return generating method list.
     * @return array
     */
    public function get_generatingMethodList() {
        return array(
            0 => $this->get_translation('keygeneratingmethod_md5'),
            1 => $this->get_translation('keygeneratingmethod_crc32'),
            2 => $this->get_translation('keygeneratingmethod_sha'),
            3 => $this->get_translation('keygeneratingmethod_uniqid'),
       );
    }
    
    /* Specific tool methods */
    
    /**
     * Load free item from database.
     * @return boolean success
     */
    public function load_freeItem() {
        $l = $this->get_list(array('status'=>0, 'limit'=>1));
        if (count($l) == 0)
            return false;
            
        foreach ($l as $i) {
            $this->id = $i->id;
            $this->get_fromArray($i->vars);
            $this->get_fromItems();
        }
         
        return true;
    }
    
    /**
     * Check if object is deletable.
     * @return boolean result
     */
    public function is_deletable() {
        /* Check plugin and object values */
        if ($this->vars['plugin'] == '' or $this->vars['object'] == '')
            return true;
        
        /* Check plugin and object objects */
        
        /* Key is still in use, do not delete */
        return false;
    }
    
    /**
     * Return object list.
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        global $camyks;
        
        /* Default params list */
        $dParams = array('status'=>-1, 'language'=>$camyks->current_language, 'limit'=>-1, 'count'=>-1, 'order'=>'sortPosition', 'orderway'=>'asc');
        
        /* Merge params */
        $params = array_merge($dParams, $params);
        
        /* Build where statement */
        $where = $this->build_whereStatement($params);
        
        /* Return list */
        return $this->get_objectList($params['language'], $where, $params['limit'], $params['count'], $params['order'], $params['orderway']);
    }
    
    /**                                                                                                                                                                 
     * Return uniqueID count with given params.                                                                                 
     * @params array $params                                                                                                                     
     * @return array                                                                                                                                     
     */
    public function count($params=array()) {
        global $camyks;
        $p = array('status'=>-1,);
        $params = array_merge($p, $params);
        $where = $this->build_whereStatement($params);
        
        /* Return result */
        return $this->get_objectCount($where);
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
        
        /* Return result */
        return implode(' and ', $w);
    }
    
    /**
     * Return config value.
     * @param mixed $param
     * @return string
     * @access private
     */
    private function get_configValue($param=array()) {
        return $this->_libParent->get_configValue($param);
    }
    
    /**
     * Generate a new unique key.
     * @return mixed
     */
    public function generate_uniqueIdValue() {
        $c = 0;
        
        /* Check if max attempts limit is exceeded */
        while($c++ < $this->get_configValue('generating_maxAttempts')) {
        
            /* Generate code from selected method */
            switch ($this->get_configValue('generating_method')) {
                case 0: $code = md5(session_id().microtime()); break;
                case 1 : $code = abs(crc32(session_id().microtime())); break;
                case 2 : $code = sha1(session_id().microtime()); break;
                case 3 : $code = uniqid(null, true); break;
            }
        
            /* Truncate value to defined max length */
            $code = substr($code, 0, $this->get_configValue('generating_length'));
            
            /* Check if exists in database */
            $sql = 'select uniqueID from '.$this->_libSQLTable;
            $sql .= ' where uniqueID = "'.$code.'"';
            if ($this->execute_DBQuery($sql, __LINE__, __FILE__)) {
                    if (!$this->get_DBQueryDataLine()) {        
                        $this->_libItems['uniqueID']->value = $code;
                        return true;
                 }
            }
            
            /* Make a pause to change the microtime value */
            usleep(20);
        }
        
        /* Attempt limit exceeded */
        $camyks->log_executionerror($this, $this->get_translation('keygenerator_attemptlimitexceeded'));
        
        /* Attempts limit exceeded, return failure */
        return false;
    }
}
?>