/**
 * @brief CookieAgreementMessage Input scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/CookieAgreementMessage/js/CookieAgreementMessage.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: May 2017
 * @date Modification: Apr 2018
 * @copyright 2017 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
var CookieAgreementMessage = {
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

    },

    /*
     * go to given anchor
     * @param string anchor
     * @access public
     */
    accept_cookies: function() {
        cookie_save('cookieAccepted', 1, this.get_param('cookieTTL'));
        document.getElementById('cookieAgreementMessage').style.display = 'none';
    },
}
