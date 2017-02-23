<?php
/*
 * Camyks Engine
 * Company                 : skymac.org
 * Author                  : sky
 *      Camyks Version          : 1.0a
 *      Object Version          : 1.0
 *      Object Type             : Engine / Tool Lib
 *      Creation Date           : Aug 2005
 *      Last Modif Date         : Mar 2007
 *
 *      Strings relative functions
 */

/*
 *
 */
function string_getSimilarBeginning ( $s1, $s2 ) {
  $result = '';
  $i = 0;
  while ( $i < min(strlen($s1), strlen($s2))) {
    if ( $s1[$i] == $s2[$i] ) {
      $result .= $s1[$i];
      $i++;
    } else {
      return $result;
    }
  }
  /* text are identical */
  return $result;
}

/*
 *
 */
function string_parseNonLetterChars( $string ) {
  $parsed = '';
  for ($index=0; $index<strlen($string); $index++) {
    $char = $string[$index];
    switch ( $char ) {
    case 'a': case 'A': $parsed.='a'; break;
    case 'b': case 'B': $parsed.='b'; break;
    case 'c': case 'C': $parsed.='c'; break;
    case 'd': case 'D': $parsed.='d'; break;
    case 'e': case 'E': $parsed.='e'; break;
    case 'f': case 'F': $parsed.='f'; break;
    case 'g': case 'G': $parsed.='g'; break;
    case 'h': case 'H': $parsed.='h'; break;
    case 'i': case 'I': $parsed.='i'; break;
    case 'j': case 'J': $parsed.='j'; break;
    case 'k': case 'K': $parsed.='k'; break;
    case 'l': case 'L': $parsed.='l'; break;
    case 'm': case 'M': $parsed.='m'; break;
    case 'n': case 'N': $parsed.='n'; break;
    case 'o': case 'O': $parsed.='o'; break;
    case 'p': case 'P': $parsed.='p'; break;
    case 'q': case 'Q': $parsed.='q'; break;
    case 'r': case 'R': $parsed.='r'; break;
    case 's': case 'S': $parsed.='s'; break;
    case 't': case 'T': $parsed.='t'; break;
    case 'u': case 'U': $parsed.='u'; break;
    case 'v': case 'V': $parsed.='v'; break;
    case 'w': case 'W': $parsed.='w'; break;
    case 'x': case 'X': $parsed.='x'; break;
    case 'y': case 'Y': $parsed.='y'; break;
    case 'z': case 'Z': $parsed.='z'; break;
    default:break;
    }
  }
  return $parsed;
}

?>