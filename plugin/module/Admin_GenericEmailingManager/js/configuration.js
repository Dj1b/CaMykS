/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Javascripts
 * Create Date		: Jan 2013
 * Last Modif Date	: Jan 2013
 *
 * Admin_GenericEmailingManager module scripts
*/

var so = null;

/*
 * open page chooser with actual value
 * @return void
 * @access public
 */
function open_pageChooser(object) {
    so = object;
    v = eval('document.edit_config.'+object+'.value');
    pc.openPageChooser(v);
}

/*
 * update selected page value 
 * @return void
 * @access public
 */
function update_selectedPage(page) {
    if ( so != null) {
        eval('document.edit_config.'+so+'.value = page');
        so = null;
    }
}