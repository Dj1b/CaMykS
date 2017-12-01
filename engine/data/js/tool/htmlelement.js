/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / Javascript Lib
 * Creation Date	: Jun 2006
 * Last Modif Date	: Jun 2006
 *      
 * HTML Javascript library
 */

/* 
 * update css class
 */
function tool_updateObjectCss ( object, css ) {
  if ( document.getElementById(object) )
    document.getElementById (object).className = css;
}


/*
 * get x position of given object
 */
function tool_getObjectPositionX(object) {
  var left = 0;
  if (object){
    /* get recursive position of successive parents */
    while (object.offsetParent){
      left += object.offsetLeft;
      object = object.offsetParent;
    }
  }
  return left;
}

/*
 * get y position of given object
 */
function tool_getObjectPositionY(object) {
  var top = 0;
  if (object){
    /* get recursive position of successive parents */
    while (object.offsetParent){
      top += object.offsetTop;
      object = object.offsetParent;
    }
  }
  return top;
}

/*
 * update left style value
 */
function html_updateLeftStylePosition(object,update) {
  if (object) {
    pos = object.style.left;
    if ( !pos )
      return;
    
    if ( pos.indexOf('px')> 0 || pos.indexOf('em')) 
      pos = parseInt(pos.substring(0, pos.length-2));
    
    pos += update;
    object.style.left = pos + 'px';
  }
}

/*
 * get left style value
 */
function html_getLeftStylePosition(object) {
  if (object) {
    var pos = object.style.left;
    if ( !pos )
      return 'NaN';
    return parseInt(pos.substring(0, pos.length-2));
  }
  return 'NaN';
}
