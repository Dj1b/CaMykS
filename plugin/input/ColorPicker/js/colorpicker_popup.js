/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Javascript Library
 * Creation Date	: May 2007
 * Last Modif Date	: May 2007
 * 
 * ColorPicker Javascript
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

function colorpicker_select( obj, color ) {
    c = document.getElementById('colorpicker_'+obj+'_'+color);
    o = document.getElementById('colorpicker_'+obj+'_newobj');
    t = document.getElementById('colorpicker_'+obj+'_newtxt');
    c.style.border="solid 1px black";
    o.style.backgroundColor="#"+color;
    t.innerHTML="#"+color; 

}

function colorpicker_unselect( obj, color ) {
    c = document.getElementById('colorpicker_'+obj+'_'+color);
    o = document.getElementById('colorpicker_'+obj+'_newobj');
    t = document.getElementById('colorpicker_'+obj+'_newtxt');
    c.style.border="solid 1px white";
    o.style.backgroundColor="#"+inputcolor;
    t.innerHTML="#"+inputcolor; 
}

function colorpicker_update ( obj, color ) {
    c = document.getElementById('colorpicker_'+obj+'_'+color);
    o = document.getElementById('colorpicker_'+obj+'_newobj');
    t = document.getElementById('colorpicker_'+obj+'_newtxt');
    /**/
    inputcolor = color;
    o.style.backgroundColor="#"+inputcolor;
    t.innerHTML="#"+inputcolor; 
}
