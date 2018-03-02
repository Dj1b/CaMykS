/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Dec 2014
 * Last Modif Date	: Feb 2018
 * 
 * Admin_ContentPage config edition scripts
 */
 
var ConfigEditor = {
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
    if (subvalue != undefined && this.params[param])
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
    /* check navigator type */
  	this.set_param('navType',  navigator.appName.indexOf("Microsoft")==-1? 'real':'msie');
  	
  	/* set form */
  	this.set_param('form', document.getElementById(this.get_param('form')));
  	
  	/* default vars */
  	this.set_param('selectedPage', '');
  	this.set_param('keyPageCnt', 0);
  	
	/* finalise initialisation */
  	this.loaded = true;
  	
  	/* after init actions */
  	this.check_selected404FallBack();
  },
  
  /* 404 fallback management methods */
  
  /*
   * check selected 404 Fallback value
   * @return void
   * @access public
   */
  check_selected404FallBack: function() {
    if (!this.loaded)
      return false;
  
    select = this.get_param('form')['page_404FallBack'];
    value = select.options[select.options.selectedIndex].value;
    
    /* check for file selection box display */
    if ( value.substring(0, 8) == 'error404')
      document.getElementById('FileSelectionBox').style.display = 'block';
    else
      document.getElementById('FileSelectionBox').style.display = 'none';
    
    /* check for page selection box display */
    if ( value.substring(0, 4) == 'page' )
      document.getElementById('PageSelectionBox').style.display = 'block';
    else
      document.getElementById('PageSelectionBox').style.display = 'none';
      
    /* check for http header sending */
    if ( value.substring(value.length-7, value.length) == 'display')
      document.getElementById('HeaderSendingBox').style.display = 'block';
    else
      document.getElementById('HeaderSendingBox').style.display = 'none';
  },
  
  /* page chooser methods */
  
  /*
   * open page chooser to select a page for given variable
   * @param string inputName
   * @return void
   */
  open_pageChooser: function (inputName) {
    this.set_param('selectedPage', inputName);
    pc.open(this.get_param('form')[inputName].value);
  },
  
  /*
   * update selected page value 
   * @param integer id
   * @param string name
   * @return void
   * @access public
   */
  update_selectedPage: function (id, name) {
    if (this.get_param('selectedPage') !== false) {
      this.get_param('form')[this.get_param('selectedPage')].value = id;
      this.get_param('form')[this.get_param('selectedPage')+'_name'].value = name;
    }
  },
  
  /* key pages management methods */
  
  /*
   * insert new key page
   * @return void
   * @access public
   */
  insert_keyPage: function() {
    keyIndex = this.get_param('form')['keyPageCnt'].value;
  
    keyLine = document.getElementById('keyPageTemplate').cloneNode(true);
    keyLine.id = 'keyPage'+keyIndex;
  	keyLine.innerHTML = keyLine.innerHTML.replaceAll('XXX', keyIndex);
    keyLine.style.display = 'block';
    
    document.getElementById('keyPages').appendChild(keyLine);
    
    this.get_param('form')['keyPageCnt'].value++;
  },
  
  /*
   * remove key page
   * @param integer pageIndex
   * @return void
   * @access public
   */
  remove_keyPage: function(pageIndex) {
    this.get_param('form')['keyPageName'+pageIndex].value = '';
    document.getElementById('keyPage'+pageIndex).style.display = 'none';
  },
  
  /* navigation management methods */
  
  /*
   * insert new navigation
   * @return void
   * @access public
   */
  insert_navigation: function() {
    keyIndex = this.get_param('form')['navAddCnt'].value;
  
    keyLine = document.getElementById('navAddTemplate').cloneNode(true);
    keyLine.id = 'navAdd'+keyIndex;
  	keyLine.innerHTML = keyLine.innerHTML.replaceAll('XXX', keyIndex);
    keyLine.style.display = 'block';
    
    document.getElementById('navAdds').appendChild(keyLine);
    
    this.get_param('form')['navAddCnt'].value++;
  },
  
  /*
   * remove navigation
   * @param integer pageIndex
   * @return void
   * @access public
   */
  remove_navigation: function(pageIndex) {
    this.get_param('form')['navAddName'+pageIndex].value = '';
    document.getElementById('navAdd'+pageIndex).style.display = 'none';
  },
}