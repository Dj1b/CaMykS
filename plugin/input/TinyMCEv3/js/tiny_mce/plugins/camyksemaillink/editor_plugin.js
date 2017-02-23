/**
 * $Id: editor_plugin_src.js 539 2008-01-14 19:08:58Z spocke $
 *
 * @author Moxiecode
 * @copyright Copyright © 2004-2008, Moxiecode Systems AB, All rights reserved.
 */

(function() {
  // Load plugin specific language pack
	tinymce.PluginManager.requireLangPack('camyksemaillink');
	
	
	tinymce.create('tinymce.plugins.CaMykSEmailLinkPlugin', {
		init : function(ed, url) {
			this.editor = ed;

			// Register commands
			ed.addCommand('CaMykSEmailLink', function() {
				var se = ed.selection;

				// No selection and not in link
				if (se.isCollapsed() && !ed.dom.getParent(se.getNode(), 'A'))
					return;

				ed.windowManager.open({
					file : url + '/link.htm',
					width : 320 + parseInt(ed.getLang('advlink.delta_width', 0)),
					height : 120 + parseInt(ed.getLang('advlink.delta_height', 0)),
					inline : 1
				}, {
					plugin_url : url
				});
			});

			// Register buttons
			ed.addButton('camyksemaillink', {
				title : 'camyksemaillink.desc',
				cmd : 'CaMykSEmailLink',
				image : url + '/img/mail.gif'
			});

			//ed.addShortcut('ctrl+k', 'advlink.advlink_desc', 'mceAdvLink');

			ed.onNodeChange.add(function(ed, cm, n, co) {
				cm.setDisabled('camyksemaillink', co && n.nodeName != 'A');
				cm.setActive('camyksemaillink', n.nodeName == 'A' && n.title == 'email' && !n.name);
			});
		},

		getInfo : function() {
			return {
				longname : 'CaMykS Email Link Editor',
				author : 'CaMykS Team',
				authorurl : 'http://www.camyks.net',
				infourl : '',
			        version : '1.0'
			};
		}
	});

	// Register plugin
	tinymce.PluginManager.add('camyksemaillink', tinymce.plugins.CaMykSEmailLinkPlugin);
})();
