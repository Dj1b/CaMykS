/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / JS Lib
 * Creation Date	: Mar 2007
 * Last Modif Date	: Mar 2007
 *
 * Admin engine javascript methods
*/

function array_in ( list, item ) {
  for (var i in list) {
    if (list[i] === item)
      return true;
  }
  return false;
}

function array_dropItem ( list, item ) {
  l = new Array();
  for (var i in list) {
    if (list[i] !== item ) {
      l[l.length] = list[i];
    }
  }
  return l;
}

function array_findItem( list, item ) {
  for (var i in list)
    if (list[i] === item)
      return i;
  return false;
}
