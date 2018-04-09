<?php
/**
 * @brief Math specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/math.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2017
 * @date Modification: Apr 2018
 * @copyright 2017 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Compute least common multiple of 2 numbers.
 * @param integer $x
 * @param integer $y
 * @return integer
 */
function math_leastCommonMultiple($x, $y) {
     return ($x * $y) / math_greatestCommonDenominator($x, $y);
}

/**
 * Compute greatest common denominator of 2 numbers.
 * @param integer $x
 * @param integer $y
 * @return integer
 */
function math_greatestCommonDenominator($x, $y) {
    return !$y ? $x : math_greatestCommonDenominator($y, $x % $y);
}

/**
 * Compute least common multiple of an array of numbers.
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