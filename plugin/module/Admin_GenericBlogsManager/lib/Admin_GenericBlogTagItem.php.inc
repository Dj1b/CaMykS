<?php
/**
 * @brief Admin_GenericBlogsManager module, tag library.
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
 * Admin_GenericBlogTagItem class.
 */
final class Admin_GenericBlogTagItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);
        /* Define object attributes */
        $this->add_newItem('newsid', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('title', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('author', 'db', 'text', 'varchar', 32, '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        /* Update name value */
        $this->_libItems['name']->value = string_parseSpecialChars(strtolower($this->_libItems['title']->value), array('pattern'=>'/[^\w]/'));
        return true;
    }

    /* Mark: Specific tool methods */

    /**
     * Return tag list.
     * @param boolean $tagMode
     * @return array
     */
    public function get_countTagList($tagMode=false) {
        global $camyks;

        /* Initialise the list */
        $tagList = array();

        /* Build SQL query */
        $sql = 'select title, count(id) as counter';
        $sql .= ' from '.$this->_libSQLTable;
        if ($tagMode !== true)
            $sql .= ' where author="'.$camyks->adminUser->login.'"';
        $sql .= ' group by title';

        /* Execute query */
        if ($this->execute_DBQuery($sql, __LINE__))
            while ($data = $this->get_DBQueryDataLine())
                $tagList[stripslashes($data['title'])] = $data['counter'];

        /* Return result */
        return $tagList;
    }

    /**
     * Update tag objects.
     * @param string $tag
     * @param string $tagValue
     * @param boolean $tagMode
     * @return boolean success
     */
    public function update_tagTitle($tag, $tagValue, $tagMode=false) {
        global $camyks;

        /* get name */
        $nameValue = string_parseSpecialChars(strtolower($tagValue), array('pattern'=>'/[^\w]/'));

        if ($tagValue == '' or $nameValue == '')
            return false;

        if ($tag == '') {
            /* Update object data */
            $this->_libItems['newsid']->value = 0;
            $this->_libItems['author']->value = $camyks->adminUser->login;
            $this->_libItems['title']->value = $tagValue;
            $this->_libItems['name']->value = $nameValue;
            return $this->save();
        } else {
            /* Build update tags SQL query */
            $sql = 'update '.$this->_libSQLTable;
            $sql .= ' set title="'.$tagValue.'"';
            $sql .= ', name="'.$nameValue.'"';
            $sql .= ' where title="'.$tag.'"';
            if ($tagMode !== true)
                $sql .= ' and author="'.$camyks->adminUser->login.'"';

            /* Execute query */
            return $this->execute_DBQuery($sql, __LINE__);
        }
    }

    /**
     * Delete tag objects from title.
     * @param string $tag
     * @param boolean $tagMode
     * @return boolean succes
     */
    public function delete_tagTitle($tag, $tagMode=false) {
        global $camyks;

        /* Build sql query */
        $sql = 'delete from '.$this->_libSQLTable.' where title="'.$tag.'"';
        if ($tagMode !== true)
            $sql .= ' and author="'.$camyks->adminUser->login.'"';

        /* Execute query */
        return $this->execute_DBQuery($sql, __LINE__);
    }

    /*
     * Delete tag objects from ids.
     * @param array $tags
     * @return boolean success
     */
    public function delete_tagIDs($tags=array()) {
        /* Check array */
        if (count($tags) == 0)
            return true;

        /* Build sql query */
        $sql = 'delete from '.$this->_libSQLTable.' where id IN('.implode(',',$tags).')';

        /* Execute query */
        return $this->execute_DBQuery($sql, __LINE__);
    }

    /**
     * Delete tags object from given news.
     * @param integer $newsid
     * @return boolean success
     */
    public function delete_newsTags($newsid=null) {
        /* Check newsid */
        if (!isset($newsid))
            return false;

        /* Build sql query */
        $sql = 'delete from '.$this->_libSQLTable.' where newsid='.$newsid;

        /* Execute query */
        return $this->execute_DBQuery($sql, __LINE__);
    }

    /**
     * Prune old tags from given news.
     * @param integer $newsid
     * @param array $tags
     * @return boolean success
     */
    public function prune_oldNewsTags($newsid=null, $tags=array()) {
        global $camyks;

        /* Check newsid */
        if (!isset($newsid))
            return false;

        /* Check tags */
        if (count($tags) == 0)
            return $this->delete_newsTags($newsid);

        /* Build sql query */
        $sql = 'delete from '.$this->_libSQLTable.' where newsid='.$newsid.' and id NOT IN ('.implode(',', $tags).')';

        /* Execute query */
        return $this->execute_DBQuery($sql, __LINE__);
    }

    /**
     * Return tag unique titles list.
     * @return array
     */
    public function get_titleList() {
        global $camyks;

        /* Build the list */
        $tagList = array();

        /* Build sql query */
        $sql = 'select title';
        $sql .= ' from '.$this->_libSQLTable;
        if ($tagMode !== true)
            $sql .= ' where author="'.$camyks->adminUser->login.'"';
        $sql .= ' group by title';

        /* Execute query */
        if ($this->execute_DBQuery($sql, __LINE__))
            while ($data = $this->get_DBQueryDataLine())
                $tagList[] = stripslashes($data['title']);

        /* Return result */
        return $tagList;
    }
}
?>
