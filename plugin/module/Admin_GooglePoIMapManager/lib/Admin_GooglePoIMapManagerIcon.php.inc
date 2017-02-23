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
 * Admin_GooglePoIMapManagerIcon object for Admin_GooglePoIMapManager Module
 */

class Admin_GooglePoIMapManagerIcon extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GooglePoIMapManagerIcon ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
    /* main content */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    
    $this->add_newItem('anchorLocX', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('anchorLocY', 'db', 'int', 'tinyint unsigned', '', 0);

    $this->add_newItem('mainImg', 'file', 'icons', '', '', '');
    $this->add_newItem('rollImg', 'file', 'icons', '', '', '');
    $this->add_newItem('slctImg', 'file', 'icons', '', '', '');
    $this->add_newItem('shdwImg', 'file', 'icons', '', '', '');

    /* generic initialisation */
    $this->init_library();
  }

  /* specific tool methods */
  
  /*
   * return name list
   * @param array $params
   * @return array
   * @access private
   */
  function get_objectNameList($params) {
    /* set default params */
    $dParams = array('none'=>false);
    /* merge params */
    $params = array_merge($dParams, $params);

    /* check params */
    if ($params['none'] == true)
      $list = array(0 => $this->get_translation('none'));
    else
      $list = array();

    return $list + $this->get_nameList();
  }

  /*
   * return object list
   * @param array $params
   * @return array
   * @access private
   */
  function get_list($params) {
    /* set default params */
    $dParams = array('ids'=>'-1', '_sized'=>false);
    /* merge params */
    $params = array_merge($dParams, $params);

    /* initialise where statement */
    $w = array();

    /* check params */
    if (is_array($params['ids'])) {
      if (count($params['ids']) == 0)
	return array();
      if (count($params['ids']) == 1)
	$w[] = 'id = '.$params['ids'][0];
      else
	$w[] = 'id in ('.implode(',', $params['ids']).')';
    }
    $w = implode(' and ', $w);

    $list = $this->get_objectList(false, $w);

    foreach ($list as $id => &$icon) {
      /* remove icons which doesn't have a main image */
      if ( $icon->vars['mainImg'] == ''){
	unset($list[$id]);
	continue;
      }

      /* check for requiered sized */
      if ( $params['_sized'] == true) {
	$f = new FSFile($icon->vars['mainImg']);
	$icon->vars['mainWidth'] = $f->moreinfos['width'];
	$icon->vars['mainHeight'] = $f->moreinfos['height'];
	$f = new FSFile($icon->vars['shdwImg']);
	if ( $f->exists ) {
	  $icon->vars['shdwWidth'] = $f->moreinfos['width'];
	  $icon->vars['shdwHeight'] = $f->moreinfos['height'];
	} else {
	  $icon->vars['shdwWidth'] = 0;
	  $icon->vars['shdwHeight'] = 0;	  
	}
      }
    }
    return $list;
  }

}
?>