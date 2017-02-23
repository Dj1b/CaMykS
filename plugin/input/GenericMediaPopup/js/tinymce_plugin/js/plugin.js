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
 * GenericMediaPopup external plugin for TinyMCE 
 * Plugin pop-up scripts
 */

/*
 * pre-initialise window, load external scripts
 * @return void
 * @access private
 */
function preinit() {

}

/*
 * pre-initialisation step 2, load download manager data
 * @return void
 * @access private
 */
function onScriptsLoaded() {

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
  
  /* load file browser link */
  document.getElementById('filebrowsercontainer').innerHTML = getFileBrowserHTML('filebrowser','media','file','mediapopup');
  
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
    if (link.indexOf('javascript:mediaPopup_open') == 0) {
        var data = link.substring(link.indexOf('('), link.lastIndexOf(')')+1);
        data = eval('get_paramsAsArray'+unescape(data));
        formObj.media.value = data[0];
        formObj.title.value = data[1];
        if ( data.length > 2 ) {
            formObj.width.value = data[2];
            formObj.height.value = data[3];
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
	if (formObj.media.value == '') {
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
  var url = 'javascript:mediaPopup_open(';
  url += '\'' + formObj.media.value + '\'';
  url += ',\'' + formObj.title.value.replace(/\'/g, '\\\'') + '\'';
  if (parseInt(formObj.width.value) > 0 && parseInt(formObj.height.value) > 0) {
    url += ',' + formObj.width.value + ',' + formObj.height.value;
  }
  url += ');';
  
  setAttrib(elm, 'href', url);
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

/* file browser link */
function getFileBrowserHTML(id, target_form_element, type, prefix) {
  var option = prefix + "_" + type + "_browser_callback", cb, html;
  
  cb = tinyMCEPopup.getParam(option, tinyMCEPopup.getParam("file_browser_callback"));
  
  if (!cb)
    return "";
  
  html = "";
  html += '<a id="' + id + '_link" href="javascript:openCaMykSBrowser(\'' + id + '\',\'' + target_form_element + '\', \'' + type + '\',\'' + option + '\');" onmousedown="return false;" class="browse filelink">';
  html += '<span id="' + id + '" title="' + tinyMCEPopup.getLang('mediapopup.browsefile') + '"></span></a>';
  
  return html;
}

function openCaMykSBrowser(element_id, target_form_element, type, option) {
  var img = document.getElementById(element_id);
  
  if (img.className == "mceButtonDisabled")
    return;
  
  tinyMCEPopup.restoreSelection();
  tinyMCEPopup.editor.execCallback(type+'_browser_callback', target_form_element, document.getElementById(target_form_element).value, type, window);
}


/*
 * return params as array
 * @return array
 * @access private
 */
function get_paramsAsArray() {
   return arguments;
}

// While loading
preinit();
tinyMCEPopup.onInit.add(init);
