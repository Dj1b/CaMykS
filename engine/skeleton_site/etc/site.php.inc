<?php
/**
 * @brief Website configuration file
 * @details Skeleton site / Site Configuration
 * @file engine/skeleton_site/etc/site.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Sep 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* Site configuration object */
$conf = array();
/* CMS name : CaMykS */
$conf['cms'] = 'CaMykS';
/* CMS version */
$conf['cms_version'] = '1.0b';
/* path to CaMykS folder */
$conf['engine_path'] = '';
/* site symbolic name ( folder name ) */
$conf['site_name'] = '';
/* site title */
$conf['site_title'] = '';
/* site url starting by 'http://' */
$conf['url'] = '';
/* site encoding : utf8 */
$conf['encoding'] = '';
/* html version */
$conf['html_version'] = 5;
/* html IE compatibility tag */
$conf['html_compatibilityTag'] = '';
/* site version */
$conf['version'] = '';
/* site admin entry point : admin.php by default */
$conf['admin_entry'] = 'admin.php';
/* site url rewriting */
$conf['friendlyurls'] = 1;
/* site author */
$conf['site_author'] = '';
/* site author company or organisation */
$conf['site_company'] = '';
/* site workflow active */
$conf['workflow'] = 0;
/* site in maintenance */
$conf['maintenance'] = 0;
/* database config */
$conf['database_driver'] = '';
$conf['database_name'] = '';
$conf['database_host'] = '';
$conf['database_login'] = '';
$conf['database_pwd'] = '';
/* site admin ssl : default | auto | forced | none */
$conf['admin_ssl'] = 'default';
/* site admin default language : fr, en */
$conf['admin_default_language'] = 'fr';
/* site admin available languages, set at least one language */
$conf['admin_languages'] = array('fr');
/* site admin theme : IndigoFlatStyle as default */
$conf['admin_default_theme'] = 'IndigoFlatStyle';
/* site ssl : default | auto | forced | none */
$conf['site_ssl'] = 'default';
/* site default theme : no theme as default */
$conf['site_default_theme'] = '';
/* site default template : no template as default  */
$conf['site_default_template'] = '';
/* site available languages */
$conf['site_languages'] = array('fr');
/* site default language */
$conf['site_default_language'] = 'fr';
/* site available language for edition */
$conf['editing_languages'] = array('fr');
/* site maximum module by page : can't be raise later, 5 is a classic value, 8 is security */
$conf['page_maxmodules'] = 8;
/* cache settings */
$conf['cache_server_side'] = ''; // currently not compatible with responsive design
$conf['cache_client_side'] = '';
/* enable handheld version */
$conf['enable_handheldVersion'] = 0;
/* enable responsive design */
$conf['enable_responsiveDesign'] = 0;
?>
