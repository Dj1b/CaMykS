/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type      : Engine / JS Library
 * Create Date		: Sep 2011
 * Last Modif Date	: Sep 2011
 * 
 * Define generic CaMykS library to be herited
 */

var CLibrary = Class.create({ 
	name : arguments[0],
	params : {},
	locales : {},
	loaded : false,
	
	/*
   * add parameter
   * @param string name
   * @param mixed value
   * @return void
   * @access public
   */
  set_param : function(param, value, subvalue) {
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
  get_param : function(param, value) {
    if (value != undefined)
      if (this.params[param][value])
        return this.params[param][value];
    if (this.params[param])
      return this.params[param];
    return false;
  },
  
  /*
   * set locale value 
   * @param string name
   * @param string value
   * @return void
   * @access public
   */
  set_locale : function(name, value) {
    this.locales[name.toLowerCase()] = value;
  },
  
  /*
   * get locale value 
   * @param string name
   * @return void
   * @access public
   */
  get_locale : function(name) {
    if (this.locales[name.toLowerCase()])
      return this.locales[name.toLowerCase()];
    return name;
  },

  /*
   * initialise object
   * @return void
   * @access public
   */
  initialise : function() {
  	this.loaded = true;
  }
});