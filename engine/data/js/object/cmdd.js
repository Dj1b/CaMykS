/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / JS Lib
 * Create Date		: Feb 2007
 * Last Modif Date	: Feb 2007
 * Dependencies		: none
 *
 * Camyks Multi Div Displayer Object        
*/

/* constructor */
function Cmdd () {
    /* vars */
    var prefix;
    var selected;
    var css_std;
    var css_sel;
    var css_over;
}

/* methods */
Cmdd.prototype.init = function ( prefix, selpage, std, sel, over ) {
    this.prefix = prefix;
    this.selected = selpage;
    this.css_std = std;
    this.css_sel = sel;
    this.css_over = over;
}

Cmdd.prototype.mouseover = function ( page ) {
    if ( page != this.selected ) {
	if ( document.getElementById( this.prefix+'_menu'+page ) ){
	    document.getElementById( this.prefix+'_menu'+page).className = this.css_over;
	}
    }
}

Cmdd.prototype.mouseout = function ( page ) {
    if ( page != this.selected ) {
	if ( document.getElementById( this.prefix+'_menu'+page ) ){
	    document.getElementById( this.prefix+'_menu'+page).className = this.css_std;
	}
    }
}

Cmdd.prototype.mouseclick = function ( page ) {
    if ( page == this.selected ) 
      return;
    
    /* unselect last one */
    if ( document.getElementById( this.prefix+'_menu'+this.selected) ) {
	document.getElementById( this.prefix+'_menu'+this.selected).className = this.css_std;
    }
    if ( document.getElementById( this.prefix+'_page'+this.selected) ) {
	document.getElementById( this.prefix+'_page'+this.selected).style.display = 'none';
    }
    
    /* update selected value */
    this.selected = page;
    
    /* select new one */
    if ( document.getElementById( this.prefix+'_menu'+this.selected) ) {
	document.getElementById( this.prefix+'_menu'+this.selected).className = this.css_sel;
    }
    if ( document.getElementById( this.prefix+'_page'+this.selected) ) {
	document.getElementById( this.prefix+'_page'+this.selected).style.display = 'block';
    }
}

Cmdd.prototype.selectChange = function ( s ) {
    v = s.options[s.selectedIndex].value;
    if ( this.selected == v)
      return;
    this.selectItem ( v );
}

Cmdd.prototype.selectItem = function ( value ) {
    /* remove old div */
    if ( document.getElementById( this.prefix+'_page'+this.selected) ) {
	document.getElementById( this.prefix+'_page'+this.selected).style.display = 'none';
    }
    
    /* update selected value */
    this.selected = value;

    /* add new div */
    if ( document.getElementById( this.prefix+'_page'+this.selected) ) {
	document.getElementById( this.prefix+'_page'+this.selected).style.display = 'block';
    }
}
