/**
 * @brief Client side scripts related to html elements.
 * @details Engine / Javascript tool library
 * @file engine/data/js/tool/htmlelements.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Jun 2006
 * @date Modification: Apr 2018
 * @copyright 2006 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Update CSS class.
 * @param string object
 * @param string css
 * @return void
 */
function tool_updateObjectCss(object, css) {
    if (document.getElementById(object))
        document.getElementById (object).className = css;
}


/**
 * Return x position of given object.
 * @param Object object
 * @return integer
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

/**
 * Return y position of given object.
 * @param Object object
 * @return integer
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

/**
 * Update left style value.
 * @param Object object
 * @param integer update
 * @return void
 */
function html_updateLeftStylePosition(object,update) {
    if (object) {
        pos = object.style.left;
        if (!pos)
            return;
        
        if (pos.indexOf('px')> 0 || pos.indexOf('em')) 
            pos = parseInt(pos.substring(0, pos.length-2));
        
        pos += update;
        object.style.left = pos + 'px';
    }
}

/**
 * Return left style value
 * @param Object object
 * @return integer
 */
function html_getLeftStylePosition(object) {
    if (object) {
        var pos = object.style.left;
        if (!pos)
            return 'NaN';
        return parseInt(pos.substring(0, pos.length-2));
    }
    return 'NaN';
}
