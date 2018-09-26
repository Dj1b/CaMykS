/**
 * @brief AdminItemListViewer Input client side scripts
 * @details Plugin / Input Scripts
 * @file plugin/input/AdminItemListViewer/js/AdminItemListViewer.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Oct 2008
 * @date Modification: Apr 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Class constructor.
 * @param string $name
 */
function AdminItemListViewer(name) {
    this._name = name;
    this._form = null;

    /* methods */

    /**
     * Initialise object.
     * @return void
     */
    this.initialise = function() {
        /* get form */
        this._form = eval('document.'+this._name+'_form');
    };

    /*
     * Reload page with selector changes.
     * @return void
     */
    this.update = function() {
        this._form.submit();
    };

    /**
     * Update given page object.
     * @param string page
     * @return void
     */
    this.update_pagePlus = function(page) {
        eval('this._form.'+this._name+'_form'+page+'.value++');
        this.update();
    };

    /**
     * Update given page object.
     * @param string page
     * @return void
     */
    this.update_pageMinus = function(page) {
        eval('this._form.'+this._name+'_form'+page+'.value--');
        this.update();
    };

    /**
     * Update sort column value.
     * @param string column
     * @return void
     * @access public
     */
    this.update_sortColumn = function(column) {
        eval('this._form.'+this._name+'_sortcolumn.value="'+column+'"');
        eval('this._form.'+this._name+'_sortway.value=""');
        this.update();
    };

    /**
     * Update sort column value.
     * @param string way
     * @return void
     * @access public
     */
    this.update_sortWay = function(way) {
        eval('this._form.'+this._name+'_sortway.value="'+way+'"');
        this.update();
    };

    /* checkbox management */

    /**
     * Update all checkboxes.
     * @param string chk
     * @return void
     */
    this.update_allCheckboxes = function(chk) {
        s = document.getElementById(chk+'_all').checked;
        i = 0;
        while (c = document.getElementById(chk+i)) {
            c.checked = s;
            i++;
        }
    };

    /**
     * Update single checkbox.
     * @param string chk
     * @return void
     */
    this.update_singleCheckbox = function(chk) {
        i = 0;
        while (c = document.getElementById(chk+i)) {
            s = c.checked;
            if (s === false) {
                document.getElementById(chk+'_all').checked = false;
                return;
            }
            i++;
        }
        document.getElementById(chk+'_all').checked = true;
    };

    /**
     * Return checked checkbox.
     * @param string chk
     * @return array
     */
    this.get_checkedBoxes = function(chk) {
        list = new Array();
        i = 0;
        while (c = document.getElementById(chk+i)) {
            if (c.checked)
                list[list.length] = c.value;
            i++;
        }
        return list;
    };
}
