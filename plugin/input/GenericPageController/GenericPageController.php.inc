<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Create Date	    : Jan 2010
 * Last Modif Date  : Jan 2010
 * History : 
 * * 10-01-20 : Initial files
 * 
 * GenericPageController
 */

class GenericPageController extends Input {

  /* 
   * constructor
   * @param string $path_type
   */
  function GenericPageController ( $path_type ) {
    parent::Input('GenericPageController', $path_type);
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Generic';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
  }
  
  /* overwrite input methods */

  /*
   * initialise input
   * @param array $params
   * @return void
   * @access public
   */
  function initialise ($params=array()) {
    global $camyks;
    
    /* initialise default params */
    $p = array('mode'=>'static',
    	'pageCurrent'=>0, 
      'pageCount'=>1, 
      'pageParams'=>array(0, '', array()), 
      'pageParam'=>'page',
      'hideEmpty'=>0,
      'theme'=>'',
      'buttonSource'=>'plugin',
      'styleSource'=>'plugin',
      'styleFile'=>'',
      'jsLink'=>'', /* obj.go_toPage(_page_); */
      'jsParentElmt'=>'',
      'jsObjName'=>'gpc');
      
    /* merge params */
    $this->params = array_merge($p, $params);
   
    /* load theme if requiered */
    if ( $this->params['buttonSource'] == 'theme' 
      or $this->params['styleSource'] == 'theme') {
      if ( $this->params['theme'] != '' and isset($camyks->themes[$this->params['theme']]))
        $this->theme = &$camyks->themes[$this->params['theme']];
      else
        $this->theme = &$camyks->themes[$camyks->get_confValue('site_default_theme')];
    }
    
    /* insert style file if requiered */
    if ($this->params['styleSource'] == 'theme') {
      if ($this->params['styleFile'] != '')
        $this->theme->add_styleFile($this->params['styleSource']);
    } else {
      if ($this->params['styleFile'] != '')
        $this->add_styleFile($this->params['styleSource']);
      else
        $this->add_styleFile('gpc.css');
    }
      
    /* send data to javascript if mode is dynamic */
    if ($this->params['mode'] == 'dynamic') {
    	$this->add_JSFile('genericpagecontroller.js');
    	$this->add_JSScript('var '.$this->params['jsObjName'].' = new GenericPageController("'.$this->params['jsObjName'].'");');
    	$this->add_JSScript($this->params['jsObjName'].'.set_param("parentElmt", "'.$this->params['jsParentElmt'].'");');
    	$this->add_JSScript($this->params['jsObjName'].'.set_param("link", "'.$this->params['jsLink'].'");');
    	$this->add_JSScript($this->params['jsObjName'].'.set_param("pageCurrent", '.$this->params['pageCurrent'].');');
    	$this->add_JSScript($this->params['jsObjName'].'.set_param("pageCount", '.$this->params['pageCount'].');');
    	$this->add_JSScript($this->params['jsObjName'].'.set_param("hideEmpty", '.$this->params['hideEmpty'].');');
    	
    	if ( $this->params['buttonSource'] != 'none' ) {
    		$this->add_JSScript($this->params['jsObjName'].'.set_param("displayBttns", 1);');
    		$this->add_JSScript($this->params['jsObjName'].'.set_param("bttnLeft", "'.$this->get_buttonURL('pager_left').'");');
    		$this->add_JSScript($this->params['jsObjName'].'.set_param("bttnLeftR", "'.$this->get_buttonURL('pager_left_r').'");');
    		$this->add_JSScript($this->params['jsObjName'].'.set_param("bttnRight", "'.$this->get_buttonURL('pager_right').'");');
    		$this->add_JSScript($this->params['jsObjName'].'.set_param("bttnRightR", "'.$this->get_buttonURL('pager_right_r').'");');
    		$this->add_JSScript($this->params['jsObjName'].'.set_param("bttnEmpty", "'.$this->get_buttonURL('pager_off').'");');
    	} else 
    		$this->add_JSScript($this->params['jsObjName'].'.set_param("displayBttns", 0);');
    	$this->add_JSLoadScript($this->params['jsObjName'].'.initialise();');
    }
    
    /* hide empty controller */
    if ($this->params['hideEmpty'] == 1 and $this->params['pageCount'] > 1 )
      $this->params['hideEmpty'] = 0;
  }
  
  /*
   * display input
   * @return void
   * @access public
   */
  function display() {
    parent::display();
  }
  
  /* specific methods */
  
  /*
   * return page url
   * @param integer $page
   * @return string
   * @access public
   */
  function get_pageURL($page) {
    global $camyks;
    
    /* check for first page link */
    if ($page == 0)
        return $camyks->get_siteLink($this->params['pageParams'][0],'',
                                 $this->params['pageParams'][1],
                                 $this->params['pageParams'][2]);
                                 
    /* return generic page link */
    return $camyks->get_siteLink($this->params['pageParams'][0],'',
                                 $this->params['pageParams'][1],
                                 array_merge($this->params['pageParams'][2], array($this->params['pageParam']=>$page)));
  }
  
  /*
   * return previous page url
   * @return string
   * @access public
   */
  function get_previousPageURL() {
    if ($this->params['pageCurrent'] == 0)
      return '';
    return $this->get_pageURL($this->params['pageCurrent']-1);
  }
  
  /*
   * return next page url
   * @return string
   * @access public
   */
  function get_nextPageURL() {
    if ($this->params['pageCount'] == 0 
        or $this->params['pageCurrent'] == $this->params['pageCount']-1)
      return '';
    return $this->get_pageURL($this->params['pageCurrent']+1);
  }
  
  /*
   * return button url
   * @param string $button
   * @return string
   * @access public
   */
  function get_buttonURL($button='') {
    if ( $this->params['buttonSource'] == 'theme') {
      switch($button) {
        case 'pager_left':
          return $this->theme->get_pictURL('left', 12, 'std');
        case 'pager_left_r':
          return $this->theme->get_pictURL('left', 12, 'ovr');
        case 'pager_right':
          return $this->theme->get_pictURL('right', 12, 'std');
        case 'pager_right_r':
          return $this->theme->get_pictURL('right', 12, 'ovr');
        case 'pager_off':
          return $this->theme->get_pictURL('empty', 12, 'std');
      }
    }
    return $this->get_fileURL('img/'.$button.'.gif');
  }
}
?>