<?php
/**
 * @brief Content_GenericFaq module, faq item library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Apr 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericFaqItem class.
 */
final class Content_GenericFaqItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('listid', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('position', 'db', 'int', 'int unsigned', '', 0);
        $this->add_newItem('language', 'db', 'text', 'varchar', 3, '');
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('title', 'db', 'etext', 'varchar', 255, '');
        $this->add_newItem('content', 'db', 'etext', 'text', '', '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object data values
     * @return boolean result
     */
    public function check_data() {
        /* Load position for new items */
        if ($this->id == 0)
            $this->_libItems['position']->value = $this->get_itemNewIndex();

        /* Return as success */
        return true;
    }

    /* Specific tool methods */

    /**
     * Return faq item new index.
     * @return int
     */
    private function get_itemNewIndex() {
        global $camyks;

        /* Build SQL query */
        $sql = 'select count(id) as p';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where listid='.$this->_libItems['listid']->value;

        /* Execute query */
        if ($this->execute_DBQuery($sql, __LINE__))
            if ($data = $this->get_DBQueryDataLine())
                return ((int)$data['p'])+1;

        /* Return default value */
        return 1;
    }

    /**
     * Move position up.
     * @return void
     */
    public function move_up() {
        global $camyks;

        /* Build SQL query */
        $sql = 'select id';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where listid='.$this->_libItems['listid']->value;
        $sql .= ' and position<'.$this->_libItems['position']->value;
        $sql .= ' order by position desc';
        $sql .= ' limit 1';

        /* Execute SQL query */
        if ($this->execute_DBQuery($sql, __LINE__))
            if ($data = $this->get_DBQueryDataLine())
                $objid = $data['id'];
            else
                /* item is the first one, no need to move it up */
                return;
        else
            return;

        /* Update item */
        $sql = 'update '.$this->_libSQLTable.' set position=position-1 where id='.$this->id;
        if ($this->execute_DBQuery($sql, __LINE__))
            return;

        /* Update other item */
        $sql = 'update '.$this->_libSQLTable.' set position='.($this->_libItems['position']->value).' where id='.$objid;
        if ($this->execute_DBQuery($sql, __LINE__))
            return;
    }

    /**
     * Move position down.
     * @return void
     */
    public function move_down() {
        global $camyks;

        /* Build SQL query */
        $sql = 'select id';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where listid='.$this->_libItems['listid']->value;
        $sql .= ' and position>'.$this->_libItems['position']->value;
        $sql .= ' order by position';
        $sql .= ' limit 1';

        /* Execute SQL query */
        if ($this->execute_DBQuery($sql, __LINE__))
            if ($data = $this->get_DBQueryDataLine())
                $objid = $data['id'];
            else
                /* item is the last one, no need to move it down */
                return;
        else
            return;

        /* Update item */
        $sql = 'update '.$this->_libSQLTable.' set position=position+1 where id='.$this->id;
        if (!$this->execute_DBQuery($sql, __LINE__))
            return;

        /* Update other item */
        $sql = 'update '.$this->_libSQLTable.' set position='.($this->_libItems['position']->value).' where id='.$objid;
        if (!$this->execute_DBQuery($sql, __LINE__))
            return;
    }

    /**
     * Return object list for admin usage.
     * @param integer $listid
     * @return array
     */
    public function get_adminlist($listid) {
        return $this->get_objectList(true, 'listid='.$listid, -1, -1, 'position');
    }

    /**
     * Return object list for site usage.
     * @param integer $listid
     * @param integer $page
     * @param integer $bypage
     * @return array
     */
    public function get_sitelist($listid, $page=-1, $bypage=-1) {
        global $camyks;
        if ($page>-1 and $bypage>-1)
            return $this->get_objectList(true, 'listid='.$listid.' and status=1 and language=\''.$camyks->current_language.'\'', $page*$bypage, $bypage, 'position', '');
        return $this->get_objectList(true, 'listid='.$listid.' and status=1 and language=\''.$camyks->current_language.'\'', -1, -1, 'position', '');
     }

    /**
     * Return object count value.
     * @param integer $listid
     * @param integer $status
     * @param string $language
     * @return integer
     */
    public function get_listcount($listid, $status=-1, $language='') {
        global $camyks;
        $where = 'listid='.$listid;
        if ($status > -1)
            $where .= ' and status='.$status;
        if ($language != '')
            $where .= ' and language="'.$language.'"';
        return $this->get_objectCount($where);
    }
}
?>
