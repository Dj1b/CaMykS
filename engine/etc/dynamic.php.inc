<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author	        : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type		: Engine / Config file
 * Creation Date	: Sep 2005
 * Last Modif Date	: Feb 2017
 * History :
 *
 * CaMykS global dynamic configuration,
 * each configuration value can be updated into site configuration file
 */
 
$this->_conf = array();

/* generic encoding configuration */
$this->_conf['server_encoding'] = '';

/* generic database configuration */
$this->_conf['database_host'] = '';
$this->_conf['database_login'] = '';
$this->_conf['database_pwd'] = '';

/* PEAR libs configuration */
$this->_conf['PEARMailDriver'] = 'smtp';
$this->_conf['PEARMailConfig'] = array('host'=>'smtp.orange.fr'); 

/* module configuration */
$this->_conf['ModuleActionDelay'] = 1;

/* define time zone */
$this->_conf['TimeZone'] = 'Europe/Paris';

/* user agent for requests */
$this->_conf['UserAgent'] = 'Mozilla/5.0 (compatible; CaMykSRequest/1.0; +http://www.camyks.net/request_bot.html)';

?>