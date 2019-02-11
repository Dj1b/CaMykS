/**
 * @brief GenericSitemapGenerator module configuration editor scripts
 * @details Plugin / Input Scripts
 * @file plugin/input/GenericSitemapGenerator/js/ConfigViewer.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Feb 2019
 * @date Modification: Feb 2019
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

var ConfigEditor = {
    name: 'ConfigEditor',
    params: {},
    locales: {},
    loaded: false,

    /**
     * Add parameter
     * @param string name
     * @param mixed value
     * @return void
     */
    set_param: function(param, value, subvalue) {
        if (subvalue != undefined && this.params[param])
            this.params[param][value] = subvalue;
        else
            this.params[param] = value;
    },

    /**
     * Return param value from name
     * @param mixed param
     * @return mixed
     */
    get_param: function(param, value) {
        if (value != undefined && (this.params[param][value] || this.params[param][value] === 0))
            return this.params[param][value];
        if (this.params[param] || this.params[param] === 0)
            return this.params[param]
        return false;
    },

    /**
     * Set locale value
     * @param string name
     * @param string value
     * @return void
     */
    set_locale: function(name, value) {
        this.locales[name.toLowerCase()] = value;
    },

    /**
     * Return locale value
     * @param string name
     * @return void
     */
    get_locale: function(name) {
        if (this.locales[name.toLowerCase()])
            return this.locales[name.toLowerCase()];
        return name;
    },

    /**
     * Initialise object
     * @return void
     */
    initialise: function() {

        /* Set up form */
        this.set_param('form', document.getElementById(this.get_param('form')));

        /* finalise initialisation */
        this.loaded = true;
    },

    /* Action methods */

    /**
     * Check update mode status.
     * @return void
     */
    check_updateModeStatus: function() {
        if (!this.loaded)
            return;

        if (this.get_param('form').update_mode.value == 1)
            document.getElementById('updateMode1').style.display = 'block';
        else
            document.getElementById('updateMode1').style.display = 'none';
    },
}
