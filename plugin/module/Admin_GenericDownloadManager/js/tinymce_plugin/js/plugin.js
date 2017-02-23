/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b1
 * Object Version	: 1.0
 * Object Type      : Plugin / Javacript
 * Creation Date   	: Jan 2011
 * Last Modif Date	: Jan 2011
 *
 * Admin_GenericDownloadManager external plugin for TinyMCE 
 * Plugin pop-up scripts
 */

/*
 * pre-initialise window, load external scripts
 * @return void
 * @access private
 */
function preinit() {
	scriptsToLoad = new Array();
	scriptsToLoad[scriptsToLoad.length] = tinyMCEPopup.getWin().camyks_data_url+'/js/object/cajaxrequest.js';
	scriptsToLoad[scriptsToLoad.length] = tinyMCEPopup.getWin().camyks_data_url+'/js/tool/xml.js';
	
	tinymce.ScriptLoader.loadScripts(scriptsToLoad, onScriptsLoaded, this );
}

/*
 * pre-initialisation step 2, load download manager data
 * @return void
 * @access private
 */
function onScriptsLoaded() {
  tinymce.request = tinyMCEPopup.getWin().get_ajaxObject('tinymce.request');
  tinymce.request._initialise(null, 'GET', onDataLoaded, 'xml', onDataError );
  tinymce.request._execute('request.php?module=Admin_GenericDownloadManager&action=loadData');
}

/*
 * download manager data reception handler
 * @param xml result
 * @return void
 * @access private
 */
function onDataLoaded(result) {
	var formObj = document.forms[0];
	
	/* save xml to js objects */
	result = tinyMCEPopup.getWin().xml_serializeObject(result);

  if ( result == null )
    return;	

	/* add categories to list */
	var categorySelectElm = document.getElementById('category');
	for(i in result['categories'])
		categorySelectElm.options[categorySelectElm.length] = new Option(result['categories'][i]['title'], result['categories'][i]['id']);
	

	/* save document list */
	docs = result['documents'];
	
	/* check for current value selection */
	if ( selDoc == 0)
		return;
	
	for(i in docs) {
		if (docs[i]['id'] == selDoc) {
			selCat = docs[i]['category'];
			selDoc = docs[i]['link'];
			break;
	  }
	} 
	selectByValue(formObj, 'category', selCat, true);
	clearSelectValue(formObj, 'document')
	for(i in docs) {
		if ( docs[i]['category'] == selCat)
			addSelectOption(formObj, 'document', docs[i]['title'], docs[i]['link']);
	}
	selectByValue(formObj, 'document', selDoc, true);
}

/*
 * download manager data reception error handler
 * @return void
 * @access private
 */
function onDataError() {
	tinyMCEPopup.alert(tinyMCEPopup.getLang('genericdownloadmanager.dataloadingerror'));
	tinyMCEPopup.close();
}

/*
 * onChange category select event
 * @return void
 * @access private
 */
function changeCategory() {
	/* init required objects */
	var formObj = document.forms[0];
	var docSelectElm = document.getElementById('document');

	/* get current values */
	var selCat = getSelectValue(formObj, 'category');

	/* empty current document list */
	clearSelectValue(formObj, 'document')
	
	/* add new items */
	if (selCat == '') {
		addSelectOption(formObj, 'document', tinyMCEPopup.getLang('not_set'), '');
	} else {
		for(i in docs) {
			if ( docs[i]['category'] == selCat) {
				addSelectOption(formObj, 'document', docs[i]['title'], docs[i]['link']);
			}
		}
	}
}

/*
 * onChange class select event
 * @return void
 * @access private
 */
function changeClass() {
}

/*
 * window init
 * @return void
 * @access private
 */
function init() {
  tinyMCEPopup.resizeToInnerSize();
  
  selDoc = 0;
    
  var formObj = document.forms[0];
  var inst = tinyMCEPopup.editor;
  var elm = inst.selection.getNode();
  var action = "insert";
  var html;
    
  elm = inst.dom.getParent(elm, "A");
  if (elm != null && elm.nodeName == "A")
    action = "update";
  
  formObj.insert.value = tinyMCEPopup.getLang(action, 'Insert', true);

  if (action == "update") {
    /* get value */
    var link = inst.dom.getAttrib(elm, 'href');
    if (link.indexOf('request.php?module=Admin_GenericDownloadManager') > -1) {
    	var idPos = link.indexOf('did=');
    	if ( idPos != -1 ) {
    		idPos += 4;
    		selDoc = link.substr(idPos);
    		if (selDoc.indexOf('&') > -1)
    			selDoc = selDoc.substr(0, selDoc.indexOf('&'));
    		selDoc = parseInt(selDoc);
    	}
    }
    
    /* build class list */
    addClassesToList('classlist', 'camykslink_styles');    
    
    /* set form values */
    selectByValue(formObj, 'classlist', inst.dom.getAttrib(elm, 'class'), true);
  } else
    addClassesToList('classlist', 'camykslink_styles');
  
  window.focus();
  return false;
}

/*
 * set attribute to given element
 * @param object elm
 * @param string attrib
 * @param mixed value
 * @return void
 * @access private
 */
function setAttrib(elm, attrib, value) {
  var formObj = document.forms[0];
  var valueElm = formObj.elements[attrib.toLowerCase()];
  var dom = tinyMCEPopup.editor.dom;
  
  if (typeof(value) == "undefined" || value == null) {
    value = "";
    
    if (valueElm)
      value = valueElm.value;
  }
  
  dom.setAttrib(elm, attrib, value);
}

/*
 * insert link action 
 * @return void
 * @access private
 */
function insertAction() {
  var inst = tinyMCEPopup.editor;
  var formObj = document.forms[0];
	var elm, elementArray, i;

	elm = inst.selection.getNode();
	elm = inst.dom.getParent(elm, "A");
	
	// Remove element if there is no href
	if (getSelectValue(formObj, 'document') == '') {
		tinyMCEPopup.execCommand("mceBeginUndoLevel");
		i = inst.selection.getBookmark();
		inst.dom.remove(elm, 1);
		inst.selection.moveToBookmark(i);
		tinyMCEPopup.execCommand("mceEndUndoLevel");
		tinyMCEPopup.close();
		return;
	}
	
	tinyMCEPopup.execCommand("mceBeginUndoLevel");
	// Create new anchor elements
	if (elm == null) {
		tinyMCEPopup.execCommand("CreateLink", false, "#mce_temp_url#", {skip_undo : 1});

		elementArray = tinymce.grep(inst.dom.select("a"), function(n) {return inst.dom.getAttrib(n, 'href') == '#mce_temp_url#';});
		for (i=0; i<elementArray.length; i++)
			setAllAttribs(elm = elementArray[i]);
	} else
	  setAllAttribs(elm);

	// Don't move caret if selection was image
	if (elm.childNodes.length != 1 || elm.firstChild.nodeName != 'IMG') {
		inst.focus();
		inst.selection.select(elm);
		inst.selection.collapse(0);
		tinyMCEPopup.storeSelection();
	}

	tinyMCEPopup.execCommand("mceEndUndoLevel");
	tinyMCEPopup.close();
}

/* 
 * set all attribute to given element
 * @param obj elm
 * @return void
 * @access private
 */
function setAllAttribs(elm) {
  var formObj = document.forms[0];
  var href = getSelectValue(formObj, 'document');  
  setAttrib(elm, 'href', href);
  setAttrib(elm, 'class', getSelectValue(formObj, 'classlist'));
}

/*
 * clear a select option list
 * @param HTMLForm form_obj
 * @param string field_name
 * @return void
 * @access private
 */
function clearSelectValue(form_obj, field_name){
	var selectObj = form_obj.elements[field_name];
	var selectParentNode = selectObj.parentNode;
	var newSelectObj = selectObj.cloneNode(false);
	selectParentNode.replaceChild(newSelectObj, selectObj);
}

/*
 * add a new option to given select element
 * @param HTMLForm form_obj
 * @param string field_name
 * @param string name
 * @param mixed value
 * @return void
 * @access private
 */
function addSelectOption(form_obj, field_name, name, value) {
	var s = form_obj.elements[field_name];
	var o = new Option(name, value);
	s.options[s.options.length] = o;
}

/*
 * get selected value from given select element
 * @param HTMLForm form_obj
 * @param string field_name
 * @return void
 * @access private
 */
function getSelectValue(form_obj, field_name) {
  var elm = form_obj.elements[field_name];
  
  if (elm == null || elm.options == null)
    return "";
  
  return elm.options[elm.selectedIndex].value;
}

/*
 * get selected text from given select element
 * @param HTMLForm form_obj
 * @param string field_name
 * @return void
 * @access private
 */
function getSelectTitle(form_obj, field_name) {
  var elm = form_obj.elements[field_name];
  
  if (elm == null || elm.options == null)
    return "";
  
  return elm.options[elm.selectedIndex].text;
}

// While loading
preinit();
tinyMCEPopup.onInit.add(init);
