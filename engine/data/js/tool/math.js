/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / JS Lib
 * Creation Date	: Jul 2007
 * Last Modif Date	: Jul 2017
 *
 * Math Javascript library
*/

/*
 * Math Modulo function
 * @access public
 * @param int x
 * @param int y
 * return int;
 */
function math_mod ( x, y ) {
    return x % y;
}

/*
 * Compute least common multiple of 2 numbers
 * @param integer x
 * @param integer y
 * @return int
 */
function math_leastCommonMultiple(x, y) {
     return (x * y) / math_greatestCommonDenominator(x, y);   
}

/*
 * Compute greatest common denominator of 2 numbers
 * @param integer x
 * @param integer y
 * @return int
 */
function math_greatestCommonDenominator(x, y) {
    return !y ? x : math_greatestCommonDenominator(y, x % y);
}

/*
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