<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version 	: 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date	: Oct 2008
 * Last Modif Date  : Mar 2017
 *
 * Admin_StatisticWebToolDetector object for Admin_Statistics Module
 */

class Admin_StatisticWebToolDetector {
  /*
   * constructor
   */
  function Admin_StatisticWebToolDetector() {
  
  }
  
  /*
   * detect web tool
   * @return mixed
   * @access public
   */
  function detect() {
    return client_checkIsTool();
  }

  /*
   * return tool title
   * @param string $tool
   * @return string
   * @access private
   */
  function get_toolTitle($tool='') {
    /* check tool */
    if ( $tool == null and $tool == '' )
      return null;
    if ( ($toolInfo = client_getToolInfos($tool)) == null )
      return null;

    /* build tool title */
    if ( $toolInfo['engine_title'] == '') {
      /* add tool title */
      if ( $toolInfo['tool_url'] == '' )
	    $toolTitle = $toolInfo['tool_title'];
      else  
	    $toolTitle = '<a href="'.$toolInfo['tool_url'].'" target="_blank">'.$toolInfo['tool_title'].'</a>';
    } else {
      /* add engine title */
      if ( $toolInfo['engine_url'] == '' )
	$toolTitle = $toolInfo['engine_title'];
      else
	$toolTitle = '<a href="'.$toolInfo['engine_url'].'" target="_blank">'.$toolInfo['engine_title'].'</a>';
      /* add tool title */
      if ( $toolInfo['tool_title'] != '' )
	if ( $toolInfo['tool_url'] == '' )
	  $toolTitle .= ' ('.$toolInfo['tool_title'].')';
	else
	  $toolTitle .= ' (<a href="'.$toolInfo['tool_url'].'" target="_blank">'.$toolInfo['tool_title'].'</a>)';
      
    }
    return $toolTitle;
  }
}
?>