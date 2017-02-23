/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	  : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Javascript
 * Creation Date		: Jul 2008
 * Last Modif Date	: Jul 2008
 * 
 * TinyMCEv3 input : TinyMCE 3 WebEditor Integration config file
 */
 
tinyMCE.init({
  mode : "textareas",
    theme : "advanced",
    
    /* enabled plugins */
    plugins : "safari,inlinepopups,camyksemaillink",
    
    /* buttons lists */
    theme_advanced_buttons1 : "newdocument,cleanup,|,undo,redo,|,justifyleft,justifycenter,justifyright,justifyfull",
    theme_advanced_buttons1_add : ",|,formatselect,styleselect",
    theme_advanced_buttons2 : "bold,italic,underline,strikethrough,|,image,link,camyksemaillink,unlink,|,charmap",
    theme_advanced_buttons3 : "",
    
    /* editor UI */
    theme_advanced_toolbar_location : "top",
    theme_advanced_toolbar_align : "left",
    theme_advanced_statusbar_location : "bottom",
    theme_advanced_resizing : false,
    apply_source_formatting : true,
    
    /* blocks list */
    theme_advanced_blockformats : "p,div,blockquote,address,pre,h1,h2,h3,h4",
    
    /* camyks params */
    editor_deselector : "mceNoEditor",
    
    /* camyks information */
    language : camyks_language,
    content_css : camyks_css_file,
    });
