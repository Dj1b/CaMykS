/**
 * @brief CookieAgreementMessage Input scripts
 * @details Plugin / Input Javascripts
 * @author CaMykS Team
 * @version 1.1.0.1
 * @date Creation: May 2017
 * @date Modification: Jun 2021
 * @copyright 2017 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
var CookieAgreementMessage = {
    params: {},
    locales: {},
    services: {},

    /**
     * add parameter
     * @param string name
     * @param mixed value
     * @return void
     */
    set_param: function(param, value, subvalue) {
        if ( subvalue != undefined && this.params[param] )
            this.params[param][value] = subvalue;
        else
            this.params[param] = value;
    },

    /**
     * return param value from name
     * @param mixed param
     * @return mixed
     */
    get_param: function(param, value) {
        if (value != undefined && (this.params[param][value] || this.params[param][value] === 0))
                return this.params[param][value];
        if (value == undefined && this.params[param] || this.params[param] === 0)
            return this.params[param]
        return false;
    },

    /**
     * set locale value
     * @param string name
     * @param string value
     * @return void
     */
    set_locale: function(name, value) {
        this.locales[name.toLowerCase()] = value;
    },

    /**
     * get locale value
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

    },

    /**
     * Expend panel.
     * @return void
     */
    expand_panel: function() {
        document.getElementById('CookieAgreementMessage').classList.remove('minimised');
    },

    /**
     * Minimise panel.
     * @return void
     */
    minimise_panel: function() {
        document.getElementById('CookieAgreementMessage').classList.add('minimised');
    },

    /**
     * Swap services selection display.
     * @return void
     */
    swap_servicesSelectionDisplay: function() {
        document.getElementById('CookieAgreementMessageServices').classList.toggle('opened');
    },

    /**
     * Enable refresh button.
     * @return void
     */
    enable_refreshButton: function() {
        document.getElementById('CookieAgreementMessageRefreshButton').classList.remove('hidden');
    },

    /**
     * Accept all cookies.
     * @return void
     */
    accept_cookies: function() {
        for (var service in this.services) {
            if (this.services[service] == 2)
                continue;
            this.services[service] = 1;
            document.getElementById(service+'Accept').classList.add('selected');
            document.getElementById(service+'Refuse').classList.remove('selected');
        }
        this.update_dataCookie();
        this.enable_refreshButton();
        if (!document.getElementById('CookieAgreementMessageServices').classList.contains('opened'))
            this.refresh_page();
    },

    /**
     * Refuse all cookies.
     * @return void
     */
    refuse_cookies: function() {
        for (var service in this.services) {
            if (this.services[service] == 2)
                continue;
            this.services[service] = 0;
            document.getElementById(service+'Accept').classList.remove('selected');
            document.getElementById(service+'Refuse').classList.add('selected');
        }
        this.update_dataCookie();
        this.enable_refreshButton();
        if (!document.getElementById('CookieAgreementMessageServices').classList.contains('opened'))
            this.refresh_page();
    },

    /**
     * Close panel and continue without accepting.
     * @return void
     */
    continue_withoutAccepting: function() {
        this.update_dataCookie();
        this.minimise_panel();
    },

    /**
     * Accept one service.
     * @param string service
     * @return void
     */
    accept_serviceCookies: function(service) {
        if (this.services[service] == 2)
            return;
        this.services[service] = 1;
        document.getElementById(service+'Accept').classList.add('selected');
        document.getElementById(service+'Refuse').classList.remove('selected');
        this.update_dataCookie();
        this.enable_refreshButton();
    },

    /**
     * Refuse one service.
     * @param string service
     * @return void
     */
    refuse_serviceCookies: function(service) {
        if (this.services[service] == 2)
            return;
        this.services[service] = 0;
        document.getElementById(service+'Accept').classList.remove('selected');
        document.getElementById(service+'Refuse').classList.add('selected');
        this.update_dataCookie();
        this.enable_refreshButton();
    },

    /**
     * Update data cookie.
     * @return void
     */
    update_dataCookie: function() {
        data = JSON.stringify(this.services);
        cookie_save('cookieAccepted', data, this.get_param('cookieTTL'));
    },

    /**
     * Refresh page.
     * @return void
     */
    refresh_page: function() {
        document.location.reload();
    },

    /**
     * Return unavailability message title.
     * @return void
     */
    get_unavailabilityMessageTitle: function() {
        return this.get_locale('unavailable_title');
    },

    /**
     * Return unavailability message content.
     * @param string service
     * @return void
     */
    get_unavailabilityMessageContent: function(service) {
        return this.get_locale('unavailable_content').replace('__SERVICE__', service);
    },
}
