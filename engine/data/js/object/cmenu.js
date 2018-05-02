/**
 * @brief Client side scripts to manage layered menus.
 * @details Engine / Javascript object library
 * @file engine/data/js/object/cmenu.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Jun 2006
 * @date Modification: Apr 2018
 * @copyright 2006 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @Warning This library is dependant to <br />
 * - tool/htmlelement.js
 * - tool/clientenv.js
 */

/**
 * @var Object globalCMenu
 * @brief The menu manager object.
 */
globalCMenu = new GlobalCMenu('globalCMenu');

/**
 * Class constructor.
 * @param string name
 */
function GlobalCMenu(name) {
    /* const vars */
    this.hiding_default_timeout = 100;
    
    /* vars */
    this.name = name;
    this.menu = new Array();
    this.zIndex = 0;
    this.nav = tool_getClientBrowserType();
    this.initdone = false;
}

/* init menus */
GlobalCMenu.prototype.init = function() {
    for (var i in this.menu) {
        this.menu[i].init();
    }
    this.initdone = true;
}

/* send and update zIndex */
GlobalCMenu.prototype.getZindex = function() {
    return ++this.zIndex;
}

/* add a menu to global object */
GlobalCMenu.prototype.registerMenu = function(menu) {
    this.menu[menu.elmtName] = menu;
    this.menu[menu.elmtName].globalCMenu = this.name;
}

/* select menu */
GlobalCMenu.prototype.select = function(menu) {
    if (this.menu[menu] && this.initdone)
        this.menu[menu].select();
}

/* unselect menu */
GlobalCMenu.prototype.unselect = function(menu) {
    if (this.menu[menu] && this.initdone)
        this.menu[menu].unselect();
}

/* update parent */
GlobalCMenu.prototype.updateParent = function(menu, _parent) {
    if (this.menu[menu] && this.initdone)
        this.menu[menu].updateParent(_parent);
}

/*
 * Menu Constructor
 */
function CMenu (elmtName, parentMenu, parentElmtName, location) {
    /* conf */
    this.elmtName = elmtName;
    this.parentMenu = parentMenu;
    this.parentElmtName = parentElmtName;
    this.location = location;
    this.location_adjustx = 0;
    this.location_adjusty = 0;
    this.globalCMenu = null;
    this.listIndex = null;
    
    /* vars */
    this.selected = false;
    this.displayed = false;
    this.displayedchild = false;
}

CMenu.prototype.init = function() {
    this.elmt = document.getElementById(this.elmtName);
    if (this.parentElmtName != null)
        this.parentElmt = document.getElementById(this.parentElmtName);
    else
        this.parentElmt = null;
}

CMenu.prototype.updateParent = function(_parent) {
    this.parentElmtName = _parent;
    this.parentElmt = document.getElementById(this.parentElmtName); 
}

/* select menu */
CMenu.prototype.select = function(sitem) {
    if (this.selected == true) {
        return;
    }
    this.selected = true;
    if (this.displayed == false) {
        this.displayMe();
    }
    if (this.parentMenu != null) {
        eval(this.globalCMenu+'.menu["'+this.parentMenu+'"].select()');
    }
}

/* unselect menu */
CMenu.prototype.unselect = function(timeout) {
    if (this.selected == false ) {
        return;
    }
    this.selected = false;
    if (! (timeout > 0)) {
        timeout = eval(''+this.globalCMenu+'.hiding_default_timeout');
    }
    setTimeout(this.globalCMenu+'.menu["'+this.elmtName+'"].hideMe();', timeout);
    if (this.parentMenu != null) {
        eval(''+this.globalCMenu+'.menu["'+this.parentMenu+'"].unselect()');
        
        if ( eval (this.globalCMenu+'.selectedItem') != null) {
            eval (this.globalCMenu+'.selectedItem') = null;
        }
    }
}

/* set menu to given position */
CMenu.prototype.setposition = function() {
    switch (this.location) {
    case 'bottom':
        this.setposition_bottom();
        break;
    case 'left':
        this.setposition_left();
        break;
    case 'right':
        this.setposition_right();
        break;
            case 'top':
	this.setposition_top();
	break;
    case 'top':
        this.setposition_over();
        break;
    case 'mouse':
        this.setposition_mouse();
        break;
    case 'none':
    default :
        this.setposition_none();
        break;	
    }
}

/* display menu */
CMenu.prototype.displayMe = function() {
    
    /* disable all element which have the same parent */
    for (var i in eval(this.globalCMenu).menu) {
        if (this.elmtName != eval(this.globalCMenu).menu[i].elmtName && 
	 this.parentMenu == eval(this.globalCMenu).menu[i].parentMenu && 
	 this.parentMenu != null) {
            eval(this.globalCMenu).menu[i].unselect(0);
        }
    }
    
    /* display menu */
    this.displayed = true;
    this.setposition();
    this.elmt.style.zIndex = eval(this.globalCMenu).getZindex();
    this.elmt.style.display = 'block';
}

/* hide menu */
CMenu.prototype.hideMe = function() {
    if (this.selected == false) {
        this.elmt.style.display = 'none';
        this.displayed = false;
    }
}

/* position : none
     set menu div to position 0,0 */
CMenu.prototype.setposition_none = function() {
    this.elmt.style.left = this.location_adjustx + 'px';
    this.elmt.style.top = this.location_adjusty + 'px';
}

/* position : bottom
     set menu div to position parentElmtName.x , parentElmtName.y + parentElmtName.h */
CMenu.prototype.setposition_bottom = function() {
    this.elmt.style.left = tool_getObjectPositionX (this.parentElmt) + this.location_adjustx + 'px';
    this.elmt.style.top    = tool_getObjectPositionY (this.parentElmt) + this.parentElmt.offsetHeight + this.location_adjusty + 'px';
}

/* position : right
     set menu div to position parentElmtName.x + parentElmtName.w , parentElmtName.y */
CMenu.prototype.setposition_right = function() {
    this.elmt.style.left = tool_getObjectPositionX (this.parentElmt) + this.parentElmt.offsetWidth + this.location_adjustx + 'px';
    this.elmt.style.top    = tool_getObjectPositionY (this.parentElmt) + this.location_adjusty + 'px';
}

/* position : left
     set menu div to position parentElmtName.x - this.w , parentElmtName.y */
CMenu.prototype.setposition_left = function() {
    this.elmt.style.left = tool_getObjectPositionX (this.parentElmt) - this.elmt.offsetWidth + this.location_adjustx + 'px';
    this.elmt.style.top    = tool_getObjectPositionY (this.parentElmt) + this.location_adjusty + 'px';
}

/* position : top
     set menu div to position parentElmtName.x , parentElmtName.y - this.h */
CMenu.prototype.setposition_top = function() {
    this.elmt.style.left = tool_getObjectPositionX (this.parentElmt) + this.location_adjustx + 'px';
    this.elmt.style.top    = tool_getObjectPositionY (this.parentElmt) - this.elmt.offsetHeight + this.location_adjusty + 'px';
}

/* position : over 
     set menu div to position parentElmtName.x , parentElmtName.y */
CMenu.prototype.setposition_over = function() {
    this.elmt.style.left = tool_getObjectPositionX (this.parentElmt) + this.location_adjustx + 'px';
    this.elmt.style.top    = tool_getObjectPositionY (this.parentElmt) + this.location_adjusty + 'px';
}

/*position : mouse
    set menu div to mouse position */
CMenu.prototype.setposition_mouse = function() {
    /* to do */
}
