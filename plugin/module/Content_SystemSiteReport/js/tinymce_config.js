/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Dec 2007
 * Last Modif Date	: Dec 2007
 *
 * WebEditor TinyMCE config file
 */
tinyMCE.init({
  mode : "textareas",
    theme : "advanced",
    plugins : "advimage,camykslink",
    theme_advanced_toolbar_location : "top",
    theme_advanced_toolbar_align : "left",
    theme_advanced_path_location : "bottom",
    height : "400",
    page_browser_callback : "page_callback",
    
    theme_advanced_buttons1 : "bold, italic, underline, separator, styleselect, separator, link, unlink, separator,undo, redo, separator, cleanup, code ",
    theme_advanced_buttons2 : "",
    theme_advanced_buttons3 : "",
    
    valid_elements : "+a[href|target|class],#p[class],#span[class],br,-strong/-b,-em/-i,-div[align]",
    
    convert_urls : false,
    relative_urls : true,

    editor_deselector : "mceNoEditor",

    /* camyks relative information */
    language : camyks_language,
    content_css : camyks_css_file,

    /* disable resizing */
    theme_advanced_resizing : false
    });
