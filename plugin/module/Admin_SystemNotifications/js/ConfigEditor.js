/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Scripts
 * Creation Date	: Jul 2017
 * Last Modif Date	: Jul 2017
 * 
 * Admin_SystemNotifications configuration editor script
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
  
    this.set_param('form', document.getElementById(this.get_param('form')));
  	
	/* finalise initialisation */
    this.loaded = true;
  };
  
  /*
   * on authentication select change handler
   * @return void
   * @access private
   */
  this.onAuthenticationChange = function() {
    value = this.get_param('form').access_authentication.options[this.get_param('form').access_authentication.options.selectedIndex].value;
    if (value == 1)
      document.getElementById('accessCredentials').style.display = 'block';
    else
      document.getElementById('accessCredentials').style.display = 'none';
    
    if (value == 2)
      document.getElementById('accessAddressIP').style.display = 'block';
    else
      document.getElementById('accessAddressIP').style.display = 'none';
  };
  
  /*
   * on module mode select change handler
   * @return void
   * @access private
   */
  this.onModuleModeChange = function() {
    value = this.get_param('form').module_mode.options[this.get_param('form').module_mode.options.selectedIndex].value;
    if (value == 1)
      document.getElementById('moduleCheckDelay').style.display = 'block';
    else
      document.getElementById('moduleCheckDelay').style.display = 'none';
  };
}