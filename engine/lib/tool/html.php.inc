<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Engine / Tool Library
 * Creation Date	: Mar 2005
 * Last Modif Date      : mar 2005
 * 
 * Some basic html methods
 * To fix and finalise
 */

/*
 */
function html_getTableHeader ( $cp=0, $cs=0, $s='', $cl='', $b=0,  $o='') {
  $html = '<table';
  $html .= ' cellpadding="'.$cp.'"';
  $html .= ' cellspacing="'.$cs.'"';
  $html .= ' border="'.$b.'"';
  if ( $cl != '' )
    $html .= ' class="'.$cl.'"';
  if ( $s != '' )
    $html .= ' style="'.$s.'"';
  if ( $o != '' )
    $html .= ' '.$o;
  $html .= '>';
  return $html;
}

function html_getTableFooter ( ) {
  return '</table>';
}

?>