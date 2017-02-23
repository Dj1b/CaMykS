/*
 * CaMykS Engine
 * Developed by			: camyks.net
 * Author						: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version  	: 1.0a
 * Object Version		: 1.0
 * Object Type      : Plugin / Module Javascripts
 * Creation Date		: May 2010
 * Last Modif Date	: May 2010
 *
 * Admin_GenericGlossaryManager scripts
 */

/*                                                                                                                               
 * open page chooser for selected button                                                                                         
 * @return void                                                                                                                  
 * @access public                                                                                                                
 */
function glossarymanager_selectButtonLink(button) {
    selectedButton = button;
    eval('v = document.edit_definition.link.value;');
    pc2.openPageChooser(v);
}
 
 
/*                                                                                                                               
 * update selected button link from page chooser                                                                                 
 * @return void                                                                                                                  
 * @access public                                                                                                                
 */
function glossarymanager_updateButtonLink(url) {
    eval('document.edit_definition.link.value = url;');
}

