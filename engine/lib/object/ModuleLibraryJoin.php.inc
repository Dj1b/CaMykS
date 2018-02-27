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

class ModuleLibraryJoin extends ModuleLibrary {
  
  private $_initParams;
  
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function ModuleLibraryJoin (&$module, $params=array()) {
    parent::ModuleLibrary(0, $module);
    
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
  function &get_newObject($id=0) {
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
  function get_item1ListForItem2($id) {
  	return $this->_get_itemJoinedList($this->_initParams['item1'], $this->_initParams['item2'], $id);
  }
  
  /*
   * return item2 id list for given item1
   * @param integer $id
   * @return array
   * @access private
   */
  function get_item2ListForItem1($id) {
  	return $this->_get_itemJoinedList($this->_initParams['item2'], $this->_initParams['item1'], $id);
  }
  
  /*
   * save item1 id list for given item2
   * @param integer $id
   * @param array $list
   * @return boolean success
   * @access public
   */
  function save_item1ListForItem2($id, $list) {
  	return $this->_save_itemJoinedList($this->_initParams['item1'], $list, $this->_initParams['item2'], $id);
  }
  
  /*
   * save item2 id list for given item1
   * @param integer $id
   * @param array $list
   * @return boolean success
   * @access public
   */
  function save_item2ListForItem1($id, $list) {
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
  function _get_itemJoinedList($target, $given, $id) {
  	global $camyks;
  	
  	/* initialise list */
  	$list = array();
  	
  	/* build sql query */
  	$sql = 'select `'.$target.'`';
  	$sql .= ' from '.$this->_libSQLTable.' as l';
  	$sql .= ' where l.'.$given.' = '.$id;
  	
  	/* execute sql query */
    if ($this->execute_DBQuery($sql, __LINE__))
      /* get data from database */
      while ( $data = $this->get_DBQueryDataLine()) {
      	$list[] = $data[$target];
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