<?php
/**
 * @brief Content_GenericHTMLNews module, news item library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Mar 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericHTMLNewsItem class.
 */
final class Content_GenericHTMLNewsItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('listid', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('language', 'db', 'text', 'varchar', 3, '');
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('title', 'db', 'etext', 'varchar', 255, '');
        $this->add_newItem('content', 'text', 'html', '', '', '');
        $this->add_newItem('author', 'db', 'text', 'varchar', 32, '');
        $this->add_newitem('ndate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newitem('source_title', 'db', 'etext', 'varchar', 255, '');
        $this->add_newitem('source_url', 'db', 'etext', 'varchar', 255, '');
        $this->add_newitem('summary', 'db', 'etext', 'text', '', '');

        /* Generic ModuleLibrary initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Initialise object
     * @return boolean success
     */
    public function initialise() {
        global $camyks;

        /* Generic object initialisation */
        parent::initialise();

        /* Update author value */
        $this->_libItems['author']->value = $camyks->adminUser->login;

        return true;
    }

    /**
     * Build SQL condition.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        return 'listid='.$this->_libParent->newslist->id;
    }

    /* mark: Specific methods */

    /**
     * Return item list for an admin usage.
     * @param integer $listid
     * @param integer $page
     * @param integer $bypage
     * @return array
     */
    function get_adminlist($listid, $page=-1, $bypage=-1) {
        global $camyks;
        if ($page>-1 and $bypage>-1)
            return $this->get_objectList(true, 'listid='.$listid.'', $page*$bypage, $bypage, 'ndate', 'desc');
        return $this->get_objectList(true, 'listid='.$listid.'', -1, -1, 'ndate', 'desc');
    }

    /**
     * Return item list for a site usage.
     * @param integer $listid
     * @param integer $page
     * @param integer $bypage
     * @return array
     */
    public function get_sitelist($listid, $page=-1, $bypage=-1) {
        global $camyks;

        $items = array();

        /* Build SQL query */
        $sql = 'select '.$this->_libSQLTable.'.id,';
        $sql .= $this->_libSQLTable.'.listid,';
        $sql .= $this->_libSQLTable.'.ndate,';
        $sql .= $this->_libSQLTable.'.title,';
        $sql .= $this->_libSQLTable.'.source_title,';
        $sql .= $this->_libSQLTable.'.source_url,';
        $sql .= $this->_libSQLTable.'.author,';
        $sql .= $this->_libSQLTable.'.summary,';
        $sql .= 'admin_user.firstname,';
        $sql .= 'admin_user.lastname,';
        $sql .= 'admin_user.email';
        $sql .= ' from '.$this->_libSQLTable.', admin_user';
        $sql .= ' where listid='.$listid;
        $sql .= ' and language="'.$camyks->current_language.'"';
        $sql .= ' and status=1';
        $sql .= ' and ndate<'.mktime();
        $sql .= ' and admin_user.login = '.$this->_libSQLTable.'.author';
        $sql .= ' order by ndate DESC';
        if ($bypage > 0 and $page > -1)
            $sql .= ' limit '.($page*$bypage).', '.$bypage;

        /* Execute SQL query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            while ($data = $this->get_DBQueryDataLine()) {
                $item = new Content_GenericHTMLNewsItem ($data['id'], $this->_libParent);
                $item->get_fromArray($data, $this->_libItemTypes['db']);
                $item->_libItems['content']->get($item->id);
                $item->get_fromItems();

                /* check author name */
                if ($data['firstname'] == '' and $data['lastname'] == '') {
                    $item->vars['author'] = $data['author'];
                } else if ($data['firstname'] == '') {
                    $item->vars['author'] = $data['lastname'];
                } else if ($data['lastname'] == '') {
                    $item->vars['author'] = $data['firstname'];
                } else {
                    $item->vars['author'] = $data['firstname'] . ' ' . $data['lastname'];
                }

                /* check author email */
                if ($data['email'] != '') {
                    $item->vars['author'] = '<a href="'.mail_encode($data['email']).'" class="link1">'.$item->vars['author'].'</a>';
                }
                $items[] = $item;
            }
        }
        return $items;
    }

    /**
     * Return item count.
     * @param integer $listid
     * @param integer $status
     * @param string $lg
     * @param boolean $dated
     * @return void
     */
    public function get_listcount($listid, $status=-1, $lg='', $dated=false) {
        global $camyks;
        $where = 'listid='.$listid;
        if ($status > -1) {
            $where .= ' and status='.$status;
        }
        if ($lg != '') {
            $where .= ' and language="'.$lg.'"';
        }
        if ($dated) {
            $where .= ' and ndate<'.mktime();
        }
        return $this->get_objectCount($where);
    }

    /**
     * Return last active items
     * @param integer $listid
     * @param string $lg
     * @param integer $count
     * @return array
     */
    public function get_lastItemsList($listid, $lg, $count) {
        return $this->get_objectList(false, 'listid='.$listid.' and status=1 and language="'.$lg.'" and ndate<'.time(), 0, $count, 'ndate', 'desc');
    }
}
?>
