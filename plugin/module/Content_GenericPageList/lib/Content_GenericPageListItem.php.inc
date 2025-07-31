<?php
/**
 * @brief Content_GenericPageList module, page list item library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.2
 * @date Creation: Nov 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericPageListItem class.
 */
final class Content_GenericPageListItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes  */
        $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('root', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('title', 'db', 'text', 'varchar', 64, '', true);
        $this->add_newItem('listorder', 'db', 'text', 'varchar', 16, '');

        /* unused, added just in case... */
        $this->add_newItem('maxdisplayed', 'db', 'int', 'int unsigned', '', 0);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        /* Check symbolic name value */
        $this->_libItems['name']->check_value('symbolic_name', 'pagelist');

        /* Return success */
        return true;
    }

    /* Mark: Specific methods */

    /**
     * Return layout list.
     * @return array
     */
    public function get_layoutList() {
        return array(
            'bordered'=>$this->get_translation('layout_bordered'),
            'borderedalt'=>$this->get_translation('layout_borderedalt'),
            'noborder'=>$this->get_translation('layout_noborder'),
        );
    }

    /**
     * Return list order list.
     * @return array
     */
    public function get_listOrderList() {
        return array(
            'normal'    => $this->get_translation('order_normal'),
            'reverse'   => $this->get_translation('order_reverse'),
        );
    }
}
?>
