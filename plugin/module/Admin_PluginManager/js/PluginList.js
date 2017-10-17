/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Script
 * Creation Date    : Oct 2017
 * Last Modif Date	: Oct 2017
 * 
 * Admin_PluginManager plugin list scripts
 */
 
function PluginList(name) {
  this.name = name;
  this.params = {};
  this.locales = {};
  this.loaded = false;
  
  /* pre-define values */
  this.params['actionURLs'] = new Array();

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
    if (value != undefined)
      if (this.params[param][value])
        return this.params[param][value];
    if (this.params[param])
      return this.params[param];
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
	/* finalise initialisation */
    this.loaded = true;
  };
  
  /*
   * attach and open action menu to selected plugin
   * @param integer plugin
   * @return void
   * @access public
   */
  this.show_menu = function(type, plugin) {
    this.set_param('selectedPlugin', plugin);
    globalCMenu.updateParent(type+'ActionMenu', 'button'+plugin );
  	globalCMenu.select(type+'ActionMenu');
  };
  
  /*
   * execute selected action to selected plugin
   * @return void
   * @access public
   */
  this.execute_action = function(action) {
    action = this.get_param('actionURLs', action).replace('__PNAME__', this.get_param('selectedPlugin'));
    document.location.href = action;
  };
}