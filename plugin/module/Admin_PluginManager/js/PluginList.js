/**
 * @brief Admin_PluginManager module plugin list scripts
 * @details Plugin / Module Scripts
 * @author CaMykS Team
 * @version 1.0.1
 * @date Creation: Oct 2017
 * @date Modification: Nov 2020
 * @copyright 2017 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

function PluginList(name) {
    this.name = name;
    this.params = {};
    this.locales = {};
    this.loaded = false;

    /* pre-define values */
    this.params['actionURLs'] = new Array();

    /*
     * add parameter
     * @param string name
     * @param mixed value
     * @return void
     */
    this.set_param = function(param, value, subvalue) {
        if ( subvalue != undefined && this.params[param] )
            this.params[param][value] = subvalue;
        else
            this.params[param] = value;
    };

    /*
     * return param value from name
     * @param mixed param
     * @return mixed
     */
    this.get_param = function(param, value) {
        if (value != undefined)
            if (this.params[param][value])
                return this.params[param][value];
        if (this.params[param])
            return this.params[param];
        return false;
    };

    /*
     * set locale value
     * @param string name
     * @param string value
     * @return void
     */
    this.set_locale = function(name, value) {
        this.locales[name.toLowerCase()] = value;
    };

    /*
     * get locale value
     * @param string name
     * @return void
     */
    this.get_locale = function(name) {
        if (this.locales[name.toLowerCase()])
            return this.locales[name.toLowerCase()];
        return name;
    };

    /*
     * initialise object
     * @return void
     */
    this.initialise = function() {
        /* finalise initialisation */
        this.loaded = true;
    };

    /*
     * attach and open action menu to selected plugin
     * @param integer plugin
     * @return void
     */
    this.show_menu = function(type, plugin) {
        this.set_param('selectedPlugin', plugin);
        globalCMenu.updateParent(type+'ActionMenu', 'button'+plugin );
        globalCMenu.select(type+'ActionMenu');
    };

    /*
     * execute selected action to selected plugin
     * @return void
     */
    this.execute_action = function(action) {
        action = this.get_param('actionURLs', action).replace('__PNAME__', this.get_param('selectedPlugin'));
        document.location.href = action;
    };
}
