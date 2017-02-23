/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Javascript
 * Creation Date	: Dec 2012
 * Last Modif Date  : Dec 2012
 * 
 * Emailing javascript object
 * step 1 : build email list
 * step 2 : send email
 * step 3 : finalise sending
 */

function ImportContactConfiguration(name) {
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
    if (value != undefined)
      if (this.params[param][value])
        return this.params[param][value];
		
    if (this.params[param] != undefined)
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
   * @param option args
   * @return void
   * @access public
   */
  this.get_locale = function(name) {
  	name = name.toLowerCase();
    if (!this.locales[name])
    	return name;
    
    locale = this.locales[name];
    for(i=1; i<arguments.length; i++)
    	locale = locale.replace('__$'+i+'__', arguments[i]);
    
		return locale;
  };

  /* 
   * initialise object
   * @return void
   * @access public
   */
  this.initialise = function() {
    this.set_param('form', document.getElementById(this.get_param('form')));
    
  };
  
  /*
   * show parameters for selected field
   * @param integer line
   * @return void
   * @access public
   */
  this.show_fieldParameters = function(line) {
    fieldSelect = eval('this.get_param("form").col'+line+'_field');
    field = fieldSelect.options[fieldSelect.options.selectedIndex].value;
    
    for (i in fieldSelect.options) {
        if ((f = fieldSelect.options[i].value) == field) {           
          if (document.getElementById('col'+line+'_'+f+'Params'))
            document.getElementById('col'+line+'_'+f+'Params').style.display='block';
        } else {
          if (document.getElementById('col'+line+'_'+f+'Params'))
            document.getElementById('col'+line+'_'+f+'Params').style.display='none';
        }
    }
  };
}