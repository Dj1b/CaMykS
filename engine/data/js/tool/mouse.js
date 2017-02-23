/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / JS Lib
 * Creation Date	: Dec 2007
 * Last Modif Date	: Dec 2007
 *
 * Mouse javascript methods
*/

/*
 * get mouse position
 * @access public
 * @param string event
 * @return array
 */
function mouse_getPosition( event ) {  
  if ( navigator.userAgent.toLowerCase().indexOf('msie')==-1 ) {
    /* Real browser */
    return {'x': event.clientX + window.scrollX,
	      'y': event.clientY + window.scrollY };
  } else {
    /* IE Hack */
    return {'x': window.event.clientX + document.documentElement.scrollLeft + document.body.scrollLeft,
	      'y': window.event.clientY + document.documentElement.scrollTop + document.body.scrollTop };
  }   
  event = null;
}
