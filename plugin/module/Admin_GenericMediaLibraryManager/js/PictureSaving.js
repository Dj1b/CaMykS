/**
 * @brief Admin_GenericMediaLibraryManager module picture saving script
 * @details Plugin / Module Scripts
 * @author CaMykS Team
 * @version 1.0.1
 * @date Creation: Jun 2015
 * @date Modification: Jan 2019
 * @copyright 2015 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
function PictureSaving(name) {
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

  	/* save form object */
  	this.set_param('adminMessage', document.getElementById('adminMessage'));

  	/* init ajax request engine */
    this.loader = new CAjaxRequest(this.name+'.loader');
    this.loader._initialise(null, 'POST', this.name+'._receiveRequestResult', 'xml', this.name+'._receiveRequestError');

  	/* initialise request queue */
  	this.requestQueue = new Array();

    /* send main picture saving request */
    this._executeRequest(this.get_param('requestBaseURL')+'&mode=optimisePictureImage&picture_id='+this.get_param('pictureId'));
  };

  /*
   * quit
   * @return void
   * @access public
   */
  this.quit = function() {
    document.location.href = this.get_param('backURL');
  }

  /* request methods */

  /*
   * execute request
   * @param string url
   * @param boolean wait
   * @return void
   * @access private
   */
  this._executeRequest = function ( url, params, wait ) {
    /* manage request queue for those browsers */
    if ( this.loader._resultStatus != 'idle' ) {
    	if (wait) this.requestQueue.push( new Array(url, params) );
      return;
    }
    this.loader._execute(url, null, params);
  };

  /*
   * receive request result
   * @param xml result
   * @return void
   * @access private
   */
  this._receiveRequestResult = function(result) {
 	/* decompile result */
	result = xml_serializeObject(result);

	/* check result : if result is undefined, what to do ? */
    if ( result == null )
      return;

	/* get errors or messages */
    if ( result['status'] == 'failure' )
      alert(result['message']);

    /* check action result */
    switch (result['action']) {
      case 'optimisePictureImage':
        this.get_param('adminMessage').innerHTML += '<br />'+this.get_locale('picture_saved');
        /* send thumb saving request */
        this._executeRequest(this.get_param('requestBaseURL')+'&mode=optimisePictureThumb&picture_id='+this.get_param('pictureId'));
    	break;
      case 'optimisePictureThumb':
        this.get_param('adminMessage').innerHTML += '<br />'+this.get_locale('thumb_saved');
        /* close saving interface */
        setTimeout(this.name+'.quit();', this.get_param('quitDelay')*1000);
        break;
    }

	/* try to reduce request queue */
    if ( this.requestQueue.length > 0 ) {
      request =  this.requestQueue.shift();
      this._executeRequest(request[0], request[1], true);
    }
  };

  /*
   * receive request error
   * @param xml result
   * @return void
   * @access private
   */
  this._receiveRequestError = function() {
	/* define what to do */
  };
}
