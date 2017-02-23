<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMyKS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Library
 * Create Date		: May 2007
 * Last Modif Date	: May 2007
 * 
 * ColorPicker config library : default
*/

$this->config = array();
$this->config['more'] = true;
$this->config['width'] = 6;
$this->config['height'] = 8;
$this->config['maxcols'] = 36;
$this->config['maxrows'] = 6;
$this->config['colors'] = array();

$item = array('FF', 'CC', '99', '66', '33', '00');

foreach ( $item as $a ) {
  foreach ( $item as $b ) {
    foreach ( $item as $c ) {
      $this->config['colors'][] = $a.$b.$c; 
    }
  }
}
?>
