<?php
/*
 * CaMykS Engine
 * Developed		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Theme
 * Create Date		: Sep 2005
 * Last Modif Date      : Jul 2008
 * History :
 * * 05-09-xx : Initial File
 * * 08-01-07 : Rebuild theme as an object
 * * 08-07-02 : Update to suit new Theme specifications
 *
 * Theme Information : Basic
 */

class Basic extends Theme {
  /*
   * constructor
   * @param string $path_type
   */
  function Basic( $path_type ) {
    parent::Theme('Basic', $path_type);
    /* set theme title */
    $this->title = 'Basic';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
  }

  /*
   * overwrite box buttons bar
   * @params array $buttons
   * @return string
   * @public private
   */
  function get_boxButtonsBar ($buttons=array()) {
    /* get min button value */
    $min = 2;
    
    /* update button size */
    if ( $sized ) {
      $cols = max( $min, count($buttons));
      $colw = 'width:'.intval(100/$cols).'%;';
    } else {
      $colw = '';
    }
    
    $str = '';
    $str .= $this->get_part('boxButtonsBarHeader');
    foreach ( $buttons as $b ) {
      if ( isset($b['link']) and $b['link']!= '') {
	$str .= $this->get_part('boxButtonWithLink', array( $colw, $b['link'], $b['title']));
      } else {
	$str .= $this->get_part('boxButtonWithoutLink', array( $colw, $b['title']));
      }
    }
    /* simulate a "min" cols bar */
    for( $i=count($buttons); $i < $min; $i++ ) {
      $str .= $this->get_part('boxButtonWithoutLink', array( $colw, '&nbsp;'));
    }
    $str .= $this->get_part('boxButtonsBarFooter');
    return $str;
  }
}
?>