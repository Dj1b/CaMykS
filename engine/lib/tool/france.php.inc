<?php
/*
 * CaMykS Engine
 * Developed by       : camyks.net
 * Author             : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version     : 1.0
 * Object Version     : 1.0
 * Object Type        : Engine / Tool Library
 * Creation Date      : Apr 2017
 * Last Modif Date    : Apr 2017
 *
 * Specific methods related to France
 * /!\ This library is not loaded with CaMykS initialisation
 */

/*
 * check if given number is valid for french phone numbers
 * @param string $number
 * @param mixed $value
 * @param boolean $keepKeys
 * @return string
 * @access public
 */
function france_isValidPhoneNumber($number, $params=array()) {
  
  /* merge params */
  $dParams = array('mobileOnly'=>false);
  $params = array_merge($dParams, $params);
  
  /* check intl format */
  if (preg_match('/^\+33 ?(\(0\))? ([0-9\- ]+)$/', $number, $matches)) {
    
    $number = preg_replace ('/[^0-9]/', '', $matches[2]);
    if (strlen($number) != 9)
      return false;
          
    if ($params['mobileOnly']==true and !in_array(substr($number, 0, 1), array(6, 7)))
      return false;
      
  } else {
    /* check locale format */
    $number = preg_replace ('/[^0-9]/', '', $number);
      
    if (strlen($number) != 10)
      return false;
    if (substr($number, 0, 1) != 0)
      return false;
        
    if ($params['mobileOnly']==true and !in_array(substr($number, 1, 1), array(6, 7)))
      return false;
  }
  return true;
}

?>