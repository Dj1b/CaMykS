<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	        : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Creation Date    : Feb 2010
 * Last Modif Date  : Feb 2018
 * History : 
 * * 10-02-25 : Initial files
 * 
 * ContentAnchorMenu : build a menu from given content anchors
 */

class ContentAnchorMenu extends Input {

  /* 
   * constructor
   * @param string $path_type
   */
  function ContentAnchorMenu ( $path_type ) {
    parent::Input('ContentAnchorMenu', $path_type);
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
    $p = array(
           'mode'       =>'AName', // AName (HTML4) / objId (HTML5)
           'name'       =>'anchorMenu',
	       'content'    =>'body',
	       'linkClass'  =>'eLink1',
	       'menuClass'  =>'',
	       'shift'      => 0 );
    
    /* merge params */
    $this->params = array_merge($p, $params);
    $this->params['name'] = string_parseSpecialChars($this->params['name'], array('pattern'=>'/[^a-zA-Z0-9_]/'));

    /* add javascript */
    $this->add_JSFile('contentanchormenu.js');
    $this->add_JSScript('var '.$this->params['name'].' = new ContentAnchorMenu("'.$this->params['name'].'");');
    $this->add_JSScript($this->params['name'].'.set_param("mode", "'.$this->params['mode'].'");');
    $this->add_JSScript($this->params['name'].'.set_param("content", "'.$this->params['content'].'");');
    $this->add_JSScript($this->params['name'].'.set_param("linkClass", "'.$this->params['linkClass'].'");');
    $this->add_JSScript($this->params['name'].'.set_param("shift", "'.$this->params['shift'].'");');
    $this->add_JSLoadScript($this->params['name'].'.initialise();');
  }
}
?>