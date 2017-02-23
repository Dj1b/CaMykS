/*
 * CaMykS Engine
 * Developed by			: camyks.net
 * Author	       		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Javascript
 * Creation Date		: Oct 2010
 * Last Modif Date	: Oct 2010
 * 
 * TinyMCEv3 methods
 */
 
/*
 * callback method for page choosing
 * @param string field_name
 * @param mixed field_value
 * @param string type
 * @param Object win
 * @return void
 * @access public
 */
function page_callback( field_name, field_value, type, win ) {
	if (!isPageChooserAvailable)
		return alert("Page Choose Input not found.");
	icb_win = win;
	icb_field = field_name;
  lg = get_currentEditorLanguage();
  pc.open(field_value, lg);
}

/*
 * receive page value
 * @param string url
 * @return void
 * @access private
 */
function page_updatevalue ( url ) {
	if (!isPageChooserAvailable)
		return alert("Page Choose Input not found.");
  icb_win.document.forms[0].elements[icb_field].value = url;
  setTimeout('icb_win.focus();', 500);
}

/*
 * return current content language
 * @return language
 * @access private
 */
function get_currentEditorLanguage() {
	if (!tinymce || !editing_languages || editing_languages.length < 2)
  	return '';
  	
  editor = tinymce.activeEditor;
  	
  if (editor.getElement().getAttribute('language') != null) {
  	/* get language from language attribute */
  	l = editor.getElement().getAttribute('language');
  } else {
  	/* guess language from content id */
  	l = editor.id.split('_');
  	if ( l.length < 2 )
  		return '';
  	l = l[l.length-1];
  }
  
  /* check for unique site language */
  if ( site_languages.length == 1 && site_languages[0] == l)
  	return '';
  
  /* check editing language */
  for (var i in editing_languages)
   	if (editing_languages[i] === l)
     	return l;
  return '';
}