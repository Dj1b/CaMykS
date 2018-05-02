/**
 * @brief Client side scripts related to mouse.
 * @details Engine / Javascript tool library
 * @file engine/data/js/tool/mouse.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Dec 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * Return mouse position.
 * @param Object event
 * @return array
 */
function mouse_getPosition(event) {  
  if (navigator.userAgent.toLowerCase().indexOf('msie')==-1) {
    /* Real browser */
    return {
        'x': event.clientX + window.scrollX,
        'y': event.clientY + window.scrollY
    };
  } else {
    /* IE Hack */
    return {
        'x': window.event.clientX + document.documentElement.scrollLeft + document.body.scrollLeft,
        'y': window.event.clientY + document.documentElement.scrollTop + document.body.scrollTop
    };
  }   
  event = null;
}
