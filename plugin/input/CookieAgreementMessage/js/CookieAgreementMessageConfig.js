/**
 * @brief CookieAgreementMessage Input configuration scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/CookieAgreementMessage/js/CookieAgreementMessageConfig.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Feb 2018
 * @date Modification: Apr 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
var CookieAgreementMessageConfig = {
    params: {},

    /*
     * add parameter
     * @param string name
     * @param mixed value
     * @return void
     * @access public
     */
    set_param: function(param, value, subvalue) {
        if ( subvalue != undefined && this.params[param] )
            this.params[param][value] = subvalue;
        else
            this.params[param] = value;
    },

    /*
     * return param value from name
     * @param mixed param
     * @return mixed
     * @access public
     */
    get_param: function(param, value) {
        if (value != undefined && (this.params[param][value] || this.params[param][value] === 0))
                return this.params[param][value];
        if (value == undefined && this.params[param] || this.params[param] === 0)
            return this.params[param]
        return false;
    },

    /*
     * initialise object
     * @return void
     * @access public
     */
    initialise: function() {
        this.set_param('form', document.getElementById(this.get_param('form')));
    },

    /*
     * handle onclick event on aboutCookie radios
     * @param string value
     * @return void
     * @access public
     */
    onAboutCookieChange: function(value) {
        console.log ('value:' + value);
        if (value == '')
            document.getElementById('aboutCookiePersValue').disabled = 'disabled';
        else
            document.getElementById('aboutCookiePersValue').disabled = false;
    },
}
