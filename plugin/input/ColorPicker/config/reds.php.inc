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
 * ColorPicker config library : reds
*/

$this->config = array();
$this->config['more'] = true;
$this->config['width'] = 12;
$this->config['height'] = 12;
$this->config['maxcols'] = 16;
$this->config['maxrows'] = 8;
$this->config['colors'] = array();

for( $i=63; $i >= 0; $i-- ) {
  $v = dechex($i*4);
  $v = str_pad($v, 2, '0', STR_PAD_LEFT );
  $this->config['colors'][] = 'FF'.$v.$v; 
}

for( $i=63; $i >= 0; $i-- ) {
  $v = dechex($i*4);
  $v = str_pad($v, 2, '0', STR_PAD_LEFT );
  $this->config['colors'][] = $v.'0000'; 
}
?>
