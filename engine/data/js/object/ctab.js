/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / JS Lib
 * Creation Date	: Nov 2006
 * last Modif Date	: Nov 2006
 * Dependencies		: none
 *
 * Tabs Objects        
*/

function CTab () {
  /* vars */
  var selected;
  var css_std;
  var css_sel;
  var css_over;
}

CTab.prototype.init = function ( seltab, std, sel, over ) {
  this.selected = seltab;
  this.css_std = std;
  this.css_sel = sel;
  this.css_over = over;
}

CTab.prototype.mouseover = function ( tab ) {
  if (tab != this.selected ) {
    if (document.getElementById('tab'+tab)) {
      document.getElementById('tab'+tab).className = this.css_over;
    }
  }
}

CTab.prototype.mouseout = function ( tab ) {
  if (tab != this.selected) {
    if (document.getElementById('tab'+tab)){
      document.getElementById('tab'+tab).className = this.css_std;
    }
  }
}

CTab.prototype.mouseclick = function ( tab ) {
  if ( tab == this.selected ) 
    return;
  
  /* unselect last one */
  if (document.getElementById('tab'+this.selected)) {
    document.getElementById('tab'+this.selected).className = this.css_std;
  }
  if (document.getElementById('item'+this.selected)) {
    document.getElementById('item'+this.selected).style.display = 'none';
  }
  
  /* update selected value */
  this.selected = tab;
  
  /* select new one */
  if (document.getElementById('tab'+this.selected)) {
    document.getElementById('tab'+this.selected).className = this.css_sel;
  }
  if (document.getElementById('item'+this.selected)) {
    document.getElementById('item'+this.selected).style.display = 'block';
  }
}
