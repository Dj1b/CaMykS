/**
 * @brief Client side scripts related maths.
 * @details Engine / Javascript tool library
 * @file engine/data/js/tool/math.js
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jul 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Math Modulo method
 * @param int x
 * @param int y
 * @return int;
 */
function math_mod (x, y) {
    return x % y;
}

/**
 * Compute least common multiple of 2 numbers
 * @param integer x
 * @param integer y
 * @return int
 */
function math_leastCommonMultiple(x, y) {
     return (x * y) / math_greatestCommonDenominator(x, y);   
}

/**
 * Compute greatest common denominator of 2 numbers
 * @param integer x
 * @param integer y
 * @return int
 */
function math_greatestCommonDenominator(x, y) {
    return !y ? x : math_greatestCommonDenominator(y, x % y);
}

/**
 * Compute least common multiple of an array of numbers
 * @param array numbers
 * @return int
 */
function math_leastCommonMultipleArray(numbers) {
    var multiple = numbers[0];
    numbers.forEach(function(n) {
        multiple = math_leastCommonMultiple(multiple, n);
    });
    return multiple;
}