<?php
/**
 * @brief Database item of Module Library Item
 * @details Engine / Object Library
 * @file engine/lib/object/MLDatabaseItem.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Apr 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MLDatabaseItem class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
class MLDatabaseItem extends ModuleLibraryItem {
    /**
     * @var string $datatype
     * @brief Item data type, can be \b text / \b etext / \b int / \b float / \b date / \b password / \b list.
     */
    public $datatype;

    /**
     * @var string $datadesc
     * @brief Item data description (database type compatible with MySQL).
     */
    public $datadesc;

    /**
     * @var string $datadesc2
     * @brief Secondary information of item data description.
     */
    public $datadesc2;
    
    /**
     * Class constructor.
     * @param string $name
     * @param string $datatype
     * @param string $desc
     * @param mixed $desc2
     * @param mixed $default
     * @return void
     */
    public function __construct($name, $datatype, $desc, $desc2='', $default=null) {
        $this->name = $name;
        $this->datatype = $datatype;
        $this->datadesc = $desc;
        $this->datadesc2 = $desc2;
        $this->default = isset($default) ? $default : $this->get_defaultValue();
    }

    /**
     * Initialise object with default value.
     * @return void
     */
    public function initialise() {
        $this->value = $this->default;
    }

    /**
     * Load object value from header.
     * @param string $prefix
     * @return void
     */
    public function get_fromHeader($prefix='') {
        global $camyks;

        /* set header value name */
        $name = $prefix.$this->name;

        /* load value case of data type */
        switch ($this->datatype) {
            case 'date':
                $this->value = $this->get_dateFromHeader($name);
                break;
            case 'text':
            case 'etext':
                $v = (string)$this->get_valueFromHeader($name);
                $v = $this->parse_PHPTags($v);
                if ($this->datadesc2 > 0)
                    $v = substr($v, 0, $this->datadesc2);
                $this->value = $v;
                break;
            case 'int':
                $this->value = (int)$this->get_valueFromHeader($name);
                break;
            case 'float':
                $this->value = preg_replace('/,/', '.', (float)preg_replace('/,/', '.', $this->get_valueFromHeader($name)));
                break;
            default:
                $this->value = $this->get_valueFromHeader($name);
                break;
        }
    }

    /**
     * Load object value from an array.
     * @return void
     */
    public function get_fromArray($data) {
        global $camyks;

        /* check if value exists in array */
        if (!isset($data[$this->name])) {
            $this->value = $this->default;
            return;
        }

        /* load value case of data type */
        switch ($this->datatype) {
            case 'etext':
                $this->value = $camyks->decode_value($data[$this->name]);
                break;
            case 'text':
                $this->value = stripslashes($data[$this->name]);
                break;
            case 'int':
            case 'date':
                $this->value = (int)$data[$this->name];
                break;
            case 'float':
                $this->value = (float)$data[$this->name];
                break;
            case 'list':
                $this->value = $this->uncompile_listValue($data[$this->name]);
                break;
            default:
                $this->value = $data[$this->name];
            break;
        }
    }

    /**
     * Return database description.
     * @return mixed
     */
    public function get_databaseDescription() {
        return array(
            'name'      => $this->name,
            'type'      => $this->datatype,
            'desc1'     => $this->datadesc,
            'desc2'     => $this->datadesc2,
            'default'   => $this->default,
        );
    }

    /**
     * Return value optimised for database.
     * @return mixed
     */
    public function get_databaseValue($language=null) {
        global $camyks;
        switch ($this->datatype) {
            case 'int':
            case 'date':
                return ''.(int)$this->value;
            case 'float':
                return preg_replace('/,/', '.', (string)$this->value);
            case 'text':
                return '"'.addslashes($this->value).'"';
            case 'etext':
                return '"'.$camyks->encode_value($this->value). '"';
            case 'password':
                return '"'.$this->value.'"';
            case 'list':
                return '"'.$this->compile_listValue($this->value).'"';
        }
    }

    /**
     * Return default value.
     * @return mixed
     */
    public function get_defaultValue() {
        switch ($this->datatype) {
            case 'int':
            case 'float':
                return 0;
            case 'text':
            case 'etext':
            case 'password':
                return '';
            case 'date':
                return time();
            case 'list':
                return array();
        }
    }

    /**
     * Return value as structured array name => value.
     * @return array
     */
    public function get_exportedValue() {
        return array($this->name => $this->value);
    }

    /**
     * Check value case of given type.
     * @param string $type
     * @param mixed $default
     * @return void
     */
    public function check_value($type=null, $default=null) {
        /* check type */
        if (!isset($type))
            $type = $this->datatype;

        /* check default */
        if (!isset($default))
            $default = $this->default;

        /* check value case of data type */
        switch ($type) {
            /* generic type */
            case 'int':
            case 'float':
            case 'text':
            case 'etext':
            case 'date':
                break;
            /* specific type */
            case 'symbolic_name':
                $v = $this->value;
                $v = preg_replace('/([^_a-zA-Z0-9]+)/', '', $v);
                if ($v == '') {
                    $v = $default;
                }
                $this->value = $v;
                break;
        }
    }
}
?>
