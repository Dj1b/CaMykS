/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Javascript Library
 * Create Date		: Oct 2008
 * Last Modif Date	: Oct 2008
 *
 * AdminItemListViewer javascript object and methods
*/

function AdminItemListViewer(name) {
  this._name = name;
  this._form = null;
  
  /* methods */
  
  /*
   * initialise object
   * @return void
   * @access public
   */
  this.initialise = function() {
    /* get form */
    this._form = eval('document.'+this._name+'_form');
  };
  
  /*
   * reload page with selector changes
   * @return void
   * @access public
   */
  this.update = function() {
    this._form.submit();
  };
  
  /*
   * update given page object
   * @param string page
   * @return void
   * @access public
   */
  this.update_pagePlus = function(page) {
    eval('this._form.'+this._name+'_form'+page+'.value++');
    this.update();
  };
  
  /*
   * update given page object
   * @param string page
   * @return void
   * @access public
   */
  this.update_pageMinus = function(page) {
    eval('this._form.'+this._name+'_form'+page+'.value--');
    this.update();
  };
  
  /*
   * update sort column value
   * @param string column
   * @return void
   * @access public
   */
  this.update_sortColumn = function(column) {
    eval('this._form.'+this._name+'_sortcolumn.value="'+column+'"');
    eval('this._form.'+this._name+'_sortway.value=""');
    this.update();
  };
  
  /*
   * update sort column value
   * @param string way
   * @return void
   * @access public
   */
  this.update_sortWay = function(way) {
    eval('this._form.'+this._name+'_sortway.value="'+way+'"');
    this.update();
  };
  
  /* checkbox management */
  
  /*
   * update all checkboxes
   * @param string chk
   * @return void
   * @access public
   */
  this.update_allCheckboxes = function(chk) {
    s = document.getElementById(chk+'_all').checked;
    i = 0;
    while (c = document.getElementById(chk+i)) {
      c.checked = s;
      i++;
    }
  };
  
  /*
   * update single checkboxe
   * @param string chk
   * @return void
   * @access public
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
  
  /*
   * return checked checkbox
   * @param string chk
   * @return array
   * @access public
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