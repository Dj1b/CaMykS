<?php
/*
 * CaMykS Engine
 * Developed by			: camyks.net
 * Author	       		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version		: 1.0a
 * Object Version 	: 1.0
 * Object Type			: Plugin / Input Engine
 * Creation Date		: Apr 2011
 * Last Modif Date	: Apr 2011
 * History : 
 * * 11-04-19 : Initial Files
 *   
 * MultiSelectionList input : Dynamic list editor
*/

class MultiSelectionList extends Input {
  /* variables */
  var $params;

  /*
   * constructor
   * @param string $path_list
   */
  function MultiSelectionList ( $path_type ) {
    parent::Input('MultiSelectionList', $path_type);
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
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
  function initialise ( $params=array() ) {
    global $camyks;
    
    /* build default params */
    $dParams = array('name'=>'MultiSelectionList',
   		'fullList'=> array(), // (id => name) array
   		'selList'=>array(), // id array
   		'formName'=>'', // string
   		'formItemName'=>'', // string
   		'itemSeparator'=>',', //sting
   		'theme'=>'', // string
      'buttonSource'=>'theme', // plugin | theme
      'selectedLayout'=>'input.html.inc',
      'listTitle' => $this->get_translation('listtitle'),
      'selectionTitle' => $this->get_translation('selectiontitle'),
    );
    
    /* merge params */
    $this->params = array_merge($dParams, $params);
    
    /* load theme if requiered */
    if ( $this->params['buttonSource'] == 'theme') {
      if ( $this->params['theme'] != '' and isset($camyks->themes[$this->params['theme']]))
        $this->theme = &$camyks->themes[$this->params['theme']];
      elseif( $camyks->mode == CAMYKS_MODE_ADMIN )
        $this->theme = &$camyks->themes[$camyks->get_confValue('admin_default_theme')];
      else
      	$this->theme = &$camyks->themes[$camyks->get_confValue('site_default_theme')];
    }

    /* set javascript file */
    $this->add_JSEngineFile('tool/array.js');
    $this->add_JSFile('multiselectionlist.js');
    
    /* set javascript object */
    $this->add_JSScript($this->params['name'].' = new MultiSelectionList("'.$this->params['name'].'");' );
    $this->add_JSScript($this->params['name'].'.set_param("fullList", {});');
    foreach ($this->params['fullList'] as $id => $name)
    	$this->add_JSScript($this->params['name'].'.set_param("fullList", '.$id.', "'.$name.'");');
    
    $this->add_JSScript($this->params['name'].'.set_param("selList", new Array());');
    foreach ($this->params['selList'] as $index => $id)
    	$this->add_JSScript($this->params['name'].'.set_param("selList", '.$index.', '.$id.');');
   
    $this->add_JSScript($this->params['name'].'.set_param("formName", "'.$this->params['formName'].'")');
    $this->add_JSScript($this->params['name'].'.set_param("formItemName", "'.$this->params['formItemName'].'")');
    $this->add_JSScript($this->params['name'].'.set_param("itemSeparator", "'.$this->params['itemSeparator'].'")');
    
  
    /* send icons */
    if ($this->params['buttonSource'] == 'theme') {
    	$this->add_JSScript($this->params['name'].'.set_param("plusIcon", "'.$this->theme->get_pictURL('plus', 12, 'std').'");');
    	$this->add_JSScript($this->params['name'].'.set_param("plusIconR", "'.$this->theme->get_pictURL('plus', 12, 'ovr').'");');

    	$this->add_JSScript($this->params['name'].'.set_param("minusIcon", "'.$this->theme->get_pictURL('minus', 12, 'std').'");');
    	$this->add_JSScript($this->params['name'].'.set_param("minusIconR", "'.$this->theme->get_pictURL('minus', 12, 'ovr').'");');
		} else {
			$this->add_JSScript($this->params['name'].'.set_param("plusIcon", "'.$this->get_fileURL('img/plus.gif').'");');
    	$this->add_JSScript($this->params['name'].'.set_param("plusIconR", "'.$this->get_fileURL('img/plusR.gif').'");');

    	$this->add_JSScript($this->params['name'].'.set_param("minusIcon", "'.$this->get_fileURL('img/minus.gif').'");');
    	$this->add_JSScript($this->params['name'].'.set_param("minusIconR", "'.$this->get_fileURL('img/minusR.gif').'");');
		}

    /* set object initialization on page load */
    $this->add_JSLoadScript ( $this->name.'.initialise();' ); 

    /* Input generic initialization */
    parent::initialise();
  }
 
  /*
   * display input
   * @return void
   * @access public
   */
  function display ( ) {
  	parent::display($this->params['selectedLayout']);
  }  
}
?>