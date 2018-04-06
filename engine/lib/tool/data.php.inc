<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0.1
 * Object Type      : Engine / Tool Library
 * Creation Date    : Jul 2005
 * Last Modif Date  : Apr 2018
 *
 * Tool methods to manage data, vars, etc...
*/

/*
 * encode properties
 * @param array $properties
 * @param string $separator
 * @return string
 */
function data_encode_properties($properties, $separator='"') {
    if (!is_array($properties) or count($properties) == 0) 
        return '';
    
    $data = array();
    foreach ($properties as $p_name => $p_value) {
        $data[] = $p_name;
        $data[] = addSlashes($p_value); 
    }
    $data = implode($separator, $data);
    return $data;
}

/*
 * decode properties
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

/*
 * serialize data
 * @param mixed $data
 * @return string
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

// serialize given object data
function data_serializeObject($data) {
    /* TO DO */
    return 'object';
}

// serialize given array data
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

// unserialize given data
function data_unserialize($data) {
    return eval ($data);
}
?>