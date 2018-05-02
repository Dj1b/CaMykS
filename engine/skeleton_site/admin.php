<?php
/**
 * @brief Admin site entry point
 * @details Skeleton site / Admin index
 * @file engine/skeleton_site/admin.php
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2005
 * @date Modification: Apr 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
/* session start */
session_start();

/* load site configuration */
if ((@include_once('./etc/site.php.inc')) === false) {
    exit('Fatal Error : Website configuration not found.');
}

/* load CaMykS */
if ((@include_once($conf['engine_path'].'/Camyks.php.inc')) === false)
    exit('Fatal Error : CaMykS folder not found.');

/* create CaMykS engine object */
$camyks = new CaMykS($conf, CAMYKS_MODE_ADMIN);

/* execute CaMykS engine */
$camyks->execute();
?>