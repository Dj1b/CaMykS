<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Mar 2010
 * Last Modif Date  : Mar 2010
 *
 * Admin_GooglePoIMapManagerCategory object for Admin_GooglePoIMapManager Module
 */

class Admin_GooglePoIMapManagerCategory extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GooglePoIMapManagerCategory ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* main content */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
    
    /* temp content */
    $this->add_newItem('points', 'temp', 'integer', '', '', 0);
    
    /* generic initialisation */
    $this->init_library();
  }
  
  /* specific methods */
  
  /*
   * return category status list
   * @return array
   * @access private
   */
  function get_statusList() {
    return array(0 => $this->get_translation('categorystatus_inactive'),
		 1 => $this->get_translation('categorystatus_active'));
  }
  
  /*
   * return category status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_multiStatusList($full=false) {
    $list = array();
    if ($full)
      $list['-1'] = $this->get_translation('categoriesstatus_all');
    $list['0'] = $this->get_translation('categoriesstatus_inactive');
    $list['1'] = $this->get_translation('categoriesstatus_active');
    return $list;
  }

  /*
   * return if category is deletable
   * @return boolean result
   * @access public
   */
  function is_deletable() {
    return (isset($this->vars['points']) and $this->vars['points'] == 0);
  }

  /*
   * return title list
   * @param array $params
   * @return array
   * @access private
   */
  function get_titleList($params) {
    /* set default params */
    $dParams = array('status'=>-1, 'language'=>null, 'ids'=>-1, '_all'=>false);
    $params = array_merge($dParams, $params);
    
    /* build where statement */
    $w = array();

    /* check status */
    if ($params['status'] != -1)
      $w[] = 'status = '.$params['status'];

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

    /* return object title list */
    $list = $this->get_nameList('title', $w, $params['language']);
    if ( $params['_all'] == true)
      return array(0 => $this->get_translation('categoriesstatus_all'))+$list;
    return $list;
  }
}
?>