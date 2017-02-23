/* Functions for the advlink plugin popup */

tinyMCEPopup.requireLangPack();

var templates = {
  "window.open" : "window.open('${url}','${target}','${options}')"
};

function preinit() {
  var url;
}

function changeClass() {
}

function init() {
  tinyMCEPopup.resizeToInnerSize();
  
  var formObj = document.forms[0];
  var inst = tinyMCEPopup.editor;
  var elm = inst.selection.getNode();
  var action = "insert";
  var html;
  var anchor;
  
  document.getElementById('pagebrowsercontainer').innerHTML = getPageBrowserHTML('pagebrowser','href','page','advlink');
  document.getElementById('filebrowsercontainer').innerHTML = getFileBrowserHTML('filebrowser','href','file','advlink');
  document.getElementById('targetlistcontainer').innerHTML = getTargetListHTML('targetlist','target');
  
  // Resize some elements
  if (isVisible('filebrowser') && isVisible('pagebrowser'))
    document.getElementById('href').style.width = '236px';
  else if(isVisible('filebrowser') || isVisible('pagebrowser'))
    document.getElementById('href').style.width = '260px';
  
  elm = inst.dom.getParent(elm, "A");
  if (elm != null && elm.nodeName == "A")
    action = "update";
  
  formObj.insert.value = tinyMCEPopup.getLang(action, 'Insert', true); 
  
  if (action == "update") {
    var url = inst.dom.getAttrib(elm, 'href');
    url = url.split('#');
    if ( url.length > 1 ) {
      href = url[0];
      anchor = url[1];
    } else {
      href = url[0];
      anchor = '';
    }
    
    // Setup form data
    setFormValue('href', href);
    setFormValue('anchor', anchor);
    setFormValue('title', inst.dom.getAttrib(elm, 'title'));
    
    addClassesToList('classlist', 'camykslink_styles');
    
    selectByValue(formObj, 'classlist', inst.dom.getAttrib(elm, 'class'), true);
    selectByValue(formObj, 'targetlist', inst.dom.getAttrib(elm, 'target'), true);
  } else
    addClassesToList('classlist', 'advlink_styles');
}

function checkPrefix(n) {
  if (n.value && Validator.isEmail(n) && !/^\s*mailto:/i.test(n.value) && confirm(tinyMCEPopup.getLang('camykslink_dlg.is_email')))
    n.value = 'mailto:' + n.value;
  
  if (/^\s*www./i.test(n.value) && confirm(tinyMCEPopup.getLang('camykslink_dlg.is_external')))
    n.value = 'http://' + n.value;
}

function setFormValue(name, value) {
  document.forms[0].elements[name].value = value;
}

function parseFunction(onclick) {
  var formObj = document.forms[0];
  var onClickData = parseLink(onclick);
  
  // TODO: Add stuff here
}

function getOption(opts, name) {
  return typeof(opts[name]) == "undefined" ? "" : opts[name];
}

function parseLink(link) {
  link = link.replace(new RegExp('&#39;', 'g'), "'");
  
  var fnName = link.replace(new RegExp("\\s*([A-Za-z0-9\.]*)\\s*\\(.*", "gi"), "$1");
  
  // Is function name a template function
  var template = templates[fnName];
  if (template) {
    // Build regexp
    var variableNames = template.match(new RegExp("'?\\$\\{[A-Za-z0-9\.]*\\}'?", "gi"));
    var regExp = "\\s*[A-Za-z0-9\.]*\\s*\\(";
    var replaceStr = "";
    for (var i=0; i<variableNames.length; i++) {
      // Is string value
      if (variableNames[i].indexOf("'${") != -1)
	regExp += "'(.*)'";
      else // Number value
	regExp += "([0-9]*)";
      
      replaceStr += "$" + (i+1);
      
      // Cleanup variable name
      variableNames[i] = variableNames[i].replace(new RegExp("[^A-Za-z0-9]", "gi"), "");
      
      if (i != variableNames.length-1) {
	regExp += "\\s*,\\s*";
	replaceStr += "<delim>";
      } else
	regExp += ".*";
    }
    
    regExp += "\\);?";
    
    // Build variable array
    var variables = [];
    variables["_function"] = fnName;
    var variableValues = link.replace(new RegExp(regExp, "gi"), replaceStr).split('<delim>');
    for (var i=0; i<variableNames.length; i++)
      variables[variableNames[i]] = variableValues[i];
    
    return variables;
  }
  
  return null;
}

function parseOptions(opts) {
  if (opts == null || opts == "")
    return [];
  
  // Cleanup the options
  opts = opts.toLowerCase();
  opts = opts.replace(/;/g, ",");
  opts = opts.replace(/[^0-9a-z=,]/g, "");
  
  var optionChunks = opts.split(',');
  var options = [];
  
  for (var i=0; i<optionChunks.length; i++) {
    var parts = optionChunks[i].split('=');
    
    if (parts.length == 2)
      options[parts[0]] = parts[1];
  }
  
  return options;
}

function setAttrib(elm, attrib, value) {
  var formObj = document.forms[0];
  var valueElm = formObj.elements[attrib.toLowerCase()];
  var dom = tinyMCEPopup.editor.dom;
  
  if (typeof(value) == "undefined" || value == null) {
    value = "";
    
    if (valueElm)
      value = valueElm.value;
  }
  
  // Clean up the style
  if (attrib == 'style')
    value = dom.serializeStyle(dom.parseStyle(value));
  
  dom.setAttrib(elm, attrib, value);
}

function insertAction() {
  var inst = tinyMCEPopup.editor;
  var elm, elementArray, i;
  
  elm = inst.selection.getNode();
  checkPrefix(document.forms[0].href);
  elm = inst.dom.getParent(elm, "A");
  
  // Remove element if there is no href and no anchor
  if (document.forms[0].href.value == '' && document.forms[0].anchor.value == '') {
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
  var anchor = formObj.anchor.value;
  if ( anchor != '' )
    href += '#'+anchor;
  var target = getSelectValue(formObj, 'targetlist');
  
  setAttrib(elm, 'href', href);
  setAttrib(elm, 'mce_href', href);
  setAttrib(elm, 'title');
  setAttrib(elm, 'target', target == '_self' ? '' : target);
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
  var targets = tinyMCEPopup.getParam('theme_advanced_link_targets', '').split(';');
  var html = '';
  
  html += '<select id="' + elm_id + '" name="' + elm_id + '" onchange="this.form.' + target_form_element + '.value=';
  html += 'this.options[this.selectedIndex].value;">';
  html += '<option value="_self">' + tinyMCEPopup.getLang('camykslink_dlg.target_same') + '</option>';
  html += '<option value="_blank">' + tinyMCEPopup.getLang('camykslink_dlg.target_blank') + ' (_blank)</option>';
  html += '<option value="_parent">' + tinyMCEPopup.getLang('camykslink_dlg.target_parent') + ' (_parent)</option>';
  html += '<option value="_top">' + tinyMCEPopup.getLang('camykslink_dlg.target_top') + ' (_top)</option>';
  
  for (var i=0; i<targets.length; i++) {
    var key, value;
    
    if (targets[i] == "")
      continue;
    
    key = targets[i].split('=')[0];
    value = targets[i].split('=')[1];
    
    html += '<option value="' + key + '">' + value + ' (' + key + ')</option>';
  }
  
  html += '</select>';
  
  return html;
}

/* page browser link */
function getPageBrowserHTML(id, target_form_element, type, prefix) {
  var option = prefix + "_" + type + "_browser_callback", cb, html;
  cb = tinyMCEPopup.getParam(option, tinyMCEPopup.getParam("page_browser_callback"));
  
  if (!cb)
    return "";
  
  html = "";
  html += '<a id="' + id + '_link" href="javascript:openCaMykSBrowser(\'' + id + '\',\'' + target_form_element + '\', \'' + type + '\',\'' + option + '\');" onmousedown="return false;" class="browse pagelink">';
  html += '<span id="' + id + '" title="' + tinyMCEPopup.getLang('camykslink_dlg.browsepage') + '"></span></a>';
  
  return html;
}

/* file browser link */
function getFileBrowserHTML(id, target_form_element, type, prefix) {
  var option = prefix + "_" + type + "_browser_callback", cb, html;
  
  cb = tinyMCEPopup.getParam(option, tinyMCEPopup.getParam("file_browser_callback"));
  
  if (!cb)
    return "";
  
  html = "";
  html += '<a id="' + id + '_link" href="javascript:openCaMykSBrowser(\'' + id + '\',\'' + target_form_element + '\', \'' + type + '\',\'' + option + '\');" onmousedown="return false;" class="browse filelink">';
  html += '<span id="' + id + '" title="' + tinyMCEPopup.getLang('camykslink_dlg.browsefile') + '"></span></a>';
  
  return html;
}

/* open selected browser */
function openCaMykSBrowser(element_id, target_form_element, type, option) {
  var img = document.getElementById(element_id);
  
  if (img.className == "mceButtonDisabled")
    return;
  
  tinyMCEPopup.restoreSelection();
  tinyMCEPopup.editor.execCallback(type+'_browser_callback', target_form_element, document.getElementById(target_form_element).value, type, window);
}

// While loading
preinit();
tinyMCEPopup.onInit.add(init);
