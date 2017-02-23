/*
 * CaMykS Engine
 * Developed by		: Ideogram Design
 * Author			: JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Dec 2014
 * Last Modif Date	: Dec 2014
 * 
 * Admin_ContentPage config edition scripts
 */
 
function ConfigEditor(name) {
  this.name = name;
  this.params = {};
  this.locales = {};
  this.loaded = false;

  /*
   * add parameter
   * @param string name
   * @param mixed value
   * @return void
   * @access public
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
   * @access public
   */
  this.get_param = function(param, value) {
    if (value != undefined && (this.params[param][value] || this.params[param][value] === 0))
        return this.params[param][value];
    if (this.params[param] || this.params[param] === 0)
      return this.params[param]
    return false;
  };
  
  /*
   * set locale value 
   * @param string name
   * @param string value
   * @return void
   * @access public
   */
  this.set_locale = function(name, value) {
    this.locales[name.toLowerCase()] = value;
  };
  
  /*
   * get locale value 
   * @param string name
   * @return void
   * @access public
   */
  this.get_locale = function(name) {
    if (this.locales[name.toLowerCase()])
      return this.locales[name.toLowerCase()];
    return name;
  };
  
  /* 
   * initialise object
   * @return void
   * @access public
   */
  this.initialise = function() {
    /* check navigator type */
  	this.set_param('navType',  navigator.appName.indexOf("Microsoft")==-1? 'real':'msie');
  	
  	/* set form */
  	this.set_param('form', document.getElementById(this.get_param('form')));
  	
	/* finalise initialisation */
  	this.loaded = true;
  	
  	/* after init actions */
  	this.check_selected404FallBack();
  };
  
  /*
   * check selected 404 Fallback value
   * @return void
   * @access public
   */
  this.check_selected404FallBack = function() {
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
    
  };
}