<?php
/**
 * @brief Database localised item of Module Library Item
 * @details Engine / Object Library
 * @file engine/lib/object/MLDatabaseLocalizedItem.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Apr 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MLDatabaseLocalizedItem class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class MLDatabaseLocalizedItem extends MLDatabaseItem {
    
    /**
     * @var array $value
     * @brief Overwrite MLDatabaseItem value, is now an array of localised values.
     */
    public $value = array();

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
        parent::__construct($name, $datatype, $desc, $desc2, $default);
    }
  
    /**
     * Initialise object with default value.
     * @return void
     */
    public function initialise() {
        global $camyks;
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $this->value[$l] = $this->default;
        }
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
    
        /* load value */
        switch ($this->datatype) {
            case 'date':
                foreach ($camyks->get_confValue('editing_languages') as $l) {
                    $this->value[$l] = $this->get_dateFromHeader($name.'_'.$l);
                }
                break;
            case 'text':
            case 'etext':
                foreach ($camyks->get_confValue('editing_languages') as $l) {
                    $v = (string)$this->get_valueFromHeader($name.'_'.$l);
                    $v = $this->parse_PHPTags($v);
                    if ($this->datadesc2 > 0)
                        $v = substr($v, 0, $this->datadesc2);
                    $this->value[$l] = $v;
                }
                break;
            case 'int':
                foreach ($camyks->get_confValue('editing_languages') as $l) {
                    $this->value[$l] = (int)$this->get_valueFromHeader($name.'_'.$l);
                }
                break;
            case 'float':
                foreach ($camyks->get_confValue('editing_languages') as $l) {
                    $this->value[$l] = $this->get_valueFromHeader($name.'_'.$l);
                    $this->value[$l] = preg_replace('/,/', '.', (float)preg_replace('/,/', '.', $this->value[$l]));
                }
                break;
            default:
                foreach ($camyks->get_confValue('editing_languages') as $l) {
                    $this->value[$l] = $this->get_valueFromHeader($name.'_'.$l);
                }
                break;
        }
    }
  
    /**
     * Load object values from array.
     * @param array $data
     * @return void
     */
    public function get_fromArray($data=array()) {
        global $camyks;
    
        /* check language */
        if (isset ($data['language']))
            $l = $data['language'];
        else
            $l = $camyks->current_language;
      
        /* check if value exists in array */
        if (isset($data[$this->name.'_'.$l]))
            $value = $data[$this->name.'_'.$l];
        elseif (isset($data[$this->name]))
            $value = $data[$this->name];
        else {
            $value = $this->default;
            return;
        }
      
        /* set value */
        switch ($this->datatype) {
            case 'etext':
                $this->value[$l] = $camyks->decode_value($value);
                break;
            case 'text':
                $this->value[$l] = stripslashes($value);
                break;
            case 'int':
            case 'date':
                $this->value[$l] = (int)$value;
                break;
            case 'list':
                $this->value[$l] = $this->uncompile_listValue($value);
                break;
            default:
                $this->value[$l] = $value;
                break;
        }
    }

    /**
     * Return value optimised for database.
     * @param string $language
     * @return void
     */
    public function get_databaseValue($language=null) {
        global $camyks;
    
        /* check if value exists in given language */
        if (!isset($this->value[$language]))
            return $this->default;
    
        /* return value case of type */
        switch ($this->datatype) {
            case 'int':
            case 'date':
                return ''.$this->value[$language];
            case 'float':
                return preg_replace('/,/', '.', (string)$this->value[$language]);
            case 'text':
                return '"'.addslashes($this->value[$language]).'"';
            case 'etext':
                return '"'.$camyks->encode_value($this->value[$language]).'"';
            case 'list':
                return '"'.$this->compile_listValue($this->value[$language]).'"';
        }
    }

    /**
     * Return localised values as structured array name => value.
     * @return array
     */
    public function get_exportedValue() {
        global $camyks;
        $v = array();
        if (count($this->value) == 1) {
            foreach($this->value as $l => $value) {
                $v[$this->name.'_'.$l] = $value;
                $v[$this->name] = $value;
            } 
        } else { 
            foreach($this->value as $l => $value) {
                $v[$this->name.'_'.$l] = $value;
            }
        }
        return $v;
    }
}
?>