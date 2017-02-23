/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Javascripts
 * Creation Date    : Jun 2010
 * Last Modif Date  : Jun 2010
 *
 * Content_GooglePoIMapViewer scripts
 */

/*
 * check all authors checkbox value
 * @return void
 * @access private
 */
function poimapviewer_checkAll() {
  form = eval('document.'+formName);
  i = 0;
  if ( form.categoryall.checked == true ) {
    while ( eval('form.category'+i) ) {
      category = eval('form.category'+i);
      category.checked = true;
      category.disabled = true;
      i++;
    }
  } else {
    while ( eval('form.category'+i) ) {
      category = eval('form.category'+i);
      category.disabled = false;
      i++;
    }
  }
}
