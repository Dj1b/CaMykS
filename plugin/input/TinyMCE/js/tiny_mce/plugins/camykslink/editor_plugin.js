/*
 *   
 */

/* Import plugin specific language pack */
tinyMCE.importPluginLanguagePack('camykslink');

var CaMykSLinkPlugin = {
  getInfo : function() {
    return {
      longname : 'CaMykS Link',
	author : 'CaMykS Team',
	authorurl : '',
	infourl : '',
	version : tinyMCE.majorVersion + "." + tinyMCE.minorVersion
	};
  },
  
  initInstance : function(inst) {
    inst.addShortcut('ctrl', 'k', 'lang_camykslink_desc', 'CaMykSLink');
  },
  
  getControlHTML : function(cn) {
    switch (cn) {
    case "link":
      return tinyMCE.getButtonHTML(cn, 'lang_camykslink_desc', '{$pluginurl}/images/icon.gif', 'CaMykSLink');
    }
    
    return "";
  },
  
  execCommand : function(editor_id, element, command, user_interface, value) {
    switch (command) {
    case "CaMykSLink":
      var anySelection = false;
      var inst = tinyMCE.getInstanceById(editor_id);
      var focusElm = inst.getFocusElement();
      var selectedText = inst.selection.getSelectedText();
      
      if (tinyMCE.selectedElement)
	anySelection = (tinyMCE.selectedElement.nodeName.toLowerCase() == "img") || (selectedText && selectedText.length > 0);
      
      if (anySelection || (focusElm != null && focusElm.nodeName == "A")) {
	var template = new Array();
	
	template['file']   = '../../plugins/camykslink/link.htm';
	template['width']  = 350;
	template['height'] = 240;
	
	// Language specific width and height addons
	template['width']  += tinyMCE.getLang('lang_advlink_delta_width', 0);
	template['height'] += tinyMCE.getLang('lang_advlink_delta_height', 0);
	
	tinyMCE.openWindow(template, {editor_id : editor_id, inline : "yes"});
      } 
      return true;
    }
    return false;
  },
  
  handleNodeChange : function(editor_id, node, undo_index, undo_levels, visual_aid, any_selection) {
    if (node == null)
      return;
    
    do {
      if (node.nodeName == "A" && tinyMCE.getAttrib(node, 'href') != "" && tinyMCE.getAttrib(node, 'title') != 'email') {
	tinyMCE.switchClass(editor_id + '_link', 'mceButtonSelected');
	return true;
      }
    } while ((node = node.parentNode));
    
    if (any_selection) {
      tinyMCE.switchClass(editor_id + '_link', 'mceButtonNormal');
      return true;
    }
    
    tinyMCE.switchClass(editor_id + '_link', 'mceButtonDisabled');
    return true;
  }
};

tinyMCE.addPlugin("camykslink", CaMykSLinkPlugin);
