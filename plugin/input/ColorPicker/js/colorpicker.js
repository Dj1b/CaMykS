/**
 * @brief ColorPicker Input client side scripts.
 * @details Plugin / Input Javascript
 * @file plugin/input/ColorPicker/js/colorpicker.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Mar 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

function colorpicker_open(name, color, config) {
  /* create input popup link */
  url = 'request.php?input=ColorPicker';
  /* add color & name */
  url += '&cp_color='+color+'&cp_name='+name;
  /* add config */
  if (config != '') {
    url += '&cp_config='+config;
  }
  title = 'ColorPicker';
  settings = 'width=360,height=210,scrollbars=no,resize=no,toolbar=no,menubar=no,personalbar=no';
  
  newWindow=window.open(url,title,settings);
  if(newWindow) {
    newWindow.focus();
  }
}

function colorpicker_show(objectname, iname, color) {
  adminengine_modalPopupOpen('colorpicker_'+objectname+'_modalwindow');
  inputname = iname;
  inputcolor = color;
  document.getElementById('colorpicker_'+objectname+'_oldtxt').innerHTML = '#'+color;
  document.getElementById('colorpicker_'+objectname+'_oldobj').style.background = '#'+color;
  document.getElementById('colorpicker_'+objectname+'_newtxt').innerHTML = '#'+color;
  document.getElementById('colorpicker_'+objectname+'_newobj').style.background = '#'+color;
}

function colorpicker_hide(objectname) {
  adminengine_modalPopupClose('colorpicker_'+objectname+'_modalwindow');
}

function colorpicker_save(objectname){
  adminengine_modalPopupClose('colorpicker_'+objectname+'_modalwindow');
  document.getElementById('colorpicker_obj'+inputname).style.backgroundColor="#"+inputcolor;
  document.getElementById('colorpicker_txt'+inputname).innerHTML="#"+inputcolor;
  document.getElementById('colorpicker_input'+inputname).value=inputcolor;
}
