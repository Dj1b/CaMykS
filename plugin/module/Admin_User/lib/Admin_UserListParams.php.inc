<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date	: Oct 2017
 * Last Modif Date	: Oct 2017
 *
 * Admin_UserListParams object for Admin_User Module
 */

final class Admin_UserListParams extends ModuleLibrary {
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  public function __construct ( $id, &$module ) {
    parent::ModuleLibrary ( $id, $module );
  
    $this->add_newItem('status', 'temp', 'int', '', '', -1);
    $this->add_newItem('search', 'temp', 'string', '', '', '');
    
    /* generic initialisation */
    $this->init_library();
  }
  
  /* specific tool methods */
  
  /*
   * return built where statement
   * @return string
   * @access public
   */
   public function build_whereStatement() {
     $s = array();
     
     if ($this->vars['status'] > -1)
       $s[] = 'active = '.(int)$this->vars['status'];
     
     $this->vars['search'] = addslashes(trim($this->vars['search']));
     if ($this->vars['search'] != '')
       $s[] = '(firstname like "%'.$this->vars['search'].'%" or lastname like "%'.$this->vars['search'].'%" or email like "%'.$this->vars['search'].'%")';
     
     return implode(' and ', $s);
   }
}
?>