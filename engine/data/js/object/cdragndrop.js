/**
 * @brief Client side scripts to manage drag'n drop.
 * @details Engine / Javascript object library
 * @file engine/data/js/object/cdragndrop.js
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Sep 2013
 * @date Modification: Apr 2018
 * @copyright 2013 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Class constructor.
 * @param string name
 */
function CDragNDrop(name) {
    /**
     * @var string name
     * @brief The object occurence name.
     */
    this.name = name;
    
    /**
     * @var array params
     * @brief The object occurence parameters.
     */
    this.params = {'elements':{}};
    
    /**
     * Set parameter value.
     * @param string name
     * @param mixed value
     * @return void
     */
    this.set_param = function(param, value, subvalue) {
        if (subvalue != undefined && this.params[param])
            this.params[param][value] = subvalue;
        else
            this.params[param] = value;
    };
     
    /**
     * Return parameter value from name.
     * @param mixed param
     * @return mixed
     */
    this.get_param = function(param, value) {
        if (value != undefined && (this.params[param][value] || this.params[param][value] === 0))
                return this.params[param][value];
        if (this.params[param] || this.params[param] === 0)
            return this.params[param]

        return false;
    };

    /**
     * Initialise object.
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
    
    /**
     * Enable drag'n'drop for element.
     * @param array params
     * @return void
     */
    this.enable_forElement = function(params) {
        /* default params list */
        dparams = {
            'element':null,
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
    
    /**
     * Disable drag'n'drop for element.
     * @param mixed elmnt
     * @return void
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

/**
 * Attach event to an HTMLElement.
 * @param HTMLElement obj
 * @param Event evt
 * @param Function fn
 * @return void
 */
function CDragNDrop_addEvent(obj,evt,fn) {
    if (obj.addEventListener)
        obj.addEventListener(evt,fn,false);
    else if (obj.attachEvent)
        obj.attachEvent('on'+evt,fn);
}

/**
 * Remove event to an HTMLElement
 * @param HTMLElement obj
 * @param Event evt
 * @param Function fn
 * @return void
 */
function CDragNDrop_removeEvent(obj,evt,fn) {
    if (obj.removeEventListener)
        obj.removeEventListener(evt,fn,false);
    else if (obj.detachEvent)
        obj.detachEvent('on'+evt,fn);
}

/**
 * _cDragNDrop class constructor
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
        if (engine.get_param('elements', __cDragNDrop.draggedObject.id)) {
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
                if (engine.get_param('elements', __cDragNDrop.draggedObject.id)) {
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
                if (engine.get_param('elements', __cDragNDrop.draggedObject.id)) {
                        element = engine.get_param('elements', __cDragNDrop.draggedObject.id);
                        object = element['element'];
                } else {
                    return;
                }
        
                /* update element position */
                if (element['enableLimits'] == 1) {            
                        __cDragNDrop.draggedObject.style.left = Math.min(element['limitXMax'], Math.max(element['limitXMin'], __cDragNDrop.startX + dX))+ 'px';
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
                if (engine.get_param('elements', __cDragNDrop.draggedObject.id)) {
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
