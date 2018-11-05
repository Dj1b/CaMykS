/**
 * @brief SiteMonitoringToolbar Input scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/SiteMonitoringToolbar/js/SiteMonitoringToolbar.js
 * @author CaMykS Team
 * @version 1.0.1
 * @date Creation: Nov 2017
 * @date Modification: Oct 2018
 * @copyright 2017 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

var SiteMonitoringToolbar = {

    /* initialise some variables */
    name: 'SiteMonitoringToolbar',
    params: {},
    locales: {},
    loaded: false,

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
        if (this.params[param] || this.params[param] === 0)
            return this.params[param]
        return false;
    },

    /*
     * set locale value
     * @param string name
     * @param string value
     * @return void
     * @access public
     */
    set_locale: function(name, value) {
        this.locales[name.toLowerCase()] = value;
    },

    /*
     * get locale value
     * @param string name
     * @return void
     * @access public
     */
    get_locale: function(name) {
        if (this.locales[name.toLowerCase()])
            return this.locales[name.toLowerCase()];
        return name;
    },

    /*
     * initialise object
     * @return void
     * @access public
     */
    initialise: function() {

        /* detect navigator type */
        this.navType = navigator.userAgent.toLowerCase().indexOf('msie') ? 'msie':'row';

        /* load ajax request engine */
        this.loader = new CAjaxRequest(this.name+'.loader');
        this.loader._initialise(null, 'POST', this.name+'._receiveRequestResult', 'txt', this.name+'._receiveRequestError');
        this.requestQueue = new Array();

        /* initialise some params */
        this.set_param('toolbarStatus', 0);
        this.set_param('dataPanelStatus', 'off');

        /* load locales */
        this.load_file(this.get_param('pluginURL')+'/js/locale/locales.'+this.get_param('locale')+'.js', 'SiteMonitoringToolbar.start()');

        /* set as loaded */
        this.loaded = true;
    },

    /*
     * finalise object initialisation
     * @return void
     * @access private
     */
    start: function() {
        /* post loaded action */
        this.execute_action('loadConfig');
    },

    /* toolbar related methods */

    /*
     * display toolbar
     * @return void
     * @access private
     */
    display_toolbar: function() {

        /* create toolbar */
        pos = this.get_param('buttonLocation');
        if (pos === false) return;
        pos = pos.split(':');

        this.toolbar = document.createElement('div');
        this.toolbar.id = 'SiteMonitoringToolbar';
        this.toolbar.className = pos[1]+' '+this.get_param('appliedTheme');
        if (pos[0] == 'top') this.toolbar.style.top = 0;
        else if (pos[0] == 'bottom') this.toolbar.style.bottom = 0;
        if (pos[1] == 'left') this.toolbar.style.left = 0;
        else if (pos[1] == 'right') this.toolbar.style.right = 0;
        this.toolbar.style.height = '42px';
        this.toolbar.style.background = 'white';
        document.getElementsByTagName('body')[0].appendChild(this.toolbar);

        /* create master button */
        button = document.createElement('div');
        button.className = 'masterButton';
        image = document.createElement('img');
        image.src = this.get_param('pictureBaseURL')+'/CaMykS.png';
        if (this.get_param('navType') == 'row') {
	        image.setAttribute('onclick', this.name+'.swap_toolbarStatus()');
        } else {
	        image.onclick = new Function('onclick', this.name+'.swap_toolbarStatus()');
        }
        button.appendChild(image);
        this.toolbar.appendChild(button);

        /* add separator */
        sep = document.createElement('div');
        sep.className = 'separator';
        this.toolbar.appendChild(sep);

        /* create PHP stats button */
        button = document.createElement('div');
        button.id = 'PHPStatsButton';
        button.className = 'button';
        image = document.createElement('img');
        image.src = this.get_param('pictureBaseURL')+'/PHPStats.png';
        if (this.get_param('navType') == 'row') {
	    image.setAttribute('onclick', this.name+'.open_PHPStatsPanel();');
        } else {
	    image.onclick = new Function('onclick', this.name+'.open_PHPStatsPanel();');
        }
        image.title = this.get_locale('displayphpstats');

        button.appendChild(image);
        this.toolbar.appendChild(button);

        /* create DB stats button */
        button = document.createElement('div');
        button.id = 'DBStatsButton';
        button.className = 'button';
        image = document.createElement('img');
        if (this.get_param('DBStatsStatus') == 0) {
            image.src = this.get_param('pictureBaseURL')+'/DBStatsEnable.png';
            if (this.get_param('navType') == 'row') {
	        image.setAttribute('onclick', this.name+'.execute_action(\'startDBStats\')');
            } else {
	        image.onclick = new Function('onclick', this.name+'.execute_action(\'startDBStats\')');
            }
            image.title = this.get_locale('startdbstats');
        } else {
            image.src = this.get_param('pictureBaseURL')+'/DBStatsDisplay.png';
            if (this.get_param('navType') == 'row') {
	        image.setAttribute('onclick', this.name+'.open_DBStatsPanel()');
            } else {
	        image.onclick = new Function('onclick', this.name+'.open_DBStatsPanel()');
            }
            image.title = this.get_locale('displaydbstats');
        }

        button.appendChild(image);
        this.toolbar.appendChild(button);

        /* create Bench stats button */
        button = document.createElement('div');
        button.id = 'BenchButton';
        button.className = 'button';
        image = document.createElement('img');
        if (this.get_param('BenchStatus') == 0) {
            image.src = this.get_param('pictureBaseURL')+'/BenchEnable.png';
            if (this.get_param('navType') == 'row') {
	        image.setAttribute('onclick', this.name+'.execute_action(\'startBench\')');
            } else {
	        image.onclick = new Function('onclick', this.name+'.execute_action(\'startBench\')');
            }
            image.title = this.get_locale('startbench');
        } else {
            image.src = this.get_param('pictureBaseURL')+'/BenchDisplay.png';
            if (this.get_param('navType') == 'row') {
	        image.setAttribute('onclick', this.name+'.open_benchPanel()');
            } else {
	        image.onclick = new Function('onclick', this.name+'.open_benchPanel()');
            }
            image.title = this.get_locale('displaybench');
        }
        button.appendChild(image);
        this.toolbar.appendChild(button);

        /* add separator */
        sep = document.createElement('div');
        sep.className = 'separator';
        this.toolbar.appendChild(sep);

        /* create reload button */
        button = document.createElement('div');
        button.className = 'button';
        image = document.createElement('img');
        image.src = this.get_param('pictureBaseURL')+'/Reload.png';
        if (this.get_param('navType') == 'row') {
	        image.setAttribute('onclick', this.name+'.reload_page()');
        } else {
	        image.onclick = new Function('onclick', this.name+'.reload_page()');
        }
        image.title = this.get_locale('reloadpage');
        button.appendChild(image);
        this.toolbar.appendChild(button);

        /* create configuration button */
        if (this.get_param('allowConfiguration')) {
            button = document.createElement('div');
            button.id = 'ConfigurationButton';
            button.className = 'button';
            image = document.createElement('img');
            image.src = this.get_param('pictureBaseURL')+'/Configuration.png';
            if (this.get_param('navType') == 'row') {
	        image.setAttribute('onclick', this.name+'.open_configurationPanel()');
            } else {
	        image.onclick = new Function('onclick', this.name+'.open_configurationPanel()');
            }
            image.title = this.get_locale('displayconfiguration');
            button.appendChild(image);
            this.toolbar.appendChild(button);
        }

        /* create disconnect button */
        if (this.get_param('allowLogout')) {
            button = document.createElement('div');
            button.className = 'button';
            image = document.createElement('img');
            image.src = this.get_param('pictureBaseURL')+'/Disconnect.png';
            if (this.get_param('navType') == 'row') {
	        image.setAttribute('onclick', this.name+'.execute_action(\'disconnect\')');
            } else {
	        image.onclick = new Function('onclick', this.name+'.execute_action(\'disconnect\')');
            }
            image.title = this.get_locale('logout');
            button.appendChild(image);
            this.toolbar.appendChild(button);
        }

        /* create data panel */
        this.dataPanel = document.createElement('div');
        this.dataPanel.id = 'SiteMonitoringToolbarDataPanel';
        this.dataPanel.style.display = 'none';
        this.dataPanel.style.top = 0;
        this.dataPanel.className = pos[1]+' '+this.get_param('appliedTheme');
        document.getElementsByTagName('body')[0].appendChild(this.dataPanel);

        /* create data panel content box */
        div = document.createElement('div');
        div.className = 'contentBox';
        this.dataPanel.appendChild(div);
    },

    /*
     * swap toolbar status
     * @return void
     * @access public
     */
    swap_toolbarStatus: function() {

        if (this.get_param('toolbarStatus') == 0) {
            /* open toolbar */

            /* update variable */
            this.set_param('toolbarStatus', 1);

            this.toolbar.style.background = null;

            /* resize toolbar */
            this.resize_toolbar();

        } else {

            /* close toolbar */
            this.toolbar.style.height = '42px';
            setTimeout("SiteMonitoringToolbar.toolbar.style.background = 'white';", 300);

            /* update variable */
            this.set_param('toolbarStatus', 0);

            /* close data panel */
            this.hide_dataPanel();
        }
    },

    /*
     * resize toolbar
     * @return void
     * @access public
     */
    resize_toolbar: function() {
        /* check for closed status */
        if (this.get_param('toolbarStatus') == 0)
            return;

        /* detect correct height */
        if (typeof( window.innerWidth ) == 'number') {height = window.innerHeight;}
        else if (document.documentElement && document.documentElement.clientHeight) {height = document.documentElement.clientHeight;}
        else if (document.body && document.body.clientHeight) {height = document.body.clientHeight;}
        else {height = 100;}

        /* apply height */
        this.toolbar.style.height = height + 'px';
    },

    /* data panel methods */

    /*
     * show and update content of data panel
     * @param HTMLElement content
     * @param integer top
     * @param integer width
     * @return void
     * @access private
     */
    show_dataPanel: function(content, top, width) {
        if (top) this.dataPanel.style.top = top + 'px';
        if (width) this.dataPanel.style.width = width + 'px';
        if (content) {
            this.dataPanel.getElementsByTagName('div')[0].innerHTML = '';
            this.dataPanel.getElementsByTagName('div')[0].appendChild(content);
        }
        this.dataPanel.style.display = 'block';
    },

    /*
     * hide data panel
     * @return void
     * @access private
     */
    hide_dataPanel: function() {
        /* update status */
        this.set_param('dataPanelStatus', 'off');

        /* hide HTML element */
        this.dataPanel.style.display = 'none';
    },

    /* action methods */

    /*
     * open/close PHP stats panel
     * @return void
     * @access private
     */
    open_PHPStatsPanel: function() {

        /* close data panel if it's already open on php stats, and stop    */
        if (this.get_param('dataPanelStatus') === 'phpstats')
            return this.hide_dataPanel();

        /* close data panel if it's already open */
        if (this.get_param('dataPanelStatus') !== 'off')
            this.hide_dataPanel();

        /* execute PHP stats loading */
        this.execute_request({'mode':'displayPHPStats'});
    },

    /*
     * open/close DB stats panel
     * @return void
     * @access private
     */
    open_DBStatsPanel: function() {

        /* close data panel if it's already open on db stats, and stop    */
        if (this.get_param('dataPanelStatus') === 'dbstats')
            return this.hide_dataPanel();

        /* close data panel if it's already open */
        if (this.get_param('dataPanelStatus') !== 'off')
            this.hide_dataPanel();

        /* execute db stats loading */
        this.execute_request({'mode':'displayDBStats'});
    },

    /*
     * open/close bench panel
     * @return void
     * @access private
     */
    open_benchPanel: function() {

        /* close data panel if it's already open on bench, and stop    */
        if (this.get_param('dataPanelStatus') === 'bench')
            return this.hide_dataPanel();

        /* close data panel if it's already open */
        if (this.get_param('dataPanelStatus') !== 'off')
            this.hide_dataPanel();

        /* execute bench loading */
        this.execute_request({'mode':'displayBench'});
    },

    /*
     * open/close configuration panel
     * @return void
     * @access private
     */
    open_configurationPanel: function() {

        /* close data panel if it's already open on bench, and stop    */
        if (this.get_param('dataPanelStatus') === 'configuration')
            return this.hide_dataPanel();

        /* close data panel if it's already open */
        if (this.get_param('dataPanelStatus') !== 'off')
            this.hide_dataPanel();

        /* execute congifuration loading */
        this.execute_request({'mode':'displayConfiguration'});
    },

    /*
     * save (and close) configuration panel
     * @return void
     * @access private
     */
    save_configuration: function() {

        /* do nothing if current panel is not configuration    */
        if (this.get_param('dataPanelStatus') !== 'configuration')
            return;

        /* load configuration values */
        params = {'mode':'saveConfiguration'};
        params['accessRestriction'] = document.getElementById('ConfigurationAccessRestriction').options[document.getElementById('ConfigurationAccessRestriction').options.selectedIndex].value;
        params['buttonLocation'] = document.getElementById('ConfigurationButtonLocation').options[document.getElementById('ConfigurationButtonLocation').options.selectedIndex].value;
        params['appliedTheme'] = document.getElementById('ConfigurationAppliedTheme').options[document.getElementById('ConfigurationAppliedTheme').options.selectedIndex].value;

        /* close panel */
        this.hide_dataPanel();

        /* execute bench loading */
        this.execute_request(params);
    },

    /*
     * execute action request
     * @param string action
     * @return void
     * @access private
     */
    execute_action: function(action) {
        this.execute_request({'mode':action});
    },

    /* request methods */

    /*
     * send request update
     * @param array urlParams
     * @param boolean wait
     * @return void
     * @access private
     */
    execute_request: function(urlParams, wait) {
        if (this.loaded === false)
            return;

        p = '';
        for (i in urlParams)
            p += '&'+i+'='+urlParams[i];


        this._executeRequest(this.get_param('requestBaseURL')+p, wait);
    },

    /*
     * execute request
     * @param string url
     * @param boolean wait
     * @return void
     * @access private
     */
    _executeRequest: function(url, wait) {
        if (!this.loaded)
            return;

        /* manage request queue for those browsers */
        if ( this.loader._resultStatus != 'idle' ) {
            if (wait) this.requestQueue.push(url);
                return;
        }
        this.loader._execute(url);
    },

    /*
     * receive request result
     * @param string result
     * @return void
     * @access private
     */
    _receiveRequestResult: function(result) {
        /* parse result as JSON */
        try {
            result = JSON.parse(result);
        } catch(e) {
            //console.log(result);
            return;
        }

        /* check result */
        if ( result == null )
            return;

        /* check action result */
        switch (result['action']) {
            /* configuration actions */
            case 'loadConfig':
                this._receive_loadConfigResult(result);
                break;

            /* PHP Stats actions */
            case 'displayPHPStats':
                this._receive_displayPHPStats(result);
                break;

            /* DB Stats actions */
            case 'startDBStats':
                this._receive_startDBStats(result);
                break;
            case 'stopDBStats':
                this._receive_stopDBStats(result);
                break;
            case 'displayDBStats':
                this._receive_displayDBStats(result);
                break;

            /* bench actions */
            case 'startBench':
                this._receive_startBench(result);
                break;
            case 'stopBench':
                this._receive_stopBench(result);
                break;
            case 'displayBench':
                this._receive_displayBench(result);
                break;

            /* configuration actions */
            case 'displayConfiguration':
                this._receive_displayConfiguration(result);
                break;

            /* tool actions */
            case 'disconnect':
                this._receive_disconnectResult(result);
                break;
            default:
                break;
        }

        /* try to reduce request queue */
        if ( this.requestQueue.length > 0 ) {
            request =    this.requestQueue.shift();
            this._executeRequest(request, true);
        }
    },

    /*
     * receive request error
     * @param xml result
     * @return void
     * @access private
     */
    _receiveRequestError: function(e) {
        //alert(e);
        /* define what to do */
    },

    /* request reception dedicated methods */

    /*
     * receive result after loadConfig request
     * @param Object result
     * @return void
     * @access private
     */
    _receive_loadConfigResult: function(result) {

        /* check config */
        if (!result['config']) return;

        /* save config */
        for (i in result['config'])
            this.set_param(i, result['config'][i]);

        /* post loaded action */
        this.display_toolbar();
    },

    /*
     * receive result after displayPHPStats request
     * @param Object result
     * @return void
     * @access private
     */
    _receive_displayPHPStats: function(result) {

        /* compute button position */
        vTop = tool_getObjectPositionY(document.getElementById('PHPStatsButton'));

        /* create container */
        box = document.createElement('div');

        /* add title */
        div = document.createElement('div');
        div.className = 'title';
        div.innerHTML = this.get_locale('phpstats_title');
        box.appendChild(div);

        /* add memory values */
        div = document.createElement('div');
        div.className = 'subtitle';
        div.innerHTML = this.get_locale('phpstats_title_memory');
        box.appendChild(div);

        div = document.createElement('div');
        div.className = 'content';
        div.innerHTML = this.get_locale('phpstats_item_memoryend') + ' <span class="value">' + result['PHPStats']['memoryEnd']+'</span> <br />';
        div.innerHTML += this.get_locale('phpstats_item_memorypeak') + ' <span class="value">' + result['PHPStats']['memoryPeak']+'</span> <br />';
        div.innerHTML += this.get_locale('phpstats_item_memorylimit') + ' <span class="value">' + result['PHPStats']['memoryLimit']+'</span> <br />';
        box.appendChild(div);

        /* add empty line */
        div = document.createElement('div');
        div.className = 'content';
        div.innerHTML = '&nbsp;';
        box.appendChild(div);

        /* add files values */
        div = document.createElement('div');
        div.className = 'subtitle';
        div.innerHTML = this.get_locale('phpstats_title_files');
        box.appendChild(div);

        div = document.createElement('div');
        div.className = 'content';
        div.innerHTML = this.get_locale('phpstats_item_includedfiles') + ' <span class="value">' + result['PHPStats']['includedFiles']+'</span> <br />';
        box.appendChild(div);

        /* add empty line */
        div = document.createElement('div');
        div.className = 'content';
        div.innerHTML = '&nbsp;';
        box.appendChild(div);

        /* add request values */
        div = document.createElement('div');
        div.className = 'subtitle';
        div.innerHTML = this.get_locale('phpstats_title_request');
        box.appendChild(div);

        div = document.createElement('div');
        if (result['PHPStats']['requestData'].length == 0) {
            div.className = 'description';
            div.innerHTML = this.get_locale('no_result');
        } else {
            div.className = 'content';
            div.innerHTML = '';
            for (i in result['PHPStats']['requestData']) {
                div.innerHTML += i + ' : <span class="value">' + result['PHPStats']['requestData'][i] +'</span> <br />';
            }
        }
        box.appendChild(div);

        /* add empty line */
        div = document.createElement('div');
        div.className = 'content';
        div.innerHTML = '&nbsp;';
        box.appendChild(div);

        /* add cookie values */
        div = document.createElement('div');
        div.className = 'subtitle';
        div.innerHTML = this.get_locale('phpstats_title_cookie');
        box.appendChild(div);

        div = document.createElement('div');
        if (result['PHPStats']['cookieData'].length == 0) {
            div.className = 'description';
            div.innerHTML = this.get_locale('no_result');
        } else {
            div.className = 'content';
            div.innerHTML = '';
            for (i in result['PHPStats']['cookieData']) {
                div.innerHTML += i + ' : <span class="value">' + result['PHPStats']['cookieData'][i] +'</span> <br />';
            }
        }
        box.appendChild(div);

        /* add empty line */
        div = document.createElement('div');
        div.className = 'content';
        div.innerHTML = '&nbsp;';
        box.appendChild(div);

        /* add cms shared objects values */
        div = document.createElement('div');
        div.className = 'subtitle';
        div.innerHTML = this.get_locale('phpstats_title_sharedobjects');
        box.appendChild(div);

        div = document.createElement('div');
        if (result['PHPStats']['sharedObjects'].length == 0) {
            div.className = 'description';
            div.innerHTML = this.get_locale('no_result');
        } else {
            div.className = 'content';
            div.innerHTML = '';
            for (i in result['PHPStats']['sharedObjects']) {
                div.innerHTML += i + ' : <span class="value">'+result['PHPStats']['sharedObjects'][i]+'</span> <br />';
            }
        }
        box.appendChild(div);

        /* add empty line */
        div = document.createElement('div');
        div.className = 'content';
        div.innerHTML = '&nbsp;';
        box.appendChild(div);

        /* add cms shared data values */
        div = document.createElement('div');
        div.className = 'subtitle';
        div.innerHTML = this.get_locale('phpstats_title_shareddata');
        box.appendChild(div);

        div = document.createElement('div');
        if (result['PHPStats']['sharedData'].length == 0) {
            div.className = 'description';
            div.innerHTML = this.get_locale('no_result');
        } else {
            div.className = 'content';
            div.innerHTML = '';
            for (i in result['PHPStats']['sharedData']) {

                if (Array.isArray(result['PHPStats']['sharedData'][i]))
                    div.innerHTML += i + ' : <span class="value"> Array('+result['PHPStats']['sharedData'][i].length +')</span> <br />';
                else if (typeof result['PHPStats']['sharedData'][i] == 'object')
                    div.innerHTML += i + ' : <span class="value"> Object </span> <br />';
                else
                    div.innerHTML += i + ' : <span class="value">'+result['PHPStats']['sharedData'][i]+'</span> <br />';
            }
        }
        box.appendChild(div);

        /* update status */
        this.set_param('dataPanelStatus', 'phpstats');

        /* display results */
        this.show_dataPanel(box, vTop, 400)
    },

    /*
     * receive result after startDBStats request
     * @param Object result
     * @return void
     * @access private
     */
    _receive_startDBStats: function(result) {
        /* reload page */
        location.reload(true);
    },

    /*
     * receive result after stopDBStats request
     * @param Object result
     * @return void
     * @access private
     */
    _receive_stopDBStats: function(result) {

    },

    /*
     * receive result after displayDBStats request
     * @param Object result
     * @return void
     * @access private
     */
    _receive_displayDBStats: function(result) {

        /* compute button position */
        vTop = tool_getObjectPositionY(document.getElementById('DBStatsButton'));

        /* create container */
        box = document.createElement('div');

        /* add title */
        div = document.createElement('div');
        div.className = 'title';
        div.innerHTML = this.get_locale('dbstats_title');
        box.appendChild(div);

        if (result['DBStats'] === false) {
            div = document.createElement('div');
            div.className = 'description';
            div.innerHTML = this.get_locale('no_result');
            box.appendChild(div);
        } else {

            for (db in result['DBStats']) {
                /* add stats subtitle */
                div = document.createElement('div');
                div.className = 'subtitle';
                div.innerHTML = db;
                box.appendChild(div);

                /* add stats */
                div = document.createElement('div');
                div.className = 'content';
                div.innerHTML = this.get_locale('dbstats_queries') + ' <span class="value">' + result['DBStats'][db]['queries']+'</span>';
                div.innerHTML += '&nbsp; &#124; &nbsp;';
                div.innerHTML += this.get_locale('dbstats_fetchedlines') + ' <span class="value">' + result['DBStats'][db]['fetchedLines']+'</span>';
                div.innerHTML += '&nbsp; &#124; &nbsp;';
                div.innerHTML += this.get_locale('dbstats_updatedlines') + ' <span class="value">' + result['DBStats'][db]['updatedLines']+'</span>';
                box.appendChild(div);

                /* add queries */
                if (result['DBQueries'][db] != undefined) {
                    div = document.createElement('div');
                    div.className = 'content';
                    div.innerHTML = this.get_locale('dbstats_querylist');
                    box.appendChild(div);

                    ul = document.createElement('ul');
                    box.appendChild(ul);

                    for (i in result['DBQueries'][db]) {
                        li = document.createElement('li');
                        li.className = 'content';
                        li.innerHTML = result['DBQueries'][db][i];
                        ul.appendChild(li);
                    }
                }

                /* add empty line */
                div = document.createElement('div');
                div.className = 'content';
                div.innerHTML = '&nbsp;';
            }
        }

        /* update status */
        this.set_param('dataPanelStatus', 'dbstats');

        /* display results */
        this.show_dataPanel(box, vTop, 600)
    },

    /*
     * receive result after startBench request
     * @param Object result
     * @return void
     * @access private
     */
    _receive_startBench: function(result) {
        /* reload page */
        location.reload(true);
    },

    /*
     * receive result after stopBench request
     * @param Object result
     * @return void
     * @access private
     */
    _receive_stopBench: function(result) {

    },

    /*
     * receive result after displayBench request
     * @param Object result
     * @return void
     * @access private
     */
    _receive_displayBench: function(result) {

        /* compute button position */
        vTop = tool_getObjectPositionY(document.getElementById('BenchButton'));

        /* create container */
        box = document.createElement('div');

        /* add title */
        div = document.createElement('div');
        div.className = 'title';
        div.innerHTML = this.get_locale('bench_title');
        box.appendChild(div);

        /* check has results */
        if (result['Bench'] === false || result['Bench'].length == 0) {
            div = document.createElement('div');
            div.className = 'description';
            div.innerHTML = this.get_locale('no_result');
            box.appendChild(div);
        } else {
            for (i in result['Bench']) {
                div = document.createElement('div');
                div.className = 'content';
                div.innerHTML = result['Bench'][i]['title']+': <span class="value">'+result['Bench'][i]['time']+'</span>';
                box.appendChild(div);
            }
        }

        /* update status */
        this.set_param('dataPanelStatus', 'bench');

        /* display results */
        this.show_dataPanel(box, vTop, 300);
    },

    /*
     * receive result after displayConfiguration request
     * @param Object result
     * @return void
     * @access private
     */
    _receive_displayConfiguration: function(result) {

        /* compute button position */
        vTop = tool_getObjectPositionY(document.getElementById('ConfigurationButton'));

        /* get data */
        configData = result['ConfigurationData'];

        /* create container */
        form = document.createElement('form');
        form.setAttribute('method',"get");
        form.setAttribute('action',"javascript:void(0);");

        /* add title */
        div = document.createElement('div');
        div.className = 'title';
        div.innerHTML = this.get_locale('configuration_title');
        form.appendChild(div);

        /* add access restriction line */
        div = document.createElement('div');
        div.className = 'formLine';
        form.appendChild(div);

        label = document.createElement('div');
        label.className = 'formLabel';
        label.innerHTML = this.get_locale('formlabel_accessrestriction');
        div.appendChild(label);

        input = document.createElement('div');
        input.className = 'formInput';
        select = document.createElement('select');
        select.id = 'ConfigurationAccessRestriction';
        select.className = 'inputs';
        for (i in configData['accessRestrictionList']) {
            if (i == configData['default']['accessRestriction'])
                selected = select.options.length;
            select.options[select.options.length] = new Option(configData['accessRestrictionList'][i], i);
        }
        select.options[selected].selected = 'selected';
        input.appendChild(select);
        div.appendChild(input);

        /* add button location line */
        div = document.createElement('div');
        div.className = 'formLine';
        form.appendChild(div);

        label = document.createElement('div');
        label.className = 'formLabel';
        label.innerHTML = this.get_locale('formlabel_buttonlocation');
        div.appendChild(label);

        input = document.createElement('div');
        input.className = 'formInput';
        select = document.createElement('select');
        select.id = 'ConfigurationButtonLocation';
        select.className = 'inputs';
        selected = 0;
        for (i in configData['buttonLocationList']) {
            if (i == this.get_param('buttonLocation'))
                selected = select.options.length;
            select.options[select.options.length] = new Option(configData['buttonLocationList'][i], i);
        }
        select.options[selected].selected = 'selected';
        input.appendChild(select);
        div.appendChild(input);

        /* add applied theme line */
        div = document.createElement('div');
        div.className = 'formLine';
        form.appendChild(div);

        label = document.createElement('div');
        label.className = 'formLabel';
        label.innerHTML = this.get_locale('formlabel_appliedtheme');
        div.appendChild(label);

        input = document.createElement('div');
        input.className = 'formInput';
        select = document.createElement('select');
        select.id = 'ConfigurationAppliedTheme';
        select.className = 'inputs';
        for (i in configData['availableThemeList']) {
            if (i == this.get_param('appliedTheme'))
                selected = select.options.length;
            select.options[select.options.length] = new Option(configData['availableThemeList'][i], i);
        }
        select.options[selected].selected = 'selected';
        input.appendChild(select);
        div.appendChild(input);

        /* add submit button line */
        div = document.createElement('div');
        div.className = 'buttonLine';
        form.appendChild(div);

        button = document.createElement('div');
        button.className = 'button';
        button.innerHTML = this.get_locale('save');
        if (this.get_param('navType') == 'row') {
	    button.setAttribute('onclick', this.name+'.save_configuration()');
        } else {
	    button.onclick = new Function('onclick', this.name+'.save_configuration()');
        }
        div.appendChild(button);

        /* update status */
        this.set_param('dataPanelStatus', 'configuration');

        /* display results */
        this.show_dataPanel(form, vTop, 400);
    },

    /*
     * receive result after disconnect request
     * @param Object result
     * @return void
     * @access private
     */
    _receive_disconnectResult: function(result) {
        /* reload page */
        this.reload_page();
    },

    /* tool methods */

    /*
     * load a JS file
     * @param string fileURL
     * @param string action
     * @return void
     * @access private
     */
    load_file: function(fileURL, action) {
        tag = document.createElement('script');
        tag.setAttribute("type","text/javascript");
        tag.setAttribute("src", fileURL+'?'+Math.floor((Math.random() * 1000) + 1));
        tag.onload = function() {
            if (typeof(action) === 'string')
                eval(action);
        }
        document.getElementsByTagName('head')[0].appendChild(tag);
    },

    /*
     * reload page
     * @return void
     * @access private
     */
    reload_page: function() {
        location.reload(true);
    },
};
