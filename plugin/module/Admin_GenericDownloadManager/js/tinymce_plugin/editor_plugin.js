/*
 * CaMykS Engine
 * Developed by			: camyks.net
 * Author						: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version		: 1.0b1
 * Object Version		: 1.0
 * Object Type      : Plugin / Javacript
 * Creation Date   	: Jan 2011
 * Last Modif Date	: Jan 2011
 *
 * Admin_GenericDownloadManager external plugin for TinyMCE
 * Plugin main scripts
 */
(function() {

tinymce.create('tinymce.plugins.GenericDownloadManager', {
	init : function(ed) {
		
		/* Register commands */
		ed.addCommand('insertDownloadLink', function() {
			var se = ed.selection;

			// No selection and not in link
			if (se.isCollapsed() && !ed.dom.getParent(se.getNode(), 'A'))
				return; 

			ed.windowManager.open({
				file : camyks_plugin_url+'/module/Admin_GenericDownloadManager/js/tinymce_plugin/link.htm',
				width : 338 + parseInt(ed.getLang('advlink.delta_width', 0)),
				height : 144 + parseInt(ed.getLang('advlink.delta_height', 0)),
				inline : 1
			}, {
				plugin_url : camyks_plugin_url+'/module/Admin_GenericDownloadManager/js/tinymce_plugin'
			});
		});

		/* Register buttons */
		ed.addButton('insertDownloadLink', {
		title : 'genericdownloadmanager.desc',
			cmd : 'insertDownloadLink',
			image : camyks_plugin_url+'/module/Admin_GenericDownloadManager/js/tinymce_plugin/img/icon.gif'
		});

		ed.onNodeChange.add(function(ed, cm, n, co) {
			cm.setDisabled('insertDownloadLink', co && n.nodeName != 'A');
			cm.setActive('insertDownloadLink', n.nodeName == 'A' && n.href.indexOf('request.php?module=Admin_GenericDownloadManager') > 1);
		});
	},

	getInfo : function() {
		return {
		  longname : 'CaMykS Download Manager Shortcut',
		  author : 'CaMykS Team',
		  authorurl : 'http://www.camyks.net',
		  infourl : '',
		  version : '1.0'
		};
	},
});

// Register plugin
tinymce.PluginManager.add('genericdownloadmanager', tinymce.plugins.GenericDownloadManager);

})();

function get_ajaxObject(name) {
	return new CAjaxRequest(name);
}