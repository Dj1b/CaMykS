/* Functions added for CaMykS Email Link plugin */

tinyMCEPopup.requireLangPack();

var templates = {
  "window.open" : "window.open('${url}','${target}','${options}')"
};

function preinit() {
}

function changeClass() {
  var formObj = document.forms[0];
}

function init() {
  tinyMCEPopup.resizeToInnerSize();
  
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
    var href = inst.dom.getAttrib(elm, 'href');

    /* decompile email */
    href = tinyMCEPopup.getWin().mail_decodeLink(href);
    
    /* build class list */
    addClassesToList('classlist', 'camykslink_styles');    
    
    /* set form values */
    setFormValue('href', href);
    selectByValue(formObj, 'classlist', inst.dom.getAttrib(elm, 'class'), true);
  } else
    addClassesToList('classlist', 'camykslink_styles');
  
  window.focus();
}

function setFormValue(name, value) {
  if (document.forms[0].elements[name] ) 
    document.forms[0].elements[name].value = value;
}

function convertURL(url, node, on_save) {
  return eval("tinyMCEPopup.windowOpener." + tinyMCE.settings['urlconverter_callback'] + "(url, node, on_save);");
}

function setAttrib(elm, attrib, value) {
  
  var formObj = document.forms[0];
  var valueElm = formObj.elements[attrib.toLowerCase()];
  
  if (typeof(value) == "undefined" || value == null) {
    value = "";
    
    if (valueElm)
      value = valueElm.value;
  }
  
  if (value != "") {
    elm.setAttribute(attrib.toLowerCase(), value);
    
    if (attrib == "style")
      attrib = "style.cssText";
    
    if (attrib.substring(0, 2) == 'on')
      value = 'return true;' + value;
    
    if (attrib == "class")
      attrib = "className";
    
    eval('elm.' + attrib + "=value;");
  } else
    elm.removeAttribute(attrib);
}

function insertAction() {
  var inst = tinyMCEPopup.editor;
	var elm, elementArray, i;

	//elm = inst.selection.getNode();
	
	elm = inst.dom.getParent(elm, "A");	
	// Remove element if there is no href
	if (!document.forms[0].href.value) {
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

function setAllAttribs(elm) {
  var formObj = document.forms[0];
  var href = formObj.href.value;
  
  href = tinyMCEPopup.getWin().mail_encodeLink( href );
  
  setAttrib(elm, 'href', href);
  setAttrib(elm, 'title', 'email');
  setAttrib(elm, 'class', getSelectValue(formObj, 'classlist'));
  
  // Refresh in old MSIE
  if (tinyMCE.isMSIE5)
    elm.outerHTML = elm.outerHTML;
}

function getSelectValue(form_obj, field_name) {
  var elm = form_obj.elements[field_name];
  
  if (elm == null || elm.options == null)
    return "";
  
  return elm.options[elm.selectedIndex].value;
}

// While loading
preinit();
tinyMCEPopup.onInit.add(init);
