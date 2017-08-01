<?php
/*
 * CaMykS Engine
 * Developed by       : camyks.net
 * Author             : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version     : 1.0
 * Object Version     : 1.0
 * Object Type        : Engine / Tool Library
 * Creation Date      : Jul 2017
 * Last Modif Date    : Jul 2017
 *
 * Specific methods related to math
 * /!\ This library is not loaded with CaMykS initialisation
 */

/*
 * Compute least common multiple of 2 numbers
 * @param integer $x
 * @param integer $y
 * @return integer
 */
function math_leastCommonMultiple($x, $y) {
     return ($x * $y) / math_greatestCommonDenominator($x, $y);   
}

/*
 * Compute greatest common denominator of 2 numbers
 * @param integer $x
 * @param integer $y
 * @return integer
 */
function math_greatestCommonDenominator($x, $y) {
    return !$y ? $x : math_greatestCommonDenominator($y, $x % $y);
}

/*
 * Compute least common multiple of an array of numbers
 * @param array $numbers
 * @return integer
 */
function math_leastCommonMultipleArray($numbers=array()) {
    $multiple = $numbers[0];
    foreach ($numbers as $n)
        $multiple = math_leastCommonMultiple($multiple, $n);
    return $multiple;
}

?>