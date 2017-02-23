/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Javascript
 * Create Date		: Jul 2008
 * Last Modif Date	: Jul 2008
 * 
 * TinyMCEv3 input : TinyMCE 3 WebEditor Integration config file
 */
 
tinyMCE.init({
  mode : "textareas",
    theme : "advanced",
    
    /* enabled plugins */
    plugins : "safari,inlinepopups,style,advimage,camykslink,camyksemaillink",
    
    /* buttons lists */
    theme_advanced_buttons1 : "newdocument,cleanup,|,undo,redo,|,bold,italic,underline,strikethrough",
    theme_advanced_buttons1_add : ",|,justifyleft,justifycenter,justifyright,justifyfull,|,formatselect,styleselect,|,image,link,camyksemaillink,unlink,|,charmap",
    theme_advanced_buttons2 : "",
    theme_advanced_buttons3 : "",
    
    /* editor UI */
    theme_advanced_toolbar_location : "top",
    theme_advanced_toolbar_align : "left",
    theme_advanced_statusbar_location : "bottom",
    theme_advanced_resizing : true,
    theme_advanced_resize_horizontal : false,
    theme_advanced_resizing_min_height : 360,
    apply_source_formatting : true,
    
    /* blocks list */
    theme_advanced_blockformats : "p,div,blockquote,address,pre,h1,h2,h3,h4",
    
    /* editor params */
    editor_deselector : "mceNoEditor",
    entity_encoding : "numeric",
    
    /* camyks plugins */
    file_browser_callback : "image_callback",
    page_browser_callback : "page_callback",
    
    /* camyks information */
    language : camyks_language,
    content_css : camyks_css_file,
    });
