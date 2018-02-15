/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Javascripts
 * Creation Date    : Feb 2010
 * Last Modif Date  : Feb 2010
 *
 * ContentAnchorMenu JS Engine
 *
 */

function ContentAnchorMenu(name) {
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
  }
  
  /*
   * return param value from name
   * @param mixed param
   * @return mixed
   * @access public
   */
  this.get_param = function(param) {
    if (this.params[param])
      return this.params[param];
    return false;
  }
  
  /* 
   * initialise object
   * @return void
   * @access public
   */
  this.initialise = function() {
    
    /* initialise navigator type */
  	this.set_param('navType', navigator.appName.indexOf("Microsoft")==-1);
        
    /* get content DOM object */
    if (document.getElementById(this.get_param('content')))
      this.set_param('contentBox', document.getElementById(this.get_param('content')));
    else if (this.get_param('content') == 'body')
      this.set_param('contentBox', document.getElementsByTagName('body')[0]);
    else
      return;
    
    /* get menu DOM object */
    if (document.getElementById(this.name)) {
      this.set_param('menuBox', document.getElementById(this.name));
      this.get_param('menuBox').innerHTML = '';
    } else
      return;
      	
    /* get anchors */
    if (this.get_param('mode') == 'AName')
      this._create_menuForANames();
    else if(this.get_param('mode') == 'objId')
      this._create_menuForObjIds();
    
    /* check hash */
    if ( window.location.hash != '' )  {
      this.go_toAnchor(window.location.hash.substring(1, window.location.hash.length));
    }
  };
  
  /*
   * go to given anchor
   * @param string anchor
   * @access public
   */
  this.go_toAnchor = function(anchor) {
    if (this.get_param('mode') == 'objId')
      document.getElementById(anchor).scrollIntoView();
    else
      document.location.href = document.location.href.split('#')[0] + '#' + anchor;
    if ( document.documentElement.scrollTop)
      document.documentElement.scrollTop = document.documentElement.scrollTop + parseInt(this.get_param('shift'));
    else if ( document.body.scrollTop ) 
      document.body.scrollTop = document.body.scrollTop + parseInt(this.get_param('shift'));
  };
  
  /*
   * search anchors and create menu for a/name mode
   * @return void
   * @access private
   */
  this._create_menuForANames = function() {
    anchors = this.get_param('contentBox').getElementsByTagName('a');
    for(var i = 0; i < anchors.length; i++) {      
      if ( anchors[i].name != undefined && anchors[i].name != ''
	  && anchors[i].title != undefined && anchors[i].title != '') {
	    a = document.createElement('a').cloneNode(true);
	    a.className = this.get_param('linkClass');
	    a.innerHTML = anchors[i].title;
	    
	    if (this.get_param('shift') == 0) {
	      a.href='#'+ anchors[i].name;
	    } else {
	      a.href = 'javascript:void(0);';
	      if (this.get_param('navType')) {
	        a.setAttribute('onclick',  this.name+'.go_toAnchor("'+anchors[i].name+'");');
	      } else {
	        a.onclick = new Function(this.name+'.go_toAnchor("'+anchors[i].name+'");');
	      }
	    }
	    this.get_param('menuBox').appendChild(a);
	    this.get_param('menuBox').style.display = 'block';
      }
    }
  };
  
  /*
   * search anchors and create menu for object id mode
   * Note: do not add object where id starts with "_" chararcter
   * @return void
   * @access private
   */
  this._create_menuForObjIds = function() {
    var anchors = this.get_param('contentBox').getElementsByTagName('*');
    for (var i=0; i< anchors.length; i++) {
      if (anchors[i].id != undefined && anchors[i].id != '' && anchors[i].id.indexOf('_') != 0) {        
        a = document.createElement('a').cloneNode(true);
	    a.className = this.get_param('linkClass');
	    if (anchors[i].title != undefined && anchors[i].title != '')
	      a.innerHTML = anchors[i].title;
	    else
	      a.innerHTML = anchors[i].innerHTML;
	    
	    if (this.get_param('shift') == 0) {
	      a.href='#'+ anchors[i].id;
	    } else {
	      a.href = 'javascript:void(0);';
	      if (this.get_param('navType')) {
	        a.setAttribute('onclick',  this.name+'.go_toAnchor("'+anchors[i].id+'");');
	      } else {
	        a.onclick = new Function(this.name+'.go_toAnchor("'+anchors[i].id+'");');
	      }
	    }
	    this.get_param('menuBox').appendChild(a);
	    this.get_param('menuBox').style.display = 'block';
      }
    }
  };
}
