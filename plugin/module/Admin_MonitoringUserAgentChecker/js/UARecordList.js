/**
 * @brief Admin_MonitoringUserAgentChecker module record list scripts
 * @details Plugin / Module Scripts
 * @file plugin/module/Admin_MonitoringUserAgentChecker/js/UARecordList.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Nov 2018
 * @date Modification: Nov 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

var UARecordList = {
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
        /* set form */
        this.set_param('form', document.getElementById(this.get_param('form')));

        /* finalise initialisation */
        this.loaded = true;
    },

    /* Action methods */

    /**
     * check selected 404 Fallback value
     * @return void
     */
    mark_recordsAsVerified: function() {
        if (!this.loaded)
            return false;

        if (!confirm(this.get_locale('confirm_message')))
            return;

        ids = recordList.get_checkedBoxes('selection');
        this.get_param('form').mode.value = 'mark_recordsAsVerified';
        this.get_param('form').ids.value = ids.join(',');
        this.get_param('form').submit();
    },
}
