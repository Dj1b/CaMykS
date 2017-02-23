<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : May 2010
 * Last Modif Date  : Jun 2010
 *
 * Admin_GenericGlossaryManagerCategory object for Admin_GenericGlossaryManager Module
 */

class Admin_GenericGlossaryManagerCategory extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericGlossaryManagerCategory ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* content items */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
   
    /* temp items */
    $this->add_newItem('definitions', 'temp', 'int', '', '', 0);

    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * build sql condition for lists
   * @param array $params
   * @return string
   * @access public
   */
  function build_SQLCondition($params) {
    if ( isset( $params['status'] ) and $params['status'] > -1 )
      return 'status='.$params['status'];
    return '';
  }

  /* specific methods */
  
  /*
   * is category deletable
   * @return boolean result
   * @access public
   */
  function is_deletable() {
    return (isset($this->vars['definitions']) and $this->vars['definitions'] == 0 );
  }
  
  /*
   * return categories status list
   * @param boolean $full
   * @return array
   * @access public
   */
  function get_multiStatusList($full=false) {
  	$list = array();
  	if($full)
  		$list['-1'] = $this->get_translation('categoriesstatus_all');
  	$list['0'] = $this->get_translation('categoriesstatus_disabled');
  	$list['1'] = $this->get_translation('categoriesstatus_enabled');
  	return $list;
  }
  
  /*
   * return single category status list
   * @return array
   * @access public
   */
  function get_statusList() {
  	return array(0 => $this->get_translation('categorystatus_disabled'),
  		1 => $this->get_translation('categorystatus_enabled'));
  }
  
  /*
   * return categories title list
   * @param array $params
   * @param string $lg
   * @return array
   * @access public
   */
  function get_titleList($params=array()) {
    global $camyks;

    /* default params */
    $dParams = array('language'=>$camyks->current_language, 'status'=>-1, 'ids'=>-1);

    /* merge params */
    $params = array_merge($dParams, $params);
    
    /* initialise where statement */
    $w = array();

    /* check status */
    if ($params['status'] != -1)
      $w[] = 'status = '. $params['status'];

    /* check id list */
    if ($params['ids'] != -1) {
      if (is_string($params['ids']))
	$params['ids'] = explode(',', $params['ids']);
      if ( count($params['ids']) == 0 )
	return array();
      if ( count($params['ids']) == 1 )
	$w[] = 'id = '.$params['ids'][0];
      else
	$w[] = 'id in ('.implode(',', $params['ids']).')';
    }

    /* compile where statement */
    $w = implode(' and ', $w);

    /* get load list */
    return $this->get_nameList('title', $w, $params['language']);
  }
}
?>