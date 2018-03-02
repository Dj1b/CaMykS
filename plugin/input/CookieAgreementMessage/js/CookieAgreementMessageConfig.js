/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	        : CaMykS Team
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Javascripts
 * Creation Date    : Feb 2018
 * Last Modif Date  : Feb 2018
 *
 * CookieAgreementMessage config JS Engine
 *
 */

var CookieAgreementMessageConfig = {
  params: {},

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
    if (value == undefined && this.params[param] || this.params[param] === 0)
      return this.params[param]
    return false;
  },
  
  /* 
   * initialise object
   * @return void
   * @access public
   */
  initialise: function() {
    this.set_param('form', document.getElementById(this.get_param('form')));
  },
  
  /*
   * handle onclick event on aboutCookie radios
   * @param string value
   * @return void
   * @access public
   */
  onAboutCookieChange: function(value) {
    console.log ('value:' + value);
    if (value == '')
      document.getElementById('aboutCookiePersValue').disabled = 'disabled';
    else
      document.getElementById('aboutCookiePersValue').disabled = false;
  },
}
