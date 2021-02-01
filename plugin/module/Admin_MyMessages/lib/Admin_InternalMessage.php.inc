<?php
/**
 * @brief Admin_MyMessages Module message library
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2007
 * @date Modification: Jan 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_InternalMessage class.
 */
final class Admin_InternalMessage extends ModuleLibrary {

    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);
        /* Content attributes */
        $this->add_newItem('senddate', 'db', 'date', 'bigint', '', time());
        $this->add_newItem('fromuser', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('fromstatus', 'db', 'int', 'tinyint', '', 0);
        $this->add_newItem('touser', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('tostatus', 'db', 'int', 'tinyint', '', 2);
        $this->add_newItem('title', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('content', 'db', 'text', 'text', '', '');

        /* Temporary attributes */
        $this->add_newItem('maxmessages', 'temp', 'int', 'int', '', $this->_libParent->maxmessages);

        /* Perform generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        global $camyks;

        /* basic info */
        $this->_libItems['fromuser']->value = $camyks->adminUser->login;

        /* check receipt user login / id */
        if (AdminUser::exists_login($this->_libItems['touser']->value) === false) {
            $this->_libError = 'touser_doesnt_exists';
            return false;
        }

        /* check if receipt user has some free slot on reveived box */
        $messagecount = $this->get_objectCount('touser="'.$this->_libItems['touser']->value.'" and tostatus>0');

        if ($messagecount >= $this->_libItems['maxmessages']->value) {
            $this->_libError = 'touser_receivedboxfull';
            return false;
        }
        return true;
    }

    /* Specific tool methods */

    /**
     * Return messages in receive box.
     * @return array
     */
    public function get_reveivedBoxMessageList() {
        global $camyks;
        return $this->get_objectList(false, 'touser="'.$camyks->adminUser->login.'" and tostatus>0', -1, -1, 'senddate', 'desc');
    }

    /**
     * Return messages in send box.
     * @return array
     */
    public function get_sentBoxMessageList() {
        global $camyks;
        return $this->get_objectList(false, 'fromuser="'.$camyks->adminUser->login.'" and fromstatus>0', -1, -1, 'senddate', 'desc');
    }

    /**
     * Delete message list
     * @param array $pms
     * @param string $view
     * @return boolean success
     */
    public function delete_messages($pms, $view) {
        global $camyks;

        /* Escape if no item exist */
        if (count($pms) == 0) {
            return true;
        }
        /* Try to delete from database messages marked as deleted as on both side */
        $sql = 'delete from '.$this->_libSQLTable;
        if (count ($pms) == 1)
            $sql .= ' where id='.$pms[0].'';
        else
            $sql .= ' where id in ('.implode(',', $pms).')';

        if ($view == 'from')
            $sql .= ' and tostatus=0;';
        else
            $sql .= ' and fromstatus=0;';

        /* Execute sql query */
        if ($this->execute_DBQuery($sql, __LINE__))
            /* Update all other message */
            return $this->update_messagesStatus($pms, $view, 0);
        return false;
    }

    /**
     * Update message list status.
     * @param array $pms
     * @param string $view
     * @param integer $status
     * @return boolean success
     */
    public function update_messagesStatus($pms, $view, $status=1) {
        global $camyks;

        /* Escape if no item exist */
        if (count($pms) == 0) {
            return true;
        }

        /* Build sql query */
        $sql = 'update '.$this->_libSQLTable;
        $sql .= ' set '.$view.'status='.$status;
        if (count($pms) == 1)
            $sql .= ' where id='.$pms[0].';';
        else
            $sql .= ' where id in ('.implode(',', $pms).');';

        /* Return result of sql query execution */
        return ($this->execute_DBQuery($sql, __LINE__));
    }
}
?>
