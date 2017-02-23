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
 * Plugin main scripts
 */
(function() {

tinymce.create('tinymce.plugins.GenericMediaPopup', {
	init : function(ed) {
		    	
		/* Register commands */
		ed.addCommand('insertMediaPopupLink', function() {
		    
			var se = ed.selection;

			// No selection and not in link
			if (se.isCollapsed() && !ed.dom.getParent(se.getNode(), 'A'))
				return; 

			ed.windowManager.open({
				file : camyks_plugin_url + '/input/GenericMediaPopup/js/tinymce_plugin/link.htm',
				width : 338 + parseInt(ed.getLang('advlink.delta_width', 0)),
				height : 168 + parseInt(ed.getLang('advlink.delta_height', 0)),
				inline : 1
			}, {
				plugin_url : camyks_plugin_url + '/input/GenericMediaPopup/js/tinymce_plugin'
			});
		});

		/* Register buttons */
		ed.addButton('insertMediaPopupLink', {
		    title : 'mediapopup.desc',
			cmd : 'insertMediaPopupLink',
			image : camyks_plugin_url + '/input/GenericMediaPopup/js/tinymce_plugin/img/icon.gif'
		});

		ed.onNodeChange.add(function(ed, cm, n, co) {
			cm.setDisabled('insertMediaPopupLink', co && n.nodeName != 'A');
			cm.setActive('insertMediaPopupLink', n.nodeName == 'A' && n.href.indexOf('javascript:mediaPopup_open') != -1);
		});
	},

	getInfo : function() {
		return {
		  longname : 'Media Popup Editor',
		  author : 'CaMykS Team',
		  authorurl : 'http://www.camyks.net',
		  infourl : '',
		  version : '1.0'
		};
	},
});

// Register plugin
tinymce.PluginManager.add('genericmediapopup', tinymce.plugins.GenericMediaPopup);

})();