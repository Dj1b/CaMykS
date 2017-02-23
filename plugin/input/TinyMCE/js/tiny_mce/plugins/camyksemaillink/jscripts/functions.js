/* Functions added for CaMykS Email Link plugin */

var templates = {
  "window.open" : "window.open('${url}','${target}','${options}')"
};

function preinit() {
  // Initialize
  tinyMCE.setWindowArg('mce_windowresize', false);
}

function changeClass() {
  var formObj = document.forms[0];
}

function init() {
  tinyMCEPopup.resizeToInnerSize();
  
  var formObj = document.forms[0];
  var inst = tinyMCE.getInstanceById(tinyMCE.getWindowArg('editor_id'));
  var elm = inst.getFocusElement();
  var action = "insert";
  var html;
    
  elm = tinyMCE.getParentElement(elm, "a");
  if (elm != null && elm.nodeName == "A")
    action = "update";
  
  formObj.insert.value = tinyMCE.getLang('lang_' + action, 'Insert', true); 

  if (action == "update") {
    var href = tinyMCE.getAttrib(elm, 'href');
    
    href = convertURL(href, elm, true);
    href = opener.mail_decodeLink( href );

    var onclick = tinyMCE.cleanupEventStr(tinyMCE.getAttrib(elm, 'onclick'));

    /* build class list */
    addClassesToList('classlist', 'camykslink_styles');    
    
    /* set form values */
    setFormValue('href', href);
    selectByValue(formObj, 'classlist', tinyMCE.getAttrib(elm, 'class'), true);
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
  var inst = tinyMCE.getInstanceById(tinyMCE.getWindowArg('editor_id'));
  var elm = inst.getFocusElement();
  
  elm = tinyMCE.getParentElement(elm, "a");
  
  tinyMCEPopup.execCommand("mceBeginUndoLevel");
  
  // Create new anchor elements
  if (elm == null) {
    if (tinyMCE.isSafari)
      tinyMCEPopup.execCommand("mceInsertContent", false, '<a href="#mce_temp_url#">' + inst.selection.getSelectedHTML() + '</a>');
    else
      tinyMCEPopup.execCommand("createlink", false, "#mce_temp_url#");
    
    var elementArray = tinyMCE.getElementsByAttributeValue(inst.getBody(), "a", "href", "#mce_temp_url#");
    for (var i=0; i<elementArray.length; i++) {
      var elm = elementArray[i];
      
      // Move cursor behind the new anchor
      if (tinyMCE.isGecko) {
	var sp = inst.getDoc().createTextNode(" ");
	
	if (elm.nextSibling)
	  elm.parentNode.insertBefore(sp, elm.nextSibling);
	else
	  elm.parentNode.appendChild(sp);
	
	// Set range after link
	var rng = inst.getDoc().createRange();
	rng.setStartAfter(elm);
	rng.setEndAfter(elm);
	
	// Update selection
	var sel = inst.getSel();
	sel.removeAllRanges();
	sel.addRange(rng);
      }
      
      setAllAttribs(elm);
    }
  } else
    setAllAttribs(elm);
  
  tinyMCE._setEventsEnabled(inst.getBody(), false);
  tinyMCEPopup.execCommand("mceEndUndoLevel");
  tinyMCEPopup.close();
}

function setAllAttribs(elm) {
  var formObj = document.forms[0];
  var href = formObj.href.value;
  
  href = opener.mail_encodeLink( href );
  
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
