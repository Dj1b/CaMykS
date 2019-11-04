<?php
/**
 * @brief Array related methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/array.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.2
 * @date Creation: Jan 2010
 * @date Modification: Oct 2019
 * @copyright 2010 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Drop given value from array.
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

/**
 * Merge arrays.
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

/**
 * Check if all elements are numerics or numeric strings.
 * @param array $array
 * @return boolean result
 */
function array_checkNumeric($array=array()) {
    return (count($array) === count(array_filter($array, 'is_numeric')));
}

/**
 * Check if all elements are integers (strict).
 * @param array $array
 * @return boolean result
 */
function array_checkInteger($array=array()) {
    return (count($array) === count(array_filter($array, 'is_integer')));
}

/**
 * Check if all elements are the same and given type.
 * @param array $array
 * @param string $type
 * @return boolean result
 */
function array_checkDataType($array=array(), $type='') {
    if (!function_exists('is_'.$type))
        return false;
    return (count($array) === count(array_filter($array, 'is_'.$type)));
}

/**
 * Return array with all abs values.
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

/**
 * Apply the same value on every key then return it.
 * @param array $array
 * @param mixed $value
 * @return array
 */
function array_applySameValue($array, $value=null) {
    return array_fill_keys(array_keys($array), $value);
}

/**
 * Check if array is associative.
 * @param array $array
 * @return boolean result
 */
function array_isAssociative($array) {
    /* Quick tests */
    if (count($array) == 0)
        return true;

    /* Harder test */
    return array_keys($array) !== range(0, count($array) - 1);
}

/**
 * Check if array is sequential.
 * @param array $array
 * @return boolean result
 */
function array_isSequential($array) {
    /* Quick tests */
    if (count($array) == 0)
        return true;

    /* Harder test */
    return array_keys($array) === range(0, count($array) - 1);
}
?>
