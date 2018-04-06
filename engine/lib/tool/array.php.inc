<?php
/*
 * CaMykS Engine
 * Developed by       : camyks.net
 * Author             : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version     : 1.0
 * Object Version     : 1.0.1
 * Object Type        : Engine / Tool Library
 * Creation Date      : Jan 2010
 * Last Modif Date    : Apr 2018
 *
 * Array related methods
 */

/*
 * drop given value from array
 * @param array $array
 * @param mixed $value
 * @param boolean $keepKeys
 * @return string
 */
function array_dropValue($array=array(), $value=null, $keepKeys=true) {
    /* check array */
    if (!is_array($array))
        return array();
    
    /* check value */
    if ($value == null)
        return $array;
    
    /* get parsed array */
    $parsed = preg_grep("/{$value}/i", $array, PREG_GREP_INVERT);
    
    /* return result */
    if ($keepKeys)
        return $parsed;
    return array_values($parsed);
}

/*
 * merge arrays
 * @param array $array1
 * @param array $array2
 * @return array
 */
function array_recursiveMerge($array1=array(), $array2=array()) {
    /* check arrays */
    if (!is_array($array1) and !is_array($array2))
        return array();
    if (!is_array($array1))
        return $array2;
    if (!is_array($array2))
        return $array1;
    
    /* merge arrays */
    foreach ($array2 as $key => $value) {
        if (!isset($array1[$key]))
            /* add value */
            $array1[$key] = $value;
        elseif (is_array($value) and is_array($array1[$key]))
            /* merge array values */
            $array1[$key] = array_recursiveMerge($array1[$key], $value);
        else
            /* merge other values */
            $array1[$key] = $value;
    }
    
    /* return merged array */
    return $array1;
}

/*
 * check if all elements are numerics or numeric strings
 * @param array $array
 * @return boolean result
 */
function array_checkNumeric($array=array()) {
    return (count($array) === count(array_filter($array, 'is_numeric')));
}

/*
 * check if all elements are integers (strict)
 * @param array $array
 * @return boolean result
 */
function array_checkInteger($array=array()) {
    return (count($array) === count(array_filter($array, 'is_integer')));
}

/*
 * return array with all abs values
 * @param array $array
 * @return array
 */
function array_abs($array=array()) {
    $result = array();
    foreach ($array as $i => $v) {
        if (is_array($v))
            $result[$i] = array_abs($v);
        elseif ($v < 0)
            $result[$i] = $v * -1;
        else
            $result[$i] = $v;
    }
    return $result;
}
?>