<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Engine / Tool Library
 * Creation Date    	: Jun 2005
 * Last Modif Date      : Mar 2007
 *
 * CaMykS object static methods
 */

/*
 * kill camyks
 */
function camyks_kill() {
  global $camyks;
  $camyks->kill();
  $camyks = null;
}
?>