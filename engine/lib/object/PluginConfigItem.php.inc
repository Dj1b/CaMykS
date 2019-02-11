<?php
/**
 * @brief Configuration item for PluginConfig library.
 * @details Engine / Object Library
 * @file engine/lib/object/PluginConfigItem.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2007
 * @date Modification: Feb 2019
 * @copyright 2007 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PushNotification class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class PluginConfigItem {
    /**
     * @var string $_name
     * @brief Item name.
     */
    public $_name;

    /**
     * @var string $_type
     * @brief Item type.
     */
    public $_type;

    /**
     * @var string $_default
     * @brief Item default value.
     */
    private $_default;

    /**
     * Class constructor.
     * @param string $name
     * @param string $type
     * @param mixed $default
     * @return void
     */
    public function __construct($name, $type, $default=null) {
        $this->_name = $name;
        $this->_type = $type;
        $this->_default = isset($default) ? $this->update_type($default) : $this->get_default();
    }

    /**
     * Initialise object with default value.
     * @return void
     */
    public function initialise() {
        return $this->_default;
    }

    /**
     * Return checked value case of object type.
     * @param mixed $value
     * @return mixed
     */
    public function check_value($value) {
        switch ($this->_type) {
            case 'string':
                return stripslashes($value);
            case 'int':
            case 'integer':
            case 'float':
            case 'boolean':
            case 'array':
            default:
                return $value;
        }
    }

    /**
     * Load object value from header.
     * @return mixed
     */
    public function get_fromHeader() {
        switch ($this->_type) {
        case 'array':
            $value = array();
            if (isset($_REQUEST[$this->_name.'_count_'])) {
                for ($i=0; $i < $_REQUEST[$this->_name.'_count_']; $i++)
                    if (isset($_REQUEST[$this->_name.'_'.$i]))
                        $value[$i] = $_REQUEST[$this->_name.'_'.$i];
            } else {
                $s = 0;
                while (isset($_REQUEST[$this->_name.'_'.$s])) {
                    $value[$s] = $_REQUEST[$this->_name.'_'.$s];
                    $s++;
                }
            }
            return $value;
        case 'date':
            $name = $this->_name;
            if (isset ($_REQUEST[$name])) {
                return $_REQUEST[$name] == -1 ? $this->default : $_REQUEST[$name];
            } else if (!isset ($_REQUEST[$name.'_year'])) {
                return $this->_default;
            } else if ($_REQUEST[$name.'_year'] == 0) {
                return 0;
            } else {
                return  mktime(
                    isset($_REQUEST[$name.'_hours']) ? $_REQUEST[$name.'_hours'] : 1,
                    isset($_REQUEST[$name.'_minutes']) ? $_REQUEST[$name.'_minutes'] : 0,
                    isset($_REQUEST[$name.'_seconds']) ? $_REQUEST[$name.'_seconds'] : 0,
                    isset($_REQUEST[$name.'_month']) ? $_REQUEST[$name.'_month'] : 1,
                    isset($_REQUEST[$name.'_day']) ? $_REQUEST[$name.'_day'] : 1,
                    isset($_REQUEST[$name.'_year']) ? $_REQUEST[$name.'_year']:date('Y')
                );
            }
        case 'string':
        case 'int':
        case 'integer':
        case 'float':
        case 'boolean':
            default:
                return isset($_REQUEST[$this->_name])?$this->update_type($_REQUEST[$this->_name]):$this->_default;
        }
    }

    /**
     * Load default value case of object type
     * @return mixed
     */
    public function get_default() {
        switch ($this->_type) {
            case 'string':
                return '';
            case 'int':
            case 'integer':
            case 'float':
            case 'date':
                return 0;
            case 'boolean':
                return false;
            case 'array':
                return array();
            default:
                return null;
        }
    }

    /**
     * Update value type
     * @param mixed $value
     * @return mixed
     */
    public function update_type($value) {
        switch ($this->_type) {
            case 'string':
                return (string)$value;
            case 'int':
            case 'integer':
                return (int)$value;
            case 'float':
                return preg_replace('/,/', '.', (float)preg_replace('/,/', '.', $value));
            case 'boolean':
                return (bool)$value;
            default:
                return $value;
        }
    }
}
?>
