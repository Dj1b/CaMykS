/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	        : CaMykS Team
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Javascripts
 * Creation Date    : May 2017
 * Last Modif Date  : May 2017
 *
 * CookieAgreementMessage JS Engine
 *
 */

function CookieAgreementMessage(name) {
  this.name = name;
  this.loaded = false;
  this.params = {};

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
    if (value == undefined && this.params[param] || this.params[param] === 0)
      return this.params[param]
    return false;
  };
  
  /* 
   * initialise object
   * @return void
   * @access public
   */
  this.initialise = function() {
    
  };
  
  /*
   * go to given anchor
   * @param string anchor
   * @access public
   */
  this.accept_cookies = function() {
    cookie_save('cookieAccepted', 1, this.get_param('cookieTTL'));
    document.getElementById('cookieAgreementMessage').style.display = 'none';
  };
}
