/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Javascript Library
 * Creation Date       	: Mar 2007
 * Last Modif Date	: Mar 2007
 *
 * QuickItemList object
 */

/* constructor */
function QuickItemList ( n ) {
  /* name */
  this.name = n;
  /* lists */
  this.fullList = new Array();
  this.editList = new Array();
  this.editListItems = new Array();
  this.iconList = {}
  this.buttonList = {};

  /* form */
  this.formname = null;
  this.itemname = null;

  /* separator */
  this.separator = null;
  
  /* html elements */
  this.divElement = document.createElement('div');
  this.tableElement = document.createElement('table');
  this.trElement = document.createElement('tr');
  this.tdElement = document.createElement('td');
  this.aElement = document.createElement('a');
  this.imgElement = document.createElement('img');
}

/* value insertion methods */
QuickItemList.prototype.add_fullListItem = function ( item ) {
  this.fullList[this.fullList.length] = item;
}

QuickItemList.prototype.add_editListItem = function ( item ) {
  this.editListItems[this.editListItems.length] = item;
}

QuickItemList.prototype.add_formValue = function ( formname, itemname ) {
  this.formname = formname;
  this.itemname = itemname;
}

QuickItemList.prototype.add_separatorValue = function ( sep ) {
  this.separator = sep;
}

/* initialisation methods */
QuickItemList.prototype.initialise = function ( ) {
  /* get html list boxes */
  this.fullListBox = document.getElementById ( this.name+'_fullListBox');
  this.editListBox = document.getElementById ( this.name+'_editListBox');
  
  /* get icon elements */
  this.buttonList['plus'] = this.get_buttonElement('plus');
  this.buttonList['minus'] = this.get_buttonElement('minus');

  /* get form item */
  this.formItem = eval ( 'document.'+this.formname+'.'+this.itemname ); 
  
  /* add full list items */
  for ( var i in this.fullList ) {
    this.add_fullItem ( this.fullList[i] );
  }
  
  /* add edit list items */
  for ( var i in this.editListItems ) {
    this.add_item ( this.editListItems[i] );
  }
}

QuickItemList.prototype.add_fullItem = function ( item ) {
  /* build div item */
  elmt = this.divElement.cloneNode(true);
  /* create table */
  table = this.tableElement.cloneNode(true);
  table.style.width='100%';
  table.style.borderSpacing='0px';
  tr = this.trElement.cloneNode(true);
  td = this.tdElement.cloneNode(true);
  td.className='eTableLine0';
  td.innerHTML = item;
  tr.appendChild ( td );
  td = null;
  td = this.tdElement.cloneNode(true);
  td.className='eTableLine0';
  td.style.width='12px';
  td.style.textAlign='center';
  a = this.aElement.cloneNode(true);
  a.href = 'javascript:'+this.name+'.add_item("'+item+'");';
  if ( this.buttonList['plus'] != null) {
    a.appendChild(this.buttonList['plus'].cloneNode('true'));
  } else {
    a.innerHTML = '+';
  }
  td.appendChild( a );
  tr.appendChild( td );
  table.appendChild ( tr );
  
  /* add element to the list box */
  this.fullListBox.appendChild( table );
}

/* running value */
QuickItemList.prototype.add_item = function ( item ) {
  if ( array_in ( this.editList, item ) ) 
    return;
  
  this.editList[this.editList.length] = item;
  
  /* build div item */
  elmt = this.divElement.cloneNode(true);
  elmt.setAttribute ('id', this.name+'_'+item);
  /* create table */
  table = this.tableElement.cloneNode(true);
  table.style.width='100%';
  table.style.borderSpacing='0px';
  tr = this.trElement.cloneNode(true);
  td = this.tdElement.cloneNode(true);
  td.className='eTableLine0';
  td.innerHTML = item;
  tr.appendChild ( td );
  td = null;
  td = this.tdElement.cloneNode(true);
  td.className='eTableLine0';
  td.style.width='12px';
  td.style.textAlign='center';
  a = this.aElement.cloneNode(true);
  a.href = 'javascript:'+this.name+'.remove_item("'+item+'");';
  if ( this.buttonList['minus'] != null) {
    a.appendChild(this.buttonList['minus'].cloneNode('true'));
  } else {
    a.innerHTML = '-';
  }
  td.appendChild( a );
  tr.appendChild( td );
  table.appendChild ( tr );
  elmt.appendChild ( table );
  
  /* add element to the list box */
  this.editListBox.appendChild( elmt );    
  
  /* update list */
  this.update_formList();
}

QuickItemList.prototype.remove_item = function ( item ) {
  /* delete div item */
  this.editList = array_dropItem ( this.editList, item );
  elmt = document.getElementById ( this.name+'_'+item ) ;
  elmt = this.editListBox.removeChild ( elmt );
  elmt = null;

  /* udpate list */
  this.update_formList();
}

QuickItemList.prototype.update_formList = function ( ) {
  this.formItem.value =  this.editList.join(this.separator);
}

/*
 * send icon url
 * @param string icon
 * @param string url
 * @return void
 * @access private
 */
QuickItemList.prototype.set_iconURL = function(icon, url) {
  this.iconList[icon] = url;
}

/*
 * build icon element
 * @param string button
 * @return HTMLDomElement
 * @access private
 */
QuickItemList.prototype.get_buttonElement = function(button) {
  /* check main icon */
  if (!this.iconList[button])
    return null;

  elmt = this.imgElement.cloneNode(true);
  elmt.setAttribute('src', this.iconList[button]);
  elmt.setAttribute('border', 0);
  elmt.setAttribute('alt', '');
  
  if (this.iconList[button+'_over']) {
    elmt.setAttribute('onmouseover', 'this.src="'+this.iconList[button+'_over']+'";');
    elmt.setAttribute('onmouseout', 'this.src="'+this.iconList[button]+'";');
  }
  return elmt;
}
