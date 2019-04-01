<?php
/**
 * @brief Admin_User Module user library.
 * @details Plugin / Module Library
 * @file plugin/module/Admin_User/lib/AdminUser.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2017
 * @date Modification: Mar 2019
 * @copyright 2017 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_UserListParams class.
 */
final class Admin_UserListParams extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        $this->add_newItem('status', 'temp', 'int', '', '', -1);
        $this->add_newItem('search', 'temp', 'string', '', '', '');

        /* generic initialisation */
        $this->init_library();
    }

    /* specific tool methods */

    /**
     * Return built where statement.
     * @return string
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
