/**
 * @brief Admin_GenericEmailingManager Module client side script to edit configuration
 * @details Plugin, Module Javascripts
 * @file plugin/module/Admin_GenericEmailingManager/js/configuration.js
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2013
 * @date Modification: Dec 2018
 * @copyright 2013 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
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
