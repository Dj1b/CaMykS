/**
 * @brief Client side scripts related to arrays.
 * @details Engine / Javascript tool library
 * @file engine/data/js/tool/array.js
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Mar 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Check if item is in list.
 * @param array list
 * @param mixed item
 * @return boolean
 */
function array_in(list, item) {
  for (var i in list) {
    if (list[i] === item)
      return true;
  }
  return false;
}

/**
 * Drop an item from a list
 * @param array list
 * @param mixed item
 * @return array
 */
function array_dropItem(list, item) {
  l = new Array();
  for (var i in list) {
    if (list[i] !== item ) {
      l[l.length] = list[i];
    }
  }
  return l;
}

/**
 * Find an item position in a list
 * @param array list
 * @param mixed item
 * @return integer
 */
function array_findItem(list, item) {
  for (var i in list)
    if (list[i] === item)
      return i;
  return false;
}
