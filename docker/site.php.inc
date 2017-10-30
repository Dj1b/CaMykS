<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * Object Version	: 1.0b1
 * Object Type      : Site Configuration
 * Creation Date    : Jun 2005
 * Last Modif Date  : Oct 2010
 *
 */

/* Site configuration object */
$conf = array();
/* CMS name : CaMykS */
$conf['cms'] = 'CaMykS';
/* CMS version */
$conf['cms_version'] = '1.0';
/* path to CaMykS folder */
$conf['engine_path'] = 'camyks';
/* site symbolic name ( folder name ) */
$conf['site_name'] = 'CaMyKs';
/* site title */
$conf['site_title'] = 'CaMyKs';
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
$conf['database_driver'] = 'MySQLi';
$conf['database_name'] = 'camyks';
$conf['database_host'] = 'localhost';
$conf['database_login'] = 'camyks';
$conf['database_pwd'] = 'camyks';
/* site admin ssl : default | auto | forced | none */
$conf['admin_ssl'] = 'default';
/* site admin default language : fr, en */
$conf['admin_default_language'] = 'en';
/* site admin available languages, set at least one language */
$conf['admin_languages'] = array('en');
/* site admin theme : GreyStyle as default */
$conf['admin_default_theme'] = 'IndigoFlatStyle';
/* site ssl : default | auto | forced | none */
$conf['site_ssl'] = 'default';
/* site default theme : GreyStyle as default */
$conf['site_default_theme'] = '';
/* site default template : DefaultPage as default  */
$conf['site_default_template'] = 'DefaultPage';
/* site available languages */
$conf['site_languages'] = array('en');
/* site default language */
$conf['site_default_language'] = 'en';
/* site available language for edition */
$conf['editing_languages'] = array('en');
/* site maximum module by page : can't be raise later, 5 is a classic value, 8 is security */
$conf['page_maxmodules'] = 8;
/* site google analytics code */
$conf['google_analytics'] = '';
$conf['google_analytics_domain'] = '';
/* cache settings */
$conf['cache_server_side'] = ''; // currently not compatible with responsive design
$conf['cache_client_side'] = '';
/* enable handheld version */
$conf['enable_handheldVersion'] = 0;
/* enable responsive design */
$conf['enable_responsiveDesign'] = 0;
?>