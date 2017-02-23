/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / JS Lib
 * Creation Date	: Jul 2007
 * Last Modif Date	: Jul 2007
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
  return x - Math.floor( x/y )*y;
}
