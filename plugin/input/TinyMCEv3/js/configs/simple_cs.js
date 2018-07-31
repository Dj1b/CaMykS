/**
 * @brief TinyMCEv3 Input simple_cs configuration scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/TinyMCEv3/js/configs/simple_cs.js
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
