<?php
/**
 * @brief Content_GenericGlossaryViewer module, content library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2010
 * @date Modification: Jan 2020
 * @copyright 2010 - 2020 Ideogram Design
 */

/**
 * Content_GenericGlossaryViewerItem class.
 */
final class Content_GenericGlossaryViewerItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* content items */
        $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('pagemode', 'db', 'int', 'tinyint unsigned', '', 1);
        $this->add_newItem('wordcount', 'db', 'int', 'tinyint unsigned', '', 20);
        $this->add_newItem('categories', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('content', 'db', 'text', 'text', '', '', true);
        $this->add_newItem('gpc_source', 'db', 'int', 'tinyint unsigned', '', 0);

        /* temp items */
        $this->add_newItem('category_cnt', 'temp', 'int', '', '', 0);
        $this->add_newItem('categories_', 'temp', 'array', '', '', array());

        /* generic init */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        global $camyks;
        /* check name */
        $this->_libItems['name']->check_value('symbolic', 'glossary');

        /* check categories */
        $categories = array();
        for ($i=0; $i< $this->_libItems['category_cnt']->value; $i++) {
            if (isset($_REQUEST['category'.$i]))
                $categories[] = $_REQUEST['category'.$i];
        }
        $this->_libItems['categories']->value = implode(',', $categories);

        /* Return result */
        return true;
    }

    /**
     * Load library data from item to a human readable array.
     * @return boolean success
     */
    public function get_fromItems() {
        /* ModuleLibrary generic method */
        if (parent::get_fromItems() === false)
            return false;

        /* decompile categories value */
        if ($this->vars['categories'] == '')
            $this->vars['categories_'] = array();
        else
            $this->vars['categories_'] = explode(',', $this->vars['categories']);

        /* Return success */
        return true;
    }

    /* Specific methods */

    /**
     * Return page mode list.
     * @param boolean $allowPageMode
     * @return array
     */
    public function get_pageModeList($allowPageMode=false) {
        $list = array();
        if ($allowPageMode == true)
            $list[0] = $this->get_translation('configpagemode_bypage');
        $list += array(
            1 => $this->get_translation('configpagemode_byletter'),
            2 => $this->get_translation('configpagemode_bygroup1'),
            3 => $this->get_translation('configpagemode_bygroup2'),
            4 => $this->get_translation('configpagemode_bygroup3')
        );
        return $list;
    }

    /**
     * Return GPC source list.
     * @return array
     */
    public function get_gpcSourceList() {
        global $camyks;
        return array(
            0 => $camyks->get_translation('theme'),
            1 => $this->get_translation('gpc_name'),
        );
    }
}
?>
