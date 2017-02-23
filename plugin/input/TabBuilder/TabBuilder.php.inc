<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Input Engine
 * Creation Date     	: Sep 2008
 * Last Modif Date      : Sep 2008
 * History : 
 * * 08-09-29 : Initial File
 *
 * Tab Builder Input : Simplify module tab management
 */
 
class TabBuilder extends Input {
  /* variables */
  var $name;
  var $params;
  var $tabs;
  
  /* 
   * constructor
   * @param string $path_type
   */
  function TabBuilder ( $path_type ) {
    parent::Input('TabBuilder', $path_type);
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* initialise plugin variables */
    $this->params = null;
    $this->tabs = array();
  }
  
  /* overwrite Input methods */
  
  /*
   * initialise object
   * @params array $params
   * @params array $tabs
   * @return void
   * @access public
   */
  function initialise( $params=array()) {
    /* get params */
    $this->params = $params;
    
    /* check parameters */
    $this->_check_params();
    
    /* check for opened tab */
    if (isset($_REQUEST['openTab']) and isset($this->tabs[$_REQUEST['openTab']])) {
      $this->params['default'] = $_REQUEST['openTab'];
    }
    
    /* initialise tabs */
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->params['name'].' = new CTab();');
    $this->add_JSScript($this->params['name'].'.init("'.$this->params['default'].'", "'
      .$this->params['theme']->parts['boxTabCSSStandart'].'","'
      .$this->params['theme']->parts['boxTabCSSSelected'].'","'
      .$this->params['theme']->parts['boxTabCSSRollover'].'");');

    /* build JS params */
    $this->jsParams = array('clic'=>$this->params['name'].'.mouseclick',
      'mover'=>$this->params['name'].'.mouseover',
      'mout'=>$this->params['name'].'.mouseout',
      'selected'=>$this->params['default']);
  }

  /*
   * display object
   * @return void
   * @access public
   */
  function display() {
    return;
  }

  /* specific methods */
  
  /*
   * add a single tab to tab list
   * @param mixed $tab
   * @param string $title
   * @return void
   * @access public;
   */
  function add_tab( $tab, $title='' ) {
    if ( is_array($tab) )
      $this->tabs[$tab['name']] = $tab;
    else
      $this->tabs[$tab] = array('name'=>$tab, 'title'=>$title);
  }
  
  /*
   * add tabs to tab list
   * @param array $tabs
   * @return void
   * @access public;
   */
  function add_tabs( $tabs ) {
    foreach ($tabs as $tab ) {
      $this->add_tab($tab);
    }
  }
  
  /*
   * return given tab display status
   * @param string $tab
   * @return string
   * @access public
   */
  function get_tabDisplay( $tab ) {
    if ( $this->params['default'] === $tab )
      return 'block';
    return 'none';
  }
  
  /*
   * check parameters
   * @param array $params
   * @return void;
   * @access private
   */
  function _check_params() {
    global $camyks;
    
    /* check if tabs is an array */
    if (!is_array($this->tabs)) {
      $this->tabs = array();
      return;
    }
    
    /* check name */
    if (!isset($this->params['name']))
      $this->params['name'] = 'genTabsObject';
    
    /* check theme */
    if (!isset($this->params['theme']))
      if ( $camyks->mode == CAMYKS_MODE_ADMIN )
        $this->params['theme'] = &$camyks->themes[$camyks->_conf['admin_default_theme']];
      else
        $this->params['theme'] = &$camyks->themes[$camyks->_conf['site_default_theme']];

    /* check default opened tab */
    if (!isset($this->params['default']) or !isset($this->tabs[$this->params['default']])) {
      foreach( $this->tabs as $tab ) {
        $this->params['default'] = $tab['name'];
        break;
      }
    }
        
    /* check request parameters */
    if (!isset($this->params['param']))
      $this->params['param'] = 'openTab';
  }
}
?>