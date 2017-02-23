/*
 *   
 */

/* Import plugin specific language pack */
tinyMCE.importPluginLanguagePack('camyksemaillink');

var CaMykSEmailLinkPlugin = {
  getInfo : function() {
    return {
      longname : 'CaMykS Email Link',
	author : 'CaMykS Team',
	authorurl : '',
	infourl : '',
	version : tinyMCE.majorVersion + "." + tinyMCE.minorVersion
	};
  },
  
  initInstance : function(inst) {
    inst.addShortcut('ctrl', 'm', 'lang_camyksemaillink_desc', 'CaMykSEmailLink');
  },
  
  getControlHTML : function(cn) {
    switch (cn) {
    case "mail":
      return tinyMCE.getButtonHTML(cn, 'lang_camyksemaillink_desc', '{$pluginurl}/images/mail.gif', 'CaMykSEmailLink');
    }
    
    return "";
  },
  
  execCommand : function(editor_id, element, command, user_interface, value) {
    switch (command) {
    case "CaMykSEmailLink":
      var anySelection = false;
      var inst = tinyMCE.getInstanceById(editor_id);
      var focusElm = inst.getFocusElement();
      var selectedText = inst.selection.getSelectedText();
      
      if (tinyMCE.selectedElement)
	anySelection = (tinyMCE.selectedElement.nodeName.toLowerCase() == "img") || (selectedText && selectedText.length > 0);
      
      if (anySelection || (focusElm != null && focusElm.nodeName == "A")) {
	var template = new Array();
	
	template['file']   = '../../plugins/camyksemaillink/link.htm';
	template['width']  = 350;
	template['height'] = 120;
	
	/* Language specific width and height addons */
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

      if (node.nodeName == "A" && tinyMCE.getAttrib(node, 'href') != "" && tinyMCE.getAttrib(node, 'title') == 'email') {
	tinyMCE.switchClass(editor_id + '_mail', 'mceButtonSelected');
	return true;
      }
    } while ((node = node.parentNode));
    
    if (any_selection) {
      tinyMCE.switchClass(editor_id + '_mail', 'mceButtonNormal');
      return true;
    }
    
    tinyMCE.switchClass(editor_id + '_mail', 'mceButtonDisabled');
    
    return true;
  }
};

tinyMCE.addPlugin("camyksemaillink", CaMykSEmailLinkPlugin);
