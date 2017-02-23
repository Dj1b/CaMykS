<?php
/*
 * CaMykS Engine
 * Developed by       : camyks.net
 * Author             : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version     : 1.0b1
 * Object Version     : 1.0
 * Object Type        : Engine / Tool Library
 * Creation Date      : Jan 2010
 * Last Modif Date    : Jan 2010
 *
 * array methods
 */

/*
 * drop given value from array
 * @param array $array
 * @param mixed $value
 * @param boolean $keepKeys
 * @return string
 * @access public
 */
function array_dropValue($array=array(), $value=null, $keepKeys=true) {
  /* check array */
  if (!is_array($array))
    return array();
  
  /* check value */
  if ($value == null)
    return $array;
  
  /* get parsed array */
  $parsed = preg_grep("/{$value}/i", $array, PREG_GREP_INVERT);

  /* return result */
  if ($keepKeys)
    return $parsed;
  return array_values($parsed);
}

/*
 * merge arrays
 * @param array $array1
 * @param array $array2
 * @return array
 * @access public
 */
function array_recursiveMerge($array1=array(), $array2=array()) {
  /* check arrays */
  if (!is_array($array1) and !is_array($array2))
    return array();
  if (!is_array($array1))
    return $array2;
  if (!is_array($array2))
    return $array1;
  
  /* merge arrays */
  foreach ($array2 as $key => $value) {
  	if (!isset($array1[$key]))
      /* add value */
  	  $array1[$key] = $value;
  	elseif (is_array($value) and is_array($array1[$key]))
  	  /* merge array values */
  	  $array1[$key] = array_recursiveMerge($array1[$key], $value);
  	else
  	  /* merge other values */
  	  $array1[$key] = $value;
  }
  
  /* return merged array */
  return $array1;
}

?>