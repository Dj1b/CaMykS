/**
 * @brief TinyMCEv3 Input flash configuration scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/TinyMCEv3/js/configs/flash.js
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
    plugins : "safari,inlinepopups,style,camykslink,camyksemaillink",

    /* buttons lists */
    theme_advanced_buttons1 : "newdocument,cleanup,|,undo,redo,|,bold,italic,underline",
    theme_advanced_buttons1_add : ",|,styleselect,|,link,unlink,|,charmap",
    theme_advanced_buttons2 : "",
    theme_advanced_buttons3 : "",

    /* editor UI */
    theme_advanced_toolbar_location : "top",
    theme_advanced_toolbar_align : "left",
    theme_advanced_statusbar_location : "bottom",
    theme_advanced_resizing : false,
    apply_source_formatting : true,

    /* valid html tags */
    valid_elements : "+a[href|target|class],#p[class|align],#span[class],br,-b,-i,-u,-div[align|class]",

    /* camyks params */
    editor_deselector : "mceNoEditor",

    /* camyks plugins */
    page_browser_callback : "page_callback",

    /* camyks information */
    language : camyks_language,
    content_css : camyks_css_file,
    relative_urls : camyks_relative_urls,
    remove_script_host : camyks_remove_host,
});
