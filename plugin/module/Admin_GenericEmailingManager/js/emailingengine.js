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

function EmailingEngine(name) {
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
    
    /* initialise loader */
    this.loader = new CAjaxRequest(this.name+'.loader');
    this.loader._initialise(null, 'POST', this.name+'._receiveStepResult', 'xml', this.name+'._receiveError');

		/* get content box */
		if(!document.getElementById('updatecontentbox'))
			return;
    this.set_param('contentBox', document.getElementById('updatecontentbox'));
    
    /* initialise current step */
    this.set_param('step', 0);
    
    /* check interval */
    if (this.get_param('sendingInterval') < 100)
      this.set_param('sendingInterval', 100);
    
    
    /* finalise engine initialisation */
    this.loaded = true;
   
    /* check what to do */
    if (this.get_param('startAt') == -1) {
      this.import_index = 0;
      this.import_count = 0;
      this._executeStep1();
    } else if (this.get_param('startAt') > this.get_param('emailCount')) {
    	this.import_index = this.get_param('startAt');
      this.import_count = this.get_param('emailCount');
    	this._executeStep3();
    } else {
      this.import_index = this.get_param('startAt');
      this.import_count = this.get_param('emailCount');
      this._initLoopStep();
    }
  };
  
  /*
   * initialise generator continuation
   * @return void
   * @access private
   */
  this._initLoopStep = function() {
    div = document.createElement('div').cloneNode(true);
    div.className = 'eContent2';
    div.innerHTML = this.get_locale('continue_sending');
    this.get_param('contentBox').appendChild (div);
    this._executeStep2();
  };
  
  /*
   * initialise step 1
   * @return void
   * @access private
   */
  this._executeStep1 = function() {
    div = document.createElement('div').cloneNode(true);
    div.className = 'eContent2';
    div.innerHTML = this.get_locale('initialise_emailing');
    div.id = 'InitBox';
    this.get_param('contentBox').appendChild (div);
    //alert(this.get_param('requestBaseURL')+'&mode=send_emailingInitialise');
    this.loader._execute(this.get_param('requestBaseURL')+'&mode=send_emailingInitialise');
  };
  
  /*
   * initialise step 2
   * @return void
   * @access private
   */
  this._executeStep2 = function() {
    div = document.createElement('div').cloneNode(true);
    div.className = 'eContent2';
    div.innerHTML = this.get_locale('send_email');
    div.id = 'BuildBox'+this.import_index;
    this.get_param('contentBox').appendChild (div);
    //alert(this.get_param('requestBaseURL')+'&mode=send_emailingExecute&obj='+this.import_index);
    this.loader._execute(this.get_param('requestBaseURL')+'&mode=send_emailingExecute&obj='+this.import_index);
  };
  
  /*
   * execute step 3
   * @return void
   * @access private
   */
  this._executeStep3 = function() {
    div = document.createElement('div').cloneNode(true);
    div.className = 'eContent2';
    div.id = 'step3';
    div.innerHTML = this.get_locale('finalise_emailing');
    this.get_param('contentBox').appendChild (div);
    //alert(this.get_param('requestBaseURL')+'&mode=send_emailingFinalise');
    this.loader._execute(this.get_param('requestBaseURL')+'&mode=send_emailingFinalise');
  };

  /*
   * http request reception
   * @return void
   * @access private
   */
  this._receiveStepResult = function( result ) {
     result = xml_serializeObject( result );
          
     if ( result == null )
        return this._executeErrorReception();
     
     switch ( result['step']) {
        case 1 : 
            this._executeStep1Result(result);
            break;
        case 2 :
            this._executeStep2Result(result);
            break;
        case 3 :
            this._executeStep3Result(result);
            break;
     }
     document.getElementById('updatebox').scrollTop = document.getElementById('updatecontentbox').offsetHeight;
  };
  
  /*
   * http request failed reception
   * @return void
   * @access private
   */
  this._receiveError = function (result) {
    return;
  };
  
  /*
   * finalise step 1
   * @return void
   * @access private
   */
  this._executeStep1Result = function ( result ) {
  
    document.getElementById('InitBox').innerHTML = result['message'];
    
    div = document.createElement('div').cloneNode(true);
    div.className = 'eContent4';
    div.innerHTML = result['message2'];
    this.get_param('contentBox').appendChild (div);
  
    if ( result['result'] == 'success' ) {
      this.import_count = parseInt(result['count']);
      setTimeout(this._executeStep2(), 4);
    }
  };
  
  /*
   * finalise step 2
   * @return void
   * @access private
   */
  this._executeStep2Result = function ( result ) {
    if ( result['result'] == 'success' ) {
      document.getElementById('BuildBox'+this.import_index).innerHTML = result['message'];
    } else {
      document.getElementById('BuildBox'+this.import_index).innerHTML = result['message'];
      document.getElementById('BuildBox'+this.import_index).style.color = '#CC3333';
      if ( result['error'] && result['error'] != '') {
        div = document.createElement('div').cloneNode(true);
        div.className = 'eContent4';
        div.innerHTML = result['error'];
        this.get_param('contentBox').appendChild (div);
      }
    }
    return this._go2NextObject();
  };
  
  /*
   * finalise step 3
   * @return void
   * @access private
   */
  this._executeStep3Result = function (result) {
    
    document.getElementById('step3').innerHTML = result['message'];
    if ( result['message2'] != null ) {
      div = document.createElement('div').cloneNode(true);
      div.className = 'eContent4';
      div.innerHTML = result['message2'];
      this.get_param('contentBox').appendChild (div);
    }
  };
  
  /*
   * continue loop to next object
   * @return void
   * @access private
   */
  this._go2NextObject = function() {
    if (++this.import_index >= this.import_count )
      return this._executeStep3();
    return setTimeout(this.name+'._executeStep2();', this.get_param('sendingInterval'));
  };
  
  this._executeErrorReception = function ( ) {
    div = document.createElement('div').cloneNode(true);
    div.className = 'eContent2';
    div.innerHTML = 'Une erreur est survenue lors de la r&eacute;ception des donn&eacute;es.';
    this.get_param('contentBox').appendChild (div);
  };
}