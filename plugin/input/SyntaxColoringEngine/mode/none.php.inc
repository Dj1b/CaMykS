<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Library
 * Create Date		: May 2007
 * Last Modif Date	: May 2007
 * 
 * SyntaxColoringEngine mode library : no colorisation
*/

class SyntaxColoringEngine_none {

  /* constructor */
  function SyntaxColoringEngine_none () {
  }

  /*
   * execute colorisation
   * @param string $text
   * @return string
   * @access private
   */
  function execute( $text ) {
    return nl2br($text);
  }
}
?>