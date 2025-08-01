<?php
/**
 * @brief Admin_GenericBlogsManager module, news library.
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
 * Admin_GenericBlogNewsItem class.
 */
final class Admin_GenericBlogNewsItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);
        /* Define object attributes */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('title', 'db', 'etext', 'varchar', 255, '');
        $this->add_newItem('content', 'db', 'etext', 'text', '', '');
        $this->add_newItem('author', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('ndate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('videolink', 'db', 'etext', 'text', '', '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Initialise object.
     * @return boolean success
     */
    public function initialise() {
        global $camyks;
        /* Generic initialisation */
        if (parent::initialise()) {
            /* Update admin user author */
            $this->_libItems['author']->value = $camyks->adminUser->login;
            /* Return success */
            return true;
        }
        return false;
    }

    /**
     * Check data.
     * @return boolean result
     */
    public function check_data() {
        /* Load tag list */
        $tagCount = isset($_REQUEST['tagCounter']) ? (int)$_REQUEST['tagCounter'] : 0;

        $this->oldTags = array();
        $this->newTags = array();

        for ($i=0; $i< $tagCount; $i++) {
            if (isset($_REQUEST['tag'.$i.'_id'])) {
                $id = $_REQUEST['tag'.$i.'_id'];
                $value = $_REQUEST['tag'.$i.'_value'];

                if ($id > 0) {
                    $this->oldTags[ $id ] = $value;
                } else {
                    if (!in_array($value, $this->oldTags)) {
                        $this->newTags[] = $value;
                    }
                }
            }
        }
        return true;
    }

    /**
     * Save object.
     * @return boolean success
     */
    public function save() {
        if (parent::save() === false)
            return false;
        return $this->save_tags();
    }

    /* Mark: Specific tool methods */

    /**
     * Load linked tag objects list.
     * @return void
     */
    public function get_tagList() {
        /* Load tag item */
        $tagItem = &$this->_libParent->tagItem;

        /* Load tag list */
        if ($this->id == 0)
            $this->tagList = array();
        else
            $this->tagList = $tagItem->get_objectList(false, 'newsid='.$this->id);
    }

    /**
     * Load comment objects list.
     * @return void
     */
    public function get_blogComments() {

        /* get tag item */
        $commentItem = &$this->_libParent->commentItem;

        /* get tag list */
        if ($this->id == 0)
            $this->vars['comments'] = array();
        else
            $this->vars['comments'] = $commentItem->get_objectList(false, 'newsid='.$this->id.' and status=1');
    }

    /**
     * Return object list by date.
     * @param array $authors
     * @param string $tag
     * @param integer $page
     * @param integer $count
     * @param boolean $dated
     * @return array
     */
    public function get_blogItemList($authors, $tag, $page, $count, $dated=false) {
        global $camyks;

        $items = array();

        /* Build sql query */
        $sql = 'select m.*';
        $sql .= ' from '.$this->_libSQLTable.' as m';
        if ($tag != null and $tag != '')
            $sql .= ', '.$this->_libParent->tagItem->_libSQLTable.' as t';

        /* Check status */
        $sql .= ' where m.status=1';

        /* Check authors */
        if (count($authors)==1)
            $sql .= ' and m.author="'.$authors[0].'"';
        else if (count($authors) > 1)
            $sql .= ' and m.author in ("'.implode('","', $authors).'")';

        /* Check date */
        if ($dated == true) {
            $sql .= ' and m.ndate < '.time();
        }

        /* Check tags */
        if ($tag != null and $tag != '') {
            $sql .= ' and t.name="'.$tag.'"';
            $sql .= ' and t.newsid=m.id';
        }

        /* Add order */
        $sql .= ' order by m.ndate desc';

        /* Add limit */
        $sql .= ' limit '.$page*$count.', '.$count;

        /* Execute query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            while ($data = $this->get_DBQueryDataLine()) {
                $item = $this->get_newObject($data['id']);
                $item->get_fromArray($data, $this->_libItemTypes['db']);
                $item->get_fromItems();
                $item->vars['coms'] = 0;
                $item->tagList = array();
                $items[$data['id']] = $item;
            }
        }

        /* Complete data */
        if (count($items) > 0) {
            $ids = array_keys($items);
            /* Load items tags */
            $tags = $this->_libParent->tagItem->get_objectList(false, 'newsid IN('.implode(',', $ids).')');
            foreach ($tags as $tag) {
                $items[$tag->vars['newsid']]->tagList[] = $tag;
            }


            /* Load items comment counts */
            $comCount = $this->_libParent->commentItem->count_newsComments($ids, 1);
            foreach($comCount as $newsid=>$coms) {
                $items[$newsid]->vars['coms'] = $coms;
            }
        }
        return $items;
    }

    /**
     * Return object count.
     * @param array $authors
     * @param string $tag
     * @param boolean $dated
     * @return array
     */
    public function get_blogItemCount($authors, $tag, $dated=false) {
        global $camyks;

        /* Build sql query */
        $sql = 'select count(m.id) as c';
        $sql .= ' from '.$this->_libSQLTable.' as m';
        if ($tag != null and $tag != '')
            $sql .= ', '.$this->_libParent->tagItem->_libSQLTable.' as t';

        /* Check active */
        $sql .= ' where m.status=1';

        /* Check authors */
        if (count($authors)==1)
            $sql .= ' and m.author="'.$authors[0].'"';
        else if (count($authors) > 1)
            $sql .= ' and m.author in ("'.implode('","', $authors).'")';

        /* Check date */
        if ($dated == true) {
            $sql .= ' and m.ndate < '.time();
        }

        /* Check tags */
        if ($tag != null and $tag != '') {
            $sql .= ' and t.name="'.$tag.'"';
            $sql .= ' and t.newsid=m.id';
        }

        /* Execute query */
        if ($this->execute_DBQuery($sql, __LINE__))
            if ($data = $this->get_DBQueryDataLine())
                return $data['c'];
        return 0;
    }

    /**
     * Return news count by author from given author list.
     * @param array $authors
     * @param boolean $dated
     * @return array
     */
    public function get_newsCountByAuthor($authors, $dated=false) {
        global $camyks;

        /* Initialise result array */
        $result = array();

        /* Pre-initialise result array values */
        if (count($authors)) {
            foreach ($authors as $a)
                $result[$a] = 0;
        }

        /* Build sql query */
        $sql = 'select count(id) as c, author';
        $sql .= ' from '.$this->_libSQLTable.' as m';

        /* Check active */
        $sql .= ' where status=1';

        /* Check authors */
        if (count($authors)==1)
            $sql .= ' and author="'.$authors[0].'"';
        else if (count($authors) > 1)
            $sql .= ' and author in ("'.implode('","', $authors).'")';
        else
            $sql .= ' and author<>""';

        /* Check date */
        if ($dated == true) {
            $sql .= ' and m.ndate < '.time();
        }

        /* Add group statement */
        $sql .= ' group by author';

        /* Execute query */
        if ($this->execute_DBQuery($sql, __LINE__))
            while ($data = $this->get_DBQueryDataLine())
                $result[$data['author']] = $data['c'];
        return $result;
    }

    /**
     * Return news count by tag from given author list.
     * @param array $authors
     * @param boolean $dated
     * @return array
     */
    public function get_newsCountByTag($authors, $dated=false) {
        global $camyks;

        /* Initialise result array */
        $result = array();

        /* Build sql query */
        $sql = 'select t.title as title, t.name as name, count(t.id) as c';
        $sql .= ' from '.$this->_libSQLTable.' as m';
        $sql .= ', '.$this->_libParent->tagItem->_libSQLTable.' as t';

        /* Check active */
        $sql .= ' where m.status=1';

        /* Check authors */
        if (count($authors)==1)
            $sql .= ' and m.author="'.$authors[0].'"';
        else if (count($authors) > 1)
            $sql .= ' and m.author in ("'.implode('","', $authors).'")';

        /* Check date */
        if ($dated == true) {
            $sql .= ' and m.ndate < '.time();
        }

        /* Check tags */
        $sql .= ' and t.newsid=m.id';

        /* Add groupe statement */
        $sql .= ' group by title, name';

        /* Execute query */
        if ($this->execute_DBQuery($sql, __LINE__)) {
            while ($data = $this->get_DBQueryDataLine()) {
                $tag = $this->_libParent->tagItem->get_newObject(0);
                $tag->vars = array();
                $tag->vars['title'] = $data['title'];
                $tag->vars['name'] = $data['name'];
                $result[] = array('count'=>$data['c'], 'tag'=>$tag);
            }
        }
        return $result;
    }

    /**
     * Check if object is valid for site display.
     * @param array $validAuthors
     * @return boolean sucess
     */
    public function check_siteDisplay($validAuthors) {
        /* Check status */
        if ($this->_libItems['status']->value == 0)
            return false;

        /* Check author */
        if (count($validAuthors)>0 and in_array($this->_libItems['author']->value, $validAuthors)===false)
            return false;

        /* return default value */
        return true;
    }

    /* Private methods */

    /**
     * Save tags.
     * @return boolean succes
     */
    private function save_tags() {
        global $camyks;

        /* Load tag item */
        $tagItem = &$this->_libParent->tagItem;

        /* Delete old unused tags */
        $tagIDs = array_keys($this->oldTags);
        if (count($tagIDs) > 0) {
            if ($tagItem->prune_oldNewsTags($this->id, $tagIDs) === false)
                return false;
        }

        /* Insert new tags */
        $tagItem->_libItems['author']->value = $camyks->adminUser->login;
        $tagItem->_libItems['newsid']->value = $this->id;;
        foreach ($this->newTags as $tag) {
            $tagItem->id = 0;
            $tagItem->_libItems['title']->value = $tag;
            if ($tagItem->save() === false)
                return false;
        }

        /* Return success */
        return true;
    }
}
?>
