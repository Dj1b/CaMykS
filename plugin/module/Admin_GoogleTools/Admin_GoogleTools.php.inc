<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Creation Date	: Sep 2007
 * Last Modif Date	: Oct 2008
 * History :
 * * 07-09-xx : Initial files
 * * 08-04-14 : Update regexp to support result values larger than a thousand
 * * 08-04-15 : Update Google page loader
 * * 08-10-21 : Update Google page parser
 * 
 * Admin_GoogleTools Module
 * Some tools based on Google engine
 */

class Admin_GoogleTools extends Module {
  /* variables */
  var $referredpages;
  var $maxreferredpages;

  var $linkedpages;
  var $maxlinkedpages;

  /*
   * constructor
   * @param string $path_type
   */
  function Admin_GoogleTools ( $path_type ) {
    parent::Module('Admin_GoogleTools', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'monitoring';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Google';
    /* set plugin author */
    $this->authors_name = 'CaMykS Team';
    $this->authors_mail = 'camyks.contact@gmail.com';
    $this->authors_group = 'camyks.net';
    /* initialise some variables */
    $this->maxreferredpages = 100;
    $this->maxlinkedpages = 100;
  }
  
  /* overwrite Module methods */  

  /*
   * initialise module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    /* if user has no rights for this module, make redirection to home */
    if ( $this->check_right(0) === false ) {
      return $this->init_admin_accessDenied();
    }

    /* get informations */
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : '' );
    
    switch ( $this->mode ) {
    case 'referred':
      $this->init_admin_referred();
      break;
    case 'linked':
      $this->init_admin_linked();
      break;
    default:
      $this->openTab = 'referred';
    }

    /* get tab engine */
    $this->tabObject = 'gtools_tabObject';
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("referred", "'
      .$this->theme->parts['boxTabCSSStandart'].'","'
      .$this->theme->parts['boxTabCSSSelected'].'","'
      .$this->theme->parts['boxTabCSSRollover'].'");');
    $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$this->openTab.'\');');

    $this->tabs = array(array('name'=>'referred',
			      'title'=>$this->get_translation('tabreferred')),
			array('name'=>'linked',
			      'title'=>$this->get_translation('tablinked')));

    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
    parent::init_admin();
  }
  
  /*
   * display module object in admin mode
   * @return void
   * @access private
   */
  function display_admin () {
    parent::display_admin();
  }

  /*
   * set module rights
   * @return void
   * @access private
   */
  function get_rights ( ) {
    global $camyks;
    $this->rights[0] = array( 'name'=>'read',
			      'title'=> $camyks->get_translation('read'),
			      'default'=> false);
  }

  /* specific methods */

  /*
   * initialise module object in admin/referred mode
   * @return void
   * @access private
   */
  function init_admin_referred() {
    global $camyks;
    $this->openTab = 'referred';
    
    $this->referredpages = array();
    $this->referredpages['count'] = 0;
    $this->referredpages['list'] = array();

    $url = $camyks->_conf['url'];
    $find = '@^(?:http://)?([^/]+)@i';
    if ( preg_match( $find, $url, $result )  )
      $url = $result[1];

    $gurl = 'http://www.google.com/search?hl=en&num='.$this->maxreferredpages;
    $gurl .= '&btnG=Google+Search&as_sitesearch='.urlencode($url);
    $gurl .= '&ie=utf-8&oe=utf-8';

    /* get google page */
    $handle = @fopen( $gurl, 'rb');
    $content = stream_get_contents($handle);
    fclose($handle);

    /* parse count result in page */
    if ( preg_match ('/about <b>([0-9,\ ]*)<\/b> from/',
		     $content,
		     $count ) ) {
      $this->referredpages['count'] = (int)preg_replace('/[^0-9]/', '', $count[1]);
    }

    /* parse list result in page */
    if ( preg_match_all('/<h[^>]*><a href="([^"]*)"[^>]*>([^<]*)<\/a><\/h/i',
			$content,
			$list ) ) {
      foreach ( $list[0] as $i=>$result ) {
	$r = array ('title'=> $list[2][$i], 'url'=> $list[1][$i] );
	$this->referredpages['list'][] = $r;
      }
    }   
  }

  /*
   * initialise module object in admin/linked mode
   * @return void
   * @access private
   */
  function init_admin_linked() {
    global $camyks;
    $this->openTab = 'linked';
    
    $this->linkedpages = array();
    $this->linkedpages['count'] = 0;
    $this->linkedpages['list'] = array();

    $url = $camyks->site_conf['url'];
    $find = '@^(?:http://)?([^/]+)@i';
    if ( preg_match( $find, $url, $result )  )
      $url = $result[1];
    
    $gurl = 'http://www.google.com/search?hl=en&q=link%3A'.urlencode($url).'&btnG=Search';
    $gurl .= '&ie=utf-8&oe=utf-8&num='.$this->maxlinkedpages;

    /* get google page */
    $handle = @fopen( $gurl, 'rb');
    $content = stream_get_contents($handle);
    fclose($handle);

    /* parse count result in page */
    if ( preg_match('/ <b>([0-9,\ ]*)<\/b> linking/',
		    $content,
		    $count ) ) {
      $this->linkedpages['count'] = (int)preg_replace('/[^0-9]/', '', $count[1]);
    }
    
    /* parse list result in page */
    if ( preg_match_all('/<h[^>]*><a href="([^"]*)"[^>]*>([^<]*)<\/a><\/h/i',
			$content,
			$list ) ) {
      foreach ( $list[0] as $i=>$result ) {
	$r = array ('title'=> $list[2][$i], 'url'=> $list[1][$i] );
	$this->linkedpages['list'][] = $r;
      }
    }   
  }
}
?>