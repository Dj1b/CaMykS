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
 * Advanced Config
 */
tinyMCE.init({
  mode : "textareas",
    theme : "advanced",
    plugins : "advimage,searchreplace,visualchars,media,camykslink,camyksemaillink,camyksfilelink",
    theme_advanced_toolbar_location : "top",
    theme_advanced_toolbar_align : "left",
    theme_advanced_path_location : "bottom",
    height : "400",
    file_browser_callback : "image_callback",
    page_browser_callback : "page_callback",

    theme_advanced_buttons1 : "newdocument, cleanup, undo, redo, separator, visualchars, separator, bold, italic, underline, strikethrough, separator, justifyleft, justifycenter, justifyright, justifyfull, separator, styleselect, formatselect",
    theme_advanced_buttons2 : "cut,copy,paste,separator,search,replace,separator, bullist, numlist, separator, charmap,  separator, image, media, separator, link, camyksfiles, mail, anchor, unlink",
    theme_advanced_buttons3 : "",

    convert_urls : false,
    relative_urls : true,

    /* */
    editor_deselector : "mceNoEditor",
    entity_encoding : "numeric",

    /* camyks relative information */
    language : camyks_language,
    content_css : camyks_css_file,

    /* disable resizing */
    theme_advanced_resizing : false
    });
