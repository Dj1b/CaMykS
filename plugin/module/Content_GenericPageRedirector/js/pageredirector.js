/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author	      	: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0b
 * Object Version	: 1.0
 * Object Type		: Plugin / Module Javascripts
 * Creation Date	: Sep 2009
 * Last Modif Date	: Apr 2010
 *
 * Content_GenericPageRedirector module scripts
*/

/*
 * open page chooser with actual value
 * @return void
 * @access public
 */
function open_pageChooser() {
    v = document.edit_form.url.value;
    pc2.openPageChooser(v);
}

/*
 * update selected page value 
 * @return void
 * @access public
 */
function update_selectedPage(page) {
    document.edit_form.url.value = page;
}

/*
 * update form item case of method value
 * @return void
 * @access public
 */
function update_formFromMethod() {
  m = document.edit_form.method.options[document.edit_form.method.options.selectedIndex].value;
  if( m == 3)
    document.getElementById('delay_block').style.display = 'none';
  else
    document.getElementById('delay_block').style.display = 'block';
}
