<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type      : Plugin / Theme 
 * Create Date		: Sep 2005
 * Last Modif Date  : Oct 2014
 * History :
 * * 05-09-xx : Initial File
 * * 08-01-07 : Rebuild theme as an object
 * * 08-07-02 : Update to suit new Theme specifications
 * * 14-10-01 : Strict standart compiancy
 *
 * Theme : Grey Style
 */

class GreyStyle extends Theme {
  /*
   * constructor
   * @param string $path_type
   */
  function GreyStyle( $path_type ) {
    parent::Theme('GreyStyle', $path_type);
    /* set theme title */
    $this->title = 'Grey Style';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* initialise plugin variables */
    $this->hasTabs = false;
  }

  /*
   * overwrite theme parts
   */

  /* 
   * overwrite box tab bar
   */
  function get_boxTabsBar ( $tabs, $click, $mover='', $mout='', $selected='') {
    $this->hasTabs = true;
    return parent::get_boxTabsBar ( $tabs, $click, $mover, $mout, $selected);
  }


  /*
   * overwrite box contents
   */
  function get_boxContent1Header($more='') {
    if ( $this->hasTabs === true ) {
      return $this->get_part('boxOpenContentHeader', $more);
    } else {
      return $this->get_part('boxContent1Header', $more);
    }
  }

  function get_boxContent2Header($more='') {
    if ( $this->hasTabs === true ) {
      return $this->get_part('boxOpenContentHeader', $more);
    } else {
      return $this->get_part('boxContent2Header', $more);
    }
  }

  function get_boxContent1Footer() {
    if ( $this->hasTabs === true ) {
      $this->hasTabs = false;
      return $this->get_part('boxOpenContentFooter');
    } else {
      return $this->get_part('boxContent1Footer');
    }
  }

  function get_boxContent2Footer() {
    if ( $this->hasTabs === true ) {
      $this->hasTabs = false;
      return $this->get_part('boxOpenContentFooter');
    } else {
      return $this->get_part('boxContent2Footer');
    }
  }

  /*
   * overwrite box buttons bar
   */
  function get_boxButtonsBar ( $buttons=array(), $sized=true ) {
    $defaultButton = array('link'=>'', 'title'=>'', 'style'=>'', 'id'=>'', 'more'=>'');

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
      $b = array_merge($defaultButton, $b);
      
      if ($b['id'] != '')
        $b['more'] .= ' id="'.$b['id'].'"';

      if ($b['link'] != '') {
	    $str .= $this->get_part('boxButtonWithLink', array( $b['style'], $b['link'], $b['title'], $b['more'], $colw));
      } else {
	    $str .= $this->get_part('boxButtonWithoutLink', array( $b['style'], $b['title'], $b['more'], $colw));
      }
    }
    /* simulate a "min" cols bar */
    for( $i=count($buttons); $i < $min; $i++ ) {
      $str .= $this->get_part('boxButtonWithoutLink', array( '', '&nbsp;', '', $colw));
    }
    $str .= $this->get_part('boxButtonsBarFooter');
    return $str;
  }
}
?>