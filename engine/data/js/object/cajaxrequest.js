/**
 * @brief Client side scripts to manage ajax requests.
 * @details Engine / Javascript object library
 * @file engine/data/js/object/cajaxrequest.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Dec 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* 
 * Class constructor.
 * @param string name
 */
function CAjaxRequest(name) {
  /* vars */
  this._name = name;
  this._requestUrl = null;
  this._requestMethod = null;
  this._requestObject = null;
  this._resultValue = null;
  this._resultStatus = 'idle';
  this._resultHandler = null;
  this._resultErrorHandler = null;  
  this._browserType = null;
  
  /* methods */
  
  /*
   * initialise connection object and other values
   */
  this._initialise = function( requestUrl, requestMethod, resultHandler, resultMethod, resultErrorHandler ) {
    this._getBrowserType();
    /* set engine values */
    this._requestUrl = requestUrl;
    this._requestMethod = requestMethod;
    this._resultHandler = resultHandler;
    if ( resultErrorHandler ) { this._resultErrorHandler = resultErrorHandler }
    if ( resultMethod ) { this._resultMethod = resultMethod; } else { this._resultMethod = 'txt'; }
    this._updateRequestObject();
    
    /* add onreadystate change handler */
    this._setReceiverHandler();
  };

  this._getBrowserType = function() {
    nav = navigator.userAgent.toLowerCase();
    app = navigator.appVersion.toLowerCase();
    
    /* check for browser version */
    if ( nav.indexOf('webkit') > -1 || nav.indexOf('opera') > -1 ) {
      /* safari based browsers and opera : full support of ajax engine */
      this._browserType = 'full';
    } else if ( nav.indexOf('msie') > -1 && app.indexOf("MSIE 10") == -1) {
      /* internet explorer < 9 : no support of ajax engine */
      this._browserType = 'none';
    } else {
      /* mozilla browsers / IE 10 : limited support of ajax engine */
      this._browserType = 'limited';
    }
  }

  this._updateRequestObject = function() {   
    /* build connection request object */
    if (this._browserType != 'none' ) {
      /* real browsers */
      this._requestObject = new XMLHttpRequest();
      if ( this.resultMethod == 'xml' ) { this._requestObject.overrideMimeType('text/xml'); }
    } else if (window.ActiveXObject) {
      /* IE Hack */
      try {
        this._requestObject = new ActiveXObject("Msxml2.XMLHTTP");
      } catch ( _e ) {
        try {
          this._requestObject = new ActiveXObject("Microsoft.XMLHTTP");
        } catch ( __e ) {
          /* unsupported browser */
          this._throwError('unsupported_browser');
          return;
        }
      }
    } else {
      /* unsupported browser */
      this._throwError('unsupported_browser');
      return;
    }
  }
    
  this._setReceiverHandler = function() {
    /* hack for FF and IE that point 'this' ref on the function */
    eval('this._requestObject.onreadystatechange = function( ) {' + this._name + '._onreadystatechange();}'); 
  }
  
  this._setProgressHandler = function(handler) {
    if ( this._browserType != 'none' ) {
      this._requestObject.upload.addEventListener('progress', function(e) { handler(e.loaded, e.total); });
    }
  }
    
  this._onreadystatechange = function( ) {
    this._resultStatus = this._requestObject.readyState;
    /* answer received  */
    if( this._requestObject.readyState == 4 ) {
      this._resultStatus = 'idle';
    if( this._requestObject.status == 200 ) {
	  if ( this._resultMethod == 'txt' ) {
	    this._receive ( this._requestObject.responseText );
	  } else {
	    this._receive ( this._requestObject.responseXML );
	  }
      } else {
	    this._throwError('http_error_'+this._requestObject.status);
      } 
    }
  };
  
  /*
   * Execute request
   */
  this._execute = function( newRequestUrl, newResultHandler, newParams ) {  
    /* update values if needed */
    if ( newRequestUrl ) {
      _rurl = newRequestUrl;
    } else {
      _rurl = this._requestUrl;
    }

    /* check params */
    if ( newParams )
      _params = newParams;
    else
      _params = null;

    /* compatibility hack */
    if ( this._browserType == 'limited' ) {
      this._setReceiverHandler();
    } else if ( this._browserType == 'none' ) {
      this._updateRequestObject();
      this._setReceiverHandler();
    }

    /* update request object status */
    this._resultStatus = 'request';
    
    /* execute request */
    this._requestObject.open(this._requestMethod, _rurl, true);
    if ( this._requestMethod.toUpperCase() == 'POST' && typeof(_params) == 'string' ) {
      this._requestObject.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      if (_params != null)
        this._requestObject.setRequestHeader("Content-length", _params.length);
      this._requestObject.setRequestHeader("Connection", "close");
    }
    this._requestObject.send(_params);
  };
  
  /*
   * Receive request result
   */
  this._receive = function ( result ) {
    this._resultValue = result;
    if ( typeof(this._resultHandler) == 'string' ) {
      eval(this._resultHandler+'( result );');
    } else if ( typeof(this._resultHandler) == 'function' ) {
      this._resultHandler(result);
    }
  };
  
  /*
   * ajax request error management
   */
  this._throwError = function ( error_type ) {
    /* throm error to parent object handler */
    if ( typeof(this._resultErrorHandler) == 'string' ) {
      return eval(this._resultErrorHandler+'( error_type );');
    } else if ( typeof(this._resulErrortHandler) == 'function' ) {
      return this._resultErrorHandler(error_type);
    }

    /* internal error management */
    switch ( error_type ) {
    case 'unsupported_browser':
      alert('Engine Error : Your internet browser doesn\'t support AJAX.');
      break;
    case 'http_error_0':
      alert('Request Error : URL seem to be empty.');
      break;
    default :
      alert('An error has occured : ' + error_type);
      break;
    }
  };
}
