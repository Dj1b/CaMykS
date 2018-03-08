<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Jun 2011
 * Last Modif Date  : Jun 2011
 *
 * Generic Module Library object used to Join 2 Module Library 
 */

abstract class ModuleLibraryJoin extends ModuleLibrary {
  
  private $_initParams;
  
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function __construct(&$module, $params=array()) {
    parent::__construct(0, $module);
    
    /* default params */
    $defaultParams = array(
        'item1'=>'item1',
    	'item2'=>'item2'
    );
    
    /* merge params */
    $this->_initParams = array_merge($defaultParams, $params);

    /* admin data */
    $this->add_newItem($this->_initParams['item1'], 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem($this->_initParams['item2'], 'db', 'int', 'bigint unsigned', '', 0);

    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */
  
  /*
   * return a new object
   * @param integer $id
   * @return Object
   * @access public
   */
  public function &get_newObject($id=0) {
    eval('$obj = new '.get_class($this).'($this->_libParent, $this->_initParams);');
    return $obj;
  }

  /* define ModuleLibraryJoin methods */
  
  /*
   * return item1 id list for given item2
   * @param integer $id
   * @return array
   * @access public
   */
  public function get_item1ListForItem2($id) {
  	return $this->_get_itemJoinedList($this->_initParams['item1'], $this->_initParams['item2'], $id);
  }
  
  /*
   * return item2 id list for given item1
   * @param integer $id
   * @return array
   * @access private
   */
  public function get_item2ListForItem1($id) {
  	return $this->_get_itemJoinedList($this->_initParams['item2'], $this->_initParams['item1'], $id);
  }
  
  /*
   * return item1 id list for given item2 id list
   * @param array $ids
   * @return array
   * @access public
   */
  public function get_item1ListForItem2List($ids) {
  	return $this->_get_itemJoinedLists($this->_initParams['item1'], $this->_initParams['item2'], $ids);
  }
  
  /*
   * return item2 id list for given item1 id list
   * @param array $ids
   * @return array
   * @access private
   */
  public function get_item2ListForItem1List($ids) {
  	return $this->_get_itemJoinedLists($this->_initParams['item2'], $this->_initParams['item1'], $ids);
  }
  
  /*
   * save item1 id list for given item2
   * @param integer $id
   * @param array $list
   * @return boolean success
   * @access public
   */
  public function save_item1ListForItem2($id, $list) {
  	return $this->_save_itemJoinedList($this->_initParams['item1'], $list, $this->_initParams['item2'], $id);
  }
  
  /*
   * save item2 id list for given item1
   * @param integer $id
   * @param array $list
   * @return boolean success
   * @access public
   */
  public function save_item2ListForItem1($id, $list) {
  	return $this->_save_itemJoinedList($this->_initParams['item2'], $list, $this->_initParams['item1'], $id);
  }
  
  /* specific private tool methods */
  
  /*
   * return item joined list
   * @param string $target
   * @param string $given
   * @param integer $id
   * @return array
   * @access private
   */
  private function _get_itemJoinedList($target, $given, $id) {
  	global $camyks;
  	
  	/* initialise list */
  	$list = array();
  	
  	/* build sql query */
  	$sql = 'select `'.$target.'`';
  	$sql .= ' from '.$this->_libSQLTable.' as l';
  	$sql .= ' where l.'.$given.' = '.(int)$id;
  	
  	/* execute sql query */
    if ($this->execute_DBQuery($sql, __LINE__))
      /* get data from database */
      while ( $data = $this->get_DBQueryDataLine()) {
      	$list[] = $data[$target];
      }
    return $list;
  }
  
  /*
   * return item joined list
   * @param string $target
   * @param string $given
   * @param array $ids
   * @return array
   * @access private
   */
  private function _get_itemJoinedLists($target, $given, $ids) {
  	global $camyks;
  	
  	/* initialise list */
  	$list = array();
  	
  	/* check id list */
  	if (!is_array($ids) or count($ids) == 0 or !array_checkInteger($ids))
  	  return $list;
  	
  	/* build sql query */
  	$sql = 'select  `'.$given.'`, `'.$target.'`';
  	$sql .= ' from '.$this->_libSQLTable.' as l';
  	if (count($ids) == 1)
  	  foreach ($ids as $id)
  	    $sql .= ' where l.'.$given.' = '.$ids;
  	else
  	  $sql .= ' where l.'.$given.' in ('.implode(',', $ids).')';
  	
  	/* execute sql query */
    if ($this->execute_DBQuery($sql, __LINE__))
      /* get data from database */
      while ( $data = $this->get_DBQueryDataLine()) {
        if (!isset($list[$data[$given]]))
          $list[$data[$given]] = array();
      	$list[$data[$given]][] = $data[$target];
      }
    return $list;
  }
  
  /*
   * save item joined list
   * @param string $target
   * @param array $list
   * @param string $given
   * @param integer $id
   * @return boolean success
   * @access private
   */
  function _save_itemJoinedList($target, $list, $given, $id) {
  	global $camyks;
  
  	/* load existing groups */
    $oldTargets = array();
    	
    /* build sql query */
    $sql = 'select `'.$target.'` from '.$this->_libSQLTable;
    $sql .= ' where '.$given.'='.$id;
    if ( $this->execute_DBQuery($sql, __LINE__))
      while($data = $this->get_DBQueryDataLine())
      	$oldTargets[] = $data[$target];
    else
    	return false;
    	
    /* compare targets */
    $add = array();
    $keep = array();
    
    if (is_array($list)) {
      foreach ($list as $t) {
	    if (in_array($t, $oldTargets))
	  	  $keep[] = $t;
	    else
		  $add[] = $t;
	  }
    }
    
    /* delete old targets */
    if ( count($keep) > 0 )
      $sup = ' and `'.$target.'` NOT IN ('.implode(',', $keep).')';
    else
    	$sup = '';

    /* build sql query */
    $sql = 'delete from `'.$this->_libSQLTable.'` where `'.$given.'`='.$id.$sup;

    /* execute query */
    if (!($this->execute_DBQuery($sql, __LINE__)))
    	return false;

	/* add new targets from list */
	if (count($add) == 0)
		return true;

    /* build sql query */
    $sql = 'insert into `'.$this->_libSQLTable.'`';
    $sql .= ' (`'.$given.'`, `'.$target.'`)';
    $sql .= ' values ('.$id.', ';
    $sql .= implode('), ('.$id.', ', $add);
    $sql .= ')';

    /* execute query */
    return ($this->execute_DBQuery($sql, __LINE__));
  } 
}
?>