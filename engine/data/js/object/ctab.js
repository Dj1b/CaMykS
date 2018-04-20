/**
 * @brief Client side scripts to manage tabs.
 * @details Engine / Javascript object library
 * @file engine/data/js/object/ctab.js
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Nov 2006
 * @date Modification: Apr 2018
 * @copyright 2006 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Class constructor.
 * @param string name
 */
function CTab() {
    /* vars */
    var selected;
    var css_std;
    var css_sel;
    var css_over;
}

CTab.prototype.init = function (seltab, std, sel, over) {
    this.selected = seltab;
    this.css_std = std;
    this.css_sel = sel;
    this.css_over = over;
}

CTab.prototype.mouseover = function (tab) {
    if (tab != this.selected) {
        if (document.getElementById('tab'+tab)) {
            document.getElementById('tab'+tab).className = this.css_over;
        }
    }
}

CTab.prototype.mouseout = function (tab) {
    if (tab != this.selected) {
        if (document.getElementById('tab'+tab)){
            document.getElementById('tab'+tab).className = this.css_std;
        }
    }
}

CTab.prototype.mouseclick = function (tab) {
    if (tab == this.selected) 
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
