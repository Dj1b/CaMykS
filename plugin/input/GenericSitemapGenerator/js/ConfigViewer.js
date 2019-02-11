/**
 * @brief GenericSitemapGenerator module configuration viewer scripts
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

var ConfigViewer = {
    name: 'ConfigViewer',
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

        /* init ajax request engine */
        this.loader = new CAjaxRequest(this.name+'.loader');
        this.loader._initialise(null, 'POST', this.name+'.receiveRequestResult', 'txt', this.name+'.receiveRequestError');
        this.requestQueue = new Array();

        /* finalise initialisation */
        this.loaded = true;
    },

    /* Action methods */

    /**
     * Initiate sitemap file update.
     * @return void
     */
    initiate_writeSitemap: function() {
        urlParams = 'mode=writeSitemap';
        this.send_request(urlParams);
    },

    /**
     * Receive sitemap file update answer.
     * @param result
     * @return void
     */
     receive_writeSitemap: function(answer) {
        document.getElementById('UpdateButton').innerHTML = answer['message'];
     },

    /* Request methods */

    /**
     * Send request
     * @param string urlParams
     * @return void
     * @private
     */
    send_request: function(urlParams) {
        if (urlParams)
            this.executeRequest(this.get_param('baseURL')+'&'+urlParams);
        else
            this.executeRequest(this.get_param('baseURL'));
    },

    /**
     * Execute request
     * @param string url
     * @param boolean wait
     * @return void
     * @private
     */
    executeRequest: function (url, params, wait) {
        if (!this.loaded)
            return;

        /* manage request queue for those browsers */
        if (this.loader._resultStatus != 'idle') {
            if (wait) this.requestQueue.push(new Array(url, params));
            return;
        }

        //console.log(url);
        this.loader._execute(url, null, params);
    },

    /**
     * Receive request result
     * @param xml result
     * @return void
     * @private
     */
    receiveRequestResult: function(result) {
        /* parse JSON result */
        try {
            result = JSON.parse(result);
        } catch(e) {
            console.log(result);
            return;
        }

        /* check action result */
        switch (result['action']) {
            case 'writeSitemap':
                this.receive_writeSitemap(result);
                break;
            default:
                break;
        }

        /* try to reduce request queue */
        if (this.requestQueue.length > 0) {
            request = this.requestQueue.shift();
            this._executeRequest(request[0], request[1], true);
        }
    },

    /**
     * Receive request error
     * @param xml result
     * @return void
     * @private
     */
    receiveRequestError: function(e) {
        //alert(e);
        /* define what to do */
    },
}
