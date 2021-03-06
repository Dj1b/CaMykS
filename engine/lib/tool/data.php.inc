<?php
/**
 * @brief Tool methods to manage data, vars, etc...
 * @details Engine / Tool Library
 * @file engine/lib/tool/data.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jul 2005
 * @date Modification: Oct 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Encode properties.
 * @param array $properties
 * @param string $separator
 * @param boolean $disableEmpty
 * @return string
 */
function data_encode_properties($properties, $separator='"', $disableEmpty=false) {
    if (!is_array($properties) or count($properties) == 0)
        return '';

    $data = array();
    foreach ($properties as $p_name => $p_value) {
        $data[] = $p_name;
        if ($p_value != '' or $disableEmpty == false)
            $data[] = addSlashes($p_value);
    }
    $data = implode($separator, $data);
    return $data;
}

/**
 * Decode properties.
 * @param string $data
 * @param string $separator
 * @return array
 */
function data_decode_properties($data, $separator='"') {
    $properties = array();
    if (strlen($data) == 0)
        return $properties;
    $t = explode($separator, $data);
    for ($i=0; $i < count($t); $i+=2) {
        $properties[$t[$i]] = (isset($t[$i+1]) ? stripslashes($t[$i+1]) : '');
    }
    return $properties;
}

/*** DEPRECATED METHODS ***/

/**
 * Serialize data.
 * @param mixed $data
 * @return string
 * @deprecated
 */
function data_serialize($data) {
    switch (gettype($data)) {
        case 'boolean':
        case 'entier':
        case 'double':
        case 'float':
        case 'integer':
            return $data;
        case 'NULL':
            return '\'\'';
        case 'array':
            return data_serializeArray($data);
        case 'object':
            return data_serializeObject($data);
        case 'string':
        default:
            return '\''.$data.'\'';
    }
}

/**
 * Serialize object data.
 * @param mixed $data
 * @return string
 * @deprecated
 */
function data_serializeObject($data) {
    /* TO DO */
    return 'object';
}

/**
 * Serialize array data.
 * @param mixed $data
 * @return string
 * @deprecated
 */
function data_serializeArray($data) {
    if (count($data))
        return 'array()';
    $str = 'array(';
    if (count($data)) {
        foreach ($data as $key =>$value) {
            $str .= $key.' => '.data_serialize($value).',';
        }
        $str = substr ($str, 0, strlen($str)-2);
    }
    $str .= ')';
    return $str;
}

/**
 * Unserialize object data.
 * @param mixed $data
 * @return string
 * @deprecated
 */
function data_unserialize($data) {
    return eval ($data);
}
?>
