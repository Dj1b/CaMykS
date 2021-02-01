<?php
/**
 * @brief Admin_ContentPage Module ContentPage library
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.1.5.2
 * @date Creation: Jun 2005
 * @date Modification: Jan 2021
 * @copyright 2005 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * ContentPage class.
 */
final class ContentPage {
    /**
     * var integer $mode
     * @brief Page mode, same as CaMykS modes.
     */
    public $mode;

    /**
     * var integer $id
     * @brief Page id.
     */
    public $id = 0;

    /**
     * var string $name
     * @brief Page symbolic name.
     */
    public $name = '';

    /**
     * var integer $parent_id
     * @brief Parent page id.
     */
    public $parent_id;

    /**
     * var integer $position
     * @brief Sorting position in parent page children list.
     */
    public $position;

    /**
     * var string $type
     * @brief Page type, currently unused.
     */
    public $type = 'page';

    /**
     * var boolean $active
     * @brief Page status.
     */
    public $active = 0;

    /**
     * var boolean $secured
     * @brief Page has to be access with https, currently unused.
     */
    public $secured = 0;

    /**
     * var integer $wf_version
     * @brief Workflow version, currently unused.
     */
    public $wf_version = 1;

    /**
     * var integer $wf_status
     * @brief Workflow status, currently unused.
     */
    public $wf_status;

    /**
     * var integer $wf_cdate
     * @brief Workflow creation date, currently unused.
     */
    public $wf_cdate;

    /**
     * var integer $wf_mdate
     * @brief Workflow modification date, currently unused.
     */
    public $wf_mdate;

    /**
     * var string $wf_owner
     * @brief Page owner.
     */
    public $wf_owner;

    /**
     * var string $wf_editor
     * @brief Page editor group.
     */
    public $wf_editor;

    /**
     * var string $wf_validator
     * @brief Page validation group, currently unused.
     */
    public $wf_validator;

    /**
     * var string $template
     * @brief Page template.
     */
    public $template = '';

    /**
     * var string $theme
     * @brief Page theme.
     */
    public $theme = '';

    /**
     * var boolean $homepage
     * @brief Is page the home page.
     */
    public $homepage;

    /**
     * var array $modules
     * @brief Included modules.
     */
    public $modules = array();

    /**
     * var array $metas
     * @brief Page metas.
     */
    public $metas = array();

    /**
     * var string $metas_
     * @brief Textual version of metas.
     */
    public $metas_ = '';

    /**
     * var array $children
     * @brief Page children.
     */
    public $children = array();

    /**
     * var array $params
     * @brief Page parameters.
     */
    public $params = array();

    /**
     * var array $params
     * @brief Textual version of page parameters.
     */
    public $params_;

    /**
     * var boolean $_libIsInstalled
     * @brief Library installation status.
     */
    public $_libIsInstalled;

    /**
     * var boolean $_libParent
     * @brief Parent module.
     */
    public $_libParent;

    /**
     * var string $object_type
     * @brief Library object type.
     */
    public $object_type = 'Module Library';

    /**
     * var integer $maxmodules
     * @brief Maximum module to be inserted in page.
     */
    public $maxmodules;

    /**
     * var integer $status
     * @brief HTTP status of the page.
     */
    public $status = 200;

    /**
     * Class constructor.
     * @param integer $mode
     * @param integer $id
     * @param array $params
     * @return void
     */
    public function __construct($mode=CAMYKS_MODE_SITE, $id=0, $params=array()) {
        global $camyks;

        /* set up page id */
        if ((int)$id >= 0) {
            $this->id = (int)$id;
        } else {
            $this->id = 0;
        }
        //$this->sitelink = '';
        $this->mode = $mode;
        $this->params_ = $params;

        $this->maxmodules = $camyks->get_confValue('page_maxmodules');
        $this->_libParent = &$camyks->modules['Admin_ContentPage'];
    }

    /* Data manipulation methods */

    /**
     * Return page case of CaMykS mode.
     * @param mixed $page the page to get
     * @return boolean success
     */
    public function get($page=null) {
        if ($this->mode == CAMYKS_MODE_SITE) {
            return $this->site_get($page);
        } else if ($this->mode == CAMYKS_MODE_ADMIN) {
            if ($this->id == 0) {
                return $this->initialise();
            } else {
                return $this->admin_get();
            }
        }
    }

    /**
     * Save object.
     * @return boolean success
     */
    public function save() {
        if ($this->check_data()) {
            if ($this->id > 0)
                return $this->update_toDatabase();
            return $this->create_toDatabase();
        }
    }

    /**
     * Return object in site mode.
     * @param mixed $page the page to get
     * @return boolean success
     */
    public function site_get($page) {
        return $this->get_fromDatabase($page);
    }

    /**
     * Load object as displayed front page.
     * @param mixed $page
     * @return boolean success
     */
    public function load_asFrontPage($page) {
        global $camyks;

        /* check page : prevent from url injection */
        if (preg_match('/[^a-zA-Z0-9_\-]/', $page))
             $page = 0;

        /* try to load page */
        if ($page == '' and $this->get_homeFromDatabase())
            return true;
        if ($this->get_fromDatabase($page))
            return true;

        /* page not found */

        /* log URL */
        $camyks->log('Error404', 'Page not found', '"'. $_SERVER['REQUEST_URI'] .'"');
        $this->status = 404;

        /* check for 404 header sending */
        if ($this->get_configValue('page_404SendHeader') == 1)
            header('HTTP/1.1 404 Not Found');

        /* load failed, use fallbacks */
        switch ($this->get_configValue('page_404FallBack')) {
            case 'home_display':
                $this->get_homeFromDatabase();
                return false;
            case 'home_redirect':
                header('Location:'.$camyks->get_siteHomepageLink());
                die();
            case 'page_display':
                if ($page != $this->get_configValue('page_404ErrorPage')) {
                    $this->site_get($this->get_configValue('page_404ErrorPage'));
                    return false;
                }
                break;
            case 'page_redirect':
                if ($page != $this->get_configValue('page_404ErrorPage')) {
                    header('Location:'.$camyks->get_siteLink($this->get_configValue('page_404ErrorPage')));
                    die();
                }
                break;
            case 'error404_display':
                if (file_exists($this->get_configValue('page_404ErrorFile'))) {
                    @readfile($this->get_configValue('page_404ErrorFile'));
                    die();
                }
                break;
            case 'error404_redirect':
                if (file_exists($this->get_configValue('page_404ErrorFile'))) {
                    header('Location:'.$camyks->get_confValue('url').'/'.$this->get_configValue('page_404ErrorFile'));
                    die();
                }
                break;
        }

        /* error on fallback page, alternate fallback, redirect to home page */
        header('Location:'.$camyks->get_siteHomepageLink());
        return false;
    }

    /**
     * Return object in admin mode.
     * @return boolean success
     */
    public function admin_get() {
        return $this->get_allVersionsFromDatabase();
    }

    /**
     * Check admin user right on this page.
     * @return boolean result
     */
    public function check_rights() {
        global $camyks;
        /* check workflow and status */
        if ($camyks->site_conf['workflow'] == 1 and $this->wf_status != 'edition') {
            return false;
        }

        /* check webmaster */
        if ($camyks->adminUser->webmaster == 1) {
            return true;
        }

        /* check owner value */
        if ($camyks->adminUser->login == $this->wf_owner) {
            return true;
        }

        /* check editor group value */
        if ($camyks->check_sharedData('cp_groups')) {
            $camyks->set_sharedData('cp_groups', array());
        }

        $groups = $camyks->modules['Admin_Group']->get_groups();
        if (isset($groups[$this->wf_editor]))
            return ($groups[$this->wf_editor]->is_userInGroup($camyks->adminUser->login));
        return false;
    }

    /**
     * Check page data.
     * @return boolean result
     */
    private function check_data() {
        global $camyks;
        /* check name */
        $this->name = trim($this->name);

        /* parse invalid chars */
        if (in_array($camyks->get_confValue('friendlyurls'), array('modern', 'modern2')))
            $this->name = preg_replace(array('/^([^a-zA-Z0-9]+)/', '/([^_a-zA-Z0-9\-]+)/', '/([^a-zA-Z0-9]+)$/'), array('', '-', ''), $this->name);
        else
            $this->name = preg_replace(array('/^([^a-zA-Z0-9]+)/', '/([^_a-zA-Z0-9]+)/', '/([^a-zA-Z0-9]+)$/'), array('', '_', ''), $this->name);

        /* check empty name */
        if ($this->name == '') {
            if ($this->id > 0) {
                $this->name = $this->type.$this->id;
            } else {
                $sql = 'select max(id) as m from admin_contentpage';
                if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__))
                    if ($data = $camyks->db_conn->get_queryDataLine())
                        $this->name = $this->type.($data['m']+1);
                    else
                        $this->name = $this->type;
                else
                    $this->name = $this->type;
            }
        } else if (!preg_match ('([_a-zA-Z\-])', $this->name)) {
            /* check if name contain at least one alphabetic char */
            $this->name = $this->type.$this->name;
        }

        /* check if name exists */
        $pages = array();
        $sql = 'select id, name';
        $sql .= ' from admin_contentpage';
        $sql .= ' where name like "'.$this->name.'%"';
        $sql .= ' group by id, name';
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__))
            while($data = $camyks->db_conn->get_queryDataLine())
                $pages[$data['name']] = $data['id'];

        if ((isset ($pages[$this->name]) and $pages[$this->name] != $this->id)) {
            $cnt = 1;
            while (isset($pages[$this->name.$cnt]) and $pages[$this->name.$cnt] != $this->id) {
                $cnt++;
            }
            $this->name .= $cnt;
        }

        /* trim localized data */
        foreach ($this->locales as $l => $trad)
            foreach ($trad as $item => $value)
                $this->locales[$l][$item] = trim($value);

        /* trim global metas */
        foreach ($this->metas as $m => $meta)
            foreach ($meta as $item => $value)
                $this->metas[$m][$item] = trim ($value);

        /* create encoded version of metas */
        $this->encode_metas();

        /* add user name if needed */
        $this->wf_owner = isset($camyks->adminUser->login)?$camyks->adminUser->login:'admin';

        return true;
    }

    /**
     * Initialise object.
     * @return boolean result
     */
    private function initialise() {
        global $camyks;

        /* get header values */
        $this->parent_id = isset($_REQUEST['parent_id'])? (int)$_REQUEST['parent_id'] : 0;
        $this->type = isset($_REQUEST['type'])? $_REQUEST['type'] : 'page';

        /* get parent relative values */
        $this->get_parentRights();
        $this->get_newPosition();

        $this->name = '';
        $this->active = 0;
        $this->secured = 0;
        $this->wf_version = 1;
        $this->wf_state = ($camyks->get_confValue('workflow') == 0 ? 'inline' : 'edition');
        $this->wf_owner = $camyks->adminUser->login;
        $this->wf_cdate = time();
        $this->wf_mdate = time();
        $this->theme = '';
        $this->template = '';
        $this->homepage = 0;
        $this->robotIndex = 1;
        $this->robotFollow = 1;

        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $this->locales[$l] = array('title'=>'', 'shorttitle'=>'', 'description'=>'', 'keywords'=>'');
        }

        return true;
    }

    /*********************** DATABASE DATA I/O ************************/

    /**
     * Load object data from database.
     * @param mixed $page the page to get
     * @return boolean success
     */
    private function get_fromDatabase($page=null) {
        if (isset($page)) {
            if (is_numeric($page))
                return $this->get_objectFromDatabase(' and admin_contentpage.id='.(int)$page);
            else if (is_string($page))
                return $this->get_objectFromDatabase(' and admin_contentpage.name="'.addSlashes($page).'"');
        }
        return $this->get_objectFromDatabase(' and admin_contentpage.id='.(int)$this->id);
    }

    /**
     * Load homepage object data from database.
     * @return boolean success
     */
    public function get_homeFromDatabase() {
        return $this->get_objectFromDatabase(' and admin_contentpage.homepage=1');
    }

    /**
     * Load first object available from database.
     * @return boolean success
     */
    private function get_firstFromDatabase() {
        return $this->get_objectFromDatabase('');
    }

    /**
     * Load object data from database generic method.
     * @param string $query some query modification
     * @return boolean success
     */
    private function get_objectFromDatabase($query='') {
        global $camyks;
        $sql = 'select *';
        $sql .= ' from admin_contentpage, admin_contentpagelocale';
        $sql .= ' where admin_contentpage.type="page"';
        $sql .= ' and admin_contentpage.wf_status="inline"';
        if (isset($_REQUEST['preview']) and $_REQUEST['preview'] == 'forced' and $camyks->modules['Admin_ContentPage']->check_right(0)) {
            /* page preview */
        } else {
            $sql .= ' and admin_contentpage.active=1';
        }
        $sql .= ' '.$query;
        $sql .= ' and admin_contentpage.id=admin_contentpagelocale.id';
        $sql .= ' and admin_contentpage.wf_version=admin_contentpagelocale.wf_version';
        $sql .= ' and admin_contentpagelocale.language="'.$camyks->current_language.'"';
        $sql .= ' limit 1';

        /* execute query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* gather object data */
            if ($data = $camyks->db_conn->get_queryDataLine()) {
                $this->get_fromArray($data);
                $this->get_localeFromArray($data);
                return true;
            }
        }
        return false;
    }

    /**
     * Load all object version from database, set the latest version to the object.
     * @return boolean success
     */
    private function get_allVersionsFromDatabase() {
        global $camyks;
        $isFirst = true;
        $sql = 'select * from admin_contentpage where id='.$this->id.' order by wf_version desc';
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* execute sql query */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                if ($isFirst) {
                    $this->get_fromArray($data);
                    $this->get_localesFromDatabase();
                    $this->versions = array();
                    $isFirst = false;
                } else {
                    $p = new ContentPage(CAMYKS_MODE_ADMIN, $this->id);
                    $p->get_fromArray();
                    $this->versions[] = $p;
                }
                return true;
            }
        }
        return false;
    }

    /**
     * Load object locales from database.
     * @return success
     */
    private function get_localesFromDatabase() {
        global $camyks;
        $this->locales = array();
        $sql = 'select * from admin_contentpagelocale where id='.$this->id.' and wf_version='.$this->wf_version;
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            while ($data = $camyks->db_conn->get_queryDataLine()){
                $this->locales[ $data['language'] ] = $this->get_localesFromArray($data);
            }
        }

        foreach ($camyks->get_confValue('editing_languages') as $l) {
            if (!isset($this->locales[$l]))
                $this->locales[$l] = $this->get_localesFromArray(array('title'=>'', 'shorttitle'=>'', 'keywords'=>'', 'description'=>''));
        }
        return true;
    }

    /**
     * Create new object to the database.
     * @return boolean success
     */
    private function create_toDatabase() {
        global $camyks;
        $sql = 'INSERT INTO `admin_contentpage` (';
        $sql .= ' `parent_id`';
        $sql .= ', `position`';
        $sql .= ', `type`';
        $sql .= ', `name`';
        $sql .= ', `active`';
        $sql .= ', `secured`';
        $sql .= ', `wf_version`';
        $sql .= ', `wf_status`';
        $sql .= ', `wf_cdate`';
        $sql .= ', `wf_mdate`';
        $sql .= ', `wf_owner`';
        $sql .= ', `wf_editor`';
        $sql .= ', `wf_validator`';
        $sql .= ', `template`';
        $sql .= ', `theme`';
        $sql .= ', `homepage`';
        $sql .= ', `metas`';
        for ($i=0; $i< $this->maxmodules; $i++) {
            $sql .= ', `m'.$i.'_name`';
            $sql .= ', `m'.$i.'_content`';
            $sql .= ', `m'.$i.'_theme`';
        }
        $sql .= ', `robotIndex`';
        $sql .= ', `robotFollow`';
        $sql .= ') VALUES (';
        $sql .= ''.(int)$this->parent_id.'';
        $sql .= ', '.(int)$this->position.'';
        $sql .= ', "'.addslashes($this->type).'"';
        $sql .= ', "'.addslashes($this->name).'"';
        $sql .= ', '.(int)$this->active.'';
        $sql .= ', '.(int)$this->secured.'';
        $sql .= ', '.(int)$this->wf_version.'';
        $sql .= ', "'.($camyks->site_conf['workflow'] == 0 ? 'inline' : 'edition').'"';
        $sql .= ', '.time().'';
        $sql .= ', '.time().'';
        $sql .= ', "'.addslashes($this->wf_owner).'"';
        $sql .= ', "'.addslashes($this->wf_editor).'"';
        $sql .= ', "'.addslashes($this->wf_validator).'"';
        $sql .= ', "'.addslashes($this->template).'"';
        $sql .= ', "'.addslashes($this->theme).'"';
        $sql .= ', '.(int)$this->homepage.'';
        $sql .= ', "'.addslashes($this->metas_).'"';
        for ($i=0; $i<$this->maxmodules; $i++) {
            if (isset ($this->modules[$i])) {
                $sql .= ', "'.addSlashes($this->modules[$i]['name']).'"';
                $sql .= ', "'.addSlashes($this->modules[$i]['content']).'"';
                $sql .= ', "'.addSlashes($this->modules[$i]['theme']).'"';
            } else {
                $sql .= ', ""';
                $sql .= ', ""';
                $sql .= ', ""';
            }
        }
        $sql .= ', '.(int)$this->robotIndex.'';
        $sql .= ', '.(int)$this->robotFollow.'';
        $sql .= ')';

        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            $this->id = $camyks->db_conn->get_queryGeneratedId();
            return $this->update_languages();
        }
        return false;
    }

    /**
     * Update object to database.
     * @return boolean success
     */
    private function update_toDatabase() {
        global $camyks;
        $sql = 'update admin_contentpage';
        $sql .= ' set ';
        if ($this->allow_content_edition and $this->allow_rights_edition) {
            $sql .= $this->update_contentQuery();
            $sql .= ', ' .$this->update_rightsQuery();
        } else if ($this->allow_content_edition) {
            $sql .= $this->update_contentQuery();
        } else if ($this->allow_rights_edition) {
            $sql .= $this->update_rightsQuery();
        } else {
            return false;
        }

        $sql .= ', `wf_mdate`='.time();
        $sql .= ' where id='.$this->id;
        $sql .= ' and wf_version='.$this->wf_version;
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            if ($this->allow_content_edition)
                return $this->update_languages();
            return true;
        } else {
            return false;
        }
    }

    /**
     * Build content part for the updating query.
     * @return string the sql query part
     */
    private function update_contentQuery() {
        $sql = ' `name`="'.addSlashes($this->name).'"';
        $sql .= ', `active`='.(int)$this->active;
        $sql .= ', `secured`='.(int)$this->secured;
        $sql .= ', `template`="'.addSlashes($this->template).'"';
        $sql .= ', `theme`="'.addSlashes($this->theme).'"';
        $sql .= ', `homepage`='.(int)$this->homepage;
        $sql .= ', `metas`="'.addslashes($this->metas_).'"';
        for ($i=0; $i< $this->maxmodules; $i++) {
            $sql .= ', `m'.$i.'_name`="'.addSlashes($this->modules[$i]['name']).'"';
            $sql .= ', `m'.$i.'_content`="'.addSlashes($this->modules[$i]['content']).'"';
            $sql .= ', `m'.$i.'_theme`="'.addSlashes($this->modules[$i]['theme']).'"';
        }
        $sql .= ', `robotIndex`='.(int)$this->robotIndex;
        $sql .= ', `robotFollow`='.(int)$this->robotFollow;
        return $sql;
    }

    /**
     * Build right part for the updating query.
     * @return string the sql query part
     */
    private function update_rightsQuery() {
        global $camyks;
        $sql = ' `wf_editor`="'.$this->wf_editor.'"';
        if ($camyks->site_conf['workflow'] == 1) {
            $sql = ' `wf_validator`="'.$this->wf_validator.'"';
        }
        return $sql;
    }

    /**
     * Update object languages.
     * @return boolean success
     */
    private function update_languages() {
        global $camyks;
        /* delete locales lines */
        $this->delete_localesFromDatabase();

        /* insert new locale values */
        $sql = 'INSERT INTO `admin_contentpagelocale` (';
        $sql .= ' `id`';
        $sql .= ', `wf_version`';
        $sql .= ', `language`';
        $sql .= ', `title`';
        $sql .= ', `shorttitle`';
        $sql .= ', `keywords`';
        $sql .= ', `description`';
        $sql .= ') values ';

        foreach ($this->locales as $lang => $l) {
            $sql .= '('.(int)$this->id.', '.(int)$this->wf_version.', "'.addSlashes($lang).'"';
            $sql .= ', "'.$camyks->encode_value($l['title']).'"';
            $sql .= ', "'.$camyks->encode_value($l['shorttitle']).'"';
            $sql .= ', "'.$camyks->encode_value($l['keywords']).'"';
            $sql .= ', "'.$camyks->encode_value($l['description']).'"';
            $sql .= '), ';
        }

        $sql = substr($sql, 0, strlen($sql)-2);
        return $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__);
    }

    /**
     * Delete object from database.
     * @return boolean success
     */
    public function delete_fromDatabase() {
        global $camyks;
        $sql = 'delete from admin_contentpage';
        $sql .= ' where id='.$this->id;
        $sql .= ' and wf_version='.$this->wf_version;
        return $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__);
    }

    /**
     * Delete object languages from database.
     * @return boolean success
     */
    public function delete_localesFromDatabase() {
        global $camyks;
        $sql = 'delete from admin_contentpagelocale';
        $sql .= ' where id='.$this->id;
        $sql .= ' and wf_version='.$this->wf_version;

        return $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__);
    }

    /**
     * Install object table into database, add first page.
     * @return boolean success
     */
    public function install() {
        global $camyks;

        /* create master table */
        $fields = array(
            array('name'=>'parent_id', 'type'=>'int', 'desc1'=>'bigint unsigned', 'desc2'=>'', 'default'=>0),
            array('name'=>'position', 'type'=>'int', 'desc1'=>'int unsigned', 'desc2'=>'', 'default'=>0),
            array('name'=>'type', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>16, 'default'=>''),
            array('name'=>'name', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>128, 'default'=>''),
            array('name'=>'active', 'type'=>'int', 'desc1'=>'tinyint unsigned', 'desc2'=>'', 'default'=>1),
            array('name'=>'secured', 'type'=>'int', 'desc1'=>'tinyint unsigned', 'desc2'=>'', 'default'=>0),
            array('name'=>'wf_version', 'type'=>'int', 'desc1'=>'int unsigned', 'desc2'=>'', 'default'=>0),
            array('name'=>'wf_status', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>16, 'default'=>''),
            array('name'=>'wf_cdate', 'type'=>'int', 'desc1'=>'bigint unsigned', 'desc2'=>'', 'default'=>0),
            array('name'=>'wf_mdate', 'type'=>'int', 'desc1'=>'bigint unsigned', 'desc2'=>'', 'default'=>0),
            array('name'=>'wf_owner', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>32, 'default'=>''),
            array('name'=>'wf_editor', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>32, 'default'=>''),
            array('name'=>'wf_validator', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>32, 'default'=>''),
            array('name'=>'template', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>255, 'default'=>''),
            array('name'=>'theme', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>255, 'default'=>''),
            array('name'=>'homepage', 'type'=>'int', 'desc1'=>'tinyint unsigned', 'desc2'=>'', 'default'=>0),
            array('name'=>'metas', 'type'=>'text', 'desc1'=>'text', 'desc2'=>'', 'default'=>''),
            array('name'=>'robotIndex', 'type'=>'int', 'desc1'=>'tinyint unsigned', 'desc2'=>'', 'default'=>1),
            array('name'=>'robotFollow', 'type'=>'int', 'desc1'=>'tinyint unsigned', 'desc2'=>'', 'default'=>1),
       );
        for ($i=0; $i< $this->maxmodules; $i++) {
            $fields[] = array('name'=>'m'.$i.'_name', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>255, 'default'=>'');
            $fields[] = array('name'=>'m'.$i.'_content', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>255, 'default'=>'');
            $fields[] = array('name'=>'m'.$i.'_theme', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>255, 'default'=>'');
        }

        if (!$camyks->db_conn->create_table('admin_contentpage', $fields, $camyks->get_mysqlencodingvalue(), true, array('id', 'wf_version')))
            return false;

        /* create locale table */
        $fields = array(
            array('name'=>'wf_version', 'type'=>'int', 'desc1'=>'int unsigned', 'desc2'=>'', 'default'=>0),
            array('name'=>'language', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>3, 'default'=>''),
            array('name'=>'title', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>255, 'default'=>''),
            array('name'=>'shorttitle', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>255, 'default'=>''),
            array('name'=>'keywords', 'type'=>'text', 'desc1'=>'text', 'desc2'=>'', 'default'=>''),
            array('name'=>'description', 'type'=>'text', 'desc1'=>'text', 'desc2'=>'', 'default'=>''),
       );

        if (!$camyks->db_conn->create_table('admin_contentpagelocale', $fields, $camyks->get_mysqlencodingvalue(), true, array('id', 'wf_version', 'language')))
            return false;

        /* add first page */
        $this->id = 0;
        $this->parent_id = 0;
        $this->position = 0;
        $this->type = 'page';
        $this->name = 'home';
        $this->active = 1;
        $this->secured = 0;

        $this->wf_version = 1;
        $this->wf_status = 'inline';
        $this->wf_owner = 'admin';
        $this->wf_editor = 'all';
        $this->wf_validator = 'all';

        $this->theme = '';
        $this->template = '';
        $this->homepage = 1;
        $this->metas_ = '';

        $this->robotIndex = 1;
        $this->robotFollow = 1;

        $this->locales = array();
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $this->locales[$l] = array('title'=>'', 'shorttitle'=>'', 'keywords'=>'', 'description'=>'');
        }
        return $this->create_toDatabase();
    }

    /**
     * Check if object is installed in database.
     * @return boolean result
     */
    public function is_installed() {
        global $camyks;

        if (!isset($this->_libIsInstalled)) {
            /* check database presence in plugin manager module */
            if (isset($camyks->modules['Admin_PluginManager']))
                $this->_libIsInstalled = $camyks->modules['Admin_PluginManager']->check_tableExists('admin_contentpage');
            else {
                /* load table list */
                $tl = $camyks->db_conn->get_tableList();

                /* check if main table is in installed table list */
                $this->_libIsInstalled = in_array('admin_contentpage', $tl);
            }
        }
        return $this->_libIsInstalled;
    }

    /**
     * Load parent page rights.
     * @return void
     */
    private function get_parentRights() {
        global $camyks;
        if ($this->parent_id > 0){
            $sql = 'select wf_editor, wf_validator from admin_contentpage where id='.$this->parent_id.' order by wf_version desc';
            if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* execute sql query */
            if ($data = $camyks->db_conn->get_queryDataLine()) {
                $this->wf_editor = $data['wf_editor'];
                $this->wf_validator = $data['wf_validator'];
                return;
            }
            }
        }
        if ($camyks->site_conf['workflow'] == 0) {
            $this->wf_editor = 'all';
            $this->wf_validator = 'all';
        } else {
            $this->wf_editor = 'none';
            $this->wf_validator = 'none';
        }
    }

    /**
     * Return next page position into page tree.
     * @return void
     */
    private function get_newPosition() {
        global $camyks;
        $sql = 'select max(position) as cnt from admin_contentpage where type="page" and parent_id='.$this->parent_id.'';
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* execute sql query */
            if ($data = $camyks->db_conn->get_queryDataLine()) {
                $this->position = $data['cnt']+1;
                return;
            }
        }
        $this->position = 0;
    }

    /*********************** HEADER DATA I/O ************************/

    /**
     * Load object data from header.
     * @return void
     */
    public function get_fromHeader() {
        global $camyks;

        if ($this->allow_content_edition) {
            /* get content values    */
            $this->parent_id = (int)$_REQUEST['parent_id'];
            $this->name = $_REQUEST['name'];
            $this->type = isset($_REQUEST['type'])? $_REQUEST['type'] : 'page';
            $this->active = isset ($_REQUEST['active']) ? (int)$_REQUEST['active'] : 0;
            $this->secured = isset ($_REQUEST['secured']) ? (int)$_REQUEST['secured'] : 0;

            $this->template = $_REQUEST['template'];
            $this->theme = $_REQUEST['theme'];
            $this->homepage = isset ($_REQUEST['homepage']) ? (int)$_REQUEST['homepage'] : 0;
            $this->robotIndex = isset ($_REQUEST['robotIndex']) ? (int)$_REQUEST['robotIndex'] : 0;
            $this->robotFollow = isset ($_REQUEST['robotFollow']) ? (int)$_REQUEST['robotFollow'] : 0;

            /* get metas lines */
            $this->metas = array();
            $meta_count = isset($_REQUEST['meta_count'])?(int)$_REQUEST['meta_count']:0;
            for ($i=0; $i<$meta_count; $i++) {
                if (isset($_REQUEST['meta_name'.$i]) and $_REQUEST['meta_name'.$i]!= '') {
                    $this->metas[] = array(
                        $_REQUEST['meta_name'.$i],
                        isset($_REQUEST['meta_content'.$i])?$_REQUEST['meta_content'.$i]:'',
                        isset($_REQUEST['meta_language'.$i])?$_REQUEST['meta_language'.$i]:'',
                        isset($_REQUEST['meta_method'.$i])?$_REQUEST['meta_method'.$i]:'',
                    );
                }
            }

            /* get modules */
            for ($i=0; $i< $this->maxmodules; $i++) {
                $m = array();
                $m['name'] = $_REQUEST['m'.$i.'_name'];
                $m['content'] = $_REQUEST['m'.$i.'_content'];
                $m['theme'] = isset($_REQUEST['m'.$i.'_theme'])?$_REQUEST['m'.$i.'_theme']:'';
                $this->modules[$i] = $m;
            }

            /* get translations */
            $this->locales = array();
            foreach ($camyks->site_conf['editing_languages'] as $l) {
                $this->locales[$l] = array();
                $this->locales[$l]['title'] = $_REQUEST['title_'.$l];
                $this->locales[$l]['shorttitle'] = $_REQUEST['shorttitle_'.$l];
                $this->locales[$l]['description'] = $_REQUEST['description_'.$l];
                $this->locales[$l]['keywords'] = $_REQUEST['keywords_'.$l];
            }
        }

        /* get rights values */
        if ($this->allow_rights_edition) {
            $this->wf_editor = $_REQUEST['wf_editor'];
            if ($camyks->site_conf['workflow'] == 1) {
                $this->wf_validator = $_REQUEST['wf_validator'];
            }
        }
    }

    /**
     * Update page location.
     * @param integer $newParentId
     * @return boolean success
     */
    public function update_move($newParentId) {
        global $camyks;

        $this->parent_id = $newParentId;
        $this->get_newPosition();

        /* build update sql query */
        $sql = 'update admin_contentpage';
        $sql .= ' set position='.$this->position;
        $sql .= ', parent_id='.$this->parent_id;
        $sql .= ' where id='.$this->id;
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }

    /**
     * Update page position up.
     * @return boolean success
     */
    public function update_moveUp() {
        return $this->update_movePosition(-1);
    }

    /**
     * Update page position down.
     * @return boolean success
     */
    public function update_moveDown() {
        return $this->update_movePosition(1);
    }

    /**
     * Update page position with differential value.
     * @param integer $pos
     * @return boolean success
     */
    public function update_movePosition($pos) {
        global $camyks;

        /* get all parent pages */
        $sql = 'select id, position';
        $sql .= ' from admin_contentpage';
        $sql .= ' where parent_id='.$this->parent_id;
        $sql .= ' and type="page"';
        $sql .= ' order by position';
        if (!($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)))
            return false;

        $pages = array();
        $position = -1;
        while ($data = $camyks->db_conn->get_queryDataLine()) {
            if ($data['id'] == $this->id)
                $position = count($pages);
            $pages[] = $data;
        }

        /* check new position value */
        if ($position == -1 or ($position+$pos<0) or $position+$pos>=count($pages))
            return false;

        /* update position */
        $temp = $pages[$position];
        $pages[$position] = $pages[$position+$pos];
        $pages[$position+$pos] = $temp;

        /* update all pages which the position is not correct */
        foreach ($pages as $index => $page) {
            if ($index != $page['position']) {
                $sql = 'update admin_contentpage';
                $sql .= ' set position='.$index;
                $sql .= ' where id='.$page['id'];
            if (!($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)))
                return false;
            }
        }
        return true;
    }

    /*********************** OTHER DATA I/O ************************/

    /**
     * Load object data from array.
     * @param array $data
     * @return void
     */
    private function get_fromArray($data) {
        /* engine values */
        $this->id = $data['id'];
        $this->parent_id = $data['parent_id'];
        $this->position = $data['position'];
        $this->type = $data['type'];
        $this->name = $data['name'];
        $this->active = $data['active'];
        $this->secured = $data['secured'];
        /* workflow values */
        $this->wf_version = $data['wf_version'];
        $this->wf_status = $data['wf_status'];
        $this->wf_cdate = $data['wf_cdate'];
        $this->wf_mdate = $data['wf_mdate'];
        $this->wf_owner = $data['wf_owner'];
        $this->wf_editor = $data['wf_editor'];
        $this->wf_validator = $data['wf_validator'];
        /* content values */
        $this->template = $data['template'];
        $this->theme = $data['theme'];
        $this->homepage = $data['homepage'];
        $this->metas_ = stripslashes($data['metas']);
        $this->decode_metas();
        for ($i=0; $i<$this->maxmodules; $i++) {
            $m = array();
            $m['name'] = $data['m'.$i.'_name'];
            $m['content'] = $data['m'.$i.'_content'];
            $m['theme'] = $data['m'.$i.'_theme'];
            $this->modules[$i] = $m;
        }
        $this->robotIndex = $data['robotIndex'];
        $this->robotFollow = $data['robotFollow'];
    }

    /**
     * Load object locale data from an array.
     * @param array $data
     * @return void
     */
    private function get_localeFromArray($data) {
        global $camyks;
        $this->title = $camyks->decode_value($data['title']);
        $this->shorttitle = $camyks->decode_value($data['shorttitle']);
        $this->keywords = $camyks->decode_value($data['keywords']);
        $this->description = $camyks->decode_value($data['description']);
    }

    /**
     * Load object locales from an array.
     * @param array $data
     * @return array
     */
    private function get_localesFromArray($data) {
        global $camyks;
        $a = array();
        $a['title'] = $camyks->decode_value($data['title']);
        $a['shorttitle'] = $camyks->decode_value($data['shorttitle']);
        $a['keywords'] = $camyks->decode_value($data['keywords']);
        $a['description'] = $camyks->decode_value($data['description']);
        return $a;
    }

    /**
     * Encode metas values.
     * @return void
     */
    private function encode_metas() {
        $list = array();
        foreach ($this->metas as $m) {
            $list[] = implode('::', $m);
        }
        $this->metas_ = implode('"', $list);
    }

    /**
     * Decode meta values.
     * @return void
     */
    private function decode_metas() {
        if ($this->metas_ != '') {
            $metas = explode('"', $this->metas_);
            foreach ($metas as $meta) {
                $meta = explode('::', $meta);
                if (count($meta) == 4)
                    $this->metas[$meta[0]] = array(
                        'name'      => $meta[0],
                        'content'   => $meta[1],
                        'language'  => $meta[2],
                        'method'    => $meta[3]
                   );
            }
        } else {
            $this->metas = array();
        }
    }

    /**
     * Set up default admin page parameters.
     * @param string $m the module to be administrate
     * @return void
     */
    public function set_adminData($m) {
        global $camyks;
        $this->template = $camyks->templates['AdminPage'];
        $this->modules = array();
        $this->modules[0] = array('name' => $m);
        $this->modules[1] = array('name' => 'Tool_InfoBar');
    }

    /********************** INIT ************************************/

    /**
     * Initialise object in site mode.
     * @return void
     */
    public function init_site() {
        global $camyks, $languages;

        /* parse params */
        if (strpos($this->params_, '-')==0 or strpos($this->params_, '/')==0) {
            $this->params_ = substr($this->params_, 1);
        }
        $this->params = data_decode_properties($this->params_, '-');

        /* add robot rules */
        $camyks->HTMLPage->set_robotInformations($this->robotIndex, $this->robotFollow);

        /* add metas */
        foreach ($this->metas as $meta) {
            if ($meta['method'] != 'hidden' and ($meta['language'] == '' or $meta['language'] == $camyks->current_language))
                $camyks->HTMLPage->add_meta($meta['name'], $meta['content'], $meta['method']);
        }

        if ($this->get_configValue('site_ogmeta') == 1) {
            $camyks->HTMLPage->add_meta('og:locale', $camyks->current_language, 'property');
            $camyks->HTMLPage->add_meta('og:site_name', $camyks->get_confValue('site_title'), 'property');
            $camyks->HTMLPage->add_meta('og:type', 'website', 'property');
            $camyks->HTMLPage->add_meta('og:title', $this->get_longTitleDisplay('html'), 'property');
            $camyks->HTMLPage->add_meta('og:url', $camyks->get_rootBaseURL('absolute_long').$camyks->get_siteCurrentLink(), 'property');
            if (trim($this->description) != '')
                $camyks->HTMLPage->add_meta('og:description', string_text2HTML($this->description), 'property');
            //$camyks->HTMLPage->add_meta('og:image', '', 'property');
        }

        if ($this->get_configValue('site_hreflang') == 1 and count($camyks->get_confValue('site_languages'))) {
            foreach ($camyks->get_confValue('site_languages') as $l)
                if ($l != $camyks->current_language)
                    $camyks->HTMLPage->add_link('alternate', $camyks->get_confValue('url').'/'.$this->get_siteLink($this->params, $l), array('hreflang'=>$languages[$l]['extend']));
        }

        /* init template */
        if ($this->template == '') {
            $this->template = $camyks->get_confValue('site_default_template');
        } else if (!isset($camyks->templates[$this->template])) {
            $camyks->log_event('Page Error', $this, 'Template not found :'.$this->template);
            $this->template = $camyks->get_confValue('site_default_template');
        }
        $this->template = &$camyks->templates[$this->template];
        $this->template->initialise();

        /* init theme - check for default theme */
        if ($this->theme == ''){
            $this->theme = $camyks->get_confValue('site_default_theme');
        } else if (! isset ($camyks->themes[$this->theme])) {
            $camyks->log_event('Page Error', $this, 'Theme not found :'.$this->theme);
            $this->theme = $camyks->get_confValue('site_default_theme');
        }
        $this->theme = &$camyks->themes[$this->theme];
        $this->theme->initialise();

        /* init modules */
        $m = array();
        $i = 0;
        for ($i=0; $i< $this->template->modules; $i++) {
            $mod_name = $this->modules[$i]['name'];
            /* module & content */
            if ($mod_name == '') {
                /* no active module */
                $m[$i] = new Module ('Empty', 'camyks');
            } else if (isset($camyks->modules[$mod_name])) {
                /* active module */
                $m[$i] = $camyks->modules[$mod_name];
            } else {
                /* log : module not found */
                $camyks->log_event('Page Error', $this, 'Module not found :'.$mod_name);
                $m[$i] = new Module('Empty', 'camyks');
            }
            /* theme */
            if ($this->modules[$i]['theme'] != '') {
                $m[$i]->set_theme($this->modules[$i]['theme']);
            } else {
                $m[$i]->set_theme($this->theme->name);
            }

            /* init module object */
            if ($camyks->benchMode !== false) $camyks->benchMode->start('Initialise module '.$i);
            $m[$i]->init_site($this->modules[$i]['content'], $this->params, $i);
        }
        $this->modules = $m;
    }

    /**
     * Initialise object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;
        $this->mode = CAMYKS_MODE_ADMIN;
        $this->template->initialise();
        foreach ($this->modules as $i=>$m) {
            $mod_name = $m['name'];
            if (isset($camyks->modules[$mod_name])) {
                $this->modules[$i] = &$camyks->modules[$mod_name];
            } else {
                $this->modules[$i] = new Module('Empty', 'camyks');
            }
        }
        foreach ($this->modules as $i=>$m) {
            $this->modules[$i]->set_theme($camyks->get_confValue('admin_default_theme'));
            $this->modules[$i]->init_admin();
        }
    }

    /********************** TOOL METHODS ****************************/

    /**
     * Check if page has children.
     * @return boolean result
     */
    public function has_children() {
        global $camyks;

        /* build sql query */
        $sql = 'select id';
        $sql .= ' from admin_contentpage';
        $sql .= ' where parent_id='.$this->id;

        /* execute query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__))
            return $camyks->db_conn->get_queryDataLine();
        return false;
    }

    /**
     * Return page object site link.
     * @param array $params
     * @param string $lg
     * @return string
     */
    public function get_siteLink($params=array(), $lg='') {
        global $camyks;

        /* add name */
        $link = $this->name;

        /* add params */
        if (count($params) > 0) {
            if ($camyks->get_confValue('friendlyurls') == 'modern' or $camyks->get_confValue('friendlyurls') == 'modern2')
                $link .= '/'.urlencode(data_encode_properties($params, '-', true));
            else {
                $link .= '-'.data_encode_properties($params, '-');

                /* encode params */
                $link = urlencode($link);
            }
        }

        /* add language */
        if ($lg != '' or count($camyks->get_confValue('site_languages'))>1) {
            if (!in_array($lg, $camyks->get_confValue('site_languages')))
                $lg = $camyks->current_language;
        }

        if ($lg != '') {
            if ($camyks->get_confValue('friendlyurls') == 'modern2')
                $link = $lg.'/'.$link;
            else
                $link .= '.'.$lg;
        }

        /* add extension */
        switch ($this->type) {
            case 'page':
                $link .= '.htm';
                break;
        }

        return $camyks->get_rootBaseURL().$link;
    }

    /********************** DISPLAY *********************************/

    /**
     * Display object in site mode.
     * @return void
     */
    public function display() {
        $this->template->display();
    }

    /**
     * Display module.
     * @param int $index
     * @return void
     */
    public function display_module($index) {
        global $camyks;

        switch ($this->mode) {
            case CAMYKS_MODE_ADMIN :
                $this->modules[$index]->display_admin();
                break;
            case CAMYKS_MODE_SITE :
                if ($camyks->benchMode !== false) $camyks->benchMode->start('Display module '.$index);
                    $this->modules[$index]->display_site($index);
                break;
        }
    }

    /******************** ELEMENTS REQUEST METHODS **********/

    /**
     * Build admin mode page tree.
     * @return array
     */
    public function get_adminPagesTree() {
        global $camyks;

        /* init values */
        $pages = array();
        /* build sql query */
        $sql = 'select id, active, type, parent_id, position, name, homepage, wf_owner, wf_editor, robotIndex, robotFollow';
        $sql .= ' from admin_contentpage';
        $sql .= ' where type="page"';
        $sql .= ' order by parent_id, position';
        /* execute query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {

            $page = new ContentPage(0, 0);
            $page->name = '';
            //$page->sitelink = '';
            $pages[0] = $page;

            /* get data from database */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                $page = new ContentPage(0, $data['id']);
                $page->name = $data['name'];
                $page->active = $data['active'];
                $page->type = $data['type'];
                $page->parent_id = $data['parent_id'];
                $page->homepage = $data['homepage'];
                $page->position = $data['position'];
                $page->wf_owner = $data['wf_owner'];
                $page->wf_editor = $data['wf_editor'];
                $page->wf_status = 'edition';
                $page->robotIndex = $data['robotIndex'];
                $page->robotFollow = $data['robotFollow'];
                $pages[$data['id']] = $page;
            }

            foreach ($pages as $p) {
                if (isset($pages[$p->parent_id]))
                    $pages[$p->parent_id]->children[] = $p->id;
            }

            /* return values */
            return $pages;
        }
        return array();
    }

    /**
     * Build complete page tree.
     * @param string $lg
     * @param string $where
     * @return array
     */
    public function get_pagesList($lg=null, $where='') {
        global $camyks;

        if (!isset($lg)) {
            $lg = $camyks->current_language;
        }

        /* init values */
        $pages = array();

        /* build sql query */
        $sql = 'select *';
        $sql .= ' from admin_contentpage, admin_contentpagelocale';
        $sql .= ' where admin_contentpage.type="page"';
        $sql .= ' and admin_contentpagelocale.id=admin_contentpage.id';
        $sql .= ' and admin_contentpagelocale.wf_version=admin_contentpage.wf_version';
        $sql .= ' and admin_contentpagelocale.language="'.$lg.'"';
        if ($where != '') {
            $sql .= ' and '.$where;
        }
        $sql .= ' order by parent_id, position;';

        /* execute query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)){

            $page = new ContentPage(0, 0);
            $page->name = '';
            //$page->sitelink = '';
            $pages[0] = $page;

            /* get data from database */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                $page = new ContentPage(0, $data['id']);
                $page->get_fromArray($data);
                $page->get_localeFromArray($data);
                $pages[$data['id']] = $page;
            }

            foreach ($pages as $p) {
                if (isset($pages[$p->parent_id])) {
                    $pages[$p->parent_id]->children[] = $p->id;
            }
            $pages[$p->name] = &$pages[$p->id];

            /* check if home page */
            if ($p->homepage == 1)
                $this->_libParent->set_siteHomePage($p->id);
            }
            /* return values */
            return $pages;
        }
        return array();
    }

    /**
     * Return models list.
     * @param $where
     * @return array
     */
    public function get_modelsList($where='') {
        global $camyks;

        /* init values */
        $models = array();

        /* build sql query */
        $sql = 'select *';
        $sql .= ' from admin_contentpage';
        $sql .= ' WHERE admin_contentpage.type="model"';
        if ($where != '') {
            $sql .= ' AND '.$where;
        }
        $sql .= ' order by id;';

        /* execute query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)){
            /* get data from database */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                $page = new ContentPage(0, $data['id']);
                $page->get_fromArray($data);
                $models[$data['id']] = $page;
            }
        }

        /* return values */
        return $models;
    }

    /**
     * Return current page long title display.
     * @param string $encoding
     * @return string
     */
    public function get_longTitleDisplay($encoding='') {
        $t = ($this->title != '' ? $this->title : ($this->shorttitle != '' ? $this->shorttitle : $this->name));
        switch ($encoding) {
            case 'html':
                return string_text2html($t);
        }
        return $t;
    }

    /**
     * Return current page short title display.
     * @param string $encoding
     * @return string
     */
    public function get_shortTitleDisplay($encoding='') {
        $t = ($this->shorttitle != '' ? $this->shorttitle : ($this->title != '' ? $this->title : $this->name));
        switch ($encoding) {
            case 'html':
                return string_text2html($t);
        }
        return $t;
    }

    /**
     * Return current page default title display.
     * @param string $encoding
     * @return string
     */
    public function get_titleDisplay($encoding='') {
        return $this->get_longTitleDisplay($encoding);
    }

    /**
     * Return parent configuration object value.
     * @param string $param
     * @param mixed $default
     * @return mixed
     */
    public function get_configValue($param='', $default=false) {
        return $this->_libParent->get_configValue($param, $default);
    }

    /* Update methods */

    /**
     * Execute version 1.1 update.
     * @return boolean success
     */
    public function update_toVersion1_1() {
        global $camyks;

        $sql = 'alter table `admin_contentpage` add column robotIndex tinyint unsigned default 1;';
        if (!$camyks->db_conn->execute_query($sql))
            return false;

        $sql = 'alter table `admin_contentpage` add column robotFollow tinyint unsigned default 1;';
        return ($camyks->db_conn->execute_query($sql));
    }

    /******************** STATIC METHODS ********************/

    /**
     * Update a single module content id for a page.
     * @param int $pid the page id
     * @param int $idx the module index
     * @param int $cid the module content id
     * @return boolean success
     */
    public function static_update_singleModuleContent($pid, $idx, $cid) {
        global $camyks;

        $sql = 'update `admin_contentpage`';
        $sql .= ' set `m'.$idx.'_content`='.$cid;
        $sql .= ' where id='.$pid;
        return $camyks->db_conn->execute_query($sql);
    }

    /* Deprecated methods */

    /**
     * Return all pages from database.
     * @return array
     * @deprecated
     */
    public function static_get_sitePages() {
        global $camyks;

        /* init values */
        $pages = array();
        /* build sql query */
        $sql = 'select id, parent_id, position, name, homepage, wf_owner, wf_editor';
        $sql .= ' from admin_contentpage';
        $sql .= ' order by parent_id, position';
        /* execute query */
        $camyks->db_conn->execute_query($sql);
        /* get data from database */
        while ($data = $camyks->db_conn->get_queryDataLine()) {
            $page = new ContentPage(0, $data['id']);
            $page->name = $data['name'];
            $page->parent_id = $data['parent_id'];
            $page->homepage = $data['homepage'];
            $page->position = $data['position'];
            $page->wf_owner = $data['wf_owner'];
            $page->wf_editor = $data['wf_editor'];
            $page->wf_status = 'edition';
            $pages[$data['id']] = $page;
        }
        /* return values */
        return $pages;
    }

    /**
     * Return  all children pages from a given page
     * @param int $page the page id
     * @param int $level the level
     * @return array
     * @deprecated
     */
    public function static_get_childrenPages($page=0, $level=1) {
        global $camyks;
        /* init values */
        $pages = array();
        /* build sql query */
        $sql = 'SELECT admin_contentpage.id';
        $sql .= ', admin_contentpage.name';
        $sql .= ', admin_contentpage.parent_id';
        $sql .= ', admin_contentpagelocale.title as title';
        $sql .= ' FROM admin_contentpage, admin_contentpagelocale';
        $sql .= ' WHERE admin_contentpage.parent_id = '.$page;
        $sql .= ' AND admin_contentpagelocale.id=admin_contentpage.id';
        $sql .= ' AND admin_contentpagelocale.wf_version=admin_contentpage.wf_version';
        $sql .= ' AND admin_contentpagelocale.language="'.$camyks->current_language.'";';
        /* execute query */
        $camyks->db_conn->execute_query($sql);
        /* get data from database */
        while ($data = $camyks->db_conn->get_queryDataLine()) {
            $page = new ContentPage(0, $data['id']);
            $page->name = $data['name'];
            $page->title = $camyks->decode_value($data['title']);
            $pages[] = $page;
        }
        /* return value */
        return $pages;
    }

    /**
     * Return children pages from current page.
     * @param int $level
     * @return array
     * @deprecated
     */
    public function static_get_relativeChildrenPages($level) {
        global $camyks;
        return ContentPage::static_get_childrenPages($camyks->content_page->id, $level);
    }

    /**
     * Return pages from a given list.
     * @param array $list
     * @param string $lg
     * @return void
     * @deprecated
     */
    public function static_get_listedPages($list, $lg='') {
        global $camyks;
        /* check if list has at least one item */
        if ($list == '')
            return array();
        /* check language */
        if ($lg == '')
            $lg = $camyks->current_language;

        /* init values */
        $pages = array();

        /* build sql query */
        $sql = 'SELECT admin_contentpage.id';
        $sql .= ', admin_contentpage.name';
        $sql .= ', admin_contentpagelocale.title as title';
        $sql .= ', admin_contentpagelocale.shorttitle as shorttitle';
        $sql .= ' FROM admin_contentpage, admin_contentpagelocale';
        $sql .= ' WHERE admin_contentpage.id IN ('.$list.')';
        $sql .= ' AND admin_contentpagelocale.id=admin_contentpage.id';
        $sql .= ' AND admin_contentpagelocale.wf_version=admin_contentpage.wf_version';
        $sql .= ' AND admin_contentpagelocale.language="'.$lg.'";';

        /* execute query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* get data from database */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                $page = new ContentPage(0, $data['id']);
                $page->name = $data['name'];
                $page->title = $camyks->decode_value($data['title']);
                $page->shorttitle = $camyks->decode_value($data['shorttitle']);
                $pages[$page->id] = $page;
            }
        }
        /* return values */
        return $pages;
    }

    /**
     * Return page basic info (id, title(current_language)) from name.
     * @param string $name
     * @return ContentPage Object
     * @deprecated
     */
    public function static_get_pageBasicInfoByName($name='') {
        global $camyks;
        /* build sql query */
        $sql = 'SELECT admin_contentpage.id';
        $sql .= ', admin_contentpage.name';
        $sql .= ', admin_contentpagelocale.title as title';
        $sql .= ' FROM admin_contentpage, admin_contentpagelocale';
        $sql .= ' WHERE admin_contentpage.name="'.$name.'"';
        $sql .= ' AND admin_contentpagelocale.id=admin_contentpage.id';
        $sql .= ' AND admin_contentpagelocale.wf_version=admin_contentpage.wf_version';
        $sql .= ' AND admin_contentpagelocale.language="'.$camyks->current_language.'";';
        /* execute sql query */
        if ($req = $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* get pages from database */
            if ($data = $camyks->db_conn->get_queryDataLine()) {
                $page = new ContentPage(0, $data['id']);
                $page->name = $data['name'];
                $page->title = $camyks->decode_value($data['title']);
                return $page;
            }
        }
        return new ContentPage(0, 0);
    }

    /**
     * Return pages basic info (id, title(current_language)) from names.
     * @param array $names
     * @return array
     * @deprecated
     */
    public function static_get_pagesBasicInfoByNames($names=array()) {
        global $camyks;
        $pages = array();

        if (count ($names) == 0) {
            return array();
        }

        /* build sql query */
        $sql = 'SELECT admin_contentpage.id';
        $sql .= ', admin_contentpage.name';
        $sql .= ', admin_contentpagelocale.title as title';
        $sql .= ' FROM admin_contentpage, admin_contentpagelocale';
        $sql .= ' WHERE admin_contentpage.name in ("'.implode('","', $names).'")';
        $sql .= ' AND admin_contentpagelocale.id=admin_contentpage.id';
        $sql .= ' AND admin_contentpagelocale.wf_version=admin_contentpage.wf_version';
        $sql .= ' AND admin_contentpagelocale.language="'.$camyks->current_language.'";';
        /* execute sql query */
        if ($req = $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* get pages from database */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                if (!isset ($pages[$data['name']])) {
                    $page = new ContentPage(0, $data['id']);
                    $page->name = $data['name'];
                    $page->title = $camyks->decode_value($data['title']);
                    $pages[$data['name']] = $page;
                }
            }
        }
        return $pages;
    }

    /**
     * Return homepage basic info (id, title(current_language) and name).
     * @return ContentPage Object
     * @deprecated
     */
    public function static_get_homepageBasicInfo() {
        global $camyks;
        $pages = array();
        /* build sql query */
        $sql = 'SELECT admin_contentpage.id';
        $sql .= ', admin_contentpage.name';
        $sql .= ', admin_contentpagelocale.title as title';
        $sql .= ' FROM admin_contentpage, admin_contentpagelocale';
        $sql .= ' WHERE admin_contentpage.isHomepage=1';
        $sql .= ' AND admin_contentpagelocale.id=admin_contentpage.id';
        $sql .= ' AND admin_contentpagelocale.wf_version=admin_contentpage.wf_version';
        $sql .= ' AND admin_contentpagelocale.language="'.$camyks->current_language.'")';
        $sql .= ' ORDER by admin_contentpage.id;';

        /* execute sql query */
        if ($req = $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* get pages from database */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                $page = new ContentPage(0, $data['id']);
                $page->name = $data['name'];
                $page->title = $camyks->decode_value($data['title']);
                return $page;
            }
        }
    }
}
?>
