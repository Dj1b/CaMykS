<?php
/**
 * @brief Temporary item of Module Library Item.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: May 2007
 * @date Modification: Mar 2023
 * @copyright 2007 - 2023 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MLTemporaryItem class.
 */
final class MLTemporaryItem extends ModuleLibraryItem {
    /**
     * @var string $type
     * @brief Item type.
     */
    public $type;

    /**
     * Class constructor.
     * @param string $name
     * @param string $type
     * @param mixed $default
     * @return void
     */
    public function __construct($name, $type='', $default='') {
        $this->name = $name;
        $this->type = $type;
        $this->datatype = $type;
        $this->default = $default;
    }

    /**
     * Initialise object with default value.
     * @return void
     */
    public function initialise() {
        $this->value = $this->default;
    }

    /**
     * Load object.
     * @return void
     */
    public function get() {
        $this->initialise();
    }

    /**
     * Load object value from header.
     * @param string $prefix
     * @return void
     */
    public function get_fromHeader($prefix = '') {
        $name = $prefix.$this->name;

        switch ($this->type) {
            case 'date':
                $this->value = $this->get_dateFromHeader($name);
                break;
            case 'text':
            case 'etext':
                $v = (string)$this->get_valueFromHeader($name);
                $this->value = $this->parse_PHPTags($v);
                break;
            case 'int':
                $this->value = (int)$this->get_valueFromHeader($name);
                break;
            case 'float':
                $this->value = $this->get_valueFromHeader($name);
                $this->value = preg_replace('/,/', '.', (float)preg_replace('/,/', '.', $this->value));
                break;
            default:
                $this->value = $this->get_valueFromHeader($name);
                break;
        }
    }

    /**
     * Return values as structured array $name => $value
     * @return array
     */
    public function get_exportedValue() {
        return array($this->name => $this->value);
    }

    /**
     * Load object value from given array.
     * @param array $data
     * @return void
     */
    public function get_fromArray($data) {
        $this->value = isset ($data[$this->name]) ? $data[$this->name] : $this->default;
    }
}
?>
