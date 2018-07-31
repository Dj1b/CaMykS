/**
 * @brief TinyMCEv3 Input textual configuration scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/TinyMCEv3/js/configs/textual.js
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
