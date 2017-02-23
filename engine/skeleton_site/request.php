<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type  	: Skeleton site / request index
 * Creation Date	: Jun 2005
 * Last Modif Date	: Mar 2007
 *
 * Request site index
 */

/* session start */
session_start();

/* get site direct conf : site name */
if ( file_exists('./etc/site.php.inc') ){
  require_once ('./etc/site.php.inc');
} else {
  die ('Configuration file not found.');
}

/* get CaMykS */
if ( file_exists ( $conf['engine_path'].'/Camyks.php.inc' ) ) {
  require_once( $conf['engine_path'].'/Camyks.php.inc' );
} else {
  die ('CaMykS engine not found, check your site configuration file !!!');
}

/* build CaMykS engine object */
$camyks = new Camyks ( $conf, CAMYKS_MODE_REQUEST );
/* execute CaMykS engine */
$camyks->execute();
?>