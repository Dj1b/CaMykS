/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	  : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0a
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
    plugins : "safari",
    
    /* buttons lists */
    theme_advanced_buttons1 : "newdocument,cleanup,|,undo,redo,|,bold,italic,underline,strikethrough",
    theme_advanced_buttons1_add : ",|,justifyleft,justifycenter,justifyright,justifyfull",
    theme_advanced_buttons2 : "",
    theme_advanced_buttons3 : "",
    
    /* editor UI */
    theme_advanced_toolbar_location : "bottom",
    theme_advanced_toolbar_align : "center",
    theme_advanced_resizing : false,
    apply_source_formatting : true,
    
    /* blocks list */
    theme_advanced_blockformats : "p,div",
    
    /* camyks params */
    editor_deselector : "mceNoEditor",
    
    /* camyks information */
    language : camyks_language,
    });
