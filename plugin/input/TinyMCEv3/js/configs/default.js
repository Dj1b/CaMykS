/**
 * @brief TinyMCEv3 Input default configuration scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/TinyMCEv3/js/configs/default.js
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Jul 2008
 * @date Modification: Jul 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
tinyMCE.init({
    mode : "textareas",
    theme : "advanced",

    /* enabled plugins */
    plugins : "safari,inlinepopups,style,layer,table,advimage,advhr,preview,media,searchreplace,print,paste,directionality,fullscreen,noneditable,visualchars,nonbreaking,xhtmlxtras,pagebreak,camykslink,camyksemaillink,camyksloremipsum,camykscontextmenu," + camyks_ext_plugins,

    /* buttons lists */
    theme_advanced_buttons1 : "newdocument,camyksloremipsum,fullscreen,preview,print,code,help,|,bold,italic,underline,strikethrough",
    theme_advanced_buttons1_add : ",|,justifyleft,justifycenter,justifyright,justifyfull,|,formatselect,styleselect,|,removeformat,",
    theme_advanced_buttons2 : "pastetext,pasteword,|,search,replace,|,undo,redo,|,ltr,rtl,visualchars,pagebreak",
    theme_advanced_buttons2_add : ",|,bullist,numlist,|,outdent,indent,|,sub,sup,|,image,media,|,link,camyksemaillink,anchor,unlink",
    theme_advanced_buttons3 : "advhr,|,tablecontrols,separator,insertlayer,moveforward,movebackward,absolute,|,cite,acronym,abbr,attribs,|,charmap,|,cleanup",
    theme_advanced_buttons4 : "" + camyks_ext_buttons,

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

    /* camyks plugins */
    file_browser_callback : "image_callback",
    page_browser_callback : "page_callback",

    /* camyks information */
    language : camyks_language,
    content_css : camyks_css_file,
    relative_urls : camyks_relative_urls,
    remove_script_host : camyks_remove_host
});
