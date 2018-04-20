/**
 * @brief ColorPicker Input popup client side scripts.
 * @details Plugin / Input Javascript
 * @file plugin/input/ColorPicker/js/colorpicker_popup.js
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Mar 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

function colorpicker_cancel() {
    window.close();
}

function colorpicker_valid() {
    parentWindow = opener.document;
    parentWindow.getElementById('colorpicker_obj'+inputname).style.backgroundColor="#"+inputcolor;
    parentWindow.getElementById('colorpicker_txt'+inputname).innerHTML="#"+inputcolor;
    parentWindow.getElementById('colorpicker_input'+inputname).value=inputcolor;
    window.close();
    opener.focus();
}

function colorpicker_select(obj, color) {
    c = document.getElementById('colorpicker_'+obj+'_'+color);
    o = document.getElementById('colorpicker_'+obj+'_newobj');
    t = document.getElementById('colorpicker_'+obj+'_newtxt');
    c.style.border="solid 1px black";
    o.style.backgroundColor="#"+color;
    t.innerHTML="#"+color; 

}

function colorpicker_unselect(obj, color) {
    c = document.getElementById('colorpicker_'+obj+'_'+color);
    o = document.getElementById('colorpicker_'+obj+'_newobj');
    t = document.getElementById('colorpicker_'+obj+'_newtxt');
    c.style.border="solid 1px white";
    o.style.backgroundColor="#"+inputcolor;
    t.innerHTML="#"+inputcolor; 
}

function colorpicker_update (obj, color) {
    c = document.getElementById('colorpicker_'+obj+'_'+color);
    o = document.getElementById('colorpicker_'+obj+'_newobj');
    t = document.getElementById('colorpicker_'+obj+'_newtxt');
    /**/
    inputcolor = color;
    o.style.backgroundColor="#"+inputcolor;
    t.innerHTML="#"+inputcolor; 
}
