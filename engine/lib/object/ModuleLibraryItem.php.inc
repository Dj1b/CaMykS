<?php
/**
 * @brief Module Library Item
 * @details Engine / Object Library
 * @file engine/lib/object/ModuleLibraryItem.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Mar 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo Try to set up get_dateFromHeader and parse_PHPTags methods as protected.
 */

/**
 * ModuleLibraryItem class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
abstract class ModuleLibraryItem {
    /**
     * Load value from array.
     * @param array $data
     * @return void
     */
    public function get_fromArray($data) {
        $this->value = isset($data[$this->name]) ? $data[$this->name] : $this->default;
    }

    /**
     * Load value from header.
     * @param string $name
     * @return string
     */
    public function get_valueFromHeader($name) {
        return isset($_REQUEST[$name]) ? $_REQUEST[$name] : $this->default;
    }

    /**
     * Load date value from header.
     * @param string $name
     * @return integer
     */
    public function get_dateFromHeader($name) {
        if (isset($_REQUEST[$name])) {
            return $_REQUEST[$name] == -1 ? $this->default : (int)$_REQUEST[$name];
        } else if (!isset($_REQUEST[$name.'_year'])) {
            return $this->default;
        } else if ($_REQUEST[$name.'_year'] == 0) {
            return 0;
        } else {
            return mktime(isset($_REQUEST[$name.'_hours']) ? (int)$_REQUEST[$name.'_hours'] : 1,
                isset($_REQUEST[$name.'_minutes']) ? (int)$_REQUEST[$name.'_minutes'] : 0,
                isset($_REQUEST[$name.'_seconds']) ? (int)$_REQUEST[$name.'_seconds'] : 0,
                isset($_REQUEST[$name.'_month']) ? (int)$_REQUEST[$name.'_month'] : 1,
                isset($_REQUEST[$name.'_day']) ? (int)$_REQUEST[$name.'_day'] : 1,
                isset($_REQUEST[$name.'_year']) ? (int)$_REQUEST[$name.'_year']:date('Y')
            );
        }
    }

    /**
     * Remove PHP tags from value
     * @param string $value
     * @return string
     */
    public function parse_PHPTags ($value){
        $tags = array();
        $tags[] = '/<\?[^\?>]*\?>/';
        $tags[] = '/<\?/';
        $tags[] = '/<qss[^>]*>/';
        $tags[] = '/<qss/';
        $tags[] = '/<script[^>]*>[^<]<\/script>/';
        $tags[] = '/<script/';
        return preg_replace ($tags, '', $value);
    }

    /* list data type specific methods */

    /**
     * Compile list value
     * @param array $value
     * @return string
     */
    protected function compile_listValue($value) {
        /* check value */
        if (!is_array($value))
            return '';

        /* define available list separators */
        $listSeparators = array(':', ';', ',', '/', '#', '$');

        $v = implode($value);

        /* check separator to use */
        $sep = '';
        foreach ($listSeparators as $i) {
            if (strpos($v, $i) === false) {
                $sep = $i;
                break;
            }
        }

        if ($sep == '')
            return '';

        /* build result */
        return $sep.implode($sep, $value).$sep;
    }

    /**
     * Uncompile list value.
     * @param string $value
     * @return array
     */
    protected function uncompile_listValue($value) {
        /* Check if it is already uncompiled */
        if (is_array($value))
            return $value;

        /* check value */
        if (!is_string($value))
            return array();
        $value = trim($value);
        if ($value == '')
            return array();

        /* detect separator */
        $sep = substr($value, 0, 1);

        /* check separator */
        if ($sep != substr($value, -1))
            return array();

        /* remove first & last separator */
        $v = substr($value, 1, -1);

        /* Check empty list */
        if (trim($v) == '')
            return array();

        /* return uncompiled value */
        return explode($sep,  $v);
    }
}
?>