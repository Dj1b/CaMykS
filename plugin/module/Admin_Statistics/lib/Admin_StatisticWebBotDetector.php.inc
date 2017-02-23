<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version 	: 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date	: May 2008
 * Last Modif Date  : Dec 2014
 *
 * Admin_StatisticWebBotDetector object for Admin_Statistics Module
 */

class Admin_StatisticWebBotDetector {
  /*
   * constructor
   */
  function Admin_StatisticWebBotDetector() {
  
  }

  /*
   * detect web bot
   * @return mixed
   * @access public
   */
  function detect() {
    return client_checkIsBot($_SERVER['HTTP_USER_AGENT']);
  }

  /*
   * return bot title
   * @param string $bot
   * @return string
   * @access private
   */
  function get_botTitle( $bot ) {
    /* check bot */
    if ( $bot == null or $bot == '' )
      return null;
    if (($botInfo = client_getBotInfos($bot)) == null )
      return null;
    
    /* build bot title */
    if ( $botInfo['engine_title'] == '') {
      /* add bot title */
      if ( $botInfo['bot_url'] == '' )
	    $botTitle = $botInfo['bot_title'];
      else  
	    $botTitle = '<a href="'.$botInfo['bot_url'].'" target="_blank">'.$botInfo['bot_title'].'</a>';
    } else {
      /* add engine title */
      if ( $botInfo['engine_url'] == '' )
	    $botTitle = $botInfo['engine_title'];
      else
	    $botTitle = '<a href="'.$botInfo['engine_url'].'" target="_blank">'.$botInfo['engine_title'].'</a>';
      /* add bot title */
      if ( $botInfo['bot_title'] != '' )
	    if ( $botInfo['bot_url'] == '' )
	  $botTitle .= ' ('.$botInfo['bot_title'].')';
	    else
	  $botTitle .= ' (<a href="'.$botInfo['bot_url'].'" target="_blank">'.$botInfo['bot_title'].'</a>)';
    }
    return $botTitle;
  }
}
?>