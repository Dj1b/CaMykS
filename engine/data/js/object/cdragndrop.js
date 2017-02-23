/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type      : Engine / JS Library
 * Creation Date    : Sep 2013
 * Last Modif Date  : Sep 2013
 *                                                                                
 * Drag'n'drop engine
 */

function CDragNDrop(name) {
  this.name = name;
  this.params = {};
  this.params['elements'] = {};
  
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
   * initialise object
   * @return void
   * @access private
   */
  this.initialise = function() {
    /* initialise default params */
    this.set_param('elementCount', 0);
    this.set_param('currentElement', -1);
    
    window._CDragNDropEngine = this;
    
    /* set object as loaded */
    this.loaded = true;
  };
  
  /* elements management methods */
  
  /*
   * enable drag'n'drop for element
   * @param array params
   * @return void
   * @access public
   */
  this.enable_forElement = function(params) {
    /* default params list */
    dparams = {'element':null,
        'enableLimits':0,
        'limitXMin':0,
        'limitXMax':0,
        'limitYMin':0,
        'limitYMax':0,
        'onStartDragAction':null,
        'onDragAction':null,
        'onDropAction':null,
        'dragClassName':''
    };
    
    /* merge params */
    for (i in params)
      dparams[i] = params[i];
    

    /* set element to engine list */
    this.set_param('elements', dparams['element'], dparams);
    
    /* enable drag'n drop engine for element */
    __cDragNDrop.init_element(dparams['element']);
  };
  
  /*
   * disable drag'n'drop for element
   * @param mixed elmnt
   * @return void
   * @access public
   */
  this.disable_forElement = function(elmnt) {
    /* search element */
    object = null;
    if (this.get_param('elements', elmnt)) {
      element = this.get_param('elements', elmnt);
    } else {
      return;
    }
  
    /* remove events */
    //CDragNDrop_removeEvent(object, 'onmousedown', eval(this.name+'.start_elementDrag'+i));
    
    /* clean object list */
    this.set_param('elements', element, null);
  };
}

/*
 * attach event to an HTMLElement
 * @param HTMLElement obj
 * @param Event evt
 * @param Function fn
 * @return void
 * @access public
 */
function CDragNDrop_addEvent(obj,evt,fn) {
  if (obj.addEventListener)
    obj.addEventListener(evt,fn,false);
  else if (obj.attachEvent)
    obj.attachEvent('on'+evt,fn);
}

/*
 * remove event to an HTMLElement
 * @param HTMLElement obj
 * @param Event evt
 * @param Function fn
 * @return void
 * @access public
 */
function CDragNDrop_removeEvent(obj,evt,fn) {
  if (obj.removeEventListener)
    obj.removeEventListener(evt,fn,false);
  else if (obj.detachEvent)
    obj.detachEvent('on'+evt,fn);
}

/*
 * _cDragNDrop object
 */
__cDragNDrop = {
	initialMouseX: undefined,
	initialMouseY: undefined,
	startX: undefined,
	startY: undefined,
	draggedObject: undefined,
	
	/* element initialisation method */
	init_element: function (element) {
		if (typeof element == 'string')
	        element = document.getElementById(element);
		element.onmousedown = __cDragNDrop.startDrag_element;
	},
	
	/* element start dragging method */
	startDrag_element: function (e) {
	    /* update dragged object */
		if (__cDragNDrop.draggedObject)
			__cDragNDrop.releaseElement();
		__cDragNDrop.startX = this.offsetLeft;
		__cDragNDrop.startY = this.offsetTop;
		__cDragNDrop.draggedObject = this;
	    
	    /* search element */
  	    engine = window._CDragNDropEngine;
        if ( engine.get_param('elements', __cDragNDrop.draggedObject.id)) {
            element = engine.get_param('elements', __cDragNDrop.draggedObject.id);
        } else {
          return;
        }
		
		/* update dragged object styles */
        if (element['dragClassName'] != '')
            this.className += ' '+element['dragClassName'];

        /* check event values */		
		var evt = e || window.event;
		__cDragNDrop.initialMouseX = evt.clientX;
		__cDragNDrop.initialMouseY = evt.clientY;
		CDragNDrop_addEvent(document,'mousemove',__cDragNDrop.drag_element);
		CDragNDrop_addEvent(document,'mouseup',__cDragNDrop.release_element);
		
		/* check for post start drag action to execute */
	    if (element['onStartDragAction'] != '')
	      eval (element['onStartDragAction']);
	  
	    /* return false */
		return false;
	},
	
	/* element dragging method */
	drag_element: function (e) {
	    /* update element position from mouse event values */
		var evt = e || window.event;
		var dX = evt.clientX - __cDragNDrop.initialMouseX;
		var dY = evt.clientY - __cDragNDrop.initialMouseY;
		__cDragNDrop.set_position(dX,dY);
		
		/* search element */
  	    engine = window._CDragNDropEngine;
        if ( engine.get_param('elements', __cDragNDrop.draggedObject.id)) {
            element = engine.get_param('elements', __cDragNDrop.draggedObject.id);
        } else {
          return;
        }
		
		/* execute action if required */
	    if (element['onDragAction'] != '')
	        eval (element['onDragAction']);
		
		/* return false */
		return false;
	},
	
	/* element position setting method */
	set_position: function (dX,dY) {
	    	    
	    /* search element */
  	    engine = window._CDragNDropEngine;
        if ( engine.get_param('elements', __cDragNDrop.draggedObject.id)) {
            element = engine.get_param('elements', __cDragNDrop.draggedObject.id);
            object = element['element'];
        } else {
          return;
        }
    
        /* update element position */
        if (element['enableLimits'] == 1) {      
            __cDragNDrop.draggedObject.style.left = Math.min(element['limitXMax'], Math.max(element['limitXMin'], __cDragNDrop.startX + dX ))+ 'px';
	        __cDragNDrop.draggedObject.style.top = Math.min(element['limitYMax'], Math.max(element['limitYMin'], __cDragNDrop.startY + dY)) + 'px';
        } else {
	        __cDragNDrop.draggedObject.style.left = (__cDragNDrop.startX + dX) + 'px';
	       __cDragNDrop.draggedObject.style.top = (__cDragNDrop.startY + dY) + 'px';
	    }
	},
	
	/* element release method */
	release_element: function() {
	    /* search element */
  	    engine = window._CDragNDropEngine;
        if ( engine.get_param('elements', __cDragNDrop.draggedObject.id)) {
            element = engine.get_param('elements', __cDragNDrop.draggedObject.id);
        } else {
          return;
        }
		
	    /* release element */
		CDragNDrop_removeEvent(document,'mousemove',__cDragNDrop.drag_element);
		CDragNDrop_removeEvent(document,'mouseup',__cDragNDrop.release_element);
		__cDragNDrop.draggedObject.className = __cDragNDrop.draggedObject.className.replace(element['dragClassName'],'');
		__cDragNDrop.draggedObject = null;
		
		/* execute action if required */
	    if (element['onDropAction'] != '')
	      eval (element['onDropAction']);
	}
}

