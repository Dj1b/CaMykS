<?php
/**
 * @brief Admin_GenericDownloadManager Module document library
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Mar 2008
 * @date Modification: Jun 2023
 * @copyright 2008 - 2023 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericDownloadManagerDocument class.
 */
final class Admin_GenericDownloadManagerDocument extends ModuleLibrary {
    /**
     * var Object $fsfile
     * @brief Full file object description.
     */
    public $fsfile = null;

    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Define object attributes */
        $this->add_newItem('category', 'db', 'int', 'int unsigned', '', 0);
        $this->add_newItem('active', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('lg', 'db', 'text', 'varchar', 4, '');
        $this->add_newItem('security', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
        $this->add_newItem('subtitle', 'db', 'text', 'varchar', 128, '', true);
        $this->add_newItem('filetitle', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('releasedate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('file', 'file', 'documents', '', '', '');

        /* Define object temporary attributes */
        $this->add_newItem('update_security', 'temp', 'int', '', '', 0);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary method */

    /**
     * Check object data
     * @return boolean result
     */
    public function check_data() {
        /* Check for security code update */
        if ($this->_libItems['update_security']->value == 1) {
            $v = $this->_libItems['releasedate']->value;
            $v .= $this->_libItems['filetitle']->value;
            $v .= $this->_libItems['category']->value;
            $this->_libItems['security']->value = substr(md5($v), 0, 8);
        }

        if ($this->_libItems['filetitle']->value == '' and $this->_libItems['file']->upload === true) {
            $this->_libItems['filetitle']->value = $this->_libItems['file']->get_uploadedFileName();
        }

        return true;
    }

    /**
     * Build SQL condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $search = array();
        if (isset($params['active']) and $params['active'] > -1)
            $search[] = 'active='.$params['active'];
        if (isset($params['category']) and $params['category'] > 0)
            $search[] = 'category='.$params['category'];
        return implode(',', $search);
    }

    /* specific tool methods */

    /**
     * Return document link.
     * @return string
     */
    public function get_link() {
        global $camyks;

        $params = array('did' => $this->id);
        if ($this->_libParent->config->vars['link_mode'] == 1)
            $params['sid'] = $this->vars['security'];

        return $camyks->get_rootBaseURL('absolute').$this->_libParent->get_requestJSLink($params);
    }

    /**
     * Return admin titles list.
     * @param string $where
     * @return array
     */
    public function get_titlesList($where='') {
        /* Initialise title list */
        $titles = array();

        /* Load language */
        $lg = $this->_libParent->get_adminEditionLanguage();

        /* Build sql query */
        $sql = 'select objectid, title from '.$this->_libSQLLocaleTable;
        $sql .= ' where language="'.$lg.'"';
        if ($where != '') {
            $sql .= ' and '.$where;
        }

        /* Bxecute SQL query */
        if ($this->execute_DBQuery($sql, __LINE__))
            /* Load data from database */
            while ($data = $this->get_DBQueryDataLine())
                $titles[$data['objectid']] = $data['title'];

        /* Return results */
        return $titles;
    }

    /**
     * Return document count by categories.
     * @param array $categories
     * @return array
     */
    public function get_documentCountByCategories($categories=null) {
        /* Initialise result list */
        $list = array();

        /* Check categories */
        if (is_array($categories) and count($categories) == 0)
            return $list;

        /* Build sql query */
        $sql = 'select category, count(id) as cnt from '.$this->_libSQLTable;
        if (is_array($categories) and count($categories)>0) {
            $sql .= ' where category in ('.implode(',', $categories).')';
        }
        $sql .= ' group by category';

        /* Execute SQL query */
        if ($this->execute_DBQuery($sql, __LINE__))
            /* Load data from database */
            while ($data = $this->get_DBQueryDataLine())
                $list[$data['category']] = $data['cnt'];

        /* Send results */
        return $list;
    }

    /**
     * Return file info.
     * @return string
     */
    public function get_fileInfos() {
        if ($this->fsfile == null)
            $this->fsfile = new FSFile($this->vars['file']);
        return $this->fsfile->hsize.', '.$this->fsfile->typedesc;
    }
}
?>
