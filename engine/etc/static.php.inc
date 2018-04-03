<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Engine / Config file
 * Creation Date    : Sep 2005
 * Last Modif Date  : Apr 2018
 *
 * CaMykS global static configuration
 * Included in camyks object
*/

/* version */
$this->title = 'CaMykS';
$this->website = 'http://www.camyks.net';
$this->version = '1.0-20180401';
$this->mversion = '1.0';
$this->nversion = '20180401';
$this->last_modification_date = mktime(0, 0, 0, 4, 1, 2018);

/* paths & folders */
$this->visit_path = '../..';
$this->engine_folder = 'engine';
$this->plugin_folder = 'plugin';
$this->conf_folder = 'etc';
$this->var_folder = 'var';
$this->cache_folder= 'cache';

/* files */
$this->file_extension = '.php.inc';
$this->folder_name = 'camyks';

/* language */
$this->default_language = 'fr';
?>