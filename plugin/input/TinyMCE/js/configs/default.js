/**
 * @brief TinyMCE Input default configuration scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/TinyMCE/js/configs/default.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Dec 2007
 * @date Modification: Jul 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
tinyMCE.init({
    mode : "textareas",
    theme : "advanced",
    plugins : "advimage,paste,searchreplace,table,preview,print,visualchars,media,camykslink,camyksemaillink,camyksfilelink",
    theme_advanced_toolbar_location : "top",
    theme_advanced_toolbar_align : "left",
    theme_advanced_path_location : "bottom",
    height : "400",
    file_browser_callback : "image_callback",
    page_browser_callback : "page_callback",

    theme_advanced_disable : "code,help,cleanup,link,anchor,unlink",
    theme_advanced_buttons1_add_before : "newdocument,cleanup,code,preview,print,help,separator,visualchars,separator",
    theme_advanced_buttons2_add_before : "cut,copy,paste,pastetext,pasteword,separator,search,replace,separator",
    theme_advanced_buttons3_add_before : "tablecontrols,separator",
    theme_advanced_buttons2_add : "media, separator, link, camyksfiles, mail, anchor, unlink",

    convert_urls : false,
    relative_urls : true,

    /* */
    editor_deselector : "mceNoEditor",

    /* camyks relative information */
    language : camyks_language,
    content_css : camyks_css_file,

    /* disable resizing */
    theme_advanced_resizing : false
});
