/**
 * @brief Admin_GenericEmailingManager Module client side script to edit configuration
 * @details Plugin, Module Javascripts
 * @file plugin/module/Admin_GenericEmailingManager/js/configuration.js
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
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
    if (document.getElementById('edit_config'))
        form = document.getElementById('edit_config')
    else if (document.getElementById('edit_pluginConfiguration'))
        form = document.getElementById('edit_pluginConfiguration')
    else
        return;
    v = form[object].value;
    pc.openPageChooser(v);
}

/*
 * update selected page value
 * @return void
 * @access public
 */
function update_selectedPage(page) {
    if (document.getElementById('edit_config'))
        form = document.getElementById('edit_config')
    else if (document.getElementById('edit_pluginConfiguration'))
        form = document.getElementById('edit_pluginConfiguration')
    else
        return;

    if (so != null) {
        form[so].value = page;
        so = null;
    }
}
