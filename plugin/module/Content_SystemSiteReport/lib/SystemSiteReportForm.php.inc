<?php
/**
 * @brief Content_SystemSiteReport module, content form library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Apr 2007
 * @date Modification: Feb 2022
 * @copyright 2007 - 2022 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * SystemSiteReportForm class.
 */
final class SystemSiteReportForm {
    /**
     * var integer $id
     * @brief Object id.
     */
    public $id = 0;

    /**
     * @brief Object data.
     */
    public $name = '';
    public $layout_name;
    public $type_list;
    public $title_mode;
    public $title_texts;
    public $title_imgs;
    public $descriptions;
    public $title_texts_; /* encoded version of title_texts; */
    public $title_imgs_; /* encoded version of title_imgs; */
    public $file_allowed;

    /**
     * @brief Object description to be similar to a ModuleLibrary object.
     */
    public $_libDesc;
    public $_libParent;
    public $_libIsInstalled;

    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        $this->id = $id;
        $this->_libDesc = 'Module:'.$module->name.' Lib:SystemSiteReportForm';
        $this->_libParent = $module;
        $this->_libIsInstalled = null;
    }

    /* Data management methods */

    /**
     * Load object.
     * @return boolean success
     */
    public function get() {
        if ($this->id == 0) {
            $this->initialise();
        } else {
            $this->get_fromDatabase();
        }
    }

    /**
     * Initialise object.
     * @return boolean success
     */
    public function initialise() {
        $this->type_list = array();
        return true;
    }

    /*
     * Load object from database.
     * @return boolean success
     */
    public function get_fromDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = 'select *';
        $sql .= ' from content_systemsitereportform';
        $sql .= ' where id='.$this->id;

        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* Load data from database */
            if ($data = $camyks->db_conn->get_queryDataLine()) {
                $this->get_fromArray ($data);
                return true;
            }
        }
        return false;
    }

    /**
     * Save object to database.
     * @return boolean success
     */
    public function save_toDatabase() {
        /* Check data validity */
        if ($this->check_data()) {
            if ($this->id == 0 and $this->create_toDatabase() or $this->update_toDatabase()) {
                return $this->save_HTMLFiles();
            }
        }
        return false;
    }

    /**
     * Create object in database.
     * @return boolean success
     */
    private function create_toDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = 'insert into `content_systemsitereportform` (';
        $sql .= ' `name`';
        $sql .= ', `type_list`';
        $sql .= ', `layout_name`';
        $sql .= ', `title_mode`';
        $sql .= ', `title_texts`';
        $sql .= ', `title_imgs`';
        $sql .= ', `file_allowed`';
        $sql .= ') VALUES (';
        $sql .= ' "'.$this->name.'"';
        $sql .= ', "'.$this->type_list.'"';
        $sql .= ', "'.$this->layout_name.'"';
        $sql .= ', '.$this->title_mode.'';
        $sql .= ', "'.addslashes($this->title_texts_).'"';
        $sql .= ', "'.addslashes($this->title_imgs_).'"';
        $sql .= ', '.$this->file_allowed.'';
        $sql .= ');';

        /* Return result of sql query execution */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            $this->id = $camyks->db_conn->get_queryGeneratedId();
            return true;
        }
        return false;
    }

    /**
     * Update object in database
     * @return boolean success
     */
    private function update_toDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = 'update `content_systemsitereportform`';
        $sql .= ' set `name`="'.$this->name.'"';
        $sql .= ', `type_list`="'.$this->type_list.'"';
        $sql .= ', `layout_name`="'.$this->layout_name.'"';
        $sql .= ', `title_mode`='.$this->title_mode.'';
        $sql .= ', `title_texts`="'.addslashes($this->title_texts_).'"';
        $sql .= ', `title_imgs`="'.addslashes($this->title_imgs_).'"';
        $sql .= ', `file_allowed`='.$this->file_allowed.'';
        $sql .= ' where id='.$this->id;

        /* Return result of sql query */
        return $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__);
    }

    /**
     * Delete object from database.
     * @return boolean success
     */
    public function delete_fromDatabase() {
        global $camyks;

        /* Build sql query */
        $sql = 'delete from content_systemsitereportform where id='.$this->id;

        /* Return result of execute sql query */
        return $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__);
    }

    /**
     * Install database.
     * @return boolean success
     */
    public function install() {
        global $camyks;

        /* Create table */
        $fields = array(
            array('name'=>'name', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>16, 'default'=>''),
            array('name'=>'type_list', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>255, 'default'=>''),
            array('name'=>'layout_name', 'type'=>'text', 'desc1'=>'varchar', 'desc2'=>64, 'default'=>''),
            array('name'=>'title_mode', 'type'=>'int', 'desc1'=>'tinyint', 'desc2'=>'', 'default'=>0),
            array('name'=>'title_texts', 'type'=>'text', 'desc1'=>'text', 'desc2'=>'', 'default'=>''),
            array('name'=>'title_imgs', 'type'=>'text', 'desc1'=>'text', 'desc2'=>'', 'default'=>''),
            array('name'=>'file_allowed', 'type'=>'int', 'desc1'=>'tinyint unsigned', 'desc2'=>'', 'default'=>0),
        );

        if ($camyks->db_conn->create_table('content_systemsitereportform', $fields, $camyks->get_mysqlencodingvalue())) {
            /* Create folder */
            if (folder_createPath($this->_libParent->plugin_var_path.'/img', '', 0771) and folder_createPath($this->_libParent->plugin_var_path.'/html', '', 0771)) {
                return true;
            } else {
                $camyks->log_pluginerror($this->_libParent, 'Installation Failed', 'Could not create "var" folder in site folder');
            }
        }
        return false;
    }

    /**
     * Uninstall database.
     * @return boolean success
     */
    public function uninstall() {
        global $camyks;

        /* Build sql query */
        $sql = 'drop table content_systemsitereportform';

        /* Return result of sql query execution */
        return $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__);
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        global $camyks;

        if ($this->_libIsInstalled === null) {
            /* Check database presence in plugin manager module */
            if (isset($camyks->modules['Admin_PluginManager']))
                $this->_libIsInstalled = $camyks->modules['Admin_PluginManager']->check_tableExists('content_systemsitereportform');
            else {
                /* Load table list */
                $tl = $camyks->db_conn->get_tableList();

                /* Check if main table is in installed table list */
                $this->_libIsInstalled = in_array('content_systemsitereportform', $tl);
            }
        }
        return $this->_libIsInstalled;
    }

    /*********************** HTML ****************************/

    /**
     * Save HTML contents.
     * @return boolean success
     */
    public function save_HTMLFiles() {
        $fcontent = file_getPHPFileHeader('htmlcontent file', '1.0');
        $fcontent .= file_getPHPFileFooter();

        foreach ($this->descriptions as $c=>$v) {
            if (get_magic_quotes_gpc()) {
                $v = stripslashes($v);
            }
            $this->filepath = $this->_libParent->plugin_var_path.'/html/file'. $this->id.'_'.$c.'.html.inc';
            if (! file_write($this->filepath, $fcontent."\n".$v)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Load HTML contents.
     * @return void
     */
    public function get_HTMLFiles() {
        global $camyks;
        $this->descriptions = array();
        foreach ($camyks->site_conf['editing_languages'] as $l) {
            $this->descriptions[$l] = $this->_libParent->get_varFilePath('html/file'.$this->id.'_'.$l.'.html.inc');
        }
    }

    /**
     * Load current language content
     * @return void
     */
    public function get_HTMLContent() {
        global $camyks;
        $this->description = 'html/file'. $this->id.'_'.$camyks->current_language.'.html.inc';
        $this->_libParent->load_varFile ($this->description);
    }


    /**
     * Load object values from array
     * @return void
     */
    public function get_fromArray($data) {
        global $camyks;
        $this->id = $data['id'];
        $this->name = $data['name'];
        $this->type_list = $data['type_list'];
        $this->layout_name = $data['layout_name'];
        $this->title_mode = $data['title_mode'];
        $this->title_texts_ = stripslashes($data['title_texts']);
        $this->title_imgs_ = stripslashes($data['title_imgs']);
        $this->title_texts = data_decode_properties($this->title_texts_);
        $this->title_imgs = data_decode_properties($this->title_imgs_);
        $this->file_allowed = $data['file_allowed'];
        $this->type_list = explode (',', $this->type_list);
    }

    /**
     * Load object values from header.
     * @return void
     */
    public function get_fromHeader() {
        global $camyks;
        $this->name = isset ($_REQUEST['name']) ? $_REQUEST['name'] : '';

        $type_count = isset ($_REQUEST['type_count']) ? $_REQUEST['type_count'] : 0;
        $this->type_list = array();
        for ($i=0; $i< $type_count; $i++) {
            if (isset ($_REQUEST['type_'.$i]) and $_REQUEST['type_'.$i]>0) {
                $this->type_list[] = $_REQUEST['type_'.$i];
            }
        }

        $this->layout_name = isset ($_REQUEST['layout_name']) ? $_REQUEST['layout_name'] : '';
        $this->title_mode = isset ($_REQUEST['title_mode']) ? $_REQUEST['title_mode'] : '';

        $this->title_texts = array();
        $this->title_texts['gen'] = isset ($_REQUEST['title_text_gen']) ? $_REQUEST['title_text_gen'] : '';
        foreach ($camyks->site_conf['editing_languages'] as $l) {
            $this->title_texts[$l] = isset ($_REQUEST['title_text_'.$l]) ? $_REQUEST['title_text_'.$l] : '';
        }

        $this->title_imgs = array();
        $this->title_imgs['gen'] = $this->get_imageFromHeader('gen');
        foreach ($camyks->site_conf['editing_languages'] as $l) {
            $this->title_imgs[$l] = $this->get_imageFromHeader($l);
        }

        $this->descriptions = array();
        foreach ($camyks->site_conf['editing_languages'] as $l) {
            $this->descriptions[$l] = isset ($_REQUEST['description_'.$l]) ? $_REQUEST['description_'.$l] : '';
        }

        $this->type_list = implode (',', $this->type_list);
        $this->title_texts_ = data_encode_properties ($this->title_texts);
        $this->title_imgs_ = data_encode_properties ($this->title_imgs);

        $this->file_allowed = isset($_REQUEST['file_allowed'])?$_REQUEST['file_allowed']:0;
    }

    /**
     * Load image name / file from header
     * @param string $img
     * @return string
     */
    public function get_imageFromHeader($img) {

        /* get value from header */
        if (isset ($_REQUEST['title_img_'.$img]) and ($_REQUEST['title_img_'.$img] != '')) {
            return $_REQUEST['title_img_'.$img];
        }

        /* get file */
        $p = $this->_libParent->plugin_var_path.'/img/';

        if (isset ($_FILES['up_title_img_'.$img])) {
            $n = basename($_FILES['up_title_img_'.$img]['name']);
            if (move_uploaded_file($_FILES['up_title_img_'.$img]['tmp_name'], $p.$n)) {
        return $n;
            }
            return '';
        }
        /* no header and file value */
        return '';
    }

    /**
     * Check object data
     * @return boolean result
     */
    public function check_data() {
        /* Check name */
        if ($this->name == '') {
            $this->name = 'form'.$this->id;
        }
        return true;
    }

    /**
     * Return site title.
     * @return string
     */
    public function get_siteTitle() {
        global $camyks;
        switch ($this->title_mode) {
            case 0:
                return '';
            case 1:
                return isset ($this->title_texts['gen']) ? $this->title_texts['gen'] : '';
            case 2:
                if (isset ($this->title_imgs['gen']) and $this->title_imgs['gen'] != '') {
                    return '<img src="'.$this->_libParent->get_varFileURL('img/'.$this->title_imgs['gen']).'" alt="" border="0"/>';
                } else {
                    return '';
                }
            case 3:
                return isset ($this->title_texts[$camyks->current_language])?$this->title_texts[$camyks->current_language]:'';
            case 4:
                if (isset ($this->title_imgs[$camyks->current_language]) and $this->title_imgs[$camyks->current_language] != '') {
                    return '<img src="'.$this->_libParent->get_varFileURL('img/'.$this->title_imgs[$camyks->current_language]).'" alt="" border="0"/>';
                } else {
                    return '';
                }
        }
        return '';
    }

    /**
     * Return all available items name.
     * @return array
     */
    public function get_namelist() {
        global $camyks;
        $items = array();

        /* Build sql query */
        $sql = 'select id, name';
        $sql .= ' from content_systemsitereportform';

        /* Execute sql query */
        if ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__)) {
            /* Load data from database */
            while ($data = $camyks->db_conn->get_queryDataLine()) {
                $items[$data['id']] = $data['name'];
            }
        }
        return $items;
    }

    /**
     * Update library to version 1.01.
     * @return boolean success
     */
    public function update_toVersion1_01() {
        global $camyks;

        /* Build sql query */
        $sql = 'alter ignore table content_systemsitereportform add column file_allowed tinyint unsigned default 0;';

        /* Execute sql query */
        return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror($this, $sql, __FILE__, __LINE__));
    }
}
?>
