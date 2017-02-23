<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Nov 2010
 * Last Modif Date  : Nov 2010
 *
 * Admin_GenericContactFormManagerForm library for Admin_GenericContactFormManager module
 */

class Admin_GenericContactFormManagerForm extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericContactFormManagerForm( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );

    /* admin items */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('ipaddress', 'db', 'text', 'varchar', 48, '');
    $this->add_newItem('edate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('locale', 'db', 'text', 'varchar', 3, '');
    $this->add_newItem('hidden', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('account', 'db', 'int', 'bigint unsigned', '', 0);

    /* request items */
    $this->add_newItem('type', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('company', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('firstname', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('lastname', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('email', 'db', 'text', 'varchar', 64, '');
    $this->add_newItem('subject', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('subject_title', 'db', 'text', 'varchar', 255, '');
    $this->add_newItem('request', 'db', 'text', 'text', '', '');
    $this->add_newItem('attachment', 'file', 'attachments', '', '', '');    

    /* answer items  */

    $this->add_newItem('answer_date', 'db', 'date', 'bigint', '', 0);
    $this->add_newItem('answer_admin', 'db', 'text', 'varchar', 16, '');
    $this->add_newItem('answer_comment', 'db', 'text', 'text', '', '');

    

    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite Module Library methods */

  /*
   * check object data
   * @return boolean success
   * @access private
   */
  function check_data () {
    global $camyks;

    /* trim author value */
    $this->_libItems['author']->value = trim($this->_libItems['author']->value);
    /* check author value */
    if ($this->_libItems['author']->value == '') {
      $this->_libError = $this->get_translation('form_saveerror_authorempty');
      return false;
    }

    /* trim email value */
    $this->_libItems['email']->value = trim($this->_libItems['email']->value);
    /* check form value */
    if ($this->_libItems['email']->value == '') {
      $this->_libError = $this->get_translation('form_saveerror_emailempty');
      return false;
    }
    if (mail_isValidEmail($this->_libItems['email']->value)==false) {
      $this->_libError = $this->get_translation('form_saveerror_emailinvalid');
      return false;
    }

    /* trim form value */
    $this->_libItems['form']->value = trim(strip_tags($this->_libItems['form']->value));
    /* check form value */
    if ($this->_libItems['form']->value == '') {
      $this->_libError = $this->get_translation('form_saveerror_formempty');
      return false;
    }

    /* complete new object data */
    if ( $this->id == 0 ) {
      $this->_libItems['status']->value = 0;
      $this->_libItems['edate']->initialise();      
      $this->_libItems['ipaddress']->value = client_getIp();
      $this->_libItems['locale']->value = $camyks->current_language;
    }
    return true;
  }
  
  /*
   * build SQL condition
   * @param array $params
   * @return string
   * @access public
   */
  function build_SQLCondition( $params ) {
    $query = array();

    /* check status */
    if ( isset($params['status']) and $params['status']!=-1)
      $query[] = 'status = '.$params['status'];
   
    return implode(' AND ', $query);
  }

  /* specific methods */

  /*
   * return objects status list
   * @param boolean $full
   * @return array
   * @access private
   */
  function get_multiStatusList($full=false) {
    $list = array();
    if ($full)
      $list[-1] = $this->get_translation('formsstatus_all');
    $list[0] = $this->get_translation('formsstatus_disabled');
    $list[1] = $this->get_translation('formsstatus_enabled');
    $list[2] = $this->get_translation('formsstatus_pending');
    return $list;
  }

  /*
   * return object status list
   * @return array
   * @access private
   */
  function get_statusList() {
    return array(0 => $this->get_translation('formstatus_disabled'),
		 1 => $this->get_translation('formstatus_enabled'),
		 2 => $this->get_translation('formstatus_pending'));
  } 

  /*
   * return object status value
   * @param mixed $status
   * @return string
   */
  function get_statusValue($status=false) {
    $list = $this->get_statusList();
    if ($status === false)
      $status = $this->vars['status'];
    return $list[$status];
  }

  /*
   * return object status icon list
   * @return array
   * @access private
   */
  function get_statusIconList() {
    $theme = &$this->_libParent->theme;
    return array(0 =>'<img src="'.$theme->get_pictURL('empty', 12, 'std').'" alt="" border="0" />',
		 1 =>'<img src="'.$theme->get_pictURL('valid', 12, 'std').'" alt="" border="0" />',
		 2 =>'<img src="'.$theme->get_pictURL('minus', 12, 'std').'" alt="" border="0" />');
  } 

  /*
   * return object status icon
   * @return array
   * @access private
   */
  function get_statusIcon($status=false) {
    $icons = $this->get_statusIconList();
    if ($status === false)
      return $icons[$this->vars['status']];
    return $icons[$status];
  }

  /*
   * return form list with given params
   * @params array $params
   * @return array
   * @access private
   */
  function get_list($params=array()) {
    global $camyks;
    $p = array('status'=>-1, 'limit'=>-1, 'count'=>-1, 'order'=>'id', 'orderway'=>'');
    $params = array_merge($p, $params);
    $w = $this->build_whereStatement($params);
    return $this->get_objectList($camyks->current_language, $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
  } 
  
  /*
   * return form count with given params
   * @params array $params
   * @return array
   * @access private
   */
  function count($params=array()) {
    global $camyks;
    $p = array('status'=>-1);
    $params = array_merge($p, $params);
    return $this->get_objectCount($this->build_whereStatement($params));
  }
  
  /*
   * build where statement from params
   * @param array $params
   * @return string
   * @access private
   */
  function build_whereStatement($params=array()) {
    $w = array();

    /* check status */
    if ( is_string($params['status']) and $params['status'] != '')
      $w[] = 'status '.$params['status'];
    elseif($params['status'] != -1 )
      $w[] = 'status = '.$params['status'];
    
    /* return result */
    return implode(' and ', $w);
  }
}
?>