<?php
/**
 * @brief Admin_GenericBlogsManager module, comment library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Apr 2008
 * @date Modification: Jul 2025
 * @copyright 2008 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericBlogCommentItem class.
 */
final class Admin_GenericBlogCommentItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);
        /* Define object attributes */
        $this->add_newItem('newsid', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 1);
        $this->add_newItem('title', 'db', 'etext', 'varchar', 64, '');
        $this->add_newItem('content', 'db', 'etext', 'text', '', '');
        $this->add_newItem('author', 'db', 'etext', 'varchar', 32, '');
        $this->add_newitem('ndate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('email', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('website', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('ipaddress', 'db', 'text', 'varchar', 48, '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object data before saving
     * @return boolean result
     */
    public function check_data() {
        /* Check newsid */
        if ($this->_libItems['newsid']->value == 0) {
            $this->_libError = $this->get_translation('savecommentfailed_internal_error');
            return false;
        }

        /* Parse content */
        $content = $this->_libItems['content']->value;
        $content = strip_tags($content);
        $content = preg_replace(array('/[\ ]+/', '/(\n\r|\n|\r)+/'), array(' ', "\n"), $content);

        /* Allow link */
        $content = preg_replace('/(https?:\/\/[^\s]*)/', '<a href="$1" target="_blank">$1</a>', $content);
        $this->_libItems['content']->value = $content;

        /* Check content */
        if ($this->_libItems['content']->value == '') {
            $this->_libError = $this->get_translation('savecommentfailed_emptycontent');
            return false;
        }

        /* Parse author */
        $author = $this->_libItems['author']->value;
        $author = strip_tags($author);
        $author = preg_replace('/\s\s+/', ' ', $author);
        $this->_libItems['author']->value = $author;
        /* Check author */
        if ($this->_libItems['author']->value == '') {
            $this->_libError = $this->get_translation('savecommentfailed_emptyauthor');
            return false;
        }

        /* Check email */
        if (mail_isValidEmail($this->_libItems['email']->value) === false){
            $this->_libError = $this->get_translation('savecommentfailed_invalidemail');
            return false;
        }
        return true;
    }

    /* mark: Specific data management methods */

    /**
     * Delete all comments from given news.
     * @param integer $newsid
     * @return boolean success
     */
    public function delete_newsComments($newsid=null) {
        /* Check news id value */
        if (!($newsid > 0))
            return false;

        /* Build sql query */
        $sql = 'delete from '.$this->_libSQLTable;
        $sql .= ' where newsid='.$newsid;

        /* return query execution result */
        return $this->execute_DBQuery($sql, __LINE__);
    }

    /* Mark: Specific data gathering methods */

    /**
     * Count comments for given news list by status.
     * @param array $newsids
     * @return array
     */
    public function count_newsCommentsByStatus($newsids) {
        /* Check newsids */
        $coms = array();
        if (count($newsids) == 0)
            return $coms;

        /* Pre-initialise coms values */
        foreach ($newsids as $id)
            $coms[$id] = array(0, 0, 0);

        /* Build sql query */
        $sql = 'select newsid, status, count(id) as c';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where newsid IN('.implode(',', $newsids).')';
        $sql .= ' group by newsid, status';

        /* Execute query */
        if ($this->execute_DBQuery($sql, __LINE__))
            while ($data = $this->get_DBQueryDataLine())
                $coms[$data['newsid']][$data['status']] = $data['c'];
        return $coms;
    }

    /**
     * Count comments for given news list.
     * @param array $newsids
     * @param integer $status
     * @return array
     */
    public function count_newsComments($newsids, $status=null) {
        /* Check newsids */
        $coms = array();
        if (count($newsids) == 0)
            return $coms;

        /* Build sql query */
        $sql = 'select newsid, count(id) as c';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where newsid IN('.implode(',', $newsids).')';
        if (isset($status))
            $sql .= ' and status='.$status;
        $sql .= ' group by newsid';

        /* Execute query */
        if ($this->execute_DBQuery($sql, __LINE__))
            while ($data = $this->get_DBQueryDataLine())
                $coms[$data['newsid']] = $data['c'];
        return $coms;
    }

    /**
     * Return unread message count for current user news.
     * @return integer
     */
    public function count_userNewsUnreadComments() {
        global $camyks;

        /* get Newsitem sql table */
        if (isset($this->_libParent->newsItem->_libSQLTable))
            $newsTable = $this->_libParent->newsItem->_libSQLTable;
        else
            $newsTable = 'admin_genericblognewsitem';

        /* Build sql query */
        $sql = 'select count('.$this->_libSQLTable.'.id) as c';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ', '.$newsTable;
        $sql .= ' where '.$newsTable.'.author="'.$camyks->adminUser->login.'"';
        $sql .= ' and '.$this->_libSQLTable.'.newsid='.$newsTable.'.id';
        $sql .= ' and '.$this->_libSQLTable.'.status=0';

        /* Execute query */
        if ($this->execute_DBQuery($sql, __LINE__))
            if ($data = $this->get_DBQueryDataLine())
                return $data['c'];
        return 0;
    }

    /**
     * Return news ids with un read comments.
     * @return array
     */
    public function get_newsWithUnreadComments() {
        $list = array();

        /* Build sql query */
        $sql = 'select id, newsid';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where status=0';

        /* Execute query */
        if ($this->execute_DBQuery($sql, __LINE__))
            while ($data = $this->get_DBQueryDataLine())
                $list[] = $data['newsid'];

        /* Return list */
        return $list;
    }

    /* mark: Specific tool methods */

    /**
     * Return available status list for this object type.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('comment_statusmode_0'),
            1 => $this->get_translation('comment_statusmode_1'),
            2 => $this->get_translation('comment_statusmode_2'),
        );
    }
}
?>
