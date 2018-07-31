/**
 * @brief TinyMCEv3 Input classic_cs configuration scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/TinyMCEv3/js/configs/classic_cs.js
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
    plugins : "safari,inlinepopups,style,advimage,preview,media,searchreplace,print,contextmenu,paste,directionality,noneditable,visualchars,nonbreaking,pagebreak,camykslink,camyksemaillink",

    /* buttons lists */
    theme_advanced_buttons1 : "newdocument,|,preview,print,cleanup,|,bold,italic,underline,strikethrough",
    theme_advanced_buttons1_add : ",|,justifyleft,justifycenter,justifyright,justifyfull,|,formatselect,styleselect,|,removeformat,",
    theme_advanced_buttons2 : "pastetext,pasteword,|,search,replace,|,undo,redo,|,ltr,rtl,visualchars,pagebreak",
    theme_advanced_buttons2_add : ",|,bullist,numlist,|,outdent,indent,|,sub,sup,|,image,media,|,link,camyksemaillink,anchor,unlink,|,charmap",
    theme_advanced_buttons3 : "",

    /* editor UI */
    theme_advanced_toolbar_location : "top",
    theme_advanced_toolbar_align : "left",
    theme_advanced_statusbar_location : "bottom",
    theme_advanced_resizing : true,
    theme_advanced_resize_horizontal : false,
    theme_advanced_resizing_min_height: 360,
    apply_source_formatting : true,

    /* blocks list */
    theme_advanced_blockformats : "p,div,blockquote,address,pre,h1,h2,h3,h4",

    /* camyks params */
    editor_deselector : "mceNoEditor",

    /* camyks information */
    language : camyks_language,
    content_css : camyks_css_file,
});
