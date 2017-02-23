/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Javascript
 * Create Date		: Apr 2007
 * Last Modif Date	: Apr 2008
 * 
 * Admin_GenericBlogsManager scripts : TinyMCE WebEditor Integration config file
 * Light Config
 */
tinyMCE.init({
  mode : "textareas",
    theme : "advanced",
    plugins : "",

    theme_advanced_toolbar_location : "top",
    theme_advanced_toolbar_align : "left",
    theme_advanced_path_location : "bottom",
    height : "400",

    theme_advanced_buttons1 : "bold, italic, underline, strikethrough, separator, link, unlink, separator undo, redo, clean ",
    theme_advanced_buttons2 : "",
    theme_advanced_buttons3 : "",

    convert_urls : false,
    relative_urls : true,

    /* */
    editor_deselector : "mceNoEditor",
    entity_encoding : "numeric",

    /* camyks relative information */
    language : camyks_language,

    /* disable resizing */
    theme_advanced_resizing : false
    });
