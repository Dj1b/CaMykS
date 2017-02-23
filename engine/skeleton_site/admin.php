<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type  	: Skeleton site / Admin index
 * Creation Date	: Jun 2005
 * Last Modif Date	: Mar 2007
 * 
 * Admin site index
*/
/* session start */
session_start();

/* get site direct conf */
require_once ('./etc/site.php.inc');

/* get CaMykS */
if ( file_exists ( $conf['engine_path'].'/Camyks.php.inc' ) ) {
  require_once( $conf['engine_path'].'/Camyks.php.inc' );
} else if ( file_exists ( $conf['engine_path'].'/html/erreur.htm' ) ) {
  header('location: '.$conf['engine_path'].'/html/erreur.htm');
} else {
  exit ('Fatal Error : can you imagine a blue screen ? &circ;&circ; ');
}

/* build CaMykS engine object */
$camyks = new Camyks ( $conf, CAMYKS_MODE_ADMIN );
/* execute CaMykS engine */
$camyks->execute();
?>