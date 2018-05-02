<?php
/**
 * @brief CaMykS dynamic configuration
 * @brief Automatically loaded by CaMykS object.
 * @details Engine / Configuration file
 * @file engine/etc/dynamic.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Sep 2005
 * @date Modification: Apr 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
 
/**
 * @var array $this->_conf
 * @brief CaMykS Configuration
 * @brief Available parameters are <br />
 * @brief \e string server_encoding - Default 'utf8'. <br />
 * @brief \e string database_driver - Multisite database driver. <br />
 * @brief \e string database_host - Multisite database host. <br />
 * @brief \e string database_login - Multisite database login. <br />
 * @brief \e string database_password - Multisite database password. <br />
 * @brief \e string ModuleActionDelay - Module delay on action - Default 4 (seconds). <br />
 * @brief \e string TimeZone - Default 'Europe/Paris'. <br />
 * @brief \e string UserAgent - Default user agent for HTTP requests - Default 'Mozilla/5.0 (compatible; CaMykSRequest/1.0; +http://www.camyks.net/request_bot.html)'. <br />
 * @brief \e string PEARMailDriver - PEAR Mail driver - To insert. <br />
 * @brief \e array PEARMailConfig - PEAR Mail configuration - To insert. <br />
 */
$this->_conf = array(
    'server_encoding'   => 'utf8',
    'database_driver'   => '', 
    'database_host'     => '', 
    'database_login'    => '', 
    'database_password' => '', 
    'ModuleActionDelay' => 4,
    'TimeZone'          => 'Europe/Paris',
    'UserAgent'         => 'Mozilla/5.0 (compatible; CaMykSRequest/1.0; +http://www.camyks.net/request_bot.html)',
);

/* load locale configuration */
if (file_exists($this->camyks_path.'/engine/etc/dynamic.local.php.inc'))
  require($this->camyks_path.'/engine/etc/dynamic.local.php.inc');
?>
