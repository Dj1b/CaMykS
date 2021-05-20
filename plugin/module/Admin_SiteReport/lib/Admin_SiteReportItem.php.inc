<?php
/*
 * @brief Admin_SiteReport Module, item library.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SiteReportItem class.
 */
final class Admin_SiteReportItem extends ModuleLibrary {
    /**
     * var array $itemlist
     * @brief Request object list.
     */
    protected $updatedItems = array('answer_date', 'answer_admin', 'answer_comment');

    /**
     * Class constructor.
     * @param integer $id
     * @param Module &module
     * @return void
     */
    public function __construct($id, &$module) {
        global $camyks;
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('language', 'db', 'text', 'varchar', 3, $camyks->get_confValue('site_default_language'));
        $this->add_newItem('type', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('creation_date', 'db', 'date', 'bigint', '', time());
        $this->add_newItem('title', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('content', 'db', 'text', 'text', '', '');
        $this->add_newItem('link', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('answer_target', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('answer_date', 'db', 'date', 'bigint', '', 0);
        $this->add_newItem('answer_admin', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('answer_comment', 'db', 'text', 'text', '', '');
        $this->add_newItem('attached_file', 'file', 'attachedfile', '', '', '');

        /* Generic initialiaation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        /* delete answer info if answer date is null */
        if ($this->_libItems['answer_date']->value == 0) {
            $this->_libItems['answer_admin']->value = '';
            $this->_libItems['answer_comment']->value = '';
        } else if ($this->_libItems['answer_date']->value == 1) {
            $this->_libItems['answer_date']->value = time();
        }
        return true;
    }

    /* Specific methods */

    /**
     * Update some items values from object to database.
     * @return boolean success
     */
    public function update_databaseItems() {
        return $this->update_databaseSpecificItems($this->updatedItems);
    }

    /**
     * Load attached file.
     * @return void
     */
    public function load_attachedFile() {
        if (!isset($this->vars['attached_file']) or $this->vars['attached_file'] == '') {
            $this->attachedFile = false;
            return;
        }
        $this->attachedFile = new FSFile($this->vars['attached_file']);
        if ($this->attachedFile->exists === false)
            $this->attachedFile = false;
    }

    /**
     * Delete attached file.
     * @return boolean result
     */
    public function delete_attachedFile() {
        if ($this->id > 0)
            return $this->_libItems['attached_file']->delete($this->id);
        return true;
    }
}
?>
