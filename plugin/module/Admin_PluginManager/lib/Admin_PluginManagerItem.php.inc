<?php
/**
 * @brief Admin_PluginManager Module plugin information library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Oct 2008
 * @date Modification: Nov 2020
 * @copyright 2008 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_PluginManagerItem class.
 */
final class Admin_PluginManagerItem {
    /**
     * var integer $id
     * @brief Object identifier.
     */
    public $id;

    /**
     * var Object $_libParent
     * @brief Link to parent module.
     */
    private $_libParent;

    /**
     * var boolean $_libIsInstalled
     * @brief Is library installed.
     */
    private $_libIsInstalled = null;

    /**
     * Class constructor.
     * @param integer $id
     * @param module $parent
     * @return void
     */
    public function __construct($id=0, $parent=null) {
        $this->id = $id;
        $this->_libParent = $parent;
    }

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        global $camyks;

        /* Build table definition */
        $fields = array(
            array('name'=>'plugin', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>255, 'default'=>''),
            array('name'=>'type', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>16, 'default'=>''),
            array('name'=>'location', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>8, 'default'=>''),
            array('name'=>'active', 'type'=>'int', 'desc1'=>'tinyint unsigned', 'desc2'=>'', 'default'=>0),
            array('name'=>'version', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>16, 'default'=>'1.0'),
        );

        /* Create table */
        if (!$camyks->db_conn->create_table('admin_pluginmanager', $fields, $camyks->get_mysqlencodingvalue(), false, array('plugin', 'type')))
            return false;

        /* Add first element, plugin itself */
        $this->pluginvalue = $this->_libParent->name;
        $this->typevalue = 'module';
        $this->locationvalue = 'camyks';
        $this->activevalue = 1;
        $this->versionvalue = $this->_libParent->version;
        return $this->create_toDatabase();
    }

    /**
     * Check installation.
     * @return boolean result
     */
    public function is_installed() {
        global $camyks;

        if ($this->_libIsInstalled == null) {

            /* Check database presence in plugin manager module */
            if (isset($camyks->modules['Admin_PluginManager']))
                $this->_libIsInstalled = $camyks->modules['Admin_PluginManager']->check_tableExists('admin_pluginmanager');
            else {
                /* Load table list */
                $tl = $camyks->db_conn->get_tableList();

                /* Check if main table is in installed table list */
                $this->_libIsInstalled = in_array('admin_pluginmanager', $tl);
            }
        }
        return $this->_libIsInstalled;
    }

    /**
     * Load plugin data from header.
     * @return void
     */
    public function get_fromHeader() {
        $this->pluginvalue = isset($_REQUEST['plugin'])?$_REQUEST['plugin']:'';
        $this->typevalue = isset($_REQUEST['type'])?$_REQUEST['type']:'';
        $this->locationvalue = isset($_REQUEST['location'])?$_REQUEST['location']:'';
    }

    /**
     * Save plugin info in database.
     * @return boolean success
     */
    public function save_toDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = 'select * from admin_pluginmanager';
        $sql .= ' where plugin="'.addslashes($this->pluginvalue).'"';
        $sql .= ' and type="'.addslashes($this->typevalue).'"';

        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* Check query result */
            if ($camyks->db_conn->get_queryDataLine()) {
                return $this->update_toDatabase();
            } else {
                return $this->create_toDatabase();
            }
        }
        return false;
    }

    /**
     * Create new entry in database.
     * @return boolean success
     */
    public function create_toDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = 'insert into admin_pluginmanager';
        $sql .= ' (plugin, type, location, active, version) VALUES';
        $sql .= ' ("'.addslashes($this->pluginvalue).'","'.addslashes($this->typevalue);
        $sql .= '","'.addslashes($this->locationvalue).'",'.(int)$this->activevalue.',';
        $sql .= '"'.addslashes($this->versionvalue).'");';

        /* Execute sql query */
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /**
     * Delete item from database.
     * @param $p array
     * @return boolean success
     */
    public function delete_fromDatabase($p) {
        global $camyks;

        /* Build sql query */
        $sql = 'delete from admin_pluginmanager';
        $sql .= ' where plugin="'.addslashes($p['plugin']).'"';
        $sql .= ' and type="'.addslashes($p['type']).'"';
        $sql .= ' and location="'.addslashes($p['location']).'"';

        /* Execute sql query */
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /**
     * Update existing entry in database.
     * @return boolean success
     */
    public function update_toDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = 'update admin_pluginmanager';
        $sql .= ' set active='.addslashes($this->activevalue);
        $sql .= ' where plugin="'.addslashes($this->pluginvalue).'"';
        $sql .= ' and type="'.addslashes($this->typevalue).'"';

        /* Execute sql query */
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /**
     * Plugin activation method.
     * @param string $plugin
     * @param string $type
     * @param string $location
     * @param string $active
     * @return boolean success
     */
    public function active_plugin($plugin=null, $type=null, $location=null, $active=null) {
        if (isset($plugin))
            $this->pluginvalue = $plugin;
        if (isset($type))
            $this->typevalue = $type;
        if (isset($location))
            $this->locationvalue = $location;
        if (isset($active))
            $this->activevalue = $active;

        /* Install module if needed */
        switch ($this->typevalue) {
            case 'module':
                $plugin = module_get($this->pluginvalue, $this->locationvalue);
                break;
            case 'template':
                $plugin = template_get($this->pluginvalue, $this->locationvalue);
                break;
            case 'theme':
                $plugin = theme_get($this->pluginvalue, $this->locationvalue);
                break;
            case 'input':
                $plugin = input_get($this->pluginvalue, $this->locationvalue);
                break;
        }

        if ($plugin->is_installed() !== true and $plugin->install() === false)
            return false;

        $this->versionvalue = $plugin->version;
        $this->locationvalue = $plugin->path_type;

        /* Active plugin in database */
        return $this->save_toDatabase();
    }

    /**
     * Update plugin version.
     * @param string $plugin
     * @param string $type
     * @param string $version
     * @return boolean success
     */
    public function update_pluginVersion($plugin, $type, $version) {
        global $camyks;

        /* Build sql query */
        $sql = 'update admin_pluginmanager';
        $sql .= ' set version="'.addslashes($version).'"';
        $sql .= ' where plugin="'.addslashes($plugin).'"';
        $sql .= ' and type="'.addslashes($type).'"';

        /* Execute sql query */
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /**
     * Set plugin as default plugin in CaMykS Configuration.
     * @param string $cMode
     * @return boolean success
     */
    public function set_asDefault($cMode='site') {
        global $camyks;

        /* Check values */
        if ($this->typevalue == 'theme' and in_array($cMode, array('admin', 'site')) or ($this->typevalue == 'template' and $cMode == 'site'))
            return $camyks->update_siteConfFile(array($cMode.'_default_'.$this->typevalue => $this->pluginvalue));

        /* By default, return false */
        return false;
    }

    /**
     * Load plugin list.
     * @param array $params
     * @return array
     */
    public function get_objectList($params=array()) {
        global $camyks;

        /* Check params */
        $params = array_merge($this->get_defaultParams(), $params);

        /* Initialise plugin list */
        $plugins = array();

        /* Build where statement */
        $where = $this->build_whereStatement($params);

        /* Build sql query */
        $sql = 'select *';
        $sql .= ' from admin_pluginmanager';

        /* add where statement */
        if ($where != '')
            $sql .= ' where '.$where;

        /* Add order statement */
        $sql .= ' order by type asc, plugin asc';

        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__))

            /* Get data from database */
            while ($data = $camyks->db_conn->get_queryDataLine())
                $plugins[] = $data;

        /* return result */
        return $plugins;
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
            $w[] = 'active = '.(int)$params['status'];

        /* Check type */
        if ($params['type'] != -1)
            $w[] = 'type = "'.$params['type'].'"';

        /* Return result */
        return implode(' and ', $w);
    }

    /**
     * Return default params
     * @return array
     */
    private function get_defaultParams() {
        return array(
            'status'    => -1,
            'type'      => -1,
        );
    }
}
?>
