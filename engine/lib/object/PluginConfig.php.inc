<?php
/**
 * @brief PluginConfig library.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Oct 2017
 * @date Modification: Nov 2020
 * @copyright 2017 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PluginConfig class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
abstract class PluginConfig {
    /**
     * @var string $object_type
     * @brief Object type description.
     */
    public $object_type = 'PluginConfig';

    /**
     * @var string $_libName
     * @brief PluginConfig name.
     */
    public $_libName;

    /**
     * @var Object $_libParent
     * @brief Object parent plugin.
     */
    public $_libParent;

    /**
     * @var array $_libItems
     * @brief Object item list.
     */
    public $_libItems = array();

    /**
     * @var string $_libDesc
     * @brief Object description.
     */
    public $_libDesc;

    /**
     * @var string $_libFolder
     * @brief Folder where object are stored.
     */
    protected $_libFolder;

    /**
     * @var string $_libFile
     * @brief Stored file for object.
     */
    protected $_libFile;

    /**
     * @var string $_libError
     * @brief Object last error.
     */
    public $_libError = '';

    /**
     * @var string $name
     * @brief Object name.
     */
    public $name;

    /**
     * @var array $vars
     * @brief Object values.
     */
    public $vars = null;

    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $plugin
     */
    public function __construct($name, &$plugin) {
        $this->name = $name;
        $this->_libName = get_class($this);
        $this->_libParent = $plugin;
        $this->_libDesc = ucwords($plugin->plugin_type).':'.$this->_libParent->name.' Lib:'.$this->_libName;
        $this->_libFolder = $this->_libParent->plugin_var_path.'/'.$this->_libName;
        $this->_libFile = $this->_libFolder.'/'.$this->name.'.php.inc';
    }

    /**
     * Install object.
     * @return boolean
     */
    public function install() {
        return $this->initialise() and $this->save();
    }

    /**
     * Uninstall object.
     * @return boolean
     */
    public function uninstall() {
        return true;
    }

    /*
     * Finish config object initialisation.
     * @return void
     */
    public function init_config() {
    }

    /*
     * Insert a new item in object.
     * @param string $name
     * @param string $type
     * @param string $default
     * @return boolean
     */
    public function add_newItem($name, $type, $default=null) {
        global $camyks;
        /* check item name */
        if (isset ($this->_libItems[$name])) {
            $camyks->log_internalerror(
                $this,
                'Plugin Config Item Definition Error',
                'Item with name "'.$name.'" already exists in this module config'
            );
            return false;
        }
        $this->_libItems[$name] = new PluginConfigItem($name, $type, $default);
        return true;
    }

    /**
     * Initialise object with default values.
     * @return boolean
     */
    public function initialise() {
        foreach ($this->_libItems as $name => $item) {
            $this->vars[$name] = $item->initialise();
        }
        return true;
    }

    /**
     * Load object from file.
     * @return boolean
     */
    public function get() {
        if (file_exists($this->_libFile)) {
            /* get file "vars" value */
            require $this->_libFile;

            /* check if vars value list exists */
            if (!isset($this->vars))
                return $this->initialise();

            /* complete items */
            foreach ($this->_libItems as $name => $item) {
                if (!isset($this->vars[$name]))
                    $this->vars[$name] = $item->initialise();
                else
                    $this->vars[$name] = $item->check_value($this->vars[$name]);
            }
            return true;
        } else {
            return $this->initialise();
        }
        return true;
    }

    /**
     * Save object to file.
     * @return boolean
     */
    public function save() {
        if (isset($this->vars) and $this->check_data()) {
            /* build config content */
            $content = file_getPHPFileHeader($this->name . ' '. $this->_libName.' file', '1.0');
            $content .= '$this->vars = ' . var_export($this->vars, true) . ';';
            $content .= file_getPHPFileFooter();

            /* create folder */
            if (!file_exists($this->_libFolder))
                folder_completePath($this->_libFolder);

            /* write file */
            if (file_write($this->_libFile, $content, true))
                return true;
        }
        return false;
    }

    /**
     * Delete object file.
     * @return boolean
     */
    public function delete() {
        if (file_exists($this->_libFile))
            return unlink($this->_libFile);
        return true;
    }

    /**
     * Reset object into file.
     * @return boolean success
     */
    public function reset() {
        $this->initialise();
        return $this->save();
    }

    /**
     * Check object items values.
     * @return boolean
     */
    public function check_data() {
        return true;
    }

    /**
     * Load object items values from header.
     * @return void
     */
    public function get_fromHeader() {
        foreach ($this->_libItems as $item) {
            $this->vars[$item->_name] = $item->get_fromHeader();
        }
    }

    /**
     * Return value.
     * @param string $param
     * @param mixed $default
     * @return mixed
     */
    public function get_value($param='', $default=false) {
        if ($this->vars == null) $this->get();
        if (!isset($this->vars[$param]))
            return $default;
        return $this->_libItems[$param]->check_value($this->vars[$param]);
    }

    /* tool methods */

    /**
     * Return locale
     * @param string $str
     * @param mixed $args
     * @return string
     */
    public function get_translation($str, $args=null) {
        return $this->_libParent->get_translation($str, $args);
    }
}
?>
