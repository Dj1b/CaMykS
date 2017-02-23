/*                                                                                
 * CaMykS Engine                                                                  
 * Developed by     : Ideogram Design
 * Author           : JB Lebrun
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Javascripts
 * Creation Date    : Feb 2011                                            
 * Last Modif Date  : Feb 2011                                           
 *                                                                                
 * GenericPageController client engine
 */

function GenericPageController(name) {
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
    if (this.params[param])
      return this.params[param];
    return false;
  };
  
  /*
   * add locale to locale db
   * @param string name
   * @param string value
   * @return void
   * @access public
   */
  this.add_locale = function(name, value) {
  	this.locales[name] = value;
  };
  
  /*
   * get locale to locale db
   * @param string name
   * @return string
   * @access public
   */
  this.get_locale = function(name) {
  	if (this.locales[name])
	  	return this.locales[name];
	 	return name;
  };
  
	/*
	 * initialise object
	 * @return void
	 * @access private
	 */
  this.initialise = function() {
  	/* initialise navigator type */
  	this.set_param('navType', navigator.appName.indexOf("Microsoft")==-1);
  
  	/* initialise DOM objects */
    if(!document.getElementById(this.get_param('parentElmt')))
    	return;
    this.set_param('parentElmtBox', document.getElementById(this.get_param('parentElmt')));
    /* finalise loading */
    this.loaded = true;    
  };
  
  /*
   * update object
   * @param boolean refresh
   * @param integer current
   * @param integer cnt
   * @return void
   * @access private
   */
  this.update = function(refresh, current, cnt) {
  	if (cnt>-1)
  		this.set_param('pageCount', cnt);
  	if (current>-1)
  		this.set_param('pageCurrent', current);
  	if(refresh)
  		this.refresh_display();
  }
  
  /*
   * refresh pager display
   * @return void
   * @access private
   */
 	this.refresh_display = function() {
		/* check if engine is correctly loaded */
 		if (this.loaded == false)
 			return;
 			
 	 	/* empty parent DOM element */
 	 	this.get_param('parentElmtBox').innerHTML = '';
 	 	
 	 	/* rebuild pager */
 	 	if (this.get_param('hideEmpty') == 1 && this.get_param('pageCount') < 2) {
 	 		/* create empty pager */
 	 		d = document.createElement('div');
 	 		d.className = 'genericPageEmptyController';
 	 		d.innerHTML = '&nbsp;';
 	 		this.get_param('parentElmtBox').appendChild(d);
 	 		return;
 	 	}
 	 	
 	 	/* create container div */
 	 	d = document.createElement('div');
 	 	d.className = 'genericPageController';

		/* create container table */
		t = document.createElement('table');
		t.className = 'gpcBox';
		t.setAttribute('cellspacing', 0);
		t.setAttribute('cellpadding', 0);
		d.appendChild(t);
		
		/* create table body */
		b = document.createElement('tbody');
		t.appendChild(b);
		
		/* create table line */
		l = document.createElement('tr');
		b.appendChild(l);
	        

		/* check for left button display */
		if (this.get_param('displayBttns') == 1) {
			/* create bttn cell */
			c = document.createElement('td');
			c.className = 'gpcButton';
			l.appendChild(c);
			
			/* create button */
			img = document.createElement('img');
			if (this.get_param('pageCurrent') == 0) {
				img.src = this.get_param('bttnEmpty');
			} else {
				img.src = this.get_param('bttnLeft');
				if (this.get_param('navType')) {
  				img.setAttribute('onclick', this.name+'.select_previousPage();');
  				img.setAttribute('onmouseover', 'this.src="'+this.get_param('bttnLeftR')+'";');
  				img.setAttribute('onmouseout', 'this.src="'+this.get_param('bttnLeft')+'";');
				}	else {
  				img.onclick = new Function(this.name+'.select_previousPage();');
  				img.onmouseover = new Function('this.src="'+this.get_param('bttnLeftR')+'";');
  				img.onmouseout = new Function('this.src="'+this.get_param('bttnLeft')+'";');
  			}
			}
			c.appendChild(img);
		}

		if (this.get_param('pageCount') <= 5) {
			/* display less than 5 pages controller */
			for(var i=0; i<this.get_param('pageCount'); i++) {
				c = document.createElement('td');
				c.className = 'gpc'+(i == this.get_param('pageCount')-1 ? 'R':'')+'Page';
				l.appendChild(c);
				
				a = document.createElement('a');
				a.className = 'gpc'+(i == this.get_param('pageCurrent') ? 'Selected':'Link');
				a.innerHTML = ' '+(i+1)+' ';
				a.href = 'javascript:'+this.name + '.select_page('+i+');';
				c.appendChild(a);
			}
		} else if (this.get_param('pageCurrent') < 3 ) {
			/* display controller with current page in the 3 firsts pages */
      for ( i=0; i<4; i++ ) {
      	/* display left cells */
      	c = document.createElement('td');
      	c.className = 'gpcLPage';
      	l.appendChild(c);
      	
      	a = document.createElement('a');
				a.className = 'gpc'+(i == this.get_param('pageCurrent') ? 'Selected':'Link');
				a.innerHTML = ' '+(i+1)+' ';
				a.href = 'javascript:'+this.name + '.select_page('+i+');';
				c.appendChild(a);
			}
			
			/* display spacer */
			c = document.createElement('td');
     	c.className = 'gpcSpacer';
     	c.innerHTML = '...';
      l.appendChild(c);
      
      /* display right cell */
      c = document.createElement('td');
      c.className = 'gpcRPage';
      l.appendChild(c);
      	
      a = document.createElement('a');
			a.className = 'gpcLink';
			a.innerHTML = this.get_param('pageCount');
			a.href = 'javascript:'+this.name + '.select_page('+(this.get_param('pageCount')-1)+');';
			c.appendChild(a);
		} else if ( this.get_param('pageCurrent') >= this.get_param('pageCount') - 3 ) {
			/* display left cell */
      c = document.createElement('td');
      c.className = 'gpcPage';
      l.appendChild(c);
      	
      a = document.createElement('a');
			a.className = 'gpcLink';
			a.innerHTML = ' 1 ';
			a.href = 'javascript:'+this.name + '.select_page(0);';
			c.appendChild(a);
			
			/* display spacer */
			c = document.createElement('td');
     	c.className = 'gpcSpacer';
     	c.innerHTML = '...';
      l.appendChild(c);
        
      for ( i = this.get_param('pageCount')-4; i < this.get_param('pageCount')-1; i++ ) {
      	c = document.createElement('td');
      	c.className = 'gpcPage';
      	l.appendChild(c);
      	
      	a = document.createElement('a');
				a.className = 'gpc'+(i == this.get_param('pageCurrent') ? 'Selected':'Link');
				a.innerHTML = ' '+(i+1)+' ';
				a.href = 'javascript:'+this.name + '.select_page('+i+');';
				c.appendChild(a);
      }
      
      /* display right cell */
      c = document.createElement('td');
      c.className = 'gpcRPage';
      l.appendChild(c);
      	
      a = document.createElement('a');
			a.className = 'gpc'+(this.get_param('pageCount')-1 == this.get_param('pageCurrent') ? 'Selected':'Link');
			a.innerHTML = this.get_param('pageCount');
			a.href = 'javascript:'+this.name + '.select_page('+(this.get_param('pageCount')-1)+');';
			c.appendChild(a);
		} else {
			/* display left cell */
      c = document.createElement('td');
      c.className = 'gpcPage';
      l.appendChild(c);
      	
      a = document.createElement('a');
			a.className = 'gpcLink';
			a.innerHTML = ' 1 ';
			a.href = 'javascript:'+this.name + '.select_page(0);';
			c.appendChild(a);
			
			/* display spacer */
			c = document.createElement('td');
     	c.className = 'gpcLPage';
     	c.innerHTML = '...';
      l.appendChild(c);
		
			/* display previous cells */
			for ( i=this.get_param('pageCurrent')-1; i<this.get_param('pageCurrent'); i++ ) {
				c = document.createElement('td');
      	c.className = 'gpcPage';
      	l.appendChild(c);
      	
      	a = document.createElement('a');
				a.className = 'gpcLink';
				a.innerHTML = ' '+(i+1)+' ';
				a.href = 'javascript:'+this.name + '.select_page('+i+');';
				c.appendChild(a);
      }
      
      /* display current cell */
      c = document.createElement('td');
      c.className = 'gpcPage';
      l.appendChild(c);
      	
      a = document.createElement('a');
			a.className = 'gpcSelected';
			a.innerHTML = (this.get_param('pageCurrent')+1);
			a.href = 'javascript:'+this.name + '.select_page('+this.get_param('pageCurrent')+');';
			c.appendChild(a);
      
      /* display next cells */
      for (i = this.get_param('pageCurrent')+1; i < this.get_param('pageCurrent')+2; i++) {
      	c = document.createElement('td');
      	c.className = 'gpcPage';
      	l.appendChild(c);
      	
      	a = document.createElement('a');
				a.className = 'gpcLink';
				a.innerHTML = ' '+(i+1)+' ';
				a.href = 'javascript:'+this.name + '.select_page('+i+');';
				c.appendChild(a);
      }
      
      /* display spacer */
			c = document.createElement('td');
     	c.className = 'gpcSpacer';
     	c.innerHTML = '...';
      l.appendChild(c);
      
      /* display right cell */
      c = document.createElement('td');
      c.className = 'gpcRPage';
      l.appendChild(c);
      	
      a = document.createElement('a');
			a.className = 'gpcLink';
			a.innerHTML = this.get_param('pageCount');
			a.href = 'javascript:'+this.name + '.select_page('+(this.get_param('pageCount')-1)+');';
			c.appendChild(a);
    }
    
    /* check for left button display */
    if (this.get_param('displayBttns') == 1) {
			/* create bttn cell */
			c = document.createElement('td');
			c.className = 'gpcButton';
			l.appendChild(c);
			
			/* create button */
			img = document.createElement('img');
			if (this.get_param('pageCurrent') == this.get_param('pageCount')-1) {
				img.src = this.get_param('bttnEmpty');
			} else {
				img.src = this.get_param('bttnRight');
				if (this.get_param('navType')) {
  				img.setAttribute('onclick', this.name+'.select_nextPage();');
  				img.setAttribute('onmouseover', 'this.src="'+this.get_param('bttnRightR')+'";');
  				img.setAttribute('onmouseout', 'this.src="'+this.get_param('bttnRight')+'";');
				}	else {
  				img.onclick = new Function(this.name+'.select_nextPage();');
  				img.onmouseover = new Function('this.src="'+this.get_param('bttnRightR')+'";');
  				img.onmouseout = new Function('this.src="'+this.get_param('bttnRight')+'";');
  			}
			}
			c.appendChild(img);
		}
		
		/* add controller to parent dom element */
		this.get_param('parentElmtBox').appendChild(d);
 	};
 	
 	/* 
 	 * select next page 
 	 * @return void
 	 * @access private
 	 */
 	this.select_nextPage = function() {
 		if ( this.get_param('pageCurrent') < this.get_param('pageCount')-1)
 			this.select_page(this.get_param('pageCurrent')+1);
 	};
 	
 	/* 
 	 * select previous page 
 	 * @return void
 	 * @access private
 	 */
 	this.select_previousPage = function() {
 		if ( this.get_param('pageCurrent') > 0 )
 			this.select_page(this.get_param('pageCurrent')-1);
 	};
 	
 	/* 
 	 * select page
 	 * @param page
 	 * @return void
 	 * @access private
 	 */
 	this.select_page = function(page) {
 		this.set_param('pageCurrent', page);
 		this.refresh_display();
 		if ( this.get_param('link') != '') {
 			eval(this.get_param('link').replace(/_page_/, page));
 		}
 	};
}
