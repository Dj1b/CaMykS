<?php
/**
 * @brief Content_GenericPageRedirector Module redirector library.
 * @details Plugin, Module Library
 * @file plugin/module/Content_GenericPageRedirector/lib/Content_GenericPageRedirectorItem.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2009
 * @date Modification: Jan 2019
 * @copyright 2009 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericPageRedirectorItem class.
 */
final class Content_GenericPageRedirectorItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);
        /* content description */
        $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('url', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('delay', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('method', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('layout', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('message', 'text', 'messages', '', '', '', true);

        /* generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        /* check symbolic name value */
        $this->_libItems['name']->check_value('symbolic_name', 'redirector');
        return true;
    }

    /* Specific tool methods */

    /**
     * Return method list.
     * @return array
     */
    public function get_methodList() {
        return array(
            0 => $this->get_translation('method_jsmeta'),
            3 => $this->get_translation('method_header')
        );
    }

    /**
     * Return layout list.
     * @return array
     */
    public function get_layoutList() {
        return array(
            'framed1' => $this->get_translation('layout_framed1'),
            'framed2' => $this->get_translation('layout_framed2'),
            'noframe' => $this->get_translation('layout_noframe'),
        );
    }
}
?>
