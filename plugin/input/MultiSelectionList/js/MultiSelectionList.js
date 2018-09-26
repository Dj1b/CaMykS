/**
 * @brief MultiSelectionList Input scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/MultiSelectionList/js/MultiSelectionList.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Apr 2011
 * @date Modification: Apr 2018
 * @copyright 2011 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* constructor */
function MultiSelectionList(name) {
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
  
  	/* get document form item */
  	if (!eval('document.'+this.get_param('formName')+'.'+this.get_param('formItemName')))
  		return;
  	this.set_param('formItem', eval('document.'+this.get_param('formName')+'.'+this.get_param('formItemName')));
  	
  	/* get list boxes */
  	if (!document.getElementById(this.name+'_fullListBox'))
  		return;
  	this.set_param('fullBox', document.getElementById(this.name+'_fullListBox'));
  	
  	if (!document.getElementById(this.name+'_selListBox'))
  		return;
  	this.set_param('selBox', document.getElementById(this.name+'_selListBox'));
  	
  	/* build HTML lists */
  	for (i in this.get_param('fullList')) {
  		if ( array_in(this.get_param('selList'), parseInt(i)))
  			this.add_itemInSelList(i);
  		else
  			this.add_itemInFullList(i);
  	}
  	  	
  	/* update form item value */
  	this.get_param('formItem').value = this.get_param('selList').join(this.get_param('itemSeparator'));
  	
  	/* finalise initialisation */
  	this.loaded = true;
  };
  
  /*
   * add item to selection list
   * @param integer i
   * @return void
   * @access private
   */
  this.add_itemInSelList = function(i) {
  	this.add_itemInList(i, 'sel', 'minus', 'remove_fromSelection');
  };
  
  /*
   * remove item from selection list
   * @param integer i
   * @return void
   * @access private
   */
  this.remove_itemFromSelList = function(i) {
  	this.remove_itemFromList(i, 'sel');
  };
  
  /*
   * add item to full list
   * @param integer i
   * @return void
   * @access private
   */
  this.add_itemInFullList = function(i) {
  	this.add_itemInList(i, 'full', 'plus', 'add_toSelection');
  };
  
  /*
   * remove item from full list
   * @param integer i
   * @return void
   * @access private
   */
  this.remove_itemFromFullList = function(i) {
  	this.remove_itemFromList(i, 'full');
  };
  
  /*
   * add item in given list
   * @param integer i
   * @param string list
   * @param string attachedButton
   * @param string action
   * @return void
   * @access private
   */
  this.add_itemInList = function(i, list, attachedButton, action) {
  	/* build line */
  	elmt = document.createElement('div').cloneNode(false);
  	elmt.id = 'elmt'+i;
  	elmt.style.height = '20px';
  	
  	/* build button */
  	b = this.get_button(attachedButton, action, i);
  	elmt.appendChild(b);
  	
  	/* build text */
  	s = document.createElement('span').cloneNode(false);
  	s.innerHTML = this.get_param('fullList', i);
  	elmt.appendChild(s);
  	  	
  	/* add line to list */
  	this.get_param(list+'Box').appendChild(elmt);
  };
  
  /*
   * remove item from given list
   * @param integer i
   * @param string list
   * @return void
   * @access private
   */
  this.remove_itemFromList = function(i, list) {
  	if (!document.getElementById('elmt'+i))
  		return;
  	this.get_param(list+'Box').removeChild(document.getElementById('elmt'+i));
  };
  
  /*
   * return HTML button 
   * @param string button
   * @param string action
   * @param integer item
   * @return void
   * @access private
   */
  this.get_button = function(button, action, item) {
  	b = document.createElement('img').cloneNode(false);
  	b.src = this.get_param(button+'Icon');
  	b.style.margin = '4px';
  	b.style.cssFloat = 'right';
  	b.style.cursor = 'pointer';
  	
  	if (this.get_param('navType')) {
  		b.setAttribute('onclick', this.name+'.'+action+'('+item+');');
  		b.setAttribute('onmouseover', 'this.src="'+this.get_param(button+'IconR')+'";');
  		b.setAttribute('onmouseout', 'this.src="'+this.get_param(button+'Icon')+'";');
  	} else {
  		b.onclick = new Function(this.name+'.'+action+'('+item+');');
  		b.onmouseover = new Function('this.src="'+this.get_param(button+'IconR')+'";');
  		b.onmouseout = new Function('this.src="'+this.get_param(button+'Icon')+'";');
  	}
  	return b;
  };
  
  /*
   * add item from full list to selection list
   * @param integer item
   * @return void
   * @access private
   */
  this.add_toSelection = function(item) {
  	this.set_param('selList', this.get_param('selList').length, item);
  	this.get_param('formItem').value = this.get_param('selList').join(this.get_param('itemSeparator'));
  	this.remove_itemFromFullList(item);
  	this.add_itemInSelList(item);
  };
  
  /*
   * remove item from sel list to full list
   * @param integer item
   * @return void
   * @access private
   */
  this.remove_fromSelection = function(item) {
  	this.set_param('selList', array_dropItem(this.get_param('selList'), item));
  	this.get_param('formItem').value = this.get_param('selList').join(this.get_param('itemSeparator'));
  	this.remove_itemFromSelList(item);
  	this.add_itemInFullList(item);
  };
}