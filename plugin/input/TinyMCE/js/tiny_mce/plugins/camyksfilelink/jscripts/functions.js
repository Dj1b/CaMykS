/* Functions added for CaMykS File Link */
function getFileBrowserHTML(id, form_element) {
  var cb = tinyMCE.getParam("file_browser_callback");
  if (cb == null)
    return "";
  
  var html = "";
  
  //javascript:openBrower('srcbrowser','src', 'image','advimage_image_browser_callback');
  
  html += '<a id="' + id + '_link" href="javascript:openFileBrowser(\''+id+'\',\''+form_element+'\');" onmousedown="return false;">';
  html += '<img id="' + id + '" src="' + themeBaseURL + '/images/browse.gif"';
  html += ' onmouseover="this.className=\'mceButtonOver\';"';
  html += ' onmouseout="this.className=\'mceButtonNormal\';"';
  html += ' onmousedown="this.className=\'mceButtonDown\';"';
  html += ' width="20" height="18" border="0" title="' + tinyMCE.getLang('lang_camyksfilelink_browse', true) + '"';
  html += ' class="mceButtonNormal" alt="'+ tinyMCE.getLang('lang_camyksfilelink_browse', true) + '" /></a>'; 
  return html;
}

function openFileBrowser(img_id, form_element) {
  var img = document.getElementById(img_id);
  
  if (img.className != "mceButtonDisabled") {
    var cb = tinyMCE.getParam('', tinyMCE.getParam("file_browser_callback"));
    
    tinyMCE.setWindowArg("window", window);
    tinyMCE.setWindowArg("document", document);
    
    var formObj = document.forms[0];
    var href = formObj.href.value;
    
    // Call to external callback
    if (eval('typeof(tinyMCEPopup.windowOpener.' + cb + ')') == "undefined")
      alert("Callback function: " + cb + " could not be found.");
    else
      eval("tinyMCEPopup.windowOpener." + cb + "('href', href, 'image', window);");
  }
}


/* Functions for the camykslink plugin popup */

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
  
  document.getElementById('hrefbrowsercontainer').innerHTML = getFileBrowserHTML('filebrowser','href');
  document.getElementById('targetlistcontainer').innerHTML = getTargetListHTML('targetlist','target');

  // Resize some elements
  if (isVisible('filebrowser'))
    document.getElementById('href').style.width = '210px';
  
  elm = tinyMCE.getParentElement(elm, "a");
  if (elm != null && elm.nodeName == "A")
    action = "update";
  
  formObj.insert.value = tinyMCE.getLang('lang_' + action, 'Insert', true); 

  if (action == "update") {
    var href = tinyMCE.getAttrib(elm, 'href');
    
    href = convertURL(href, elm, true);

    if ( href.indexOf('#') != -1 ) {
      href = href.substring(0, href.indexOf('#'));
    }
      
    /* set select class list */
    addClassesToList('classlist', 'camyksfilelink_styles');

    /* set form data */
    setFormValue('href', href);
    setFormValue('title', tinyMCE.getAttrib(elm, 'title'));
        
    selectByValue(formObj, 'classlist', tinyMCE.getAttrib(elm, 'class'), true);
    selectByValue(formObj, 'targetlist', tinyMCE.getAttrib(elm, 'target'), true);
  } else
    addClassesToList('classlist', 'camyksfilelink_styles');
  
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
  var target = getSelectValue(formObj, 'targetlist');
  
  setAttrib(elm, 'href', href);
  setAttrib(elm, 'mce_href', href);
  setAttrib(elm, 'title');
  setAttrib(elm, 'target', target == '_self' ? '' : target);
  setAttrib(elm, 'id');
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

function getTargetListHTML(elm_id, target_form_element) {
  var html = '';
  
  html += '<select id="' + elm_id + '" name="' + elm_id + '" onfocus="tinyMCE.addSelectAccessibility(event, this, window);" onchange="this.form.' + target_form_element + '.value=';
  html += 'this.options[this.selectedIndex].value;">';
  html += '<option value="_self">'+tinyMCE.getLang('lang_camyksfilelink_target_same') + '</option>';
  html += '<option value="_blank">'+tinyMCE.getLang('lang_camyksfilelink_target_blank')+' (_blank)</option>';
  html += '<option value="_parent">'+tinyMCE.getLang('lang_camyksfilelink_target_parent')+' (_parent)</option>';
  html += '<option value="_top">'+tinyMCE.getLang('lang_camyksfilelink_target_top')+' (_top)</option>';
  html += '</select>';
  
  return html;
}

// While loading
preinit();
