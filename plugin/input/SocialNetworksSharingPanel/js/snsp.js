/**
 * @brief SocialNetworksSharingPanel Input scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/SocialNetworksSharingPanel/js/snsp.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Nov 2009
 * @date Modification: Jul 2018
 * @copyright 2009 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

function SNSPanel(name) {
  this.name = name;
  this.opened = 0;
  this.params = new Array();

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
   * initialise object
   * @return void
   * @access public
   */
  this.initialise = function() {
    if (this.get_param('fblike_allowed') == 1)
      this._load_facebookEngine();

    if (this.get_param('gplus_allowed') == 1)
    	this._load_googlePlusEngine();
  };

  /*
   */
  this.open_panel = function(panelid) {
    if (this.opened > 0)
      this.close_panel(this.opened);

    if (document.getElementById('snsPanel'+panelid)) {
      panel = document.getElementById('snsPanel'+panelid);
      panel.style.display='block';

      if ( navigator.appName.indexOf("Microsoft")!=-1 ) {
	panel.style.top = ((document.body.offsetHeight-panel.offsetHeight)/2+document.body.scrollTop)+'px';
	panel.style.left = ((document.body.offsetWidth-panel.offsetWidth)/2+document.body.scrollLeft)+'px';
      } else {
	panel.style.top = ((window.innerHeight-panel.offsetHeight)/2+document.body.scrollTop)+'px';
	panel.style.left = ((window.innerWidth-panel.offsetWidth)/2+document.body.scrollLeft)+'px';
      }
      this.opened = panelid;
    }
  };

  this.close_panel = function(panelid) {
    if (document.getElementById('snsPanel'+panelid)) {
      document.getElementById('snsPanel'+panelid).style.display = 'none';
      this.opened = 0;
    }
  };

  /*
   * load facebook engine
   * @return void
   * @access private
   */
  this._load_facebookEngine = function() {
    window.fbAsyncInit = function() {
      FB.init({appId: '', status: true, cookie: true,
	    xfbml: true});
    };
    (function() {
      var e = document.createElement('script'); e.async = true;
    e.src = document.location.protocol +
      '//connect.facebook.net/'+
      snsp.get_param('fblike_language')+
      '/all.js';
    document.getElementById('fb-root').appendChild(e);
    }());
  };

  /*
   * load google engine
   * @return void
   * @access private
   */
  this._load_googlePlusEngine = function() {
	var po = document.createElement('script');
	po.type = 'text/javascript';
	po.async = true;
	po.src = 'https://apis.google.com/js/plusone.js';
	var s = document.getElementsByTagName('script')[0];
	s.parentNode.insertBefore(po, s);
	window.___gcfg = {
		lang: this.get_param('gplus_language')
	};
  };
}
