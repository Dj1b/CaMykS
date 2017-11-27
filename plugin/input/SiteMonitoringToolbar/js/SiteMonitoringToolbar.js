/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Javascript
 * Creation Date    : Nov 2017
 * Last Modif Date  : Nov 2017
 * 
 * SiteMonitoringToolbar master script
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
    
    /* load locales */
    this.load_file(this.get_param('pluginURL')+'/js/locale/locales.'+this.get_param('locale')+'.js');
  
    /* load ajax request engine */
    this.loader = new CAjaxRequest(this.name+'.loader');
    this.loader._initialise(null, 'POST', this.name+'._receiveRequestResult', 'txt', this.name+'._receiveRequestError');
    this.requestQueue = new Array();
    
    /* initialise some params */
    this.set_param('toolbarStatus', 0);
    this.set_param('dataPanelStatus', 'off');
    
    /* set as loaded */
    this.loaded = true;
    
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
    pos = this.get_param('toolbarLocation');
    if (pos === false) return;
    pos = pos.split(':');
    
    this.toolbar = document.createElement('div');
    this.toolbar.id = 'SiteMonitoringToolbar';
    if (pos[0] == 'top') this.toolbar.style.top = 0;
    else if (pos[0] == 'bottom') this.toolbar.style.bottom = 0;
    if (pos[1] == 'left') this.toolbar.style.left = 0;
    else if (pos[1] == 'right') this.toolbar.style.right = 0;
    this.toolbar.style.height = '42px';
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
    
    /* create DB stats button */
    button = document.createElement('div');
    button.id = 'DBStatsButton';
    button.className = 'button';
    image = document.createElement('img');
    if (this.get_param('DBStatsStatus') == 0) {
      console.log ('build: sql stats not enabled'); 
      image.src = this.get_param('pictureBaseURL')+'/DBStatsEnable.png';
      if (this.get_param('navType') == 'row') {
	    image.setAttribute('onclick', this.name+'.execute_action(\'startDBStats\')');
      } else {
	    image.onclick = new Function('onclick', this.name+'.execute_action(\'startDBStats\')');
      }
    } else {
      console.log ('build: sql stats enabled'); 
      image.src = this.get_param('pictureBaseURL')+'/DBStatsDisplay.png';
      if (this.get_param('navType') == 'row') {
	    image.setAttribute('onclick', this.name+'.open_DBStatsPanel()');
      } else {
	    image.onclick = new Function('onclick', this.name+'.open_DBStatsPanel()');
      }
    }
    
    button.appendChild(image);
    this.toolbar.appendChild(button);
    
    /* create Bench stats button */
    button = document.createElement('div');
    button.id = 'BenchButton';
    button.className = 'button';
    image = document.createElement('img');
    if (this.get_param('BenchStatus') == 0) {
      console.log ('build: bench not enabled'); 
      image.src = this.get_param('pictureBaseURL')+'/BenchEnable.png';
      if (this.get_param('navType') == 'row') {
	    image.setAttribute('onclick', this.name+'.execute_action(\'startBench\')');
      } else {
	    image.onclick = new Function('onclick', this.name+'.execute_action(\'startBench\')');
      }
    } else {
      console.log ('build: bench enabled'); 
      image.src = this.get_param('pictureBaseURL')+'/BenchDisplay.png';
      if (this.get_param('navType') == 'row') {
	    image.setAttribute('onclick', this.name+'.open_benchPanel()');
      } else {
	    image.onclick = new Function('onclick', this.name+'.open_benchPanel()');
      }
    }
    button.appendChild(image);
    this.toolbar.appendChild(button);
    
    /* add separator */
    sep = document.createElement('div');
    sep.className = 'separator';
    this.toolbar.appendChild(sep);
    
    /* create disconnect button */
    button = document.createElement('div');
    button.className = 'button';
    image = document.createElement('img');
    image.src = this.get_param('pictureBaseURL')+'/Disconnect.png';
    if (this.get_param('navType') == 'row') {
	    image.setAttribute('onclick', this.name+'.execute_action(\'disconnect\')');
    } else {
	    image.onclick = new Function('onclick', this.name+'.execute_action(\'disconnect\')');
    }
    button.appendChild(image);
    this.toolbar.appendChild(button);
    
    /* create data panel */
    this.dataPanel = document.createElement('div');
    this.dataPanel.id = 'SiteMonitoringToolbarDataPanel';
    this.dataPanel.style.display = 'none';
    this.dataPanel.style.top = 0;
    this.dataPanel.className = pos[1];
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
      
      /* resize toolbar */
      this.resize_toolbar();
      
    } else {
      /* close toolbar */
      this.toolbar.style.height = '42px';
      
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
   * open/close bench panel
   * @return void
   * @access private
   */
  open_DBStatsPanel: function() {
    
    /* close data panel if it's already open on bench, and stop  */
    if (this.get_param('dataPanelStatus') === 'dbstats')
      return this.hide_dataPanel();

    /* close data panel if it's already open */
    if (this.get_param('dataPanelStatus') !== 'off')
      this.hide_dataPanel();

    /* execute bench loading */
    this.execute_request({'mode':'displayDBStats'});
  },
  
  /*
   * open/close bench panel
   * @return void
   * @access private
   */
  open_benchPanel: function() {
    
    /* close data panel if it's already open on bench, and stop  */
    if (this.get_param('dataPanelStatus') === 'bench')
      return this.hide_dataPanel();

    /* close data panel if it's already open */
    if (this.get_param('dataPanelStatus') !== 'off')
      this.hide_dataPanel();

    /* execute bench loading */
    this.execute_request({'mode':'displayBench'});
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
    console.log(url);
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
    result = JSON.parse(result);
  
    /* check result */
    if ( result == null )
      return;
   
    /* check action result */
    switch (result['action']) {
      /* configuration actions */
      case 'loadConfig':
        this._receive_loadConfigResult(result);
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
      
      /* tool actions */
      case 'disconnect':
        this._receive_disconnectResult(result);
        break;
      default:
        break;
    }

    /* try to reduce request queue */
    if ( this.requestQueue.length > 0 ) {
      request =  this.requestQueue.shift();
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
      
    console.log('configuration loaded');
  
    /* post loaded action */
    this.display_toolbar();
  },
  
  /*
   * receive result after startDBStats request
   * @param Object result
   * @return void
   * @access private
   */
  _receive_startDBStats: function(result) {
    console.log('sql stats started');    
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
    console.log('sql stats stopped');
  },
  
  /*
   * receive result after displayDBStats request
   * @param Object result
   * @return void
   * @access private
   */
  _receive_displayDBStats: function(result) {
    console.log('sql stats display');
    
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
        if (result['DBQueries'][db]) {
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
    console.log('bench started');
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
    console.log('bench stopped');
  
  },
  
  /*
   * receive result after displayBench request
   * @param Object result
   * @return void
   * @access private
   */
  _receive_displayBench: function(result) {
    console.log('bench display');
    
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
    this.show_dataPanel(box, vTop, 300)
  },
  
  /*
   * receive result after disconnect request
   * @param Object result
   * @return void
   * @access private
   */
  _receive_disconnectResult: function(result) {    
    /* reload page */
    location.reload(true);
  },
  
  /* tool methods */
  
  /*
   * load a JS file
   * @param string fileURL
   * @return void
   * @access private
   */
  load_file: function(fileURL) {
    tag = document.createElement('script');
    tag.setAttribute("type","text/javascript");
    tag.setAttribute("src", fileURL+'?'+Math.floor((Math.random() * 1000) + 1));
    //tag.onload = function() {}
    document.getElementsByTagName('head')[0].appendChild(tag);
  },
  
};